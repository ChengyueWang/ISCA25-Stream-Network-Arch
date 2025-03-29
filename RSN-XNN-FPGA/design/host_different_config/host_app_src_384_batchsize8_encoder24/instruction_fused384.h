#pragma once

#include "instruction_onelayer.h"


void generate_instruction_fused384_coreA(bool enable_load, bool enable_send, int repeat_num,  uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {


    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    bool enable_softmax = true;



    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000001;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = enable_load;
    inst_memcore_A.inst_val.enable_send_to_aie    = enable_send;
    inst_memcore_A.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 2;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) {inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];    }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000010;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = enable_load;
    inst_memcore_A.inst_val.enable_send_to_aie    = enable_send;
    inst_memcore_A.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 2;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) {inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];    }



}


void generate_instruction_fused384_coreB(bool enable_load, bool enable_send, int repeat_num,  uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {

    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    bool enable_softmax = true;



    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000001;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = enable_load;
    inst_memcore_B.inst_val.enable_send_to_aie    = enable_send;
    inst_memcore_B.inst_val.is_loading_bias     = false;
    inst_memcore_B.inst_val.enable_transpose    = true;
    inst_memcore_B.inst_val.one_mem_tile_dim1   = 64;
    inst_memcore_B.inst_val.one_mem_tile_dim2   = 128;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 1;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) {inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000010;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = enable_load;
    inst_memcore_B.inst_val.enable_send_to_aie    = enable_send;
    inst_memcore_B.inst_val.is_loading_bias     = false;
    inst_memcore_B.inst_val.enable_transpose    = true;
    inst_memcore_B.inst_val.one_mem_tile_dim1   = 64;
    inst_memcore_B.inst_val.one_mem_tile_dim2   = 256;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 2;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) {inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000100;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = enable_load;
    inst_memcore_B.inst_val.enable_send_to_aie    = enable_send;
    inst_memcore_B.inst_val.is_loading_bias   = false;
    inst_memcore_B.inst_val.enable_transpose  = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1 = 384;
    inst_memcore_B.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 1;
    inst_memcore_B.inst_val.compute_tile_access_K = 3;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) {inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}



}


void generate_instruction_fused384_coreC0123(bool enable_recv, bool enable_send, int repeat_num,  uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {

    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    uint32_t num_layer = repeat_num;
    bool enable_softmax = true;


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b000001;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = enable_send;
    inst_memcore_C.inst_val.enable_recv_from_aie = enable_recv;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 128;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 1;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b000010;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie  = enable_send;
    inst_memcore_C.inst_val.enable_recv_from_aie = enable_recv;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 256;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 2;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b000100;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = enable_send;
    inst_memcore_C.inst_val.enable_recv_from_aie = enable_recv;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 128;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 1;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b001000;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = enable_send;
    inst_memcore_C.inst_val.enable_recv_from_aie = enable_recv;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 256;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 2;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }






}

void generate_instruction_fused384_coreC45(bool enable_recv, bool enable_store, int repeat_num,  uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {

    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    bool enable_softmax = true;


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b010000;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = enable_store;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = enable_recv;
    inst_memcore_C.inst_val.enable_softmax = false;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b100000;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = enable_store;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = enable_recv;
    inst_memcore_C.inst_val.enable_softmax = false;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];}



}



void generate_instruction_fused384_meshA( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {

    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;
    uint32_t num_layer = params.num_layer;

    bool enable_softmax = true;


    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 4;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}




    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 8;
    inst_header.inst_val.repeat_num = num_layer - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i]; }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];    }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 




    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 4;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i]; }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];    }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 







}


void generate_instruction_fused384_meshB( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {

    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;
    uint32_t num_layer = params.num_layer;

    bool enable_softmax = true;

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 3;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = 2 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}



    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 5;
    inst_header.inst_val.repeat_num = num_layer - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = 2 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num =  1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}



}



void generate_instruction_fused384 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {

    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    uint32_t num_layer = params.num_layer;
    bool enable_softmax = true;
    uint32_t ddr_addr_L1_inA  = params.ddr_offset_512b_inA_L1;
    uint32_t ddr_addr_L1_inB  = params.ddr_offset_512b_inB_L1;
    uint32_t ddr_addr_L2_inB  = params.ddr_offset_512b_inB_L2;
    uint32_t ddr_addr_L2_outC = params.ddr_offset_512b_outC_L2;

    bool enable_load; bool enable_send; int repeat_num;
    bool enable_recv; bool enable_store;
    int gap_num = 16; 


    enable_load = true;  enable_send = false; repeat_num = 1;
    generate_instruction_fused384_coreA(enable_load, enable_send, repeat_num, inst_sequence, count4B, countInstPkt, params);
    enable_load = true;  enable_send = false; repeat_num = 1;
    generate_instruction_fused384_coreB(enable_load, enable_send, repeat_num, inst_sequence, count4B, countInstPkt, params);
    enable_recv = true;  enable_send = false; repeat_num = 1;
    generate_instruction_fused384_coreC0123(enable_recv, enable_send, repeat_num, inst_sequence, count4B, countInstPkt, params);
    enable_recv = true;  enable_store = false; repeat_num = 1;
    generate_instruction_fused384_coreC45(enable_recv, enable_store, repeat_num, inst_sequence, count4B, countInstPkt, params);

    enable_load = true;  enable_send = true; repeat_num = num_layer - 1;
    generate_instruction_fused384_coreA(enable_load, enable_send, repeat_num, inst_sequence, count4B, countInstPkt, params);
    enable_load = true;  enable_send = true; repeat_num = num_layer - 1;
    generate_instruction_fused384_coreB(enable_load, enable_send, repeat_num, inst_sequence, count4B, countInstPkt, params);
    enable_recv = true;  enable_send = true; repeat_num = num_layer - 1;
    generate_instruction_fused384_coreC0123(enable_recv, enable_send, repeat_num, inst_sequence, count4B, countInstPkt, params);
    enable_recv = true;  enable_store = true; repeat_num = num_layer - 1;
    generate_instruction_fused384_coreC45(enable_recv, enable_store, repeat_num, inst_sequence, count4B, countInstPkt, params);

    enable_load = false;  enable_send = true; repeat_num = 1;
    generate_instruction_fused384_coreA(enable_load, enable_send, repeat_num, inst_sequence, count4B, countInstPkt, params);
    enable_load = false;  enable_send = true; repeat_num = 1;
    generate_instruction_fused384_coreB(enable_load, enable_send, repeat_num, inst_sequence, count4B, countInstPkt, params);
    enable_recv = false;  enable_send = true; repeat_num = 1;
    generate_instruction_fused384_coreC0123(enable_recv, enable_send, repeat_num, inst_sequence, count4B, countInstPkt, params);
    enable_recv = false;  enable_store = true; repeat_num = 1;
    generate_instruction_fused384_coreC45(enable_recv, enable_store, repeat_num, inst_sequence, count4B, countInstPkt, params);



    // generate_instruction_fused384_meshB(inst_sequence, count4B, countInstPkt, params);

    // generate_instruction_fused384_meshA(inst_sequence, count4B, countInstPkt, params);


    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 3;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = 2 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}




    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 4;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}






    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 5;
    inst_header.inst_val.repeat_num = 2;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = ddr_addr_L1_inA + gap_num * 1 * 128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L1_inB + gap_num * 1*128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = true;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L1_inA;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0; // @@@
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L1_inB;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = 0;  // @@@
    inst_ddr.inst_val.chunk_count = 1;  
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = true;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L2_inB;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 3; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = true;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }




    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 8;
    inst_header.inst_val.repeat_num = num_layer - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i]; }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];    }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 




    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 4;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i]; }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];    }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 




    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 5;
    inst_header.inst_val.repeat_num = num_layer - 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = 2 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num =  1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}


    for (int batch =0; batch < BATCH_SIZE - 1 ; batch ++){


    ddr_addr_L1_inA  +=  (64*128/16) * 2 ;
    ddr_addr_L1_inB  +=  (64*128/16) * 2 ;
    ddr_addr_L2_inB  +=  (64*128/16) * 2 ;
    ddr_addr_L2_outC +=  0 ;

    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 7;
    inst_header.inst_val.repeat_num = 16 - 2;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = ddr_addr_L1_inA + gap_num * 1 * 128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L1_inB + gap_num * 1*128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = true;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L1_inA;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0; // @@@
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L1_inB;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = 0;  // @@@
    inst_ddr.inst_val.chunk_count = 1;  
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = true;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }


    inst_ddr.inst_val.start_address = ddr_addr_L2_inB;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 3; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = true;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L2_outC; // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0;  // @@@
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L2_outC + gap_num * 1*128*64/16;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }




    ddr_addr_L1_inA  +=  (64*128/16) * 46 ;
    ddr_addr_L1_inB  +=  (64*128/16) * 46 ;
    ddr_addr_L2_inB  +=  (64*128/16) * 46 ;
    // ddr_addr_L1_inA  +=  (64*128/16) * 62 ;
    // ddr_addr_L1_inB  +=  (64*128/16) * 62 ;
    // ddr_addr_L2_inB  +=  (64*128/16) * 62 ;
    ddr_addr_L2_outC +=  (64*128/16) * 14 ;

    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 7;
    inst_header.inst_val.repeat_num = 2;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = ddr_addr_L1_inA + gap_num * 1 * 128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L1_inB + gap_num * 1*128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = true;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L1_inA;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0; // @@@
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L1_inB;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = 0;  // @@@
    inst_ddr.inst_val.chunk_count = 1;  
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = true;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }


    inst_ddr.inst_val.start_address = ddr_addr_L2_inB;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 3; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = true;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L2_outC; // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0;  // @@@
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L2_outC + gap_num * 1*128*64/16;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }


        // ddr_addr_L2_outC +=  (64*128/16) * 50 ;
        ddr_addr_L2_outC +=  (64*128/16) * 34 ;


    }





    ddr_addr_L1_inA  +=  (64*128/16) * 2 ;
    ddr_addr_L1_inB  +=  (64*128/16) * 2 ;
    ddr_addr_L2_inB  +=  (64*128/16) * 2 ;
    ddr_addr_L2_outC +=  0 ;

    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 7;
    inst_header.inst_val.repeat_num = 14;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = ddr_addr_L1_inA + gap_num * 1 * 128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L1_inB + gap_num * 1*128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = true;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L1_inA;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0; // @@@
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L1_inB;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = 0;  // @@@
    inst_ddr.inst_val.chunk_count = 1;  
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = true;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }


    inst_ddr.inst_val.start_address = ddr_addr_L2_inB;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 3; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = true;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }

    inst_ddr.inst_val.start_address = ddr_addr_L2_outC; // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0;  // @@@
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L2_outC + gap_num * 1*128*64/16;  // @@@
    inst_ddr.inst_val.address_offset = 64*128 / 16;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }




    ddr_addr_L2_outC +=  (64*128/16) * 14 ;

    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num = 2;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = ddr_addr_L2_outC; // @@@
    inst_ddr.inst_val.address_offset = 64*128/16;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0;  // @@@
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L2_outC + gap_num *1*128*64/16;  // @@@
    inst_ddr.inst_val.address_offset = 64*128/16;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = gap_num * 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }








}

void generate_instruction_fused384_numlayer1 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {

    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    uint32_t num_layer = params.num_layer;
    bool enable_softmax = true;

    assert(num_layer == 1);

    uint32_t ddr_addr_L1_inA  = params.ddr_offset_512b_inA_L1;
    uint32_t ddr_addr_L1_inB  = params.ddr_offset_512b_inB_L1;
    uint32_t ddr_addr_L2_inB  = params.ddr_offset_512b_inB_L2;
    uint32_t ddr_addr_L2_outC = params.ddr_offset_512b_outC_L2;

    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 7;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = ddr_addr_L1_inA;  // @@@
    inst_ddr.inst_val.address_offset = 0; // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0; // @@@
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L1_inA + 128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 0; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L1_inB;  // @@@
    inst_ddr.inst_val.address_offset = 0; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = 0;  // @@@
    inst_ddr.inst_val.chunk_count = 1;  
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = true;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L1_inB + 1*128*64/16 ;  // @@@
    inst_ddr.inst_val.address_offset = 0; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = true;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L2_inB;  // @@@
    inst_ddr.inst_val.address_offset = 0; // @@@
    inst_ddr.inst_val.chunck_size = 128*64; 
    inst_ddr.inst_val.stride_offset = 128*64/16;  // @@@
    inst_ddr.inst_val.chunk_count = 3; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = true;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L2_outC; // @@@
    inst_ddr.inst_val.address_offset = 0;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 0;  // @@@
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }
    inst_ddr.inst_val.start_address = ddr_addr_L2_outC + 1*128*64/16;  // @@@
    inst_ddr.inst_val.address_offset = 0;  // @@@
    inst_ddr.inst_val.chunck_size = 128*64;
    inst_ddr.inst_val.stride_offset = 128*64/16; // @@@
    inst_ddr.inst_val.chunk_count = 2; 
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
    for (int i = 0; i < CNT4B_DDR ; i++) {inst_sequence[count4B++] = inst_ddr.raw_32b[i];    }


    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000001;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = false;
    inst_memcore_A.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 2;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) {inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];    }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000010;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = true;
    inst_memcore_A.inst_val.enable_send_to_aie    = false;
    inst_memcore_A.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 2;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) {inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];    }


    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000001;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = false;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_A.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_A.inst_val.compute_tile_access_A = 1;
    inst_memcore_A.inst_val.compute_tile_access_B = 2;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) {inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];    }


    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000010;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.enable_load_from_dram = false;
    inst_memcore_A.inst_val.enable_send_to_aie    = true;
    inst_memcore_A.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 2;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) {inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];    }


    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000001;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = false;
    inst_memcore_B.inst_val.is_loading_bias     = false;
    inst_memcore_B.inst_val.enable_transpose    = true;
    inst_memcore_B.inst_val.one_mem_tile_dim1   = 64;
    inst_memcore_B.inst_val.one_mem_tile_dim2   = 128;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 1;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) {inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000010;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = false;
    inst_memcore_B.inst_val.is_loading_bias     = false;
    inst_memcore_B.inst_val.enable_transpose    = true;
    inst_memcore_B.inst_val.one_mem_tile_dim1   = 64;
    inst_memcore_B.inst_val.one_mem_tile_dim2   = 256;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 2;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) {inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000001;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = false;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias     = false;
    inst_memcore_B.inst_val.enable_transpose    = true;
    inst_memcore_B.inst_val.one_mem_tile_dim1   = 64;
    inst_memcore_B.inst_val.one_mem_tile_dim2   = 128;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 1;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) {inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}



    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000010;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = false;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias     = false;
    inst_memcore_B.inst_val.enable_transpose    = true;
    inst_memcore_B.inst_val.one_mem_tile_dim1   = 64;
    inst_memcore_B.inst_val.one_mem_tile_dim2   = 256;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 2;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) {inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}






    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000100;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = true;
    inst_memcore_B.inst_val.enable_send_to_aie    = false;
    inst_memcore_B.inst_val.is_loading_bias   = false;
    inst_memcore_B.inst_val.enable_transpose  = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1 = 384;
    inst_memcore_B.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 1;
    inst_memcore_B.inst_val.compute_tile_access_K = 3;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) {inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000100;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.enable_load_from_dram = false;
    inst_memcore_B.inst_val.enable_send_to_aie    = true;
    inst_memcore_B.inst_val.is_loading_bias   = false;
    inst_memcore_B.inst_val.enable_transpose  = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1 = 384;
    inst_memcore_B.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 1;
    inst_memcore_B.inst_val.compute_tile_access_K = 3;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) {inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}



    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b000001;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 128;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 1;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b000010;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie  = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 256;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 2;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b000100;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 128;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 1;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b001000;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 256;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 2;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }








    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b000001;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = true;
    inst_memcore_C.inst_val.enable_recv_from_aie = false;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 128;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 1;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b000010;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie  = true;
    inst_memcore_C.inst_val.enable_recv_from_aie = false;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 256;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 2;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b000100;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = true;
    inst_memcore_C.inst_val.enable_recv_from_aie = false;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 128;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 1;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b001000;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = true;
    inst_memcore_C.inst_val.enable_recv_from_aie = false;
    inst_memcore_C.inst_val.enable_softmax = enable_softmax;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 256;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 2;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }







    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b010000;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax = false;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b100000;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = false;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax = false;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];}



    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b010000;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = true;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = false;
    inst_memcore_C.inst_val.enable_softmax = false;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b100000;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = true;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = false;
    inst_memcore_C.inst_val.enable_softmax = false;
    inst_memcore_C.inst_val.enable_gelu          = false;
    inst_memcore_C.inst_val.enable_layer_norm    = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 64;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 1;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 2;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter = 1;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) {inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];}




    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 8;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    // tile 0, upper left
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    // tile 1, upper right
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    // tile 2, low left
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    // tile 3, low right
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i]; }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 
    inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];    }
    inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
    for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 

    

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 6;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
    inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
    for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}





    return;
}






// void generate_instruction_fused384_meshA( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {

//     union_inst_header inst_header;
//     union_inst_ddr inst_ddr;
//     union_inst_memcore_A inst_memcore_A;
//     union_inst_memcore_B inst_memcore_B;
//     union_inst_memcore_C inst_memcore_C;
//     union_inst_mesh_A inst_mesh_A;
//     union_inst_mesh_B inst_mesh_B;
//     uint32_t num_layer = params.num_layer;

//     bool enable_softmax = true;
//     uint32_t ddr_addr_L1_inA  = params.ddr_offset_512b_inA_L1;
//     uint32_t ddr_addr_L1_inB  = params.ddr_offset_512b_inB_L1;
//     uint32_t ddr_addr_L2_inB  = params.ddr_offset_512b_inB_L2;
//     uint32_t ddr_addr_L2_outC = params.ddr_offset_512b_outC_L2;




//     inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
//     inst_header.inst_val.mask = false;
//     inst_header.inst_val.is_last_mOP = false;
//     inst_header.inst_val.mop_buffer_window_size = 8;
//     inst_header.inst_val.repeat_num = num_layer;
//     inst_sequence[count4B++] = inst_header.raw_32b;
//     printHeaderInst(inst_header.inst_val, countInstPkt);
//     countInstPkt ++;
//     // tile 0, upper left
//     inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
//     for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
//     // tile 1, upper right
//     inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
//     for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
//     // tile 2, low left
//     inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
//     for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
//     // tile 3, low right
//     inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
//     for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}
//     inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
//     inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC0_to_computecore4 = true;
//     inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
//     inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
//     for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i]; }
//     inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
//     inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
//     inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC1_to_computecore4 = true;
//     inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
//     for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 
//     inst_mesh_A.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
//     inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC2_to_computecore5 = true;
//     inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;    
//     for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];    }
//     inst_mesh_A.inst_val.size = 1 * 2 * 32 * 32 /2 ; 
//     inst_mesh_A.inst_val.memcoreA0_to_computecore0 = false;
//     inst_mesh_A.inst_val.memcoreA0_to_computecore1 = false; 
//     inst_mesh_A.inst_val.memcoreA1_to_computecore2 = false;
//     inst_mesh_A.inst_val.memcoreA1_to_computecore3 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreA2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
//     inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
//     inst_mesh_A.inst_val.memcoreC3_to_computecore5 = true;   
//     for (int i = 0; i < CNT4B_MESH_A ; i++) {inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];} 

// }



// void generate_instruction_fused384_meshB( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsFusedLayer & params) {

//     union_inst_header inst_header;
//     union_inst_ddr inst_ddr;
//     union_inst_memcore_A inst_memcore_A;
//     union_inst_memcore_B inst_memcore_B;
//     union_inst_memcore_C inst_memcore_C;
//     union_inst_mesh_A inst_mesh_A;
//     union_inst_mesh_B inst_mesh_B;
//     uint32_t num_layer = params.num_layer;

//     bool enable_softmax = true;
//     uint32_t ddr_addr_L1_inA  = params.ddr_offset_512b_inA_L1;
//     uint32_t ddr_addr_L1_inB  = params.ddr_offset_512b_inB_L1;
//     uint32_t ddr_addr_L2_inB  = params.ddr_offset_512b_inB_L2;
//     uint32_t ddr_addr_L2_outC = params.ddr_offset_512b_outC_L2;



//     inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
//     inst_header.inst_val.mask = false;
//     inst_header.inst_val.is_last_mOP = false;
//     inst_header.inst_val.mop_buffer_window_size = 6;
//     inst_header.inst_val.repeat_num = num_layer;
//     inst_sequence[count4B++] = inst_header.raw_32b;
//     printHeaderInst(inst_header.inst_val, countInstPkt);
//     countInstPkt ++;
//     inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
//     inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
//     inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
//     inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
//     inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
//     for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
//     inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
//     inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
//     inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
//     inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
//     inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
//     for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
//     inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
//     inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
//     inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
//     inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
//     for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
//     inst_mesh_B.inst_val.size = 1 * 1 * 32 * 32 /2 ;
//     inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
//     inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
//     inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
//     inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
//     for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
//     inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
//     inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
//     inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
//     inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore4 = true;
//     inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
//     for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}
//     inst_mesh_B.inst_val.size =  1 * 3 * 32 * 32 / 2;
//     inst_mesh_B.inst_val.memcore0_to_computecore0 = false;
//     inst_mesh_B.inst_val.memcore0_to_computecore2 = false;
//     inst_mesh_B.inst_val.memcore0_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore1 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore3 = false;
//     inst_mesh_B.inst_val.memcore1_to_computecore5 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
//     inst_mesh_B.inst_val.memcore2_to_computecore5 = true;
//     for (int i = 0; i < CNT4B_MESH_B ; i++) {inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}



// }

