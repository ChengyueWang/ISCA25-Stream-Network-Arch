#include "memcore_A.h"

ap_uint<64> concat_32b_to_64b_coreA(ap_uint<32> in0, ap_uint<32> in1) {
  ap_uint<64> out;
  out(31, 0) = in0;
  out(63, 32) = in1;
  return out;
}

void loadA_from_dramStream(
#ifdef SW_EMU_PRINT
    int core_id,
#endif
    ap_uint<32> buf_A[BUFA_DIM1][BUFA_DIM2], bool enable_load_from_dram, ap_uint<9> size_dim1,
    ap_uint<8> size_dim2, hls::stream<ap_uint<1024>> &stream_from_dramA) {

#ifdef SW_EMU_PRINT
  std::ofstream outFile(
      "/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/memcoreA" +
          std::to_string(core_id) + "_loadA_from_dramStream.txt",
      std::ios_base::app);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file for writing." << std::endl;
  }
  outFile << "ENTER loadA_from_dramStream ==========================   ";
#endif
  if (enable_load_from_dram) {
#ifdef SW_EMU_PRINT
    // initialize the buffer
    for (uint16_t dim1 = 0; dim1 < BUFA_DIM1; dim1++) {
      for (uint16_t dim2 = 0; dim2 < BUFA_DIM2; dim2++) {
        buf_A[dim1][dim2] = 0;
      }
    }
#endif

    // block size 128x64
    for (uint16_t dim1 = 0; dim1 < size_dim1 / 128; dim1++) {
      for (uint16_t dim2 = 0; dim2 < size_dim2 / 64; dim2++) {
        for (uint16_t block_r = 0; block_r < (128 / 2); block_r++) {
          for (uint16_t block_c = 0; block_c < (64 / 16); block_c++) {
// each iteration get 16 32-bit data from dram at row0, and 16 32-bit from row1
#pragma HLS PIPELINE II = 1
            ap_uint<1024> data_1024b = stream_from_dramA.read();
#ifdef SW_EMU_PRINT
            for (int word = 0; word < 16; word++) {  // outFile
              UNION_FP_UINT32 temp_union;
              temp_union.uint32_val = data_1024b(word * 32 + 31, word * 32);  // outFile
              outFile << temp_union.float_val << " ";
            }
            outFile << std::endl;
#endif
            for (uint16_t i = 0; i < 16; i++) {
              buf_A[dim1 * 128 + block_r * 2][dim2 * 64 + block_c * 16 + i] =
                  data_1024b(32 * i + 31, 32 * i);
              buf_A[dim1 * 128 + block_r * 2 + 1][dim2 * 64 + block_c * 16 + i] =
                  data_1024b(32 * i + 31 + 512, 32 * i + 512);
            }
          }
        }
      }
    }

#ifdef SW_EMU_PRINT
    // Print matrix size
    outFile << "Size: (" << BUFA_DIM1 << ", " << BUFA_DIM2 << ")\n";
    // Print column headers
    outFile << "   ";  // Indentation for row headers
    for (int j = 0; j < BUFA_DIM2; j++) {
      outFile << std::setw(3) << j;
    }
    outFile << "\n";

    // Print matrix data with row headers
    for (int i = 0; i < BUFA_DIM1; i++) {
      outFile << std::setw(3) << i;  // Row header
      for (int j = 0; j < BUFA_DIM2; j++) {
        UNION_FP_UINT32 temp_union;
        temp_union.uint32_val = buf_A[i][j];
        outFile << std::setw(3) << std::fixed << std::setprecision(0) << temp_union.float_val;
      }
      outFile << "\n";
    }
#endif
  }

#ifdef SW_EMU_PRINT
  outFile << "EXIT loadA_from_dramStream   ==========================   ";
  outFile.close();
#endif
}

void sendA_to_aie(
#ifdef SW_EMU_PRINT
    int core_id,
#endif
    ap_uint<32> buf_A[BUFA_DIM1][BUFA_DIM2], bool enable_sendrecv_aie, uint16_t size_dim1,
    uint16_t size_dim2, ap_uint<3> compute_tile_access_A, ap_uint<3> compute_tile_access_B,
    hls::stream<ap_uint<64>> &to_computeCore0_A0_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_A0_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_A0_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_A0_CASC3,
    hls::stream<ap_uint<64>> &to_computeCore0_A1_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_A1_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_A1_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_A1_CASC3,
    hls::stream<ap_uint<64>> &to_computeCore0_A2_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_A2_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_A2_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_A2_CASC3,
    hls::stream<ap_uint<64>> &to_computeCore0_A3_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_A3_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_A3_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_A3_CASC3) {
#ifdef SW_EMU_PRINT
  std::ofstream outFile(
      "/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/memcoreA" +
          std::to_string(core_id) + "_sendA_to_aie.txt",
      std::ios_base::app);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file for writing." << std::endl;
  }
#endif

  if (enable_sendrecv_aie) {
    for (uint16_t reuse_a = 0; reuse_a < compute_tile_access_A * 128; reuse_a += 128) {
      for (uint16_t reuse_b = 0; reuse_b < compute_tile_access_B; reuse_b++) {
        for (uint16_t dim1 = 0; dim1 < 128; dim1 = dim1 + 8) {
          for (uint16_t dim2 = 0; dim2 < 128; dim2 = dim2 + 16) {
            for (uint16_t row2_id = 0; row2_id < 8; row2_id = row2_id + 4) {
              for (uint16_t col4_id = 0; col4_id < 16;
                   col4_id = col4_id + 8) {  // 2 columns of 4x4 blocks

                uint16_t row_addr_op1 = reuse_a;
                uint16_t row_addr_op2 = dim1 + row2_id;
                uint16_t row_addr = row_addr_op1 + row_addr_op2;
                uint16_t col_addr = dim2 + col4_id;

#pragma HLS bind_op variable = row_addr_op1 op = mul impl = fabric
#pragma HLS bind_op variable = row_addr_op2 op = add impl = fabric
#pragma HLS bind_op variable = row_addr op = add impl = fabric
#pragma HLS bind_op variable = col_addr op = add impl = fabric

#ifdef SW_EMU_PRINT
                outFile << "row_addr " << row_addr << " col_addr " << col_addr << "  ";
                for (int i = 0; i < 4; i++) {
                  for (int j = 0; j < 8; j++) {
                    UNION_FP_UINT32 temp_union;
                    temp_union.uint32_val = buf_A[row_addr + i][col_addr + j];
                    outFile << temp_union.float_val << " ";
                  }
                }
                outFile << std::endl;
#endif

#pragma HLS PIPELINE II = 1
                ap_uint<64> data_A0_casc0, data_A0_casc1, data_A0_casc2, data_A0_casc3;
                ap_uint<64> data_A1_casc0, data_A1_casc1, data_A1_casc2, data_A1_casc3;
                ap_uint<64> data_A2_casc0, data_A2_casc1, data_A2_casc2, data_A2_casc3;
                ap_uint<64> data_A3_casc0, data_A3_casc1, data_A3_casc2, data_A3_casc3;

                data_A0_casc0 = concat_32b_to_64b_coreA(buf_A[row_addr + 0][col_addr + 0],
                                                        buf_A[row_addr + 0][col_addr + 4 + 0]);
                data_A0_casc1 = concat_32b_to_64b_coreA(buf_A[row_addr + 0][col_addr + 1],
                                                        buf_A[row_addr + 0][col_addr + 4 + 1]);
                data_A0_casc2 = concat_32b_to_64b_coreA(buf_A[row_addr + 0][col_addr + 2],
                                                        buf_A[row_addr + 0][col_addr + 4 + 2]);
                data_A0_casc3 = concat_32b_to_64b_coreA(buf_A[row_addr + 0][col_addr + 3],
                                                        buf_A[row_addr + 0][col_addr + 4 + 3]);
                data_A1_casc0 = concat_32b_to_64b_coreA(buf_A[row_addr + 1][col_addr + 0],
                                                        buf_A[row_addr + 1][col_addr + 4 + 0]);
                data_A1_casc1 = concat_32b_to_64b_coreA(buf_A[row_addr + 1][col_addr + 1],
                                                        buf_A[row_addr + 1][col_addr + 4 + 1]);
                data_A1_casc2 = concat_32b_to_64b_coreA(buf_A[row_addr + 1][col_addr + 2],
                                                        buf_A[row_addr + 1][col_addr + 4 + 2]);
                data_A1_casc3 = concat_32b_to_64b_coreA(buf_A[row_addr + 1][col_addr + 3],
                                                        buf_A[row_addr + 1][col_addr + 4 + 3]);
                data_A2_casc0 = concat_32b_to_64b_coreA(buf_A[row_addr + 2][col_addr + 0],
                                                        buf_A[row_addr + 2][col_addr + 4 + 0]);
                data_A2_casc1 = concat_32b_to_64b_coreA(buf_A[row_addr + 2][col_addr + 1],
                                                        buf_A[row_addr + 2][col_addr + 4 + 1]);
                data_A2_casc2 = concat_32b_to_64b_coreA(buf_A[row_addr + 2][col_addr + 2],
                                                        buf_A[row_addr + 2][col_addr + 4 + 2]);
                data_A2_casc3 = concat_32b_to_64b_coreA(buf_A[row_addr + 2][col_addr + 3],
                                                        buf_A[row_addr + 2][col_addr + 4 + 3]);
                data_A3_casc0 = concat_32b_to_64b_coreA(buf_A[row_addr + 3][col_addr + 0],
                                                        buf_A[row_addr + 3][col_addr + 4 + 0]);
                data_A3_casc1 = concat_32b_to_64b_coreA(buf_A[row_addr + 3][col_addr + 1],
                                                        buf_A[row_addr + 3][col_addr + 4 + 1]);
                data_A3_casc2 = concat_32b_to_64b_coreA(buf_A[row_addr + 3][col_addr + 2],
                                                        buf_A[row_addr + 3][col_addr + 4 + 2]);
                data_A3_casc3 = concat_32b_to_64b_coreA(buf_A[row_addr + 3][col_addr + 3],
                                                        buf_A[row_addr + 3][col_addr + 4 + 3]);

                to_computeCore0_A0_CASC0.write(data_A0_casc0);
                to_computeCore0_A0_CASC1.write(data_A0_casc1);
                to_computeCore0_A0_CASC2.write(data_A0_casc2);
                to_computeCore0_A0_CASC3.write(data_A0_casc3);
                to_computeCore0_A1_CASC0.write(data_A1_casc0);
                to_computeCore0_A1_CASC1.write(data_A1_casc1);
                to_computeCore0_A1_CASC2.write(data_A1_casc2);
                to_computeCore0_A1_CASC3.write(data_A1_casc3);
                to_computeCore0_A2_CASC0.write(data_A2_casc0);
                to_computeCore0_A2_CASC1.write(data_A2_casc1);
                to_computeCore0_A2_CASC2.write(data_A2_casc2);
                to_computeCore0_A2_CASC3.write(data_A2_casc3);
                to_computeCore0_A3_CASC0.write(data_A3_casc0);
                to_computeCore0_A3_CASC1.write(data_A3_casc1);
                to_computeCore0_A3_CASC2.write(data_A3_casc2);
                to_computeCore0_A3_CASC3.write(data_A3_casc3);
              }
            }
          }
        }
      }
    }
  }
#ifdef SW_EMU_PRINT
  outFile << "EXIT sendA_to_aie   ==========================   ";
  outFile.close();
#endif
}

void memcore_A(
#ifdef SW_EMU_PRINT
    int core_id,
#endif

    hls::stream<uop_memcore_A_type> &stream_uOP_memcore_A,
    hls::stream<ap_uint<1024>> &stream_from_dramA,

    hls::stream<ap_uint<64>> &to_computeCore0_A0_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_A0_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_A0_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_A0_CASC3,

    hls::stream<ap_uint<64>> &to_computeCore0_A1_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_A1_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_A1_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_A1_CASC3,

    hls::stream<ap_uint<64>> &to_computeCore0_A2_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_A2_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_A2_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_A2_CASC3,

    hls::stream<ap_uint<64>> &to_computeCore0_A3_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_A3_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_A3_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_A3_CASC3) {

  ap_uint<32> buf0_A[BUFA_DIM1][BUFA_DIM2];
  ap_uint<32> buf1_A[BUFA_DIM1][BUFA_DIM2];

#pragma HLS bind_storage variable = buf0_A type = RAM_T2P impl = BRAM
#pragma HLS ARRAY_PARTITION variable = buf0_A dim = 1 cyclic factor = 2
#pragma HLS ARRAY_PARTITION variable = buf0_A dim = 2 cyclic factor = 8
#pragma HLS bind_storage variable = buf1_A type = RAM_T2P impl = BRAM
#pragma HLS ARRAY_PARTITION variable = buf1_A dim = 1 cyclic factor = 2
#pragma HLS ARRAY_PARTITION variable = buf1_A dim = 2 cyclic factor = 8

  bool is_computing_buf1 = 0;

  uop_memcore_A_type uOP;
  bool is_last_uOP = false;
WHILE_LOOP:
  while (is_last_uOP == false) {
    uOP = stream_uOP_memcore_A.read();
    is_last_uOP = uOP.is_last_uOP;

    bool enable_load_from_dram = uOP.enable_load_from_dram;
    bool enable_send_to_aie = uOP.enable_send_to_aie;
    ap_uint<9> one_mem_tile_dim1 = uOP.one_mem_tile_dim1;
    ap_uint<8> one_mem_tile_dim2 = uOP.one_mem_tile_dim2;
    ap_uint<3> compute_tile_access_A = uOP.compute_tile_access_A;
    ap_uint<3> compute_tile_access_B = uOP.compute_tile_access_B;

    // bool is_computing_buf1 = uOP.is_computing_buf1;
    uint16_t one_compute_tile_dim1 = 128;
    uint16_t one_compute_tile_dim2 = 128;

    if (is_computing_buf1 == 1) {
      // first send (write) then read; otherwise simulation will be blocked
      sendA_to_aie(
#ifdef SW_EMU_PRINT
          core_id,
#endif
          buf1_A, enable_send_to_aie, one_compute_tile_dim1, one_compute_tile_dim2,
          compute_tile_access_A, compute_tile_access_B, to_computeCore0_A0_CASC0,
          to_computeCore0_A0_CASC1, to_computeCore0_A0_CASC2, to_computeCore0_A0_CASC3,
          to_computeCore0_A1_CASC0, to_computeCore0_A1_CASC1, to_computeCore0_A1_CASC2,
          to_computeCore0_A1_CASC3, to_computeCore0_A2_CASC0, to_computeCore0_A2_CASC1,
          to_computeCore0_A2_CASC2, to_computeCore0_A2_CASC3, to_computeCore0_A3_CASC0,
          to_computeCore0_A3_CASC1, to_computeCore0_A3_CASC2, to_computeCore0_A3_CASC3);
      loadA_from_dramStream(
#ifdef SW_EMU_PRINT
          core_id,
#endif
          buf0_A, enable_load_from_dram, one_mem_tile_dim1, one_mem_tile_dim2, stream_from_dramA);
    } else {
      sendA_to_aie(
#ifdef SW_EMU_PRINT
          core_id,
#endif
          buf0_A, enable_send_to_aie, one_compute_tile_dim1, one_compute_tile_dim2,
          compute_tile_access_A, compute_tile_access_B, to_computeCore0_A0_CASC0,
          to_computeCore0_A0_CASC1, to_computeCore0_A0_CASC2, to_computeCore0_A0_CASC3,
          to_computeCore0_A1_CASC0, to_computeCore0_A1_CASC1, to_computeCore0_A1_CASC2,
          to_computeCore0_A1_CASC3, to_computeCore0_A2_CASC0, to_computeCore0_A2_CASC1,
          to_computeCore0_A2_CASC2, to_computeCore0_A2_CASC3, to_computeCore0_A3_CASC0,
          to_computeCore0_A3_CASC1, to_computeCore0_A3_CASC2, to_computeCore0_A3_CASC3);
      loadA_from_dramStream(
#ifdef SW_EMU_PRINT
          core_id,
#endif
          buf1_A, enable_load_from_dram, one_mem_tile_dim1, one_mem_tile_dim2, stream_from_dramA);
    }

    if (is_computing_buf1 == 1) {
      is_computing_buf1 = 0;
    } else {
      is_computing_buf1 = 1;
    }
  }
}
