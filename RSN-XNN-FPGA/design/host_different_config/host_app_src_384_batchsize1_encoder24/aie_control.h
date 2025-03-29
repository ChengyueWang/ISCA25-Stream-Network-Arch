#pragma once

#include "comm.h"


void write_opcode_mem (uint32_t* array, int core_id, int dima_id, int dimb_id, int casc_id, int offset, uint32_t value ){
   array[core_id * 4 * 4 * 4 * 512 + dima_id * 4 * 4 * 512 + dimb_id * 4 * 512 + casc_id * 512 + offset] = value;
}


uint32_t read_opcode_mem (uint32_t* array, int core_id, int dima_id, int dimb_id, int casc_id, int offset ){
   return array[core_id * 4 * 4 * 4 * 512 + dima_id * 4 * 4 * 512 + dimb_id * 4 * 512 + casc_id * 512 + offset];
}


void print_opcode_mem_array (uint32_t* array){
   #ifdef SW_EMU_PRINT
   std::ofstream outFile("/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/01_opcode_mem_array.txt", std::ios_base::app); 
   if (!outFile.is_open()){ std::cerr << "Unable to open file for writing." << std::endl;}
   
   for (int core_id = 0; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               outFile << "core_id = " << core_id << " dima_id = " << dima_id << " dimb_id = " << dimb_id << " csc = " << csc << std::endl;
               uint32_t print_code = read_opcode_mem(array, core_id, dima_id, dimb_id, csc, 0);
               outFile << "print_code = " << print_code << std::endl;
               uint32_t opcode_len = read_opcode_mem(array, core_id, dima_id, dimb_id, csc, 1);
               outFile << "opcode_len = " << opcode_len << std::endl;
               for (int i=2; i<16; i++){
                  uint32_t opcode = read_opcode_mem(array, core_id, dima_id, dimb_id, csc, i);
                  int a_iter = opcode & 0x0000000F;
                  int b_iter = (opcode & 0x000000F0) >> 4;
                  int k_iter = (opcode & 0x00007F00) >> 8;
                  int compute_tile_access_A = (opcode & 0x00018000) >> 15;
                  int compute_tile_access_B = (opcode & 0x000E0000) >> 17;
                  bool enable_load_pre_norm_weight = (opcode & 0x00100000) >> 20;
                  bool enable_bias = (opcode & 0x00200000) >> 21;
                  bool dimb_is_32  = (opcode & 0x00400000) >> 22; 
                  bool dimk_is_32  = (opcode & 0x00800000) >> 23;
                  bool enable_accum_kiter = (opcode & 0x01000000) >> 24;
                  bool enable_muladd_pre_layer = (opcode & 0x02000000) >> 25;
                  bool need_muladd_pre_layer_in_cur_aie = (opcode & 0x04000000) >> 26;
                  outFile << "a_iter = " << a_iter << " b_iter = " << b_iter << " k_iter = " << k_iter;
                  outFile << " compute_tile_access_A = " << compute_tile_access_A << " compute_tile_access_B = " << compute_tile_access_B;
                  outFile << " enable_load_pre_norm_weight = " << enable_load_pre_norm_weight << " enable_bias = " << enable_bias;
                  outFile << " dimb_is_32 = " << dimb_is_32 << " dimk_is_32 = " << dimk_is_32;
                  outFile << " enable_accum_kiter = " << enable_accum_kiter << " enable_muladd_pre_layer = " << enable_muladd_pre_layer;
                  outFile << " need_muladd_pre_layer_in_cur_aie = " << need_muladd_pre_layer_in_cur_aie << std::endl;
               }
            }
         }
      }
   }
   outFile.close();
   #endif
}



void generate_aie_rtp_opcode_mem_384 ( xrtGraphHandle gemm_aie_gr) {

   std::cout<<"generate_aie_rtp_opcode_mem_384" << std::endl;

   uint32_t* opcode_mem = (uint32_t*)malloc(6 * 4 * 4 * 4 * 512 * 4);
   uint32_t opcode_id;

   for (int i = 0; i < 6 * 4 * 4 * 4 * 512 ; i++){
      opcode_mem[i] = 0;
   }
   
   uint32_t a_iter;
   uint32_t b_iter;
   uint32_t k_iter;
   uint32_t compute_tile_access_A;
   uint32_t compute_tile_access_B;
   uint32_t enable_load_pre_norm_weight;
   uint32_t enable_bias;
   uint32_t dimb_is_32;
   uint32_t dimk_is_32;
   uint32_t enable_accum_kiter;
   uint32_t enable_muladd_pre_layer;
   uint32_t need_muladd_pre_layer_in_cur_aie;
   uint32_t opcode;

   // index 0: print_code => 0: no print, 1>=: print
   // index 1: the number of opcodes
   for (int core_id = 0; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 0, 0);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, 0);
            }
         }
      }
   }



for (int en = 0; en < NUM_ENCODER; en++){


   std::cout<<"Query Key Value " << std::endl;

   a_iter = 1;
   b_iter = 1;
   k_iter = 8;
   compute_tile_access_A = 1;
   compute_tile_access_B = 4;
   enable_load_pre_norm_weight = 0;
   enable_bias = 1;
   dimb_is_32 = 1;
   dimk_is_32 = 1;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;

   for (int core_id = 0; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_Q
                  opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
                  write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
                  write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif

               #ifdef ENABLE_TEST_K
                  opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
                  write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
                  write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif

               #ifdef ENABLE_TEST_V
                  opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
                  write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
                  write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }

   std::cout<<"Self Attention " << std::endl;

   int fused_numlayer_a_iter = 2;
   int fused_numlayer_b_iter = 4;


   a_iter = fused_numlayer_a_iter; // @@ no larger than 31
   b_iter = fused_numlayer_b_iter;
   k_iter = 1;
   compute_tile_access_A = 1;
   compute_tile_access_B = 1;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 1;
   dimk_is_32 = 0;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 0; core_id < 1; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }
   

   a_iter = fused_numlayer_a_iter; // @@ no larger than 31
   b_iter = fused_numlayer_b_iter;
   k_iter = 1;
   compute_tile_access_A = 1;
   compute_tile_access_B = 2;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 1;
   dimk_is_32 = 0;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 1; core_id < 2; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }


   a_iter = fused_numlayer_a_iter; // @@ no larger than 31
   b_iter = fused_numlayer_b_iter;
   k_iter = 1;
   compute_tile_access_A = 2;
   compute_tile_access_B = 1;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 1;
   dimk_is_32 = 0;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 2; core_id < 3; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }


   a_iter = fused_numlayer_a_iter; // @@ no larger than 31
   b_iter = fused_numlayer_b_iter;
   k_iter = 1;
   compute_tile_access_A = 2;
   compute_tile_access_B = 2;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 1;
   dimk_is_32 = 0;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 3; core_id < 4; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }



   // a_iter = 12; 
   // b_iter = 8;
   // k_iter = 4;
   a_iter = fused_numlayer_a_iter; 
   b_iter = fused_numlayer_b_iter;
   k_iter = 3;
   compute_tile_access_A = 1;
   compute_tile_access_B = 1;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 0;
   dimk_is_32 = 1;
   enable_accum_kiter = 1;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 4; core_id < 5; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }

   a_iter = fused_numlayer_a_iter; 
   b_iter = fused_numlayer_b_iter;
   k_iter = 3;
   compute_tile_access_A = 2;
   compute_tile_access_B = 1;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 0;
   dimk_is_32 = 1;
   enable_accum_kiter = 1;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 5; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }

////// ===================================================== 64 ======= 


   a_iter = fused_numlayer_a_iter; // @@ no larger than 31
   b_iter = fused_numlayer_b_iter;
   k_iter = 1;
   compute_tile_access_A = 1;
   compute_tile_access_B = 1;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 1;
   dimk_is_32 = 0;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 0; core_id < 1; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }
   

   a_iter = fused_numlayer_a_iter; // @@ no larger than 31
   b_iter = fused_numlayer_b_iter;
   k_iter = 1;
   compute_tile_access_A = 1;
   compute_tile_access_B = 2;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 1;
   dimk_is_32 = 0;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 1; core_id < 2; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }


   a_iter = fused_numlayer_a_iter; // @@ no larger than 31
   b_iter = fused_numlayer_b_iter;
   k_iter = 1;
   compute_tile_access_A = 2;
   compute_tile_access_B = 1;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 1;
   dimk_is_32 = 0;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 2; core_id < 3; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }


   a_iter = fused_numlayer_a_iter; // @@ no larger than 31
   b_iter = fused_numlayer_b_iter;
   k_iter = 1;
   compute_tile_access_A = 2;
   compute_tile_access_B = 2;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 1;
   dimk_is_32 = 0;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 3; core_id < 4; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }



   // a_iter = 12; 
   // b_iter = 8;
   // k_iter = 4;
   a_iter = fused_numlayer_a_iter; 
   b_iter = fused_numlayer_b_iter;
   k_iter = 3;
   compute_tile_access_A = 1;
   compute_tile_access_B = 1;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 0;
   dimk_is_32 = 1;
   enable_accum_kiter = 1;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 4; core_id < 5; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }

   a_iter = fused_numlayer_a_iter; 
   b_iter = fused_numlayer_b_iter;
   k_iter = 3;
   compute_tile_access_A = 2;
   compute_tile_access_B = 1;
   enable_load_pre_norm_weight = 0;
   enable_bias = 0;
   dimb_is_32 = 0;
   dimk_is_32 = 1;
   enable_accum_kiter = 1;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;


   for (int core_id = 5; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_ATTENTION
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }






   std::cout<<"Normalization 1 " << std::endl;

   a_iter = 1;
   b_iter = 1;
   k_iter = 8;
   // a_iter = 1;
   // b_iter = 1;
   // k_iter = 1;
   compute_tile_access_A = 1;
   compute_tile_access_B = 4;
   enable_load_pre_norm_weight = 1;
   enable_bias = 1;
   dimb_is_32 = 1;
   dimk_is_32 = 1;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 1;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;
   
   for (int core_id = 0; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_NORM1
               uint32_t opcode_id; 
               need_muladd_pre_layer_in_cur_aie =  (csc == dimb_id)? 1 : 0;
               opcode = (opcode & ~ 0x04000000 ) | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }

   std::cout<<"GELU 1 " << std::endl;
   a_iter = 1;
   b_iter = 4;
   k_iter = 8;
   compute_tile_access_A = 1;
   compute_tile_access_B = 4;
   enable_load_pre_norm_weight = 0;
   enable_bias = 1;
   dimb_is_32 = 1;
   dimk_is_32 = 1;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 0;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;

   for (int core_id = 0; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_GELU
                  opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
                  write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
                  write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }

   std::cout<<"Normalization 2 " << std::endl;

   a_iter = 1;
   b_iter = 1;
   k_iter = 32;
   compute_tile_access_A = 1;
   compute_tile_access_B = 4;
   enable_load_pre_norm_weight = 1;
   enable_bias = 1;
   dimb_is_32 = 1;
   dimk_is_32 = 1;
   enable_accum_kiter = 0;
   enable_muladd_pre_layer = 1;
   need_muladd_pre_layer_in_cur_aie = 0;

   opcode = 0x00000000 ;
   opcode = opcode | (0x0000000F & a_iter) ;
   opcode = opcode | (0x000000F0 & (b_iter << 4)) ;
   opcode = opcode | (0x00007F00 & (k_iter << 8)) ; // 7 bits for k_iter
   opcode = opcode | (0x00018000 & (compute_tile_access_A << 15)) ; // 2 bits for compute_tile_access_A
   opcode = opcode | (0x000E0000 & (compute_tile_access_B << 17)) ; // 3 bits for compute_tile_access_B
   opcode = opcode | (0x00100000 & (enable_load_pre_norm_weight      << 20)) ;
   opcode = opcode | (0x00200000 & (enable_bias           << 21)) ;
   opcode = opcode | (0x00400000 & (dimb_is_32            << 22)) ;
   opcode = opcode | (0x00800000 & (dimk_is_32            << 23)) ;
   opcode = opcode | (0x01000000 & (enable_accum_kiter    << 24)) ;
   opcode = opcode | (0x02000000 & (enable_muladd_pre_layer    << 25)) ;
   opcode = opcode | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;
   
   for (int core_id = 0; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               #ifdef ENABLE_TEST_NORM2
               uint32_t opcode_id; 
               need_muladd_pre_layer_in_cur_aie =  (csc == dimb_id)? 1 : 0;
               opcode = (opcode & ~ 0x04000000 ) | (0x04000000 & (need_muladd_pre_layer_in_cur_aie << 26)) ;
               opcode_id = read_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, opcode_id + 2, opcode);
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 1, opcode_id + 1);
               #endif
            }
         }
      }
   }


}



   std::cout<<"Print " << std::endl;

   for (int core_id = 0; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            for (int csc = 0; csc < 4; csc++){
               int print_code = (dima_id == 0 && dimb_id == 0)? core_id + 1 : 0;
               write_opcode_mem(opcode_mem, core_id, dima_id, dimb_id, csc, 0, print_code);
            }
         }
      }
   }

   print_opcode_mem_array(opcode_mem);

   
   for (int core_id = 0; core_id < 6; core_id++){
      for (int dima_id = 0; dima_id < 4; dima_id++){
         for (int dimb_id = 0; dimb_id < 4; dimb_id++){
            std::string rtp_opcode; 
            const char *rtp_opcode_obj;  

            const char *opcode_ptr0 = reinterpret_cast<const char *>(opcode_mem + core_id * 4 * 4 * 4 * 512 + dima_id * 4 * 4 * 512 + dimb_id * 4 * 512 + 0 * 512);
            rtp_opcode = "G.FG["+to_string(core_id)+"]["+to_string(dima_id)+"]["+to_string(dimb_id)+"].k0.in[2]";
            rtp_opcode_obj = rtp_opcode.c_str();
            xrtGraphUpdateRTP(gemm_aie_gr, rtp_opcode_obj, opcode_ptr0,  512 * sizeof (uint32_t));

            const char *opcode_ptr1 = reinterpret_cast<const char *>(opcode_mem + core_id * 4 * 4 * 4 * 512 + dima_id * 4 * 4 * 512 + dimb_id * 4 * 512 + 1 * 512);
            rtp_opcode = "G.FG["+to_string(core_id)+"]["+to_string(dima_id)+"]["+to_string(dimb_id)+"].k1.in[3]";
            rtp_opcode_obj = rtp_opcode.c_str();
            xrtGraphUpdateRTP(gemm_aie_gr, rtp_opcode_obj, opcode_ptr1,  512 * sizeof (uint32_t));

            const char *opcode_ptr2 = reinterpret_cast<const char *>(opcode_mem + core_id * 4 * 4 * 4 * 512 + dima_id * 4 * 4 * 512 + dimb_id * 4 * 512 + 2 * 512);
            rtp_opcode = "G.FG["+to_string(core_id)+"]["+to_string(dima_id)+"]["+to_string(dimb_id)+"].k2.in[3]";
            rtp_opcode_obj = rtp_opcode.c_str();
            xrtGraphUpdateRTP(gemm_aie_gr, rtp_opcode_obj, opcode_ptr2,  512 * sizeof (uint32_t));

            const char *opcode_ptr3 = reinterpret_cast<const char *>(opcode_mem + core_id * 4 * 4 * 4 * 512 + dima_id * 4 * 4 * 512 + dimb_id * 4 * 512 + 3 * 512);
            rtp_opcode = "G.FG["+to_string(core_id)+"]["+to_string(dima_id)+"]["+to_string(dimb_id)+"].k3.in[3]";
            rtp_opcode_obj = rtp_opcode.c_str();
            xrtGraphUpdateRTP(gemm_aie_gr, rtp_opcode_obj, opcode_ptr3,  512 * sizeof (uint32_t));
         }
      }
   }

}


