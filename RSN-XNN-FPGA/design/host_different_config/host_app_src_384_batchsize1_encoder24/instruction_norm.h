#pragma once

#include "instruction.h"



void generate_instruction_Klarger16_steady_ddr (int loadA_a, int loadA_b, int storeC_a, int storeC_b, uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;
    uint32_t loadA_address, loadB_address, storeC_address;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    loadA_address = params.ddr_offset_512b_input + loadA_a * 768 * 128 * k_iter / 16 ; 
    storeC_address = params.ddr_offset_512b_output;
    storeC_address += (storeC_a * 768 * 1024 * b_iter + storeC_b * 128 * 1024) / 16;   


    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 30;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + 0;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = true;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
 
    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + 0 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = true;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
 
    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + 128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = true;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}





    inst_ddr.inst_val.start_address = storeC_address + 128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = true;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = true;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}




    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter)*128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = true;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 21;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;

    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter+1)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = true;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter+1)*128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = true;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = true;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter)*128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = true;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter+1)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = true;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}


    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter+1)*128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = true;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }



    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 3;
    inst_header.inst_val.repeat_num = k_iter - 13;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}



}




void generate_load_weight_previous_norm(uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

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
    uint32_t loadB_address = params.lpddr_offset_512b_pre_layer_weight;

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

    assert (b_iter == 1);

    // does not enable mop_buffer_window_size for memcores
    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = false;
    inst_memcore_B.inst_val.is_loading_bias       = true;
    inst_memcore_B.inst_val.enable_transpose      = false;
    // size_dim1=16, size_dim2=1 => bias 1024;  b_iter = 1  
    // size_dim1=32, size_dim2=1 => bias 2048;  b_iter = 2
    // size_dim1=32, size_dim2=2 => bias 4096;  b_iter = 4
    inst_memcore_B.inst_val.one_mem_tile_dim1     = (b_iter == 1) ? 16 : 32;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = 1; // when b_iter == 1  
    inst_memcore_B.inst_val.compute_tile_access_A = false;
    inst_memcore_B.inst_val.compute_tile_access_B = false;
    inst_memcore_B.inst_val.compute_tile_access_K = false;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = false;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias       = true;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = false;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = false; 
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


void generate_instruction_onelayer_cores_meshes_add_prev_layer ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = 1;
    uint32_t b_iter = 1;
    uint32_t k_iter = params.k_iter;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    bool enable_layer_norm = params.enable_norm;
    bool enable_gelu = params.enable_gelu;
    

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = false;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 8 - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    // inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    // inst_header.inst_val.mask = 0b000111;
    // inst_header.inst_val.is_last_mOP = false;
    // inst_header.inst_val.mop_buffer_window_size = 1;
    // inst_header.inst_val.repeat_num = 1;
    // inst_sequence[count4B++] = inst_header.raw_32b;
    // printHeaderInst(inst_header.inst_val, countInstPkt);
    // countInstPkt ++;
    // inst_memcore_A.inst_val.enable_load_from_dram = false;
    // inst_memcore_A.inst_val.enable_send_to_aie    = true;
    // inst_memcore_A.inst_val.one_mem_tile_dim1     = false;
    // inst_memcore_A.inst_val.one_mem_tile_dim2     = false;
    // inst_memcore_A.inst_val.compute_tile_access_A = 1;
    // inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    // for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }


    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 256/2;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }



    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num = 8/2;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 1*1*1*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 1*1*1*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}





    // inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    // inst_header.inst_val.mask = 0b000111;
    // inst_header.inst_val.is_last_mOP = false;
    // inst_header.inst_val.mop_buffer_window_size = 1;
    // inst_header.inst_val.repeat_num = 1 ;
    // inst_sequence[count4B++] = inst_header.raw_32b;
    // printHeaderInst(inst_header.inst_val, countInstPkt);
    // countInstPkt ++;
    // inst_memcore_A.inst_val.enable_load_from_dram = true;
    // inst_memcore_A.inst_val.enable_send_to_aie    = false;
    // inst_memcore_A.inst_val.one_mem_tile_dim1     = 256;
    // inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    // inst_memcore_A.inst_val.compute_tile_access_A = false;
    // inst_memcore_A.inst_val.compute_tile_access_B = false;  
    // for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter  - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 256/2;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 2/2;
    inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = false;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = false;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = false;
    inst_memcore_A.inst_val.compute_tile_access_A = 2/2;
    inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = false;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = 512;
    inst_memcore_B.inst_val.compute_tile_access_A = false;
    inst_memcore_B.inst_val.compute_tile_access_B = false;
    inst_memcore_B.inst_val.compute_tile_access_K = false;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

   inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter  -1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = 512;
    inst_memcore_B.inst_val.compute_tile_access_A = 2/2;
    inst_memcore_B.inst_val.compute_tile_access_B = 4;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

   inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = false;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = false;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = false;
    inst_memcore_B.inst_val.compute_tile_access_A = 2/2;
    inst_memcore_B.inst_val.compute_tile_access_B = 4;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = k_iter * 1 * 1* (2/2)*4*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = k_iter * 1 * 1*(2/2)*4*32*32/2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) { inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b111111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie   = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax       = false;
    inst_memcore_C.inst_val.enable_gelu          = enable_gelu;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256/2;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2/2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter =  k_iter + 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) { inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b111111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 -1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = true;
    inst_memcore_C.inst_val.enable_send_to_aie   = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax       = false;
    inst_memcore_C.inst_val.enable_gelu          = enable_gelu;
    inst_memcore_C.inst_val.enable_layer_norm    = enable_layer_norm;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256/2;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2/2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter =  k_iter;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) { inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b111111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = true;
    inst_memcore_C.inst_val.enable_send_to_aie   = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = false;
    inst_memcore_C.inst_val.enable_softmax       = false;
    inst_memcore_C.inst_val.enable_gelu          = enable_gelu;
    inst_memcore_C.inst_val.enable_layer_norm    = enable_layer_norm;    
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256/2;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2/2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter =  k_iter;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) { inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }   
}


void generate_instruction_onelayer_cores_meshes_add_prev_layer_prolog ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = 1;
    uint32_t b_iter = 1;
    uint32_t k_iter = params.k_iter;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    bool enable_layer_norm = params.enable_norm;
    bool enable_gelu = params.enable_gelu;
    

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = false;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 16 - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }



    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num = 8;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 1*1*1*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 1*1*1*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter  - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    // inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    // inst_header.inst_val.mask = 0b000111;
    // inst_header.inst_val.is_last_mOP = false;
    // inst_header.inst_val.mop_buffer_window_size = 1;
    // inst_header.inst_val.repeat_num = 1;
    // inst_sequence[count4B++] = inst_header.raw_32b;
    // printHeaderInst(inst_header.inst_val, countInstPkt);
    // countInstPkt ++;
    // inst_memcore_A.inst_val.enable_load_from_dram = false;
    // inst_memcore_A.inst_val.enable_send_to_aie    = true;
    // inst_memcore_A.inst_val.one_mem_tile_dim1     = false;
    // inst_memcore_A.inst_val.one_mem_tile_dim2     = false;
    // inst_memcore_A.inst_val.compute_tile_access_A = 2;
    // inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    // for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }


    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }





    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = false;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = 512;
    inst_memcore_B.inst_val.compute_tile_access_A = false;
    inst_memcore_B.inst_val.compute_tile_access_B = false;
    inst_memcore_B.inst_val.compute_tile_access_K = false;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

   inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter  -1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = 512;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 4;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

   inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = false;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = false;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = false;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 4;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = k_iter * 1 * 1*2*4*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = k_iter * 1 * 1*2*4*32*32/2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) { inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b111111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie   = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax       = false;
    inst_memcore_C.inst_val.enable_gelu          = enable_gelu;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter =  k_iter + 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) { inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b111111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = true;
    inst_memcore_C.inst_val.enable_send_to_aie   = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax       = false;
    inst_memcore_C.inst_val.enable_gelu          = enable_gelu;
    inst_memcore_C.inst_val.enable_layer_norm    = enable_layer_norm;    
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter =  k_iter+1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) { inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }   
}


void generate_instruction_onelayer_cores_meshes_add_prev_layer_epilog ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = 1;
    uint32_t b_iter = 1;
    uint32_t k_iter = params.k_iter;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    bool enable_layer_norm = params.enable_norm;
    bool enable_gelu = params.enable_gelu;
    

    // inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    // inst_header.inst_val.mask = 0b000111;
    // inst_header.inst_val.is_last_mOP = false;
    // inst_header.inst_val.mop_buffer_window_size = 1;
    // inst_header.inst_val.repeat_num = 1 ;
    // inst_sequence[count4B++] = inst_header.raw_32b;
    // printHeaderInst(inst_header.inst_val, countInstPkt);
    // countInstPkt ++;
    // inst_memcore_A.inst_val.enable_load_from_dram = true;
    // inst_memcore_A.inst_val.enable_send_to_aie    = false;
    // inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    // inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    // inst_memcore_A.inst_val.compute_tile_access_A = 1;
    // inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    // for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 16 - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }



    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num = 8;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 1*1*1*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 1*1*1*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter  - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = false;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = false;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = false;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = false;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = 512;
    inst_memcore_B.inst_val.compute_tile_access_A = false;
    inst_memcore_B.inst_val.compute_tile_access_B = false;
    inst_memcore_B.inst_val.compute_tile_access_K = false;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

   inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter  -1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = 512;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 4;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

   inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = false;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = false;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = false;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 4;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = k_iter * 1 * 1*2*4*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = k_iter * 1 * 1*2*4*32*32/2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) { inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b111111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = true;
    inst_memcore_C.inst_val.enable_send_to_aie   = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = false;
    inst_memcore_C.inst_val.enable_softmax       = false;
    inst_memcore_C.inst_val.enable_gelu          = enable_gelu;
    inst_memcore_C.inst_val.enable_layer_norm    = enable_layer_norm;    
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter =  k_iter+1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) { inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }   
}


void generate_instruction_onelayer_cores_meshes_add_prev_layer_steady ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = 1;
    uint32_t b_iter = 1;
    uint32_t k_iter = params.k_iter;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    bool enable_layer_norm = params.enable_norm;
    bool enable_gelu = params.enable_gelu;
    

    // inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    // inst_header.inst_val.mask = 0b000111;
    // inst_header.inst_val.is_last_mOP = false;
    // inst_header.inst_val.mop_buffer_window_size = 1;
    // inst_header.inst_val.repeat_num = 1 ;
    // inst_sequence[count4B++] = inst_header.raw_32b;
    // printHeaderInst(inst_header.inst_val, countInstPkt);
    // countInstPkt ++;
    // inst_memcore_A.inst_val.enable_load_from_dram = true;
    // inst_memcore_A.inst_val.enable_send_to_aie    = false;
    // inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    // inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    // inst_memcore_A.inst_val.compute_tile_access_A = 1;
    // inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    // for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 16 - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 1;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }



    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num = 8;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 1*1*1*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 1*1*1*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter  - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    // inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    // inst_header.inst_val.mask = 0b000111;
    // inst_header.inst_val.is_last_mOP = false;
    // inst_header.inst_val.mop_buffer_window_size = 1;
    // inst_header.inst_val.repeat_num = 1;
    // inst_sequence[count4B++] = inst_header.raw_32b;
    // printHeaderInst(inst_header.inst_val, countInstPkt);
    // countInstPkt ++;
    // inst_memcore_A.inst_val.enable_load_from_dram = false;
    // inst_memcore_A.inst_val.enable_send_to_aie    = true;
    // inst_memcore_A.inst_val.one_mem_tile_dim1     = false;
    // inst_memcore_A.inst_val.one_mem_tile_dim2     = false;
    // inst_memcore_A.inst_val.compute_tile_access_A = 2;
    // inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    // for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2     = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }




    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = false;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = 512;
    inst_memcore_B.inst_val.compute_tile_access_A = false;
    inst_memcore_B.inst_val.compute_tile_access_B = false;
    inst_memcore_B.inst_val.compute_tile_access_K = false;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

   inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter  -1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = 128;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = 512;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 4;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

   inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1 ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = false;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias       = false;
    inst_memcore_B.inst_val.enable_transpose      = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1     = false;
    inst_memcore_B.inst_val.one_mem_tile_dim2     = false;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 4;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = k_iter * 1 * 1*2*4*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = k_iter * 1 * 1*2*4*32*32/2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) { inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b111111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = true;
    inst_memcore_C.inst_val.enable_send_to_aie   = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax       = false;
    inst_memcore_C.inst_val.enable_gelu          = enable_gelu;
    inst_memcore_C.inst_val.enable_layer_norm    = enable_layer_norm;    
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter =  k_iter+1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) { inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }   
}





void generate_instruction_load_prev_layer(int a, int b, uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;
    uint32_t loadA_address, loadB_address, storeC_address;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    loadA_address = params.ddr_offset_512b_pre_layer +  a * (768/2) * 1024 / 16 ;
    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 6;
    inst_header.inst_val.repeat_num = 4;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*4 /16;
    inst_ddr.inst_val.chunk_count = 1;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + (256/2) *1024 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*4 /16;
    inst_ddr.inst_val.chunk_count = 1;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + (256/2) *1024 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*4 /16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
  

    inst_ddr.inst_val.start_address = loadA_address +  0 / 16 + 128*128*4 /16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 0;
    inst_ddr.inst_val.chunk_count = 1;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + (256/2) *1024 / 16 + 128*128*4 /16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 0;
    inst_ddr.inst_val.chunk_count = 1;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + (256/2) *1024 * 2 / 16 + 128*128*4 /16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 0;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}


    // loadA_address = params.ddr_offset_512b_pre_layer +  a * (768/2) * 1024 / 16 + 128 * 1024 / 16 ;
    // inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    // inst_header.inst_val.mask = false;
    // inst_header.inst_val.is_last_mOP = false;
    // inst_header.inst_val.mop_buffer_window_size = 3;
    // inst_header.inst_val.repeat_num = 4;
    // inst_sequence[count4B++] = inst_header.raw_32b;
    // printHeaderInst(inst_header.inst_val, countInstPkt);
    // countInstPkt ++;
    // inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    // inst_ddr.inst_val.address_offset =  128*128 / 16; 
    // inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    // inst_ddr.inst_val.stride_offset = 128*128*4 /16;
    // inst_ddr.inst_val.chunk_count = 1;
    // inst_ddr.inst_val.is_store = false; 
    // inst_ddr.inst_val.is_load = true;
    // inst_ddr.inst_val.load_to_memcoreA0 = true;
    // inst_ddr.inst_val.load_to_memcoreA1 = false;
    // inst_ddr.inst_val.load_to_memcoreA2 = false;
    // inst_ddr.inst_val.load_to_memcoreB0 = false;
    // inst_ddr.inst_val.load_to_memcoreB1 = false;
    // inst_ddr.inst_val.load_to_memcoreB2 = false;
    // inst_ddr.inst_val.load_to_memcoreC0 = false;
    // inst_ddr.inst_val.load_to_memcoreC1 = false;
    // inst_ddr.inst_val.load_to_memcoreC2 = false;
    // inst_ddr.inst_val.load_to_memcoreC3 = false;
    // inst_ddr.inst_val.load_to_memcoreC4 = false;
    // inst_ddr.inst_val.load_to_memcoreC5 = false;
    // inst_ddr.inst_val.store_from_memcoreC0 = false;
    // inst_ddr.inst_val.store_from_memcoreC1 = false;
    // inst_ddr.inst_val.store_from_memcoreC2 = false;
    // inst_ddr.inst_val.store_from_memcoreC3 = false;
    // inst_ddr.inst_val.store_from_memcoreC4 = false;
    // inst_ddr.inst_val.store_from_memcoreC5 = false;
    // for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    // inst_ddr.inst_val.start_address = loadA_address + 256*1024 / 16;
    // inst_ddr.inst_val.address_offset = 128*128 / 16;
    // inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    // inst_ddr.inst_val.stride_offset = 128*128*4 /16;
    // inst_ddr.inst_val.chunk_count = 1;
    // inst_ddr.inst_val.is_store = false; 
    // inst_ddr.inst_val.is_load = true;
    // inst_ddr.inst_val.load_to_memcoreA0 = false;
    // inst_ddr.inst_val.load_to_memcoreA1 = true;
    // inst_ddr.inst_val.load_to_memcoreA2 = false;
    // inst_ddr.inst_val.load_to_memcoreB0 = false;
    // inst_ddr.inst_val.load_to_memcoreB1 = false;
    // inst_ddr.inst_val.load_to_memcoreB2 = false;
    // inst_ddr.inst_val.load_to_memcoreC0 = false;
    // inst_ddr.inst_val.load_to_memcoreC1 = false;
    // inst_ddr.inst_val.load_to_memcoreC2 = false;
    // inst_ddr.inst_val.load_to_memcoreC3 = false;
    // inst_ddr.inst_val.load_to_memcoreC4 = false;
    // inst_ddr.inst_val.load_to_memcoreC5 = false;
    // inst_ddr.inst_val.store_from_memcoreC0 = false;
    // inst_ddr.inst_val.store_from_memcoreC1 = false;
    // inst_ddr.inst_val.store_from_memcoreC2 = false;
    // inst_ddr.inst_val.store_from_memcoreC3 = false;
    // inst_ddr.inst_val.store_from_memcoreC4 = false;
    // inst_ddr.inst_val.store_from_memcoreC5 = false;
    // for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    // inst_ddr.inst_val.start_address = loadA_address + 256*1024 * 2 / 16;
    // inst_ddr.inst_val.address_offset = 128*128 / 16;
    // inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    // inst_ddr.inst_val.stride_offset = 128*128*4 /16;
    // inst_ddr.inst_val.chunk_count = 1; 
    // inst_ddr.inst_val.is_store = false; 
    // inst_ddr.inst_val.is_load = true;
    // inst_ddr.inst_val.load_to_memcoreA0 = false;
    // inst_ddr.inst_val.load_to_memcoreA1 = false;
    // inst_ddr.inst_val.load_to_memcoreA2 = true;
    // inst_ddr.inst_val.load_to_memcoreB0 = false;
    // inst_ddr.inst_val.load_to_memcoreB1 = false;
    // inst_ddr.inst_val.load_to_memcoreB2 = false;
    // inst_ddr.inst_val.load_to_memcoreC0 = false;
    // inst_ddr.inst_val.load_to_memcoreC1 = false;
    // inst_ddr.inst_val.load_to_memcoreC2 = false;
    // inst_ddr.inst_val.load_to_memcoreC3 = false;
    // inst_ddr.inst_val.load_to_memcoreC4 = false;
    // inst_ddr.inst_val.load_to_memcoreC5 = false;
    // inst_ddr.inst_val.store_from_memcoreC0 = false;
    // inst_ddr.inst_val.store_from_memcoreC1 = false;
    // inst_ddr.inst_val.store_from_memcoreC2 = false;
    // inst_ddr.inst_val.store_from_memcoreC3 = false;
    // inst_ddr.inst_val.store_from_memcoreC4 = false;
    // inst_ddr.inst_val.store_from_memcoreC5 = false;
    // for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    
    
    // inst_ddr.inst_val.start_address = loadA_address +  0 / 16 + 128*128*4 /16; // divided by 16 because 1 address hold 16 32float (512bit)
    // inst_ddr.inst_val.address_offset =  128*128 / 16 ; 
    // inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    // inst_ddr.inst_val.stride_offset = 0;
    // inst_ddr.inst_val.chunk_count = 1;
    // inst_ddr.inst_val.is_store = false; 
    // inst_ddr.inst_val.is_load = true;
    // inst_ddr.inst_val.load_to_memcoreA0 = true;
    // inst_ddr.inst_val.load_to_memcoreA1 = false;
    // inst_ddr.inst_val.load_to_memcoreA2 = false;
    // inst_ddr.inst_val.load_to_memcoreB0 = false;
    // inst_ddr.inst_val.load_to_memcoreB1 = false;
    // inst_ddr.inst_val.load_to_memcoreB2 = false;
    // inst_ddr.inst_val.load_to_memcoreC0 = false;
    // inst_ddr.inst_val.load_to_memcoreC1 = false;
    // inst_ddr.inst_val.load_to_memcoreC2 = false;
    // inst_ddr.inst_val.load_to_memcoreC3 = false;
    // inst_ddr.inst_val.load_to_memcoreC4 = false;
    // inst_ddr.inst_val.load_to_memcoreC5 = false;
    // inst_ddr.inst_val.store_from_memcoreC0 = false;
    // inst_ddr.inst_val.store_from_memcoreC1 = false;
    // inst_ddr.inst_val.store_from_memcoreC2 = false;
    // inst_ddr.inst_val.store_from_memcoreC3 = false;
    // inst_ddr.inst_val.store_from_memcoreC4 = false;
    // inst_ddr.inst_val.store_from_memcoreC5 = false;
    // for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    // inst_ddr.inst_val.start_address = loadA_address + 256*1024 / 16 + 128*128*4 /16;
    // inst_ddr.inst_val.address_offset = 128*128 / 16;
    // inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    // inst_ddr.inst_val.stride_offset = 0;
    // inst_ddr.inst_val.chunk_count = 1;
    // inst_ddr.inst_val.is_store = false; 
    // inst_ddr.inst_val.is_load = true;
    // inst_ddr.inst_val.load_to_memcoreA0 = false;
    // inst_ddr.inst_val.load_to_memcoreA1 = true;
    // inst_ddr.inst_val.load_to_memcoreA2 = false;
    // inst_ddr.inst_val.load_to_memcoreB0 = false;
    // inst_ddr.inst_val.load_to_memcoreB1 = false;
    // inst_ddr.inst_val.load_to_memcoreB2 = false;
    // inst_ddr.inst_val.load_to_memcoreC0 = false;
    // inst_ddr.inst_val.load_to_memcoreC1 = false;
    // inst_ddr.inst_val.load_to_memcoreC2 = false;
    // inst_ddr.inst_val.load_to_memcoreC3 = false;
    // inst_ddr.inst_val.load_to_memcoreC4 = false;
    // inst_ddr.inst_val.load_to_memcoreC5 = false;
    // inst_ddr.inst_val.store_from_memcoreC0 = false;
    // inst_ddr.inst_val.store_from_memcoreC1 = false;
    // inst_ddr.inst_val.store_from_memcoreC2 = false;
    // inst_ddr.inst_val.store_from_memcoreC3 = false;
    // inst_ddr.inst_val.store_from_memcoreC4 = false;
    // inst_ddr.inst_val.store_from_memcoreC5 = false;
    // for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    // inst_ddr.inst_val.start_address = loadA_address + 256*1024 * 2 / 16 + 128*128*4 /16;
    // inst_ddr.inst_val.address_offset = 128*128 / 16;
    // inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    // inst_ddr.inst_val.stride_offset = 0;
    // inst_ddr.inst_val.chunk_count = 1; 
    // inst_ddr.inst_val.is_store = false; 
    // inst_ddr.inst_val.is_load = true;
    // inst_ddr.inst_val.load_to_memcoreA0 = false;
    // inst_ddr.inst_val.load_to_memcoreA1 = false;
    // inst_ddr.inst_val.load_to_memcoreA2 = true;
    // inst_ddr.inst_val.load_to_memcoreB0 = false;
    // inst_ddr.inst_val.load_to_memcoreB1 = false;
    // inst_ddr.inst_val.load_to_memcoreB2 = false;
    // inst_ddr.inst_val.load_to_memcoreC0 = false;
    // inst_ddr.inst_val.load_to_memcoreC1 = false;
    // inst_ddr.inst_val.load_to_memcoreC2 = false;
    // inst_ddr.inst_val.load_to_memcoreC3 = false;
    // inst_ddr.inst_val.load_to_memcoreC4 = false;
    // inst_ddr.inst_val.load_to_memcoreC5 = false;
    // inst_ddr.inst_val.store_from_memcoreC0 = false;
    // inst_ddr.inst_val.store_from_memcoreC1 = false;
    // inst_ddr.inst_val.store_from_memcoreC2 = false;
    // inst_ddr.inst_val.store_from_memcoreC3 = false;
    // inst_ddr.inst_val.store_from_memcoreC4 = false;
    // inst_ddr.inst_val.store_from_memcoreC5 = false;
    // for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}


}


void generate_instruction_onelayer_norm ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(params.enable_addmul_pre_layer == true);
    assert(params.enable_bias == true);

    generate_load_weight_previous_norm(inst_sequence, count4B, countInstPkt, params);
    generate_bias(inst_sequence, count4B, countInstPkt, params);
    
    int a, b;

    a=0; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    a=1; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    a=2; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    a=3; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

}





void generate_instruction_onelayer_norm_numlayer1 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(params.enable_addmul_pre_layer == true);
    assert(params.enable_bias == true);

    generate_load_weight_previous_norm(inst_sequence, count4B, countInstPkt, params);
    generate_bias(inst_sequence, count4B, countInstPkt, params);
    
    int a, b;

    a=0; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
    
}



void generate_instruction_onelayer_norm_overlap_A4B1K8 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(params.enable_addmul_pre_layer == true);
    assert(params.enable_bias == true);

    generate_load_weight_previous_norm(inst_sequence, count4B, countInstPkt, params);
    generate_bias(inst_sequence, count4B, countInstPkt, params);
    
    int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

    a=0; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer_prolog(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);

    a=1; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer_steady(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 1; loadA_b = 0; storeC_a = 0; storeC_b = 0; 
    generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);


    a=2; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer_steady(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 2; loadA_b = 0; storeC_a = 1; storeC_b = 0;
    generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);


    a=3; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer_epilog(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 3; loadA_b = 0; storeC_a = 2; storeC_b = 0;
    generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

}





void generate_instruction_onelayer_norm_overlap_A4B1K32 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(params.enable_addmul_pre_layer == true);
    assert(params.enable_bias == true);

    generate_load_weight_previous_norm(inst_sequence, count4B, countInstPkt, params);
    generate_bias(inst_sequence, count4B, countInstPkt, params);
    
    int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

    a=0; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer_prolog(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);

    a=1; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer_steady(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 1; loadA_b = 0; storeC_a = 0; storeC_b = 0; 
    generate_instruction_Klarger16_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);


    a=2; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer_steady(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 2; loadA_b = 0; storeC_a = 1; storeC_b = 0;
    generate_instruction_Klarger16_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a=3; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer_epilog(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    // generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 3; loadA_b = 0; storeC_a = 2; storeC_b = 0;
    generate_instruction_Klarger16_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);


}





void generate_instruction_onelayer_norm_overlap_A1B1K8 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(params.enable_addmul_pre_layer == true);
    assert(params.enable_bias == true);

    generate_load_weight_previous_norm(inst_sequence, count4B, countInstPkt, params);
    generate_bias(inst_sequence, count4B, countInstPkt, params);
    
    int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

    a=0; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

}






void generate_instruction_onelayer_norm_K32 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(params.enable_addmul_pre_layer == true);
    assert(params.enable_bias == true);

    generate_load_weight_previous_norm(inst_sequence, count4B, countInstPkt, params);
    generate_bias(inst_sequence, count4B, countInstPkt, params);
    
    int a, b;

    a=0; b=0;
    generate_instruction_onelayer_cores_meshes_add_prev_layer(inst_sequence, count4B, countInstPkt, params);
    generate_instruction_load_prev_layer(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
    generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

}

