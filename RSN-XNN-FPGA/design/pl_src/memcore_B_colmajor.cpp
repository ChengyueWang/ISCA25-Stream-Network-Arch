#include "memcore_B_colmajor.h"

ap_uint<64> concat_32b_to_64b_coreB_colmajor(ap_uint<32> in0, ap_uint<32> in1) {
  ap_uint<64> out;
  out(31, 0) = in0;
  out(63, 32) = in1;
  return out;
}

void loadB_from_dramStream_colmajor(

    ap_uint<32> buf_B[BUFBCORE2_DIM1][BUFBCORE2_DIM2], bool enable_load_from_dram,
    ap_uint<10> size_dim1, ap_uint<10> size_dim2, hls::stream<ap_uint<1024>> &stream_from_dramB) {

  if (enable_load_from_dram) {


    // block size 128x64
    for (uint16_t dim1 = 0; dim1 < size_dim1 / 128; dim1++) {
      for (uint16_t dim2 = 0; dim2 < size_dim2 / 64; dim2++) {
        for (uint16_t block_r = 0; block_r < (128 / 2); block_r++) {
          for (uint16_t block_c = 0; block_c < (64 / 16); block_c++) {
// each iteration get 16 32-bit data from dram at row0, and 16 32-bit from row1
#pragma HLS PIPELINE II = 1
            ap_uint<1024> data_1024b;
            data_1024b = stream_from_dramB.read();

            for (uint8_t i = 0; i < 16; i++) {
              buf_B[dim1 * 128 + block_r * 2][dim2 * 64 + block_c * 16 + i] =
                  data_1024b(32 * i + 31, 32 * i);
              buf_B[dim1 * 128 + block_r * 2 + 1][dim2 * 64 + block_c * 16 + i] =
                  data_1024b(32 * i + 31 + 512, 32 * i + 512);
            }
          }
        }
      }
    }

  }

}

void sendB_to_aie_colmajor(

    ap_uint<32> buf_B[BUFBCORE2_DIM1][BUFBCORE2_DIM2], bool enable_sendrecv_aie, uint16_t size_dim1,
    uint16_t size_dim2, ap_uint<3> compute_tile_access_A, ap_uint<3> compute_tile_access_B,
    ap_uint<3> compute_tile_access_K, hls::stream<ap_uint<64>> &to_computeCore0_B0_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_B0_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_B0_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_B0_CASC3,
    hls::stream<ap_uint<64>> &to_computeCore0_B1_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_B1_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_B1_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_B1_CASC3,
    hls::stream<ap_uint<64>> &to_computeCore0_B2_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_B2_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_B2_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_B2_CASC3,
    hls::stream<ap_uint<64>> &to_computeCore0_B3_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_B3_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_B3_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_B3_CASC3) {


  if (enable_sendrecv_aie) {
    for (uint16_t reuse_a = 0; reuse_a < compute_tile_access_A; reuse_a++) {
      for (uint16_t reuse_b = 0; reuse_b < compute_tile_access_B * 128; reuse_b += 128) {
        for (uint16_t reuse_k = 0; reuse_k < compute_tile_access_K * 128; reuse_k += 128) {
          for (uint16_t dim2 = 0; dim2 < 128; dim2 = dim2 + 32) {
            for (uint16_t dim1 = 0; dim1 < 128; dim1 = dim1 + 4) {
              for (uint16_t col8_id = 0; col8_id < 32;
                   col8_id = col8_id + 8) {  // 2 columns of 4x4 blocks

                uint16_t row_addr_op1 = reuse_k;
                uint16_t row_addr = row_addr_op1 + dim1;
                uint16_t col_addr_op1 = reuse_b;
                uint16_t col_addr_op2 = col8_id + dim2;
                uint16_t col_addr = col_addr_op1 + col_addr_op2;

#pragma HLS bind_op variable = row_addr_op1 op = mul impl = fabric
#pragma HLS bind_op variable = row_addr op = add impl = fabric
#pragma HLS bind_op variable = col_addr_op1 op = mul impl = fabric
#pragma HLS bind_op variable = col_addr_op2 op = add impl = fabric
#pragma HLS bind_op variable = col_addr op = add impl = fabric

#pragma HLS PIPELINE II = 1
                ap_uint<64> data_B0_casc0, data_B0_casc1, data_B0_casc2, data_B0_casc3;
                ap_uint<64> data_B1_casc0, data_B1_casc1, data_B1_casc2, data_B1_casc3;
                ap_uint<64> data_B2_casc0, data_B2_casc1, data_B2_casc2, data_B2_casc3;
                ap_uint<64> data_B3_casc0, data_B3_casc1, data_B3_casc2, data_B3_casc3;

                if (col_addr < 64) {


                  data_B0_casc0 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 0][col_addr + 0], buf_B[row_addr + 0][col_addr + 4 + 0]);
                  data_B0_casc1 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 1][col_addr + 0], buf_B[row_addr + 1][col_addr + 4 + 0]);
                  data_B0_casc2 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 2][col_addr + 0], buf_B[row_addr + 2][col_addr + 4 + 0]);
                  data_B0_casc3 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 3][col_addr + 0], buf_B[row_addr + 3][col_addr + 4 + 0]);
                  data_B1_casc0 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 0][col_addr + 1], buf_B[row_addr + 0][col_addr + 4 + 1]);
                  data_B1_casc1 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 1][col_addr + 1], buf_B[row_addr + 1][col_addr + 4 + 1]);
                  data_B1_casc2 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 2][col_addr + 1], buf_B[row_addr + 2][col_addr + 4 + 1]);
                  data_B1_casc3 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 3][col_addr + 1], buf_B[row_addr + 3][col_addr + 4 + 1]);
                  data_B2_casc0 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 0][col_addr + 2], buf_B[row_addr + 0][col_addr + 4 + 2]);
                  data_B2_casc1 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 1][col_addr + 2], buf_B[row_addr + 1][col_addr + 4 + 2]);
                  data_B2_casc2 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 2][col_addr + 2], buf_B[row_addr + 2][col_addr + 4 + 2]);
                  data_B2_casc3 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 3][col_addr + 2], buf_B[row_addr + 3][col_addr + 4 + 2]);
                  data_B3_casc0 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 0][col_addr + 3], buf_B[row_addr + 0][col_addr + 4 + 3]);
                  data_B3_casc1 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 1][col_addr + 3], buf_B[row_addr + 1][col_addr + 4 + 3]);
                  data_B3_casc2 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 2][col_addr + 3], buf_B[row_addr + 2][col_addr + 4 + 3]);
                  data_B3_casc3 = concat_32b_to_64b_coreB_colmajor(
                      buf_B[row_addr + 3][col_addr + 3], buf_B[row_addr + 3][col_addr + 4 + 3]);
                } else {

                  UNION_FP_UINT32 zero;
                  zero.float_val = 0;
                  ap_uint<64> two_zeros;
                  two_zeros(31, 0) = zero.uint32_val;
                  two_zeros(63, 32) = zero.uint32_val;
                  data_B0_casc0 = two_zeros;
                  data_B0_casc1 = two_zeros;
                  data_B0_casc2 = two_zeros;
                  data_B0_casc3 = two_zeros;
                  data_B1_casc0 = two_zeros;
                  data_B1_casc1 = two_zeros;
                  data_B1_casc2 = two_zeros;
                  data_B1_casc3 = two_zeros;
                  data_B2_casc0 = two_zeros;
                  data_B2_casc1 = two_zeros;
                  data_B2_casc2 = two_zeros;
                  data_B2_casc3 = two_zeros;
                  data_B3_casc0 = two_zeros;
                  data_B3_casc1 = two_zeros;
                  data_B3_casc2 = two_zeros;
                  data_B3_casc3 = two_zeros;
                }

                to_computeCore0_B0_CASC0.write(data_B0_casc0);
                to_computeCore0_B0_CASC1.write(data_B0_casc1);
                to_computeCore0_B0_CASC2.write(data_B0_casc2);
                to_computeCore0_B0_CASC3.write(data_B0_casc3);
                to_computeCore0_B1_CASC0.write(data_B1_casc0);
                to_computeCore0_B1_CASC1.write(data_B1_casc1);
                to_computeCore0_B1_CASC2.write(data_B1_casc2);
                to_computeCore0_B1_CASC3.write(data_B1_casc3);
                to_computeCore0_B2_CASC0.write(data_B2_casc0);
                to_computeCore0_B2_CASC1.write(data_B2_casc1);
                to_computeCore0_B2_CASC2.write(data_B2_casc2);
                to_computeCore0_B2_CASC3.write(data_B2_casc3);
                to_computeCore0_B3_CASC0.write(data_B3_casc0);
                to_computeCore0_B3_CASC1.write(data_B3_casc1);
                to_computeCore0_B3_CASC2.write(data_B3_casc2);
                to_computeCore0_B3_CASC3.write(data_B3_casc3);
              }
            }
          }
        }
      }
    }
  }

}

void memcore_B_colmajor(

    hls::stream<uop_memcore_B_type> &stream_uOP_memcore_B,
    hls::stream<ap_uint<1024>> &stream_from_dramB,

    hls::stream<ap_uint<64>> &to_computeCore0_B0_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_B0_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_B0_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_B0_CASC3,

    hls::stream<ap_uint<64>> &to_computeCore0_B1_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_B1_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_B1_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_B1_CASC3,

    hls::stream<ap_uint<64>> &to_computeCore0_B2_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_B2_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_B2_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_B2_CASC3,

    hls::stream<ap_uint<64>> &to_computeCore0_B3_CASC0,
    hls::stream<ap_uint<64>> &to_computeCore0_B3_CASC1,
    hls::stream<ap_uint<64>> &to_computeCore0_B3_CASC2,
    hls::stream<ap_uint<64>> &to_computeCore0_B3_CASC3) {

  ap_uint<32> buf0_B[BUFBCORE2_DIM1][BUFBCORE2_DIM2];
  ap_uint<32> buf1_B[BUFBCORE2_DIM1][BUFBCORE2_DIM2];

#pragma HLS bind_storage variable = buf0_B type = RAM_T2P impl = BRAM
#pragma HLS ARRAY_PARTITION variable = buf0_B dim = 1 cyclic factor = 2
#pragma HLS ARRAY_PARTITION variable = buf0_B dim = 2 cyclic factor = 8
#pragma HLS bind_storage variable = buf1_B type = RAM_T2P impl = BRAM
#pragma HLS ARRAY_PARTITION variable = buf1_B dim = 1 cyclic factor = 2
#pragma HLS ARRAY_PARTITION variable = buf1_B dim = 2 cyclic factor = 8



  bool is_computing_buf1 = 0;

  uop_memcore_B_type uOP;
  bool is_last_uOP = false;
WHILE_LOOP:
  while (is_last_uOP == false) {
    uOP = stream_uOP_memcore_B.read();

    is_last_uOP = uOP.is_last_uOP;
    bool enable_load_from_dram = uOP.enable_load_from_dram;
    bool enable_send_to_aie = uOP.enable_send_to_aie;

    ap_uint<10> one_mem_tile_dim1 = uOP.one_mem_tile_dim1;
    ap_uint<10> one_mem_tile_dim2 = uOP.one_mem_tile_dim2;
    ap_uint<3> compute_tile_access_A = uOP.compute_tile_access_A;
    ap_uint<3> compute_tile_access_B = uOP.compute_tile_access_B;
    ap_uint<3> compute_tile_access_K = uOP.compute_tile_access_K;

    // bool is_computing_buf1 = uOP.is_computing_buf1;
    uint16_t one_compute_tile_dim1 = 128;
    uint16_t one_compute_tile_dim2 = 128;

    if (is_computing_buf1 == 1) {
      sendB_to_aie_colmajor(

          buf1_B, enable_send_to_aie, one_compute_tile_dim1, one_compute_tile_dim2,
          compute_tile_access_A, compute_tile_access_B, compute_tile_access_K,
          to_computeCore0_B0_CASC0, to_computeCore0_B0_CASC1, to_computeCore0_B0_CASC2,
          to_computeCore0_B0_CASC3, to_computeCore0_B1_CASC0, to_computeCore0_B1_CASC1,
          to_computeCore0_B1_CASC2, to_computeCore0_B1_CASC3, to_computeCore0_B2_CASC0,
          to_computeCore0_B2_CASC1, to_computeCore0_B2_CASC2, to_computeCore0_B2_CASC3,
          to_computeCore0_B3_CASC0, to_computeCore0_B3_CASC1, to_computeCore0_B3_CASC2,
          to_computeCore0_B3_CASC3);
      loadB_from_dramStream_colmajor(

          buf0_B, enable_load_from_dram, one_mem_tile_dim1, one_mem_tile_dim2, stream_from_dramB);
    } else {
      sendB_to_aie_colmajor(

          buf0_B, enable_send_to_aie, one_compute_tile_dim1, one_compute_tile_dim2,
          compute_tile_access_A, compute_tile_access_B, compute_tile_access_K,
          to_computeCore0_B0_CASC0, to_computeCore0_B0_CASC1, to_computeCore0_B0_CASC2,
          to_computeCore0_B0_CASC3, to_computeCore0_B1_CASC0, to_computeCore0_B1_CASC1,
          to_computeCore0_B1_CASC2, to_computeCore0_B1_CASC3, to_computeCore0_B2_CASC0,
          to_computeCore0_B2_CASC1, to_computeCore0_B2_CASC2, to_computeCore0_B2_CASC3,
          to_computeCore0_B3_CASC0, to_computeCore0_B3_CASC1, to_computeCore0_B3_CASC2,
          to_computeCore0_B3_CASC3);
      loadB_from_dramStream_colmajor(

          buf1_B, enable_load_from_dram, one_mem_tile_dim1, one_mem_tile_dim2, stream_from_dramB);
    }

    if (is_computing_buf1 == 1) {
      is_computing_buf1 = 0;
    } else {
      is_computing_buf1 = 1;
    }
  }


}
