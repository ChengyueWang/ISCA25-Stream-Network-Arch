#include "memcore_B.h"

ap_uint<64> concat_32b_to_64b_coreB(ap_uint<32> in0, ap_uint<32> in1) {
  ap_uint<64> out;
  out(31, 0) = in0;
  out(63, 32) = in1;
  return out;
}

void loadB_from_dramStream(

    ap_uint<32> buf_B[BUFB_DIM1][BUFB_DIM2], bool enable_load_from_dram, bool is_loading_bias,
    bool enable_transpose, ap_uint<10> size_dim1, ap_uint<10> size_dim2,
    hls::stream<ap_uint<1024>> &stream_from_ddr, hls::stream<ap_uint<1024>> &stream_from_lpddr) {

  if (enable_load_from_dram) {

    if (is_loading_bias == true) {

      // size_dim1=16, size_dim2=1 => bias 1024;
      // size_dim1=32, size_dim2=1 => bias 2048;
      // size_dim1=32, size_dim2=2 => bias 4096;
      for (uint16_t dim2 = 0; dim2 < size_dim2; dim2++) {    // size_dim2 1, 2, 3, 4
        for (uint16_t dim1 = 0; dim1 < size_dim1; dim1++) {  // size_dim1 16 , 32
#pragma HLS PIPELINE II = 4
          ap_uint<1024> data_1024b_1, data_1024b_2;
          data_1024b_1 = stream_from_lpddr.read();
          for (uint16_t i = 0; i < 16; i++) {
            buf_B[dim1 * 4][dim2 * 32 + i] = data_1024b_1(32 * i + 31, 32 * i);
          }
          data_1024b_2 = stream_from_lpddr.read();
          for (uint16_t i = 0; i < 16; i++) {
            buf_B[dim1 * 4][dim2 * 32 + i + 16] = data_1024b_2(32 * i + 31, 32 * i);
          }
        }
      }
    } else if (enable_transpose == false) {


      // block size 128x64
      for (uint16_t dim1 = 0; dim1 < size_dim1 / 128; dim1++) {
        for (uint16_t dim2 = 0; dim2 < size_dim2 / 64; dim2++) {
          for (uint16_t block_r = 0; block_r < (128 / 2); block_r++) {
            for (uint16_t block_c = 0; block_c < (64 / 16); block_c++) {
// each iteration get 16 32-bit data from dram at row0, and 16 32-bit from row1
#pragma HLS PIPELINE II = 1
              ap_uint<1024> data_1024b;
              data_1024b = stream_from_lpddr.read();

              for (uint16_t i = 0; i < 16; i++) {
                buf_B[dim1 * 128 + block_r * 2][dim2 * 64 + block_c * 16 + i] =
                    data_1024b(32 * i + 31, 32 * i);
                buf_B[dim1 * 128 + block_r * 2 + 1][dim2 * 64 + block_c * 16 + i] =
                    data_1024b(32 * i + 31 + 512, 32 * i + 512);
              }
            }
          }
        }
      }
    } else {

      // block size 128x64
      for (uint16_t dim1 = 0; dim1 < size_dim2 / 128; dim1++) {
        for (uint16_t dim2 = 0; dim2 < size_dim1 / 64; dim2++) {
          for (uint16_t block_r = 0; block_r < (128 / 2); block_r++) {
            for (uint16_t block_c = 0; block_c < (64 / 16); block_c++) {
// each iteration get 16 32-bit data from dram at row0, and 16 32-bit from row1
#pragma HLS PIPELINE II = 1
              ap_uint<1024> data_1024b;
              data_1024b = stream_from_ddr.read();

              for (uint16_t i = 0; i < 16; i++) {
                buf_B[dim2 * 64 + block_c * 16 + i][dim1 * 128 + block_r * 2] =
                    data_1024b(32 * i + 31, 32 * i);
                buf_B[dim2 * 64 + block_c * 16 + i][dim1 * 128 + block_r * 2 + 1] =
                    data_1024b(32 * i + 31 + 512, 32 * i + 512);
              }
            }
          }
        }
      }
    }


  }

}

void sendB_to_aie(

    ap_uint<32> buf_B[BUFB_DIM1][BUFB_DIM2], bool enable_sendrecv_aie, uint16_t size_dim1,
    uint16_t size_dim2, ap_uint<3> compute_tile_access_A, ap_uint<3> compute_tile_access_B,
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

  if (enable_sendrecv_aie) {


    for (uint16_t reuse_a = 0; reuse_a < compute_tile_access_A; reuse_a++) {
      for (uint16_t reuse_b = 0; reuse_b < compute_tile_access_B * 128; reuse_b += 128) {
        for (uint16_t dim2 = 0; dim2 < 128; dim2 = dim2 + 32) {
          for (uint16_t dim1 = 0; dim1 < 128; dim1 = dim1 + 4) {
            for (uint16_t col8_id = 0; col8_id < 32;
                 col8_id = col8_id + 8) {  // 2 columns of 4x4 blocks

              uint16_t row_addr = dim1;
              uint16_t col_addr_op1 = reuse_b;
              uint16_t col_addr_op2 = dim2 + col8_id;
              uint16_t col_addr = col_addr_op1 + col_addr_op2;

#pragma HLS bind_op variable = col_addr_op1 op = mul impl = fabric
#pragma HLS bind_op variable = col_addr_op2 op = add impl = fabric
#pragma HLS bind_op variable = col_addr op = add impl = fabric


#pragma HLS PIPELINE II = 1
              ap_uint<64> data_B0_casc0, data_B0_casc1, data_B0_casc2, data_B0_casc3;
              ap_uint<64> data_B1_casc0, data_B1_casc1, data_B1_casc2, data_B1_casc3;
              ap_uint<64> data_B2_casc0, data_B2_casc1, data_B2_casc2, data_B2_casc3;
              ap_uint<64> data_B3_casc0, data_B3_casc1, data_B3_casc2, data_B3_casc3;

              data_B0_casc0 = concat_32b_to_64b_coreB(buf_B[row_addr + 0][col_addr + 0],
                                                      buf_B[row_addr + 0][col_addr + 4 + 0]);
              data_B0_casc1 = concat_32b_to_64b_coreB(buf_B[row_addr + 1][col_addr + 0],
                                                      buf_B[row_addr + 1][col_addr + 4 + 0]);
              data_B0_casc2 = concat_32b_to_64b_coreB(buf_B[row_addr + 2][col_addr + 0],
                                                      buf_B[row_addr + 2][col_addr + 4 + 0]);
              data_B0_casc3 = concat_32b_to_64b_coreB(buf_B[row_addr + 3][col_addr + 0],
                                                      buf_B[row_addr + 3][col_addr + 4 + 0]);
              data_B1_casc0 = concat_32b_to_64b_coreB(buf_B[row_addr + 0][col_addr + 1],
                                                      buf_B[row_addr + 0][col_addr + 4 + 1]);
              data_B1_casc1 = concat_32b_to_64b_coreB(buf_B[row_addr + 1][col_addr + 1],
                                                      buf_B[row_addr + 1][col_addr + 4 + 1]);
              data_B1_casc2 = concat_32b_to_64b_coreB(buf_B[row_addr + 2][col_addr + 1],
                                                      buf_B[row_addr + 2][col_addr + 4 + 1]);
              data_B1_casc3 = concat_32b_to_64b_coreB(buf_B[row_addr + 3][col_addr + 1],
                                                      buf_B[row_addr + 3][col_addr + 4 + 1]);
              data_B2_casc0 = concat_32b_to_64b_coreB(buf_B[row_addr + 0][col_addr + 2],
                                                      buf_B[row_addr + 0][col_addr + 4 + 2]);
              data_B2_casc1 = concat_32b_to_64b_coreB(buf_B[row_addr + 1][col_addr + 2],
                                                      buf_B[row_addr + 1][col_addr + 4 + 2]);
              data_B2_casc2 = concat_32b_to_64b_coreB(buf_B[row_addr + 2][col_addr + 2],
                                                      buf_B[row_addr + 2][col_addr + 4 + 2]);
              data_B2_casc3 = concat_32b_to_64b_coreB(buf_B[row_addr + 3][col_addr + 2],
                                                      buf_B[row_addr + 3][col_addr + 4 + 2]);
              data_B3_casc0 = concat_32b_to_64b_coreB(buf_B[row_addr + 0][col_addr + 3],
                                                      buf_B[row_addr + 0][col_addr + 4 + 3]);
              data_B3_casc1 = concat_32b_to_64b_coreB(buf_B[row_addr + 1][col_addr + 3],
                                                      buf_B[row_addr + 1][col_addr + 4 + 3]);
              data_B3_casc2 = concat_32b_to_64b_coreB(buf_B[row_addr + 2][col_addr + 3],
                                                      buf_B[row_addr + 2][col_addr + 4 + 3]);
              data_B3_casc3 = concat_32b_to_64b_coreB(buf_B[row_addr + 3][col_addr + 3],
                                                      buf_B[row_addr + 3][col_addr + 4 + 3]);

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

void memcore_B(


    hls::stream<uop_memcore_B_type> &stream_uOP_memcore_B,
    hls::stream<ap_uint<1024>> &stream_from_ddr, hls::stream<ap_uint<1024>> &stream_from_lpddr,

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

  ap_uint<32> buf0_B[BUFB_DIM1][BUFB_DIM2];
  ap_uint<32> buf1_B[BUFB_DIM1][BUFB_DIM2];

#pragma HLS bind_storage variable = buf0_B type = RAM_T2P impl = BRAM
#pragma HLS ARRAY_PARTITION variable = buf0_B dim = 1 cyclic factor = 8
#pragma HLS ARRAY_PARTITION variable = buf0_B dim = 2 cyclic factor = 8
#pragma HLS bind_storage variable = buf1_B type = RAM_T2P impl = BRAM
#pragma HLS ARRAY_PARTITION variable = buf1_B dim = 1 cyclic factor = 8
#pragma HLS ARRAY_PARTITION variable = buf1_B dim = 2 cyclic factor = 8

  bool is_computing_buf1 = 0;

  uop_memcore_B_type uOP;
  bool is_last_uOP = false;
WHILE_LOOP:
  while (is_last_uOP == false) {
    uOP = stream_uOP_memcore_B.read();
    is_last_uOP = uOP.is_last_uOP;

    bool enable_load_from_dram = uOP.enable_load_from_dram;
    bool is_loading_bias = uOP.is_loading_bias;
    bool enable_transpose = uOP.enable_transpose;
    bool enable_send_to_aie = uOP.enable_send_to_aie;

    ap_uint<10> one_mem_tile_dim1 = uOP.one_mem_tile_dim1;
    ap_uint<10> one_mem_tile_dim2 = uOP.one_mem_tile_dim2;
    ap_uint<3> compute_tile_access_A = uOP.compute_tile_access_A;
    ap_uint<3> compute_tile_access_B = uOP.compute_tile_access_B;

    uint16_t one_compute_tile_dim1 = 128;
    uint16_t one_compute_tile_dim2 = 128;
    // bool is_computing_buf1  = uOP.is_computing_buf1;

    if (is_computing_buf1 == 1) {
      loadB_from_dramStream(

          buf0_B, enable_load_from_dram, is_loading_bias, enable_transpose, one_mem_tile_dim1,
          one_mem_tile_dim2, stream_from_ddr, stream_from_lpddr);
      sendB_to_aie(

          buf1_B, enable_send_to_aie, one_compute_tile_dim1, one_compute_tile_dim2,
          compute_tile_access_A, compute_tile_access_B, to_computeCore0_B0_CASC0,
          to_computeCore0_B0_CASC1, to_computeCore0_B0_CASC2, to_computeCore0_B0_CASC3,
          to_computeCore0_B1_CASC0, to_computeCore0_B1_CASC1, to_computeCore0_B1_CASC2,
          to_computeCore0_B1_CASC3, to_computeCore0_B2_CASC0, to_computeCore0_B2_CASC1,
          to_computeCore0_B2_CASC2, to_computeCore0_B2_CASC3, to_computeCore0_B3_CASC0,
          to_computeCore0_B3_CASC1, to_computeCore0_B3_CASC2, to_computeCore0_B3_CASC3);
    } else {
      loadB_from_dramStream(

          buf1_B, enable_load_from_dram, is_loading_bias, enable_transpose, one_mem_tile_dim1,
          one_mem_tile_dim2, stream_from_ddr, stream_from_lpddr);
      sendB_to_aie(

          buf0_B, enable_send_to_aie, one_compute_tile_dim1, one_compute_tile_dim2,
          compute_tile_access_A, compute_tile_access_B, to_computeCore0_B0_CASC0,
          to_computeCore0_B0_CASC1, to_computeCore0_B0_CASC2, to_computeCore0_B0_CASC3,
          to_computeCore0_B1_CASC0, to_computeCore0_B1_CASC1, to_computeCore0_B1_CASC2,
          to_computeCore0_B1_CASC3, to_computeCore0_B2_CASC0, to_computeCore0_B2_CASC1,
          to_computeCore0_B2_CASC2, to_computeCore0_B2_CASC3, to_computeCore0_B3_CASC0,
          to_computeCore0_B3_CASC1, to_computeCore0_B3_CASC2, to_computeCore0_B3_CASC3);
    }

    if (is_computing_buf1 == 1) {
      is_computing_buf1 = 0;
    } else {
      is_computing_buf1 = 1;
    }
  }
}
