/*
Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
SPDX-License-Identifier: MIT
Modifications Copyright (C) 2025 Chengyue Wang
*/

#include "graph.h"

TopGraph G;

#if defined(__AIESIM__) || defined(__X86SIM__)
int main(int argc, char** argv) {
  printf("=========== START AIE simulation ============================================\n");

  printf("Expected cycles for 1 32x32x32: %d\n",
         (AIE_TILE_A * AIE_TILE_B * AIE_TILE_AB) / (8 * 64 / 68));
  printf("Expected cycles for 1 32x16x32: %d\n", (AIE_TILE_A * AIE_TILE_B * 16) / (8 * 64 / 68));

  G.init();

  // B1 B0: a_iter * b_iter
  // B3 B2: k_iter
  // B4 : compute_tile_access_B
  // B5 : enable_norm enable_bias dimb_is_32 dimk_is_32
  // B6 : enable_accum_kiter
  // B7 : print_enable

  uint8_t a_iter = 1;
  uint8_t b_iter = 2;
  uint8_t k_iter = 2;
  uint8_t compute_tile_access_A = 1;
  uint8_t compute_tile_access_B = 1;
  bool enable_norm = 0;
  bool enable_bias = 1;
  bool dimb_is_32 = 1;
  bool dimk_is_32 = 1;
  bool enable_accum_kiter = 0;
  uint8_t print_enable = 1;

  uint32_t opcode = 0x00000000;
  opcode = opcode | (0x0000000F & a_iter);
  opcode = opcode | (0x000000F0 & (b_iter << 4));
  opcode = opcode | (0x00007F00 & (k_iter << 8));  // 7 bits for k_iter
  opcode =
      opcode | (0x00018000 & (compute_tile_access_A << 15));  // 2 bits for compute_tile_access_A
  opcode =
      opcode | (0x000E0000 & (compute_tile_access_B << 17));  // 3 bits for compute_tile_access_B
  opcode = opcode | (0x00100000 & (enable_norm << 20));
  opcode = opcode | (0x00200000 & (enable_bias << 21));
  opcode = opcode | (0x00400000 & (dimb_is_32 << 22));
  opcode = opcode | (0x00800000 & (dimk_is_32 << 23));
  opcode = opcode | (0x01000000 & (enable_accum_kiter << 24));
  opcode = opcode | (0xF0000000 & (print_enable << 28));

  // when use synchronize parementer, the order of G.update and G.run can re ordered freely
  // synchronize:
  // asynchronize:
  // G.wait(); // need to have wait otherwise will Assertion failure

  uint32_t opcode_mem[512];

  G.run(1);

  opcode_mem[0] = 1;
  opcode_mem[1] = opcode;

  for (int core_id = 0; core_id < NUM_CORES; core_id++) {
    for (int dima_id = 0; dima_id < NUM_AIE_DIMA; dima_id++) {
      for (int dimb_id = 0; dimb_id < NUM_AIE_DIMB; dimb_id++) {
        for (int i = 0; i < NUM_AIE_CASC; i++) {
          G.update(G.opcode_mem[core_id][dima_id][dimb_id][i], opcode_mem, 512);
        }
      }
    }
  }

  G.end();

  printf("=========== Stop AIE simulation ============================================\n");

  return 0;
}
#endif
