/*
Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
SPDX-License-Identifier: MIT
*/

#include <adf.h>

#include <fstream>  // Include for file operations

#include "aie_kernels.h"
#include "system_settings.h"

using namespace adf;

#define NUM_CORES 6
#define NUM_AIE_CASC 4
#define NUM_AIE_DIMA 4
#define NUM_AIE_DIMB 4

extern float chess_storage(% chess_alignof(v8float)) k0_local_buf_1K[1024];  // for bias
extern float chess_storage(% chess_alignof(v8float)) k1_local_buf[128];  // for weight of pre layer
extern float chess_storage(% chess_alignof(v8float)) k2_local_buf[128];  // for weight of pre layer
extern float chess_storage(% chess_alignof(v8float)) k3_local_buf[128];  // for weight of pre layer

class MatMultFloatGraph : public graph {
 private:
  kernel k0, k1, k2, k3;
  parameter
      graph_k0_local_buf_1K;  // 1 local buffer for every cascaed 4 AIE engines, stay in the k0
  parameter graph_k1_local_buf;
  parameter graph_k2_local_buf;
  parameter graph_k3_local_buf;

 public:
  port<input> ina[4];
  port<input> inb[4];
  port<output> outc;
  port<direction::in> opcode_mem[4];

  MatMultFloatGraph() {
    k0 = kernel::create(mm_casc_startk0);
    k1 = kernel::create(mm_casc_middlek1);
    k2 = kernel::create(mm_casc_middlek2);
    k3 = kernel::create(mm_casc_endk3);
    source(k0) = "aie_kernels/mm_casc_startk0.cpp";
    source(k1) = "aie_kernels/mm_casc_middlek1.cpp";
    source(k2) = "aie_kernels/mm_casc_middlek2.cpp";
    source(k3) = "aie_kernels/mm_casc_endk3.cpp";
    runtime<ratio>(k0) = 0.8;
    runtime<ratio>(k1) = 0.8;
    runtime<ratio>(k2) = 0.8;
    runtime<ratio>(k3) = 0.8;

    graph_k0_local_buf_1K = parameter::array(k0_local_buf_1K);
    connect(graph_k0_local_buf_1K, k0);
    location<parameter>(graph_k0_local_buf_1K) = location<kernel>(k0);

    graph_k1_local_buf = parameter::array(k1_local_buf);
    connect(graph_k1_local_buf, k1);
    location<parameter>(graph_k1_local_buf) = location<kernel>(k1);

    graph_k2_local_buf = parameter::array(k2_local_buf);
    connect(graph_k2_local_buf, k2);
    location<parameter>(graph_k2_local_buf) = location<kernel>(k2);

    graph_k3_local_buf = parameter::array(k3_local_buf);
    connect(graph_k3_local_buf, k3);
    location<parameter>(graph_k3_local_buf) = location<kernel>(k3);

    connect net_k0_a(ina[0], k0.in[0]);
    connect net_k1_a(ina[1], k1.in[0]);
    connect net_k2_a(ina[2], k2.in[0]);
    connect net_k3_a(ina[3], k3.in[0]);
    connect net_k0_b(inb[0], k0.in[1]);
    connect net_k1_b(inb[1], k1.in[1]);
    connect net_k2_b(inb[2], k2.in[1]);
    connect net_k3_b(inb[3], k3.in[1]);
    connect net_cascade01(k0.out[0], k1.in[2]);
    connect net_cascade12(k1.out[0], k2.in[2]);
    connect net_cascade23(k2.out[0], k3.in[2]);
    connect net_k3_c(k3.out[0], outc);

    connect<parameter>(opcode_mem[0], k0.in[2]);
    connect<parameter>(opcode_mem[1], k1.in[3]);
    connect<parameter>(opcode_mem[2], k2.in[3]);
    connect<parameter>(opcode_mem[3], k3.in[3]);
  }

  void setLocations(int COL, int ROW, bool from_left_to_right) {
    if (from_left_to_right == true) {
      location<kernel>(k0) = tile(COL, ROW);
      location<buffer>(k0.in[0]) = {address(COL, ROW, 0), address(COL, ROW, 4096)};
      location<buffer>(k0.in[1]) = {address(COL, ROW, 8192), address(COL, ROW, 8192 * 2)};
      location<stack>(k0) = address(COL, ROW, 8192 + 4096);
      location<buffer>(k0.in[2]) = {address(COL, ROW, 8192 * 2 + 4096),
                                    address(COL, ROW, 8192 * 2 + 4096 + 2048)};

      location<kernel>(k1) = tile(COL + 1, ROW);
      location<buffer>(k1.in[0]) = {address(COL + 1, ROW, 0), address(COL + 1, ROW, 4096)};
      location<buffer>(k1.in[1]) = {address(COL + 1, ROW, 8192), address(COL + 1, ROW, 8192 * 2)};
      location<stack>(k1) = address(COL + 1, ROW, 8192 + 4096);
      location<buffer>(k1.in[3]) = {address(COL + 1, ROW, 8192 * 3),
                                    address(COL + 1, ROW, 8192 * 3 + 4096)};

      location<kernel>(k2) = tile(COL + 2, ROW);
      location<buffer>(k2.in[0]) = {address(COL + 2, ROW, 0), address(COL + 2, ROW, 4096)};
      location<buffer>(k2.in[1]) = {address(COL + 2, ROW, 8192), address(COL + 2, ROW, 8192 * 2)};
      location<stack>(k2) = address(COL + 2, ROW, 8192 + 4096);
      location<buffer>(k2.in[3]) = {address(COL + 2, ROW, 8192 * 3),
                                    address(COL + 2, ROW, 8192 * 3 + 4096)};

      location<kernel>(k3) = tile(COL + 3, ROW);
      location<buffer>(k3.in[0]) = {address(COL + 3, ROW, 0), address(COL + 3, ROW, 4096)};
      location<buffer>(k3.in[1]) = {address(COL + 3, ROW, 8192), address(COL + 3, ROW, 8192 * 2)};
      location<buffer>(k3.out[0]) = {address(COL + 3, ROW, 8192 * 3),
                                     address(COL + 3, ROW, 8192 * 3 + 4096)};
      location<stack>(k3) = address(COL + 3, ROW, 8192 + 4096);
      location<buffer>(k3.in[3]) = {address(COL + 3, ROW, 8192 * 2 + 4096),
                                    address(COL + 3, ROW, 8192 * 2 + 4096 + 2048)};
    } else {
      location<kernel>(k0) = tile(COL + 3, ROW);
      location<buffer>(k0.in[0]) = {address(COL + 3, ROW, 0), address(COL + 3, ROW, 4096)};
      location<buffer>(k0.in[1]) = {address(COL + 3, ROW, 8192), address(COL + 3, ROW, 8192 * 2)};
      location<stack>(k0) = address(COL + 3, ROW, 8192 + 4096);
      location<buffer>(k0.in[2]) = {address(COL + 3, ROW, 8192 * 2 + 4096),
                                    address(COL + 3, ROW, 8192 * 2 + 4096 + 2048)};

      location<kernel>(k1) = tile(COL + 2, ROW);
      location<buffer>(k1.in[0]) = {address(COL + 2, ROW, 0), address(COL + 2, ROW, 4096)};
      location<buffer>(k1.in[1]) = {address(COL + 2, ROW, 8192), address(COL + 2, ROW, 8192 * 2)};
      location<stack>(k1) = address(COL + 2, ROW, 8192 + 4096);
      location<buffer>(k1.in[3]) = {address(COL + 2, ROW, 8192 * 3),
                                    address(COL + 2, ROW, 8192 * 3 + 4096)};

      location<kernel>(k2) = tile(COL + 1, ROW);
      location<buffer>(k2.in[0]) = {address(COL + 1, ROW, 0), address(COL + 1, ROW, 4096)};
      location<buffer>(k2.in[1]) = {address(COL + 1, ROW, 8192), address(COL + 1, ROW, 8192 * 2)};
      location<stack>(k2) = address(COL + 1, ROW, 8192 + 4096);
      location<buffer>(k2.in[3]) = {address(COL + 1, ROW, 8192 * 3),
                                    address(COL + 1, ROW, 8192 * 3 + 4096)};

      location<kernel>(k3) = tile(COL, ROW);
      location<buffer>(k3.in[0]) = {address(COL, ROW, 0), address(COL, ROW, 4096)};
      location<buffer>(k3.in[1]) = {address(COL, ROW, 8192), address(COL, ROW, 8192 * 2)};
      location<buffer>(k3.out[0]) = {address(COL, ROW, 8192 * 3),
                                     address(COL, ROW, 8192 * 3 + 4096)};
      location<stack>(k3) = address(COL, ROW, 8192 + 4096);
      location<buffer>(k3.in[3]) = {address(COL, ROW, 8192 * 2 + 4096),
                                    address(COL, ROW, 8192 * 2 + 4096 + 2048)};
    }
  }
};

class TopGraph : public graph {
 public:
  input_plio ina[NUM_CORES][NUM_AIE_DIMA][NUM_AIE_CASC];
  input_plio inb[NUM_CORES][NUM_AIE_DIMB][NUM_AIE_CASC];
  output_plio outc[NUM_CORES][NUM_AIE_DIMA][NUM_AIE_DIMB];

  // how many times to accumulate over the output buffer
  input_port opcode_mem[NUM_CORES][NUM_AIE_DIMA][NUM_AIE_DIMB][NUM_AIE_CASC];

  MatMultFloatGraph FG[NUM_CORES][NUM_AIE_DIMA][NUM_AIE_DIMB];

  TopGraph() {
    for (int core_id = 0; core_id < NUM_CORES; core_id++) {
      for (int dima_id = 0; dima_id < NUM_AIE_DIMA; dima_id++) {
        for (int i = 0; i < NUM_AIE_CASC; i++) {
          ina[core_id][dima_id][i] =
              input_plio::create("Core" + std::to_string(core_id) + "_InA" +
                                     std::to_string(dima_id) + "_CASC" + std::to_string(i),
                                 plio_64_bits, "data/inputa_float.txt");
        }
      }
      for (int dimb_id = 0; dimb_id < NUM_AIE_DIMB; dimb_id++) {
        for (int i = 0; i < NUM_AIE_CASC; i++) {
          inb[core_id][dimb_id][i] =
              input_plio::create("Core" + std::to_string(core_id) + "_InB" +
                                     std::to_string(dimb_id) + "_CASC" + std::to_string(i),
                                 plio_64_bits, "data/inputb_float.txt");
        }
      }
      for (int dima_id = 0; dima_id < NUM_AIE_DIMA; dima_id++) {
        for (int dimb_id = 0; dimb_id < NUM_AIE_DIMB; dimb_id++) {
          outc[core_id][dima_id][dimb_id] =
              output_plio::create("Core" + std::to_string(core_id) + "_OutC" +
                                      std::to_string(dima_id) + std::to_string(dimb_id),
                                  plio_64_bits,
                                  "float_output" + std::to_string(core_id) +
                                      std::to_string(dima_id) + std::to_string(dimb_id) + ".txt");
        }
      }

      for (int dima_id = 0; dima_id < NUM_AIE_DIMA; dima_id++) {
        for (int dimb_id = 0; dimb_id < NUM_AIE_DIMB; dimb_id++) {
          int col = (core_id == 0 ? 0 : 2 + core_id * 8) + (dimb_id % 2 == 0 ? 0 : 4);
          int row = dima_id * 2 + (dimb_id < 2 ? 0 : 1);
          FG[core_id][dima_id][dimb_id].setLocations(col, row, row % 2 == 0);
        }
      }

      for (int dima_id = 0; dima_id < NUM_AIE_DIMA; dima_id++) {
        for (int dimb_id = 0; dimb_id < NUM_AIE_DIMB; dimb_id++) {
          for (int i = 0; i < NUM_AIE_CASC; i++) {
            adf::connect<>(ina[core_id][dima_id][i].out[0], FG[core_id][dima_id][dimb_id].ina[i]);
            adf::connect<>(inb[core_id][dimb_id][i].out[0], FG[core_id][dima_id][dimb_id].inb[i]);
          }
          adf::connect<>(FG[core_id][dima_id][dimb_id].outc, outc[core_id][dima_id][dimb_id].in[0]);
        }
      }
    }

    for (int core_id = 0; core_id < NUM_CORES; core_id++) {
      for (int dima_id = 0; dima_id < NUM_AIE_DIMA; dima_id++) {
        for (int dimb_id = 0; dimb_id < NUM_AIE_DIMB; dimb_id++) {
          for (int i = 0; i < NUM_AIE_CASC; i++) {
            adf::connect<parameter>(opcode_mem[core_id][dima_id][dimb_id][i],
                                    FG[core_id][dima_id][dimb_id].opcode_mem[i]);
          }
        }
      }
    }
  }
};
