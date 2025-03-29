#include "aie_control.h"
#include "instruction.h"
#include "test.h"
#include "instruction_onelayer.h"
#include "instruction_fused.h"
#include "instruction_norm.h"
#include "instruction_overlaplayers.h"



int main(int argc, char ** argv)
{
      if(argc==2 || (argc==3 && strcmp(argv[2],"RUN_CODE")==0)) {
      }else{ std::cout<<"Usage: "<<argv[0]<<" <xclbin> [RUN_CODE]"<<std::endl;return 1;}

      char pwd_print_buffer[1024];
      if (getcwd(pwd_print_buffer, sizeof(pwd_print_buffer)) != NULL) {
            std::cout << "Current Directory: " << pwd_print_buffer << std::endl;
      }

      #ifdef SW_EMU_PRINT
      std::string command = "rm -f /home/cw4/github/versal-float32/19-gelu-norm-bias/design/pl_src/output/*";
      int result = std::system(command.c_str());
      std::ofstream outFile("/home/cw4/github/versal-float32/19-gelu-norm-bias/design/pl_src/output/00_out_main.txt");
      outFile<< "test number 1" << std::endl;
      outFile.close();
      #endif

      const char* xclbinFilename = argv[1];
      auto dhdl = xrtDeviceOpen(0);
      auto xclbin = load_xclbin(dhdl, xclbinFilename);
      auto top = reinterpret_cast<const axlf*>(xclbin.data());         
      int ret;
      xrtKernelHandle khdl_hls[1];
      xrtRunHandle rhdl_hls[1];
      
      std::string hls_obj_str; hls_obj_str = "dma_hls:{dma_hls_0}"; 
      const char *hls_obj; hls_obj = hls_obj_str.c_str();
      khdl_hls[0] = xrtPLKernelOpenExclusive(dhdl, top->m_header.uuid, hls_obj);

      xrtBufferHandle lpddr_port;
      xrtBufferHandle ddr_port; 
      xrtBufferHandle instruction_port;
      float* host_lpddr;
      float* host_ddr; 
      uint32_t* host_instruction;

      xrtMemoryGroup bank_grp_id_lpddr_port0 = xrtKernelArgGroupId(khdl_hls[0], 0);
      xrtMemoryGroup bank_grp_id_lpddr_port1 = xrtKernelArgGroupId(khdl_hls[0], 1);
      xrtMemoryGroup bank_grp_id_ddr_port0 = xrtKernelArgGroupId(khdl_hls[0], 2); 
      xrtMemoryGroup bank_grp_id_ddr_port1 = xrtKernelArgGroupId(khdl_hls[0], 3);
      xrtMemoryGroup bank_grp_id_instruction_port = xrtKernelArgGroupId(khdl_hls[0], 4);
      std::cout << "bank_grp_id_lpddr_port0 = " << bank_grp_id_lpddr_port0 << std::endl;
      std::cout << "bank_grp_id_lpddr_port1 = " << bank_grp_id_lpddr_port1 << std::endl;
      std::cout << "bank_grp_id_ddr_port0 = " << bank_grp_id_ddr_port0 << std::endl;
      std::cout << "bank_grp_id_ddr_port1 = " << bank_grp_id_ddr_port1 << std::endl;
      std::cout << "bank_grp_id_instruction_port = " << bank_grp_id_instruction_port << std::endl;

      size_t offsetFP32_weight [8];
      size_t offsetFP32_bias   [8];
      size_t offsetFP32_fmap   [11];

      offsetFP32_weight[0] = 0;
      offsetFP32_weight[1] = offsetFP32_weight[0] + 1024 * 1024;
      offsetFP32_weight[2] = offsetFP32_weight[1] + 1024 * 1024;
      offsetFP32_weight[3] = offsetFP32_weight[2] + 1024 * 1024;
      offsetFP32_weight[4] = offsetFP32_weight[3] + 1024 * 1024;
      offsetFP32_weight[5] = offsetFP32_weight[4] + 1024 ;
      offsetFP32_weight[6] = offsetFP32_weight[5] + 1024 * 4096;
      offsetFP32_weight[7] = offsetFP32_weight[6] + 4096 * 1024;

      offsetFP32_bias[0] = offsetFP32_weight[7] + 1024;
      offsetFP32_bias[1] = offsetFP32_bias[0] + 1024;
      offsetFP32_bias[2] = offsetFP32_bias[1] + 1024;
      offsetFP32_bias[3] = offsetFP32_bias[2] + 1024;
      offsetFP32_bias[4] = offsetFP32_bias[3] + 1024;
      offsetFP32_bias[5] = offsetFP32_bias[4] + 1024;
      offsetFP32_bias[6] = offsetFP32_bias[5] + 4096;
      offsetFP32_bias[7] = offsetFP32_bias[6] + 1024;

      offsetFP32_fmap[0] = 0;
      offsetFP32_fmap[1] = offsetFP32_fmap[0] + 6 * 512 * 1024;
      offsetFP32_fmap[2] = offsetFP32_fmap[1] + 6 * 512 * 1024;
      offsetFP32_fmap[3] = offsetFP32_fmap[2] + 6 * 512 * 1024;
      offsetFP32_fmap[4] = offsetFP32_fmap[3] + 6 * 512 * 1024;
      offsetFP32_fmap[5] = offsetFP32_fmap[4] + 6 * 512 * 1024;
      offsetFP32_fmap[6] = offsetFP32_fmap[5] + 6 * 512 * 1024;
      offsetFP32_fmap[7] = offsetFP32_fmap[6] + 6 * 512 * 1024;
      offsetFP32_fmap[8] = offsetFP32_fmap[7] + 6 * 512 * 4096;
      offsetFP32_fmap[9] = offsetFP32_fmap[8] + 6 * 512 * 4096;
      offsetFP32_fmap[10] = offsetFP32_fmap[9] + 6 * 512 * 1024;

      size_t sizeBytes_lpddr = 4096 * 4096 * 4;
      size_t sizeBytes_ddr = 4 * 4096 * 4096 * 4;
      size_t sizeBytes_instruction = 1024*128 * 4;

      std::cout << "offsetFP32_weight[7] = " << offsetFP32_weight[7] << std::endl;
      std::cout << "offsetFP32_bias[7] = " << offsetFP32_bias[7] << std::endl;
      std::cout << "offsetFP32_fmap[10] = " << offsetFP32_fmap[10] << std::endl;
      std::cout << "sizeBytes_lpddr = " << sizeBytes_lpddr << std::endl;
      std::cout << "sizeBytes_ddr = " << sizeBytes_ddr << std::endl;
      std::cout << "sizeBytes_instruction = " << sizeBytes_instruction << std::endl;

      lpddr_port  = xrtBOAlloc(dhdl, sizeBytes_lpddr, 0, bank_grp_id_lpddr_port0);
      ddr_port  = xrtBOAlloc(dhdl, sizeBytes_ddr , 0, bank_grp_id_ddr_port0);
      instruction_port  = xrtBOAlloc(dhdl, sizeBytes_instruction, 0, bank_grp_id_instruction_port);

      host_lpddr = (float*)xrtBOMap(lpddr_port);
      host_ddr   = (float*)xrtBOMap(ddr_port);
      host_instruction = (uint32_t*)xrtBOMap(instruction_port);

      float* weight0_query  = host_lpddr + offsetFP32_weight[0];
      float* weight1_key    = host_lpddr + offsetFP32_weight[1];
      float* weight2_value  = host_lpddr + offsetFP32_weight[2];
      float* weight3_dense1 = host_lpddr + offsetFP32_weight[3];
      float* weight4_norm1  = host_lpddr + offsetFP32_weight[4];
      float* weight5_dense2 = host_lpddr + offsetFP32_weight[5];
      float* weight6_dense3 = host_lpddr + offsetFP32_weight[6];
      float* weight7_norm2  = host_lpddr + offsetFP32_weight[7];

      float* bias0_query  = host_lpddr + offsetFP32_bias[0];
      float* bias1_key    = host_lpddr + offsetFP32_bias[1];
      float* bias2_value  = host_lpddr + offsetFP32_bias[2];
      float* bias3_dense1 = host_lpddr + offsetFP32_bias[3];
      float* bias4_norm1  = host_lpddr + offsetFP32_bias[4];
      float* bias5_dense2 = host_lpddr + offsetFP32_bias[5];
      float* bias6_dense3 = host_lpddr + offsetFP32_bias[6];
      float* bias7_norm2  = host_lpddr + offsetFP32_bias[7];

      float* fmap0_embedding  = host_ddr + offsetFP32_fmap[0];
      float* fmap1_query      = host_ddr + offsetFP32_fmap[1];
      float* fmap2_key        = host_ddr + offsetFP32_fmap[2];
      float* fmap3_value      = host_ddr + offsetFP32_fmap[3];
      float* fmap4_self_attention = host_ddr + offsetFP32_fmap[4];
      float* fmap5_dense1     = host_ddr + offsetFP32_fmap[5];
      float* fmap6_norm1      = host_ddr + offsetFP32_fmap[6];
      float* fmap7_dense2     = host_ddr + offsetFP32_fmap[7];
      float* fmap8_gelu       = host_ddr + offsetFP32_fmap[8];
      float* fmap9_dense3     = host_ddr + offsetFP32_fmap[9];
      float* fmap10_norm2     = host_ddr + offsetFP32_fmap[10];

      

      std::string python_gold_file;
      #ifdef SW_EMU_PRINT
      python_gold_file = "/home/cw4/github/versal-float32/19-gelu-norm-bias/workspace/app_component/host_app_src/python_gold/";
      #else
      python_gold_file = "/home/root/python_gold/";
      #endif

      std::cout<<"layer query"<<std::endl;
      
      float* load_gold_query = (float*)malloc(6 * 512 * 1024 * 4);
      #ifdef ENABLE_TEST_Q 
      load_data(python_gold_file + "0-attention.self.query-input.txt" , fmap0_embedding, 512*1024);
      load_data(python_gold_file + "0-attention.self.query-weight.txt", weight0_query, 1024*1024);
      load_data(python_gold_file + "0-attention.self.query-bias.txt"  , bias0_query, 1024);
      load_data(python_gold_file + "0-attention.self.query-output.txt", load_gold_query , 512*1024);
      replicate_matrix (fmap0_embedding, 512, 1024, 6);
      replicate_matrix (load_gold_query, 512, 1024, 6);
      #endif
      // calculate_matrix (fmap0_embedding, weight0_query, fmap1_query, 6 * 512, 1024, 1024);
      // add_matrix_with_bias(fmap1_query, bias0_query, 6 * 512, 1024);
      // print_matrix_to_file("/home/cw4/github/versal-float32/19-gelu-norm-bias/design/pl_src/output/01_0-attention.self.query-output.txt", fmap1_query, 512, 1024);
      // valid(fmap1_query, gold_query, 6*512*1024);

      ParamsOneLayer params_query;
      // params_query.set_iter(2, 1, 1);
      params_query.set_iter(2, 1, 8);
      params_query.enable_bias = true;
      params_query.enable_gelu = false;
      params_query.enable_norm = false;
      params_query.enable_addmul_pre_layer = false;
      params_query.lpddr_offset_512b_weight = offsetFP32_weight[0]/16;
      params_query.lpddr_offset_512b_bias   = offsetFP32_bias[0]/16;
      params_query.ddr_offset_512b_input    = offsetFP32_fmap[0]/16;
      params_query.ddr_offset_512b_output   = offsetFP32_fmap[1]/16;
      convert_input_weight_gold_to_2AXI(fmap0_embedding, weight0_query, load_gold_query, params_query);

      std::cout<<"layer gold"<<std::endl;

      float* load_gold_key = (float*)malloc(6 * 512 * 1024 * 4);
      #ifdef ENABLE_TEST_K
      load_data(python_gold_file + "1-attention.self.key-weight.txt", weight1_key, 1024*1024);
      load_data(python_gold_file + "1-attention.self.key-bias.txt"  , bias1_key, 1024);
      load_data(python_gold_file + "1-attention.self.key-output.txt", load_gold_key , 512*1024);
      replicate_matrix (load_gold_key, 512, 1024, 6);
      matrix_scale (load_gold_key, 1.0/8, 6 * 512, 1024);
      matrix_scale (weight1_key, 1.0/8, 1024, 1024);
      matrix_scale (bias1_key, 1.0/8, 1, 1024);
      #endif
      ParamsOneLayer params_key;
      params_key.set_iter(2, 1, 8);
      params_key.enable_bias = true;
      params_key.lpddr_offset_512b_weight = offsetFP32_weight[1]/16;
      params_key.lpddr_offset_512b_bias   = offsetFP32_bias[1]/16;
      params_key.ddr_offset_512b_input    = offsetFP32_fmap[0]/16;
      params_key.ddr_offset_512b_output   = offsetFP32_fmap[2]/16;
      convert_weight_gold_to_2AXI(weight1_key, load_gold_key, params_key);

      std::cout<<"layer value"<<std::endl;

      float* load_gold_value = (float*)malloc(6 * 512 * 1024 * 4);
      #ifdef ENABLE_TEST_V
      load_data(python_gold_file + "2-attention.self.value-weight.txt", weight2_value, 1024*1024);
      load_data(python_gold_file + "2-attention.self.value-bias.txt"  , bias2_value, 1024);
      load_data(python_gold_file + "2-attention.self.value-output.txt", load_gold_value , 512*1024);
      replicate_matrix (load_gold_value, 512, 1024, 6);
      #endif
      ParamsOneLayer params_value;
      params_value.set_iter(2, 1, 8);
      params_value.enable_bias = true;
      params_value.lpddr_offset_512b_weight = offsetFP32_weight[2]/16;
      params_value.lpddr_offset_512b_bias   = offsetFP32_bias[2]/16;
      params_value.ddr_offset_512b_input    = offsetFP32_fmap[0]/16;
      params_value.ddr_offset_512b_output   = offsetFP32_fmap[3]/16;
      convert_weight_gold_to_2AXI(weight2_value, load_gold_value, params_value);

      std::cout<<"layer attention"<<std::endl;

      float* load_gold_attention = (float*)malloc(6 * 512 * 1024 * 4);
      #ifdef ENABLE_TEST_ATTENTION
      load_data(python_gold_file + "3-attention.output.dense-input.txt", load_gold_attention, 512*1024); 
      replicate_matrix (load_gold_attention, 512, 1024, 6);
      convert_simple_to_blocked_layout(load_gold_attention, 6 * 512, 1024, 128, 64);
      convert_blocked_to_2AXI_layout(load_gold_attention, 6 * 512, 1024);
      #endif
      ParamsFusedLayer params_attention;
      params_attention.ddr_offset_512b_inA_L1 = offsetFP32_fmap[1]/16;
      params_attention.ddr_offset_512b_inB_L1 = offsetFP32_fmap[2]/16;
      params_attention.ddr_offset_512b_inB_L2 = offsetFP32_fmap[3]/16;
      params_attention.ddr_offset_512b_outC_L2 = offsetFP32_fmap[4]/16;
      params_attention.num_layer = 96 / 2;


      std::cout<<"layer fused_dense1_norm1"<<std::endl;

      // load_data(python_gold_file + "3-attention.output.dense-input.txt", fmap4_self_attention, 512*1024); 
      // replicate_matrix (fmap4_self_attention, 512, 1024, 6);
      // convert_simple_to_blocked_layout(fmap4_self_attention, 6 * 512, 1024, 128, 64);
      // convert_blocked_to_2AXI_layout(fmap4_self_attention, 6 * 512, 1024);

      // load_data(python_gold_file + "0-attention.self.query-input.txt" , fmap0_embedding, 512*1024);
      // replicate_matrix (fmap0_embedding, 512, 1024, 6);
      // convert_simple_to_blocked_layout(fmap0_embedding, 6 * 512, 1024, 128, 64);
      // convert_blocked_to_2AXI_layout(fmap0_embedding, 6 * 512, 1024);


      // dense1 and norm1 are fused together
      float* load_gold_fuseddense1norm1 = (float*)malloc(6 * 512 * 1024 * 4);
      #ifdef ENABLE_TEST_NORM1
      load_data(python_gold_file + "3-attention.output.dense-bias.txt", bias3_dense1, 1024);
      load_data(python_gold_file + "3-attention.output.dense-weight.txt", weight3_dense1, 1024*1024);
      load_data(python_gold_file + "4-fused_dense1_norm1_output.txt", load_gold_fuseddense1norm1, 512*1024);
      replicate_matrix (load_gold_fuseddense1norm1, 512, 1024, 6);
      // previous norm's weight      
      init_matrix (weight4_norm1, 1, 1024, 1.0); 
      #endif
      ParamsOneLayer params_norm1;
      // params_norm1.set_iter(2, 1, 1);
      params_norm1.set_iter(2, 1, 8);
      params_norm1.enable_bias = true;
      params_norm1.enable_norm = true;
      params_norm1.enable_addmul_pre_layer = true;
      params_norm1.lpddr_offset_512b_weight = offsetFP32_weight[3]/16;
      params_norm1.lpddr_offset_512b_bias   = offsetFP32_bias[3]/16;
      params_norm1.ddr_offset_512b_input    = offsetFP32_fmap[4]/16;
      params_norm1.ddr_offset_512b_output   = offsetFP32_fmap[6]/16;
      params_norm1.lpddr_offset_512b_pre_layer_weight = offsetFP32_weight[4]/16;
      params_norm1.ddr_offset_512b_pre_layer = offsetFP32_fmap[0]/16;
      convert_weight_gold_to_2AXI(weight3_dense1, load_gold_fuseddense1norm1, params_norm1);
      

      std::cout<<"layer fused_norm1_dense2_gelu"<<std::endl;

      // load_data(python_gold_file + "4-fused_dense1_norm1_output.txt", fmap6_norm1, 512*1024);
      // replicate_matrix (fmap6_norm1, 512, 1024, 6);

      float* load_gold_norm1dense2gelu = (float*)malloc(6 * 512 * 4096 * 4);
      #ifdef ENABLE_TEST_GELU
      load_data(python_gold_file + "5-fused_norm1_dense2_weight.txt", weight5_dense2, 1024*4096);
      load_data(python_gold_file + "5-fused_norm1_dense2_bias.txt"  , bias5_dense2, 4096);
      load_data(python_gold_file + "6-output.dense-input.txt", load_gold_norm1dense2gelu , 512*4096);
      replicate_matrix (load_gold_norm1dense2gelu, 512, 4096, 6);
      #endif
      ParamsOneLayer params_dense2;
      params_dense2.set_iter(2, 4, 8);
      params_dense2.enable_bias = true;
      params_dense2.enable_gelu = true;
      params_dense2.lpddr_offset_512b_weight = offsetFP32_weight[5]/16;
      params_dense2.lpddr_offset_512b_bias   = offsetFP32_bias[5]/16;
      params_dense2.ddr_offset_512b_input    = offsetFP32_fmap[6]/16; // fmap6_norm1
      params_dense2.ddr_offset_512b_output   = offsetFP32_fmap[7]/16; // fmap7_dense2
      convert_input_weight_gold_to_2AXI(fmap6_norm1, weight5_dense2, load_gold_norm1dense2gelu, params_dense2);
      reorderArray_4096(bias5_dense2);

      std::cout<<"layer fused_dense3_norm2"<<std::endl;

      // dense1 and norm1 are fused together
      float* load_gold_fuseddense3norm2 = (float*)malloc(6 * 512 * 1024 * 4);
      float* norm1_bias = (float*)malloc(1024 * 4);
      #ifdef ENABLE_TEST_NORM2
      load_data(python_gold_file + "6-output.dense-bias.txt", bias6_dense3, 1024);
      load_data(python_gold_file + "4-attention.output.LayerNorm-bias.txt", norm1_bias, 1024);
      matrix_add(bias6_dense3, norm1_bias, 1, 1024);
      load_data(python_gold_file + "6-output.dense-weight.txt", weight6_dense3, 4096*1024);
      load_data(python_gold_file + "7-fused_dense3_norm2.txt", load_gold_fuseddense3norm2, 512*1024);
      replicate_matrix (load_gold_fuseddense3norm2, 512, 1024, 6);
      // previous norm's weight  
      load_data(python_gold_file + "4-attention.output.LayerNorm-weight.txt", weight7_norm2, 1024);
      #endif
      ParamsOneLayer params_norm2;
      params_norm2.set_iter(2, 1, 32);
      params_norm2.enable_bias = true;
      params_norm2.enable_norm = true;
      params_norm2.enable_addmul_pre_layer = true;
      params_norm2.lpddr_offset_512b_weight = offsetFP32_weight[6]/16; // weight6_dense3
      params_norm2.lpddr_offset_512b_bias   = offsetFP32_bias[6]/16;   // bias6_dense3
      params_norm2.ddr_offset_512b_input    = offsetFP32_fmap[7]/16;   // fmap7_dense2
      params_norm2.ddr_offset_512b_output   = offsetFP32_fmap[10]/16;  // fmap10_norm2
      params_norm2.lpddr_offset_512b_pre_layer_weight = offsetFP32_weight[7]/16; // weight7_norm2
      params_norm2.ddr_offset_512b_pre_layer = offsetFP32_fmap[6]/16;  // fmap6_norm1
      convert_weight_gold_to_2AXI(weight6_dense3, load_gold_fuseddense3norm2, params_norm2);
      



      // generate_data_onelayer_with_bias(fmap6_norm1, weight5_dense2, bias5_dense2, fmap7_dense2, load_gold_norm1dense2gelu, params_dense2);
      // generate_data_onelayer_with_bias(fmap0_embedding, weight0_query, bias0_query, fmap1_query, load_gold_query, params_query);
      // generate_data_fusedlayer(fmap1_query, fmap2_key, fmap3_value, fmap4_self_attention, load_gold_attention, params_attention);
      // generate_data_onelayer_norm(
      //       fmap4_self_attention , fmap0_embedding,
      //       weight4_norm1 ,
      //       weight3_dense1 , bias3_dense1  , 
      //       fmap6_norm1    , load_gold_fuseddense1norm1 , 
      //       params_norm1
      // );

      uint32_t count4B      = 0;
      uint32_t countInstPkt = 0;

      // generate_instruction_onelayer_overlap_128_512_A4B1K8(host_instruction + 2, count4B, countInstPkt, params_query);
      // generate_instruction_onelayer(host_instruction + 2, count4B, countInstPkt, params_dense2);
      // generate_instruction_onelayer_overlap_128_512_A4B4K8(host_instruction + 2, count4B, countInstPkt, params_dense2);
      // generate_instruction_fusedlayer_numlayer1(host_instruction + 2 , count4B, countInstPkt, params_attention);
      // generate_instruction_onelayer_norm_overlap_A4B1K8(host_instruction + 2, count4B, countInstPkt, params_norm1);
      // generate_instruction_onelayer_overlap_128_512_A4B1K8(host_instruction + 2, count4B, countInstPkt, params_query);


      // #ifdef ENABLE_TEST_Q
      // // generate_instruction_onelayer(host_instruction + 2, count4B, countInstPkt, params_query);
      // generate_instruction_onelayer_overlap_128_512_A4B1K8(host_instruction + 2, count4B, countInstPkt, params_query);
      // #endif
      // #ifdef ENABLE_TEST_K
      // // generate_instruction_onelayer(host_instruction + 2, count4B, countInstPkt, params_key);
      // generate_instruction_onelayer_overlap_128_512_A4B1K8(host_instruction + 2, count4B, countInstPkt, params_key);
      // #endif
      // #ifdef ENABLE_TEST_V
      // // generate_instruction_onelayer(host_instruction + 2, count4B, countInstPkt, params_value);
      // generate_instruction_onelayer_overlap_128_512_A4B1K8(host_instruction + 2, count4B, countInstPkt, params_value);
      // #endif
      // #ifdef ENABLE_TEST_ATTENTION 
      // generate_instruction_fusedlayer(host_instruction + 2 , count4B, countInstPkt, params_attention);
      // #endif
      // #ifdef ENABLE_TEST_NORM1
      // // generate_instruction_onelayer_norm(host_instruction + 2, count4B, countInstPkt, params_norm1);
      // generate_instruction_onelayer_norm_overlap_A4B1K8(host_instruction + 2, count4B, countInstPkt, params_norm1);
      // #endif
      // #ifdef ENABLE_TEST_GELU
      // // generate_instruction_onelayer(host_instruction + 2, count4B, countInstPkt, params_dense2);
      // generate_instruction_onelayer_first2load_A4B4K8(host_instruction + 2, count4B, countInstPkt, params_dense2);
      // #endif
      // #ifdef ENABLE_TEST_NORM2
      // // generate_instruction_onelayer_norm(host_instruction + 2, count4B, countInstPkt, params_norm2);
      // generate_instruction_onelayer_norm_overlap_A4B1K32(host_instruction + 2, count4B, countInstPkt, params_norm2);
      // #endif

      #if defined(ENABLE_TEST_Q) && defined(ENABLE_TEST_K) && defined(ENABLE_TEST_V)
      generate_instruction_query_key_value(host_instruction + 2, count4B, countInstPkt, params_query, params_key, params_value);
      #endif
      #ifdef ENABLE_TEST_ATTENTION 
      generate_instruction_fusedlayer(host_instruction + 2 , count4B, countInstPkt, params_attention);
      #endif
      #if defined(ENABLE_TEST_NORM1) && defined(ENABLE_TEST_GELU) && defined(ENABLE_TEST_NORM2)
      generate_instruction_norm1_gelu_norm2(host_instruction + 2, count4B, countInstPkt, params_norm1, params_dense2, params_norm2);
      #endif


      generate_last_inst_for_all_modules(host_instruction + 2, count4B, countInstPkt);
      host_instruction[0] = count4B ;
      host_instruction[1] = countInstPkt;
      std::cout<< "count4B = " << count4B << std::endl;
      std::cout<< "countInstPkt = " << countInstPkt << std::endl;

      xrtBOSync(lpddr_port, XCL_BO_SYNC_BO_TO_DEVICE, sizeBytes_lpddr, 0);
      xrtBOSync(ddr_port, XCL_BO_SYNC_BO_TO_DEVICE, sizeBytes_ddr, 0);
      xrtBOSync(instruction_port, XCL_BO_SYNC_BO_TO_DEVICE, sizeBytes_instruction, 0);

      std::cout<<"Set Args" << std::endl;
      rhdl_hls[0] = xrtRunOpen(khdl_hls[0]);
      xrtRunSetArg(rhdl_hls[0], 0, lpddr_port);
      xrtRunSetArg(rhdl_hls[0], 1, lpddr_port); 
      xrtRunSetArg(rhdl_hls[0], 2, ddr_port); 
      xrtRunSetArg(rhdl_hls[0], 3, ddr_port);
      xrtRunSetArg(rhdl_hls[0], 4, instruction_port);

      std::string gemm_aie_obj_str = "G";
      const char *gemm_aie_obj = gemm_aie_obj_str.c_str();
      xrtGraphHandle gemm_aie_gr = xrtGraphOpen(dhdl, top->m_header.uuid, gemm_aie_obj);
      if (!gemm_aie_gr) {throw std::runtime_error("Unable to open GEMM g graph handle");}else{ printf("GEMM graph g Initialised...\n");}

      xrtGraphReset(gemm_aie_gr);
      ret = xrtGraphRun(gemm_aie_gr, 1);
      if (ret) {throw std::runtime_error("Unable to run GEMM g graph");}else{ printf("GEMM graph g running...\n");}

      generate_aie_rtp_opcode_mem(gemm_aie_gr);      

      std::cout<<"Run hls kernels" << std::endl;
      xrtRunStart(rhdl_hls[0]);
      Timer timer;      
      xrtRunWait(rhdl_hls[0]);
      // sleep(1);
      double timer_stop=timer.stop();

      // xrtGraphEnd(gemm_aie_gr, 0); // if use xrtGraphEnd(gemm_aie_gr, 16) or xrtGraphWait the sw emu report undefined warming
      xrtBOSync(ddr_port, XCL_BO_SYNC_BO_FROM_DEVICE, sizeBytes_ddr, 0);

      std::cout<<"Duration ="<<timer_stop<<" us"<<std::endl;
      // double throughput = params_query.calThroughput(timer_stop);
      // std::cout<<"Throughput = "<<throughput<<" GOPS/s"<<std::endl;

      #ifdef SW_EMU_PRINT
      std::string file_name = "/home/cw4/github/versal-float32/19-gelu-norm-bias/design/pl_src/output/03_";
      print_matrix_to_file( file_name + "fmap1_query_2AXI.txt", fmap1_query, params_query.getMatrixDim_A(), params_query.getMatrixDim_B());
      #endif



      #ifdef ENABLE_TEST_Q
      std::cout<<"Compare query"<<std::endl;
      valid(fmap1_query, load_gold_query, 3 * 512 * 1024 );
      #endif

      #ifdef ENABLE_TEST_K
      std::cout<<"Compare key"<<std::endl;
      valid(fmap2_key, load_gold_key, 3 * 512 * 1024);
      #endif

      #ifdef ENABLE_TEST_V
      std::cout<<"Compare value"<<std::endl;
      valid(fmap3_value, load_gold_value, 3 * 512 * 1024);
      #endif

      #ifdef ENABLE_TEST_ATTENTION
      std::cout<<"Compare attention"<<std::endl;
      valid(fmap4_self_attention, load_gold_attention, params_attention.num_layer * 512 * 64);
      #endif

      #ifdef ENABLE_TEST_NORM1
      std::cout<<"Compare fused dense1 norm1"<<std::endl;
      valid(fmap6_norm1, load_gold_fuseddense1norm1, 3 * 512 * 1024);
      #endif

      #ifdef ENABLE_TEST_GELU
      std::cout<<"Compare fused norm1 dense2 gelu"<<std::endl;
      valid(fmap7_dense2, load_gold_norm1dense2gelu, 3 * 512 * 4096);
      #endif

      #ifdef ENABLE_TEST_NORM2
      std::cout<<"Compare fused dense3 norm2"<<std::endl;
      valid(fmap10_norm2, load_gold_fuseddense3norm2, 3 * 512 * 1024);
      #endif

      std::cout<<"PASSED!"<<std::endl;


      std::cout<<"Close HLS"<<std::endl;
      xrtRunClose(rhdl_hls[0]);
      xrtKernelClose(khdl_hls[0]);
      xrtBOFree(lpddr_port);
      xrtBOFree(ddr_port);
      xrtBOFree(instruction_port);
      std::cout<<"GEMM Graph close()"<<std::endl;
      xrtGraphClose(gemm_aie_gr);
      std::cout<<"Close Device"<<std::endl;
      xrtDeviceClose(dhdl);

      // free(gold_query);

      return 0; 
      
}

