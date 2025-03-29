#pragma once
#include "instruction.h"



void generate_bias(uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;
    uint32_t loadB_address = params.lpddr_offset_512b_bias;


    inst_header.inst_val.opcode = OPCODE_LOADB_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++; 
    inst_loadB_dram.inst_val.start_address = loadB_address + 0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_loadB_dram.inst_val.address_offset = 0; 
    inst_loadB_dram.inst_val.chunck_size = 512 * b_iter;
    inst_loadB_dram.inst_val.stride_offset = 0;
    inst_loadB_dram.inst_val.chunk_count = 1;
    inst_loadB_dram.inst_val.load_to_memcoreB0 = true;
    inst_loadB_dram.inst_val.load_to_memcoreB1 = false;
    inst_loadB_dram.inst_val.is_loading_bias   = true;
    for (int i = 0; i < CNT4B_LOAD_B_DRAM ; i++) { inst_sequence[count4B++] = inst_loadB_dram.raw_32b[i];}
    inst_loadB_dram.inst_val.start_address = loadB_address + 512 * b_iter / 16;
    inst_loadB_dram.inst_val.address_offset = 0;
    inst_loadB_dram.inst_val.chunck_size = 512 * b_iter;
    inst_loadB_dram.inst_val.stride_offset = 0;
    inst_loadB_dram.inst_val.chunk_count = 1;
    inst_loadB_dram.inst_val.load_to_memcoreB0 = false;
    inst_loadB_dram.inst_val.load_to_memcoreB1 = true;
    inst_loadB_dram.inst_val.is_loading_bias   = true;
    for (int i = 0; i < CNT4B_LOAD_B_DRAM ; i++) { inst_sequence[count4B++] = inst_loadB_dram.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.is_loading_bias = true;
    inst_memcore_B.inst_val.enable_transpose    = false;
    // size_dim1=16, size_dim2=1 => bias 1024;  b_iter = 1  
    // size_dim1=32, size_dim2=1 => bias 2048;  b_iter = 2
    // size_dim1=32, size_dim2=2 => bias 4096;  b_iter = 4
    inst_memcore_B.inst_val.one_mem_tile_dim1 = (b_iter == 1) ? 16 : 32;
    assert (b_iter == 1);
    inst_memcore_B.inst_val.one_mem_tile_dim2 = 1; // when b_iter == 1  
    // inst_memcore_B.inst_val.one_compute_tile_dim1 = 128; // (b_iter == 1) ? 64 : 128; but need to padding to be 32x32 per AIE
    // inst_memcore_B.inst_val.one_compute_tile_dim2 = 128; // 32; // when b_iter == 1 
    inst_memcore_B.inst_val.compute_tile_access_A = 1;
    inst_memcore_B.inst_val.compute_tile_access_B = 1;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size =  1 * 1 * b_iter*1*1*32*32/2 ; // 1 * 1 * b_iter*1*1*16*8/2 ; // when b_iter == 1 , 1024 total bias, 1 AIE only got 128 bias
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) { inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}

}





void generate_instruction_onelayer_with_bias ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(params.enable_bias == true);
    
    generate_bias(inst_sequence, count4B, countInstPkt, params);

    generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

    for (int a = 0; a < a_iter; a++){
        for (int b = 0; b< b_iter; b++){
            generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
            generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
            generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
        }
    }

    generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}



void generate_instruction_onelayer_overlap_128_512_A4B1K8_with_bias  ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(a_iter == 4);
    assert(b_iter == 1);
    assert(k_iter == 8);

    assert(params.enable_bias == true);
    
    generate_bias(inst_sequence, count4B, countInstPkt, params);

    generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

    int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

    a = 0; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 0; offset = 0; repeat_num = k_iter; 
    generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt, params);
    
    a = 1; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 1; loadA_b = 0; storeC_a = 0; storeC_b = 0; 
    generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a = 2; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 2; loadA_b = 0; storeC_a = 1; storeC_b = 0;
    generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a = 3; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 3; loadA_b = 0; storeC_a = 2; storeC_b = 0;
    generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a = 3; b = 0; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}


