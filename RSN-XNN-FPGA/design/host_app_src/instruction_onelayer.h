#pragma once

#include "instruction.h"

void generate_instruction_onelayer_coresAB_meshesAB(uint32_t *inst_sequence, uint32_t &count4B,
                                                    uint32_t &countInstPkt, ParamsOneLayer params) {
  uint32_t a_iter = params.a_iter;
  uint32_t b_iter = params.b_iter;
  uint32_t k_iter = params.k_iter;

  union_inst_header inst_header;
  union_inst_ddr inst_ddr;
  union_inst_load_B_dram inst_loadB_dram;
  union_inst_memcore_A inst_memcore_A;
  union_inst_memcore_B inst_memcore_B;
  union_inst_memcore_C inst_memcore_C;
  union_inst_mesh_A inst_mesh_A;
  union_inst_mesh_B inst_mesh_B;

  inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
  inst_header.inst_val.mask = 0b000111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_A.inst_val.enable_load_from_dram = true;
  inst_memcore_A.inst_val.enable_send_to_aie = false;
  inst_memcore_A.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_A.inst_val.one_mem_tile_dim2 = 128;
  inst_memcore_A.inst_val.compute_tile_access_A = false;
  inst_memcore_A.inst_val.compute_tile_access_B = false;
  for (int i = 0; i < CNT4B_MEMCORE_A; i++) {
    inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
  inst_header.inst_val.mask = 0b000111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = k_iter * a_iter * b_iter - 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_A.inst_val.enable_load_from_dram = true;
  inst_memcore_A.inst_val.enable_send_to_aie = true;
  inst_memcore_A.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_A.inst_val.one_mem_tile_dim2 = 128;
  inst_memcore_A.inst_val.compute_tile_access_A = 2;
  inst_memcore_A.inst_val.compute_tile_access_B = 4;
  for (int i = 0; i < CNT4B_MEMCORE_A; i++) {
    inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
  inst_header.inst_val.mask = 0b000111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_A.inst_val.enable_load_from_dram = false;
  inst_memcore_A.inst_val.enable_send_to_aie = true;
  inst_memcore_A.inst_val.one_mem_tile_dim1 = false;
  inst_memcore_A.inst_val.one_mem_tile_dim2 = false;
  inst_memcore_A.inst_val.compute_tile_access_A = 2;
  inst_memcore_A.inst_val.compute_tile_access_B = 4;
  for (int i = 0; i < CNT4B_MEMCORE_A; i++) {
    inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
  inst_header.inst_val.mask = 0b000011;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_B.inst_val.enable_load_from_dram = true;
  inst_memcore_B.inst_val.enable_send_to_aie = false;
  inst_memcore_B.inst_val.is_loading_bias = false;
  inst_memcore_B.inst_val.enable_transpose = false;
  inst_memcore_B.inst_val.one_mem_tile_dim1 = 128;
  inst_memcore_B.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_B.inst_val.compute_tile_access_A = false;
  inst_memcore_B.inst_val.compute_tile_access_B = false;
  inst_memcore_B.inst_val.compute_tile_access_K = false;
  for (int i = 0; i < CNT4B_MEMCORE_B; i++) {
    inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
  inst_header.inst_val.mask = 0b000011;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = k_iter * a_iter * b_iter - 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_B.inst_val.enable_load_from_dram = true;
  inst_memcore_B.inst_val.enable_send_to_aie = true;
  inst_memcore_B.inst_val.is_loading_bias = false;
  inst_memcore_B.inst_val.enable_transpose = false;
  inst_memcore_B.inst_val.one_mem_tile_dim1 = 128;
  inst_memcore_B.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_B.inst_val.compute_tile_access_A = 2;
  inst_memcore_B.inst_val.compute_tile_access_B = 4;
  inst_memcore_B.inst_val.compute_tile_access_K = 1;
  for (int i = 0; i < CNT4B_MEMCORE_B; i++) {
    inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
  inst_header.inst_val.mask = 0b000011;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_B.inst_val.enable_load_from_dram = false;
  inst_memcore_B.inst_val.enable_send_to_aie = true;
  inst_memcore_B.inst_val.is_loading_bias = false;
  inst_memcore_B.inst_val.enable_transpose = false;
  inst_memcore_B.inst_val.one_mem_tile_dim1 = false;
  inst_memcore_B.inst_val.one_mem_tile_dim2 = false;
  inst_memcore_B.inst_val.compute_tile_access_A = 2;
  inst_memcore_B.inst_val.compute_tile_access_B = 4;
  inst_memcore_B.inst_val.compute_tile_access_K = 1;
  for (int i = 0; i < CNT4B_MEMCORE_B; i++) {
    inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_mesh_A.inst_val.size = k_iter * a_iter * b_iter * 2 * 4 * 32 * 32 / 2;
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
  for (int i = 0; i < CNT4B_MESH_A; i++) {
    inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_mesh_B.inst_val.size = k_iter * a_iter * b_iter * 2 * 4 * 32 * 32 / 2;
  inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
  inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
  inst_mesh_B.inst_val.memcore0_to_computecore4 = true;
  inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
  inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
  inst_mesh_B.inst_val.memcore1_to_computecore5 = true;
  inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
  inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
  for (int i = 0; i < CNT4B_MESH_B; i++) {
    inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];
  }
}

void generate_instruction_onelayer_cores_meshes(uint32_t *inst_sequence, uint32_t &count4B,
                                                uint32_t &countInstPkt, ParamsOneLayer params) {
  uint32_t a_iter = params.a_iter;
  uint32_t b_iter = params.b_iter;
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
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_A.inst_val.enable_load_from_dram = true;
  inst_memcore_A.inst_val.enable_send_to_aie = false;
  inst_memcore_A.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_A.inst_val.one_mem_tile_dim2 = 128;
  inst_memcore_A.inst_val.compute_tile_access_A = false;
  inst_memcore_A.inst_val.compute_tile_access_B = false;
  for (int i = 0; i < CNT4B_MEMCORE_A; i++) {
    inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
  inst_header.inst_val.mask = 0b000111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = k_iter * a_iter * b_iter - 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_A.inst_val.enable_load_from_dram = true;
  inst_memcore_A.inst_val.enable_send_to_aie = true;
  inst_memcore_A.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_A.inst_val.one_mem_tile_dim2 = 128;
  inst_memcore_A.inst_val.compute_tile_access_A = 2;
  inst_memcore_A.inst_val.compute_tile_access_B = 4;
  for (int i = 0; i < CNT4B_MEMCORE_A; i++) {
    inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
  inst_header.inst_val.mask = 0b000111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_A.inst_val.enable_load_from_dram = false;
  inst_memcore_A.inst_val.enable_send_to_aie = true;
  inst_memcore_A.inst_val.one_mem_tile_dim1 = false;
  inst_memcore_A.inst_val.one_mem_tile_dim2 = false;
  inst_memcore_A.inst_val.compute_tile_access_A = 2;
  inst_memcore_A.inst_val.compute_tile_access_B = 4;
  for (int i = 0; i < CNT4B_MEMCORE_A; i++) {
    inst_sequence[count4B++] = inst_memcore_A.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
  inst_header.inst_val.mask = 0b000011;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_B.inst_val.enable_load_from_dram = true;
  inst_memcore_B.inst_val.enable_send_to_aie = false;
  inst_memcore_B.inst_val.is_loading_bias = false;
  inst_memcore_B.inst_val.enable_transpose = false;
  inst_memcore_B.inst_val.one_mem_tile_dim1 = 128;
  inst_memcore_B.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_B.inst_val.compute_tile_access_A = false;
  inst_memcore_B.inst_val.compute_tile_access_B = false;
  inst_memcore_B.inst_val.compute_tile_access_K = false;
  for (int i = 0; i < CNT4B_MEMCORE_B; i++) {
    inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
  inst_header.inst_val.mask = 0b000011;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = k_iter * a_iter * b_iter - 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_B.inst_val.enable_load_from_dram = true;
  inst_memcore_B.inst_val.enable_send_to_aie = true;
  inst_memcore_B.inst_val.is_loading_bias = false;
  inst_memcore_B.inst_val.enable_transpose = false;
  inst_memcore_B.inst_val.one_mem_tile_dim1 = 128;
  inst_memcore_B.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_B.inst_val.compute_tile_access_A = 2;
  inst_memcore_B.inst_val.compute_tile_access_B = 4;
  inst_memcore_B.inst_val.compute_tile_access_K = 1;
  for (int i = 0; i < CNT4B_MEMCORE_B; i++) {
    inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
  inst_header.inst_val.mask = 0b000011;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_B.inst_val.enable_load_from_dram = false;
  inst_memcore_B.inst_val.enable_send_to_aie = true;
  inst_memcore_B.inst_val.is_loading_bias = false;
  inst_memcore_B.inst_val.enable_transpose = false;
  inst_memcore_B.inst_val.one_mem_tile_dim1 = false;
  inst_memcore_B.inst_val.one_mem_tile_dim2 = false;
  inst_memcore_B.inst_val.compute_tile_access_A = 2;
  inst_memcore_B.inst_val.compute_tile_access_B = 4;
  inst_memcore_B.inst_val.compute_tile_access_K = 1;
  for (int i = 0; i < CNT4B_MEMCORE_B; i++) {
    inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_mesh_A.inst_val.size = k_iter * a_iter * b_iter * 2 * 4 * 32 * 32 / 2;
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
  for (int i = 0; i < CNT4B_MESH_A; i++) {
    inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_mesh_B.inst_val.size = k_iter * a_iter * b_iter * 2 * 4 * 32 * 32 / 2;
  inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
  inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
  inst_mesh_B.inst_val.memcore0_to_computecore4 = true;
  inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
  inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
  inst_mesh_B.inst_val.memcore1_to_computecore5 = true;
  inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
  inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
  for (int i = 0; i < CNT4B_MESH_B; i++) {
    inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = false;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = true;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.enable_gelu = enable_gelu;
  inst_memcore_C.inst_val.enable_layer_norm = enable_layer_norm;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = a_iter * b_iter - 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = true;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = true;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.enable_gelu = enable_gelu;
  inst_memcore_C.inst_val.enable_layer_norm = enable_layer_norm;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = true;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = false;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.enable_gelu = enable_gelu;
  inst_memcore_C.inst_val.enable_layer_norm = enable_layer_norm;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }
}

void generate_bias(uint32_t *inst_sequence, uint32_t &count4B, uint32_t &countInstPkt,
                   ParamsOneLayer params) {
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
  countInstPkt++;
  inst_loadB_dram.inst_val.start_address =
      loadB_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_loadB_dram.inst_val.address_offset = 0;
  inst_loadB_dram.inst_val.chunck_size = 512 * b_iter;
  inst_loadB_dram.inst_val.stride_offset = 0;
  inst_loadB_dram.inst_val.chunk_count = 1;
  inst_loadB_dram.inst_val.load_to_memcoreB0 = true;
  inst_loadB_dram.inst_val.load_to_memcoreB1 = false;
  inst_loadB_dram.inst_val.is_loading_bias = true;
  for (int i = 0; i < CNT4B_LOAD_B_DRAM; i++) {
    inst_sequence[count4B++] = inst_loadB_dram.raw_32b[i];
  }
  inst_loadB_dram.inst_val.start_address = loadB_address + 512 * b_iter / 16;
  inst_loadB_dram.inst_val.address_offset = 0;
  inst_loadB_dram.inst_val.chunck_size = 512 * b_iter;
  inst_loadB_dram.inst_val.stride_offset = 0;
  inst_loadB_dram.inst_val.chunk_count = 1;
  inst_loadB_dram.inst_val.load_to_memcoreB0 = false;
  inst_loadB_dram.inst_val.load_to_memcoreB1 = true;
  inst_loadB_dram.inst_val.is_loading_bias = true;
  for (int i = 0; i < CNT4B_LOAD_B_DRAM; i++) {
    inst_sequence[count4B++] = inst_loadB_dram.raw_32b[i];
  }

  // does not enable mop_buffer_window_size for memcores
  inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
  inst_header.inst_val.mask = 0b000011;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_B.inst_val.enable_load_from_dram = true;
  inst_memcore_B.inst_val.enable_send_to_aie = false;
  inst_memcore_B.inst_val.is_loading_bias = true;
  inst_memcore_B.inst_val.enable_transpose = false;
  // size_dim1=16, size_dim2=1 => bias 1024;  b_iter = 1
  // size_dim1=32, size_dim2=1 => bias 2048;  b_iter = 2
  // size_dim1=32, size_dim2=2 => bias 4096;  b_iter = 4

  if (b_iter == 1) {
    inst_memcore_B.inst_val.one_mem_tile_dim1 = 16;
    inst_memcore_B.inst_val.one_mem_tile_dim2 = 1;
  } else if (b_iter == 2) {
    inst_memcore_B.inst_val.one_mem_tile_dim1 = 32;
    inst_memcore_B.inst_val.one_mem_tile_dim2 = 1;
  } else if (b_iter == 4) {
    inst_memcore_B.inst_val.one_mem_tile_dim1 = 32;
    inst_memcore_B.inst_val.one_mem_tile_dim2 = 2;
  } else {
    assert(0);
  }

  inst_memcore_B.inst_val.compute_tile_access_A = false;
  inst_memcore_B.inst_val.compute_tile_access_B = false;
  inst_memcore_B.inst_val.compute_tile_access_K = false;
  for (int i = 0; i < CNT4B_MEMCORE_B; i++) {
    inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
  inst_header.inst_val.mask = 0b000011;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_B.inst_val.enable_load_from_dram = false;
  inst_memcore_B.inst_val.enable_send_to_aie = true;
  inst_memcore_B.inst_val.is_loading_bias = true;
  inst_memcore_B.inst_val.enable_transpose = false;
  inst_memcore_B.inst_val.one_mem_tile_dim1 = false;
  inst_memcore_B.inst_val.one_mem_tile_dim2 = false;
  inst_memcore_B.inst_val.compute_tile_access_A = 1;
  inst_memcore_B.inst_val.compute_tile_access_B = 1;
  inst_memcore_B.inst_val.compute_tile_access_K = 1;
  for (int i = 0; i < CNT4B_MEMCORE_B; i++) {
    inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_mesh_B.inst_val.size =
      1 * 1 * 1 * 1 * 1 * 32 * 32 / 2;  // 1 * 1 * b_iter*1*1*16*8/2 ; // when b_iter == 1 , 1024
                                        // total bias, 1 AIE only got 128 bias
  inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
  inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
  inst_mesh_B.inst_val.memcore0_to_computecore4 = true;
  inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
  inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
  inst_mesh_B.inst_val.memcore1_to_computecore5 = true;
  inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
  inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
  for (int i = 0; i < CNT4B_MESH_B; i++) {
    inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];
  }
}

void generate_instruction_loadB(int a, int b, uint32_t *inst_sequence, uint32_t &count4B,
                                uint32_t &countInstPkt, ParamsOneLayer params) {
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

  loadB_address = params.lpddr_offset_512b_weight;

  loadB_address += b * 128 * 1024 / 16;
  inst_header.inst_val.opcode = OPCODE_LOADB_DRAM;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 2;
  inst_header.inst_val.repeat_num = k_iter;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_loadB_dram.inst_val.start_address =
      loadB_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_loadB_dram.inst_val.address_offset = 128 * 512 * 2 * b_iter / 16;
  inst_loadB_dram.inst_val.chunck_size = 128 * 512;  // 8 tiles, each 128x64
  inst_loadB_dram.inst_val.stride_offset = 0;
  inst_loadB_dram.inst_val.chunk_count = 1;
  inst_loadB_dram.inst_val.load_to_memcoreB0 = true;
  inst_loadB_dram.inst_val.load_to_memcoreB1 = false;
  inst_loadB_dram.inst_val.is_loading_bias = false;
  for (int i = 0; i < CNT4B_LOAD_B_DRAM; i++) {
    inst_sequence[count4B++] = inst_loadB_dram.raw_32b[i];
  }
  inst_loadB_dram.inst_val.start_address = loadB_address + 1 * 128 * 512 / 16;
  inst_loadB_dram.inst_val.address_offset = 128 * 512 * 2 * b_iter / 16;
  inst_loadB_dram.inst_val.chunck_size = 128 * 512;  // 8 tiles, each 128x64
  inst_loadB_dram.inst_val.stride_offset = 0;
  inst_loadB_dram.inst_val.chunk_count = 1;
  inst_loadB_dram.inst_val.load_to_memcoreB0 = false;
  inst_loadB_dram.inst_val.load_to_memcoreB1 = true;
  inst_loadB_dram.inst_val.is_loading_bias = false;
  for (int i = 0; i < CNT4B_LOAD_B_DRAM; i++) {
    inst_sequence[count4B++] = inst_loadB_dram.raw_32b[i];
  }
}

void generate_instruction_loadA(int a, int b, int offset, int repeat_num, uint32_t *inst_sequence,
                                uint32_t &count4B, uint32_t &countInstPkt, ParamsOneLayer params) {
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

  loadA_address = params.ddr_offset_512b_input;
  loadA_address += a * 768 * 128 * k_iter / 16 + offset;
  inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 3;
  inst_header.inst_val.repeat_num = repeat_num;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
}

void generate_instruction_storeC(int a, int b, uint32_t *inst_sequence, uint32_t &count4B,
                                 uint32_t &countInstPkt, ParamsOneLayer params) {
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

  storeC_address = params.ddr_offset_512b_output;
  storeC_address += (a * 768 * 1024 * b_iter + b * 128 * 1024) / 16;
  inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 6;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_ddr.inst_val.start_address = storeC_address + 0;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC0 = true;
  inst_ddr.inst_val.store_from_memcoreC1 = false;
  inst_ddr.inst_val.store_from_memcoreC2 = false;
  inst_ddr.inst_val.store_from_memcoreC3 = false;
  inst_ddr.inst_val.store_from_memcoreC4 = false;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC1 = true;
  inst_ddr.inst_val.store_from_memcoreC2 = false;
  inst_ddr.inst_val.store_from_memcoreC3 = false;
  inst_ddr.inst_val.store_from_memcoreC4 = false;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (4 * b_iter) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC2 = true;
  inst_ddr.inst_val.store_from_memcoreC3 = false;
  inst_ddr.inst_val.store_from_memcoreC4 = false;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (4 * b_iter + 1) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC3 = true;
  inst_ddr.inst_val.store_from_memcoreC4 = false;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (8 * b_iter) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC4 = true;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (8 * b_iter + 1) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
}

void generate_instruction_K8_steady_ddr(int loadA_a, int loadA_b, int storeC_a, int storeC_b,
                                        uint32_t *inst_sequence, uint32_t &count4B,
                                        uint32_t &countInstPkt, ParamsOneLayer params) {
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

  loadA_address = params.ddr_offset_512b_input + loadA_a * 768 * 128 * k_iter / 16;
  storeC_address = params.ddr_offset_512b_output;
  storeC_address += (storeC_a * 768 * 1024 * b_iter + storeC_b * 128 * 1024) / 16;

  inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 2;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 31;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 0;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 0 + 128 * 1024 * b_iter / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 128 * 512 / 16 + 128 * 1024 * b_iter / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + (4 * b_iter) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address =
      storeC_address + (4 * b_iter) * 128 * 512 / 16 + 128 * 1024 * b_iter / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + (4 * b_iter + 1) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC3 = true;
  inst_ddr.inst_val.store_from_memcoreC4 = false;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (8 * b_iter) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC4 = true;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (8 * b_iter + 1) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
}

void generate_instruction_K8_steady_colapsetwolayer_storeCloadA(
    int loadA_a, int loadA_b, int storeC_a, int storeC_b, uint32_t *inst_sequence,
    uint32_t &count4B, uint32_t &countInstPkt, ParamsOneLayer params_storeC,
    ParamsOneLayer params_loadA) {
  uint32_t a_iter = params_storeC.a_iter;
  uint32_t b_iter = params_storeC.b_iter;
  uint32_t k_iter = params_storeC.k_iter;
  uint32_t loadA_address, loadB_address, storeC_address;
  union_inst_header inst_header;
  union_inst_ddr inst_ddr;
  union_inst_load_B_dram inst_loadB_dram;
  union_inst_memcore_A inst_memcore_A;
  union_inst_memcore_B inst_memcore_B;
  union_inst_memcore_C inst_memcore_C;
  union_inst_mesh_A inst_mesh_A;
  union_inst_mesh_B inst_mesh_B;

  loadA_address = params_loadA.ddr_offset_512b_input + loadA_a * 768 * 128 * k_iter / 16;
  storeC_address = params_storeC.ddr_offset_512b_output;
  storeC_address += (storeC_a * 768 * 1024 * b_iter + storeC_b * 128 * 1024) / 16;

  inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 2;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 31;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 0;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 0 + 128 * 1024 * b_iter / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 128 * 512 / 16 + 128 * 1024 * b_iter / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + (4 * b_iter) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address =
      storeC_address + (4 * b_iter) * 128 * 512 / 16 + 128 * 1024 * b_iter / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + (4 * b_iter + 1) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC3 = true;
  inst_ddr.inst_val.store_from_memcoreC4 = false;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (8 * b_iter) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC4 = true;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (8 * b_iter + 1) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
}

void generate_instruction_onelayer_B1_with_bias(uint32_t *inst_sequence, uint32_t &count4B,
                                                uint32_t &countInstPkt, ParamsOneLayer params) {
  uint32_t a_iter = params.a_iter;
  uint32_t b_iter = params.b_iter;
  uint32_t k_iter = params.k_iter;

  assert(params.enable_bias == true);
  assert(b_iter == 1);

  // MOP OPCODE_MEMCORE_B needs the depth of 2
  generate_bias(inst_sequence, count4B, countInstPkt, params);

  // MOP OPCODE_MEMCORE_A needs the depth of 3
  // MOP OPCODE_MEMCORE_B needs the depth of 3
  // MOP OPCODE_MEMCORE_C needs the depth of 3
  generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

  for (int a = 0; a < a_iter; a++) {
    for (int b = 0; b < b_iter; b++) {
      generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
      generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
      generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
    }
  }

  generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}

void generate_instruction_onelayer_overlap_128_512_A4B1K8(uint32_t *inst_sequence,
                                                          uint32_t &count4B, uint32_t &countInstPkt,
                                                          ParamsOneLayer params) {
  uint32_t a_iter = params.a_iter;
  uint32_t b_iter = params.b_iter;
  uint32_t k_iter = params.k_iter;

  assert(a_iter == 4);
  assert(b_iter == 1);
  assert(k_iter == 8);

  if (params.enable_bias == true) {
    generate_bias(inst_sequence, count4B, countInstPkt, params);
  }

  generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

  int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

  a = 0;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
  a = 0;
  b = 0;
  offset = 0;
  repeat_num = k_iter;
  generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt,
                             params);

  a = 1;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
  loadA_a = 1;
  loadA_b = 0;
  storeC_a = 0;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params);

  a = 2;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
  loadA_a = 2;
  loadA_b = 0;
  storeC_a = 1;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params);

  a = 3;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
  loadA_a = 3;
  loadA_b = 0;
  storeC_a = 2;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params);

  a = 3;
  b = 0;
  generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

  // generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}

void generate_instruction_query_key(uint32_t *inst_sequence, uint32_t &count4B,
                                    uint32_t &countInstPkt, ParamsOneLayer params_query,
                                    ParamsOneLayer params_key) {
  uint32_t a_iter = params_query.a_iter;
  uint32_t b_iter = params_query.b_iter;
  uint32_t k_iter = params_query.k_iter;

  union_inst_header inst_header;
  union_inst_ddr inst_ddr;
  union_inst_memcore_C inst_memcore_C;

  assert(a_iter == 4);
  assert(b_iter == 1);
  assert(k_iter == 8);

  assert(params_query.enable_bias == true);

  generate_bias(inst_sequence, count4B, countInstPkt, params_query);

  generate_instruction_onelayer_coresAB_meshesAB(inst_sequence, count4B, countInstPkt,
                                                 params_query);

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = false;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = true;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = a_iter * b_iter;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = true;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = true;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

  a = 0;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_query);
  a = 0;
  b = 0;
  offset = 0;
  repeat_num = k_iter;
  generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt,
                             params_query);

  a = 1;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_query);
  loadA_a = 1;
  loadA_b = 0;
  storeC_a = 0;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_query);

  a = 2;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_query);
  loadA_a = 2;
  loadA_b = 0;
  storeC_a = 1;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_query);

  a = 3;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_query);
  loadA_a = 3;
  loadA_b = 0;
  storeC_a = 2;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_query);

  // a = 3; b = 0; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt,
  // params_query);

  generate_bias(inst_sequence, count4B, countInstPkt, params_key);

  generate_instruction_onelayer_coresAB_meshesAB(inst_sequence, count4B, countInstPkt,
                                                 params_query);

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = a_iter * b_iter - 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = true;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = true;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = true;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = false;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  a = 0;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_key);
  // a = 0; b = 0; offset = 0; repeat_num = k_iter;
  // generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt,
  // params_key);
  loadA_a = 0;
  loadA_b = 0;
  storeC_a = 3;
  storeC_b = 0;
  generate_instruction_K8_steady_colapsetwolayer_storeCloadA(loadA_a, loadA_b, storeC_a, storeC_b,
                                                             inst_sequence, count4B, countInstPkt,
                                                             params_query, params_key);

  a = 1;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_key);
  loadA_a = 1;
  loadA_b = 0;
  storeC_a = 0;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_key);

  a = 2;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_key);
  loadA_a = 2;
  loadA_b = 0;
  storeC_a = 1;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_key);

  a = 3;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_key);
  loadA_a = 3;
  loadA_b = 0;
  storeC_a = 2;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_key);

  a = 3;
  b = 0;
  generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params_key);

  generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}

void generate_instruction_query_key_value(uint32_t *inst_sequence, uint32_t &count4B,
                                          uint32_t &countInstPkt, ParamsOneLayer params_query,
                                          ParamsOneLayer params_key, ParamsOneLayer params_value) {
  uint32_t a_iter = params_query.a_iter;
  uint32_t b_iter = params_query.b_iter;
  uint32_t k_iter = params_query.k_iter;

  union_inst_header inst_header;
  union_inst_ddr inst_ddr;
  union_inst_memcore_C inst_memcore_C;

  assert(a_iter == 4);
  assert(b_iter == 1);
  assert(k_iter == 8);

  assert(params_query.enable_bias == true);

  generate_bias(inst_sequence, count4B, countInstPkt, params_query);

  generate_instruction_onelayer_coresAB_meshesAB(inst_sequence, count4B, countInstPkt,
                                                 params_query);

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = false;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = true;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = a_iter * b_iter;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = true;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = true;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

  a = 0;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_query);
  a = 0;
  b = 0;
  offset = 0;
  repeat_num = k_iter;
  generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt,
                             params_query);

  a = 1;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_query);
  loadA_a = 1;
  loadA_b = 0;
  storeC_a = 0;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_query);

  a = 2;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_query);
  loadA_a = 2;
  loadA_b = 0;
  storeC_a = 1;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_query);

  a = 3;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_query);
  loadA_a = 3;
  loadA_b = 0;
  storeC_a = 2;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_query);

  generate_bias(inst_sequence, count4B, countInstPkt, params_key);
  generate_instruction_onelayer_coresAB_meshesAB(inst_sequence, count4B, countInstPkt, params_key);

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = a_iter * b_iter;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = true;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = true;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  a = 0;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_key);
  // a = 0; b = 0; offset = 0; repeat_num = k_iter;
  // generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt,
  // params_key);
  loadA_a = 0;
  loadA_b = 0;
  storeC_a = 3;
  storeC_b = 0;
  generate_instruction_K8_steady_colapsetwolayer_storeCloadA(loadA_a, loadA_b, storeC_a, storeC_b,
                                                             inst_sequence, count4B, countInstPkt,
                                                             params_query, params_key);

  a = 1;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_key);
  loadA_a = 1;
  loadA_b = 0;
  storeC_a = 0;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_key);

  a = 2;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_key);
  loadA_a = 2;
  loadA_b = 0;
  storeC_a = 1;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_key);

  a = 3;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_key);
  loadA_a = 3;
  loadA_b = 0;
  storeC_a = 2;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_key);

  // a = 3; b = 0; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt,
  // params_key);

  generate_bias(inst_sequence, count4B, countInstPkt, params_value);
  generate_instruction_onelayer_coresAB_meshesAB(inst_sequence, count4B, countInstPkt,
                                                 params_value);

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = a_iter * b_iter - 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = true;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = true;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
  inst_header.inst_val.mask = 0b111111;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 1;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_memcore_C.inst_val.enable_store_to_dram = true;
  inst_memcore_C.inst_val.enable_send_to_aie = false;
  inst_memcore_C.inst_val.enable_recv_from_aie = false;
  inst_memcore_C.inst_val.enable_softmax = false;
  inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
  inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
  inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
  inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
  inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
  inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
  inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
  inst_memcore_C.inst_val.k_iter = k_iter;
  for (int i = 0; i < CNT4B_MEMCORE_C; i++) {
    inst_sequence[count4B++] = inst_memcore_C.raw_32b[i];
  }

  a = 0;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_value);
  // a = 0; b = 0; offset = 0; repeat_num = k_iter;
  // generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt,
  // params_value);
  loadA_a = 0;
  loadA_b = 0;
  storeC_a = 3;
  storeC_b = 0;
  generate_instruction_K8_steady_colapsetwolayer_storeCloadA(loadA_a, loadA_b, storeC_a, storeC_b,
                                                             inst_sequence, count4B, countInstPkt,
                                                             params_key, params_value);

  a = 1;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_value);
  loadA_a = 1;
  loadA_b = 0;
  storeC_a = 0;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_value);

  a = 2;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_value);
  loadA_a = 2;
  loadA_b = 0;
  storeC_a = 1;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_value);

  a = 3;
  b = 0;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params_value);
  loadA_a = 3;
  loadA_b = 0;
  storeC_a = 2;
  storeC_b = 0;
  generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B,
                                     countInstPkt, params_value);

  a = 3;
  b = 0;
  generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params_value);
}

void generate_instruction_onelayer(uint32_t *inst_sequence, uint32_t &count4B,
                                   uint32_t &countInstPkt, ParamsOneLayer params) {
  uint32_t a_iter = params.a_iter;
  uint32_t b_iter = params.b_iter;
  uint32_t k_iter = params.k_iter;

  // assert(b_iter == 1);

  // MOP OPCODE_MEMCORE_B needs the depth of 2
  if (params.enable_bias == true) {
    generate_bias(inst_sequence, count4B, countInstPkt, params);
  }

  generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

  for (int a = 0; a < a_iter; a++) {
    for (int b = 0; b < b_iter; b++) {
      generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
      generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
      generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
    }
  }
}

void generate_instruction_ddr_K8_steady_for_gelu(int loadA_a, int loadA_b, int storeC_a,
                                                 int storeC_b, uint32_t *inst_sequence,
                                                 uint32_t &count4B, uint32_t &countInstPkt,
                                                 ParamsOneLayer params) {
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

  loadA_address = params.ddr_offset_512b_input + loadA_a * 768 * 128 * k_iter / 16;
  storeC_address = params.ddr_offset_512b_output;
  storeC_address += (storeC_a * 768 * 1024 * b_iter + storeC_b * 128 * 1024) / 16;

  inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 2;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
  inst_header.inst_val.mask = false;
  inst_header.inst_val.is_last_mOP = false;
  inst_header.inst_val.mop_buffer_window_size = 31;
  inst_header.inst_val.repeat_num = 1;
  inst_sequence[count4B++] = inst_header.raw_32b;
  printHeaderInst(inst_header.inst_val, countInstPkt);
  countInstPkt++;
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 0;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 0 + 128 * 1024 * b_iter / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  loadA_address = loadA_address + 128 * 128 / 16;
  inst_ddr.inst_val.start_address =
      loadA_address + 0 / 16;  // divided by 16 because 1 address hold 16 32float (512bit)
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each tile 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = loadA_address + k_iter * 256 * 128 * 2 / 16;
  inst_ddr.inst_val.address_offset = 128 * 128 / 16;
  inst_ddr.inst_val.chunck_size = 128 * 128;  // 2 tiles, each 128x64
  inst_ddr.inst_val.stride_offset = 128 * 128 * k_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + 128 * 512 / 16 + 128 * 1024 * b_iter / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + (4 * b_iter) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address =
      storeC_address + (4 * b_iter) * 128 * 512 / 16 + 128 * 1024 * b_iter / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }

  inst_ddr.inst_val.start_address = storeC_address + (4 * b_iter + 1) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC3 = true;
  inst_ddr.inst_val.store_from_memcoreC4 = false;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (8 * b_iter) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  inst_ddr.inst_val.store_from_memcoreC4 = true;
  inst_ddr.inst_val.store_from_memcoreC5 = false;
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
  inst_ddr.inst_val.start_address = storeC_address + (8 * b_iter + 1) * 128 * 512 / 16;
  inst_ddr.inst_val.address_offset = 0;
  inst_ddr.inst_val.chunck_size = 128 * 512;
  inst_ddr.inst_val.stride_offset = 128 * 1024 * b_iter / 16;
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
  for (int i = 0; i < CNT4B_DDR; i++) {
    inst_sequence[count4B++] = inst_ddr.raw_32b[i];
  }
}

void generate_instruction_onelayer_first2load_A4B4K8(uint32_t *inst_sequence, uint32_t &count4B,
                                                     uint32_t &countInstPkt,
                                                     ParamsOneLayer params) {
  uint32_t a_iter = params.a_iter;
  uint32_t b_iter = params.b_iter;
  uint32_t k_iter = params.k_iter;

  assert(params.enable_bias == true);

  generate_bias(inst_sequence, count4B, countInstPkt, params);

  int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

  a = 0;
  b = 0;
  generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
  generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);

  storeC_a = 0;
  storeC_b = 0;

  for (int a = 0; a < 4; a++) {
    for (int b = 0; b < 4; b++) {
      if (a == 0 && b == 0) continue;
      if (a == 3 && b == 3) continue;
      generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
      loadA_a = a;
      loadA_b = b;
      generate_instruction_ddr_K8_steady_for_gelu(loadA_a, loadA_b, storeC_a, storeC_b,
                                                  inst_sequence, count4B, countInstPkt, params);
      // generate_instruction_loadA(loadA_a, loadA_b, 0, k_iter, inst_sequence, count4B,
      // countInstPkt, params); generate_instruction_storeC(storeC_a, storeC_b, inst_sequence,
      // count4B, countInstPkt, params);

      storeC_a = a;
      storeC_b = b;
    }
  }

  a = 3;
  b = 3;
  generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
  loadA_a = 3;
  loadA_b = 3;
  storeC_a = 3;
  storeC_b = 2;
  generate_instruction_ddr_K8_steady_for_gelu(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence,
                                              count4B, countInstPkt, params);

  // generate_instruction_loadA(loadA_a, loadA_b, 0, k_iter, inst_sequence, count4B, countInstPkt,
  // params); generate_instruction_storeC(storeC_a, storeC_b, inst_sequence, count4B, countInstPkt,
  // params);

  generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
}
