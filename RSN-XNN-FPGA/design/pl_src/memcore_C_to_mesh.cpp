#include "memcore_C_to_mesh.h"



float my_tanh_to_mesh(float t_in) {
#pragma HLS inline recursive

  static const int exp_bias = fp_struct<float>::EXP_BIAS;

  fp_struct<float> din(t_in);
  float abst_in = hls::fabs(t_in);
  float resultf;

  if (din.exp == fp_struct<float>::EXP_INFNAN) {
    if (din.sig != 0) {
      resultf = ::hls::nan("");
    } else {
      resultf = (float)1.0;
    }
  } else if ((din.exp < exp_bias - 55) or (din.exp == exp_bias - 55 and din.sig == 0)) {
    const float cst1 = 1.0;
    resultf = abst_in * (cst1 + abst_in);
  } else if (abst_in < (float)22.0) {
    float x;
    if (din.exp < exp_bias) {
      x = -abst_in - abst_in;
    } else {
      x = abst_in + abst_in;
    }

    float expx;
#pragma HLS bind_op variable = expx op = fexp impl = meddsp latency = 21
    fp_struct<float> xs(x);
    if (xs.exp == 0) {
      expx = 0;
    } else if (xs.exp < 96) {
      expx = x;
    } else {
      expx = expf(x) - 1;
    }

    if (din.exp < exp_bias) {
      const float cst2 = 2.0;
      resultf = -expx / (expx + cst2);
    } else {
      const float cst1 = 1.0;
      const float cst2 = 2.0;
      resultf = cst1 - cst2 / (expx + cst2);
    }
  } else {
    resultf = (float)1.0;
  }

  // return
  if (din.sign == 0) {  // positive
    return resultf;
  } else {
    return -resultf;
  };
}

float gelu_to_mesh(float x) {
  // #pragma HLS inline
  float x1;

  x1 = 0.5f * x * (1.0f + my_tanh_to_mesh(0.7978845608f * (x + 0.044715f * x * x * x)));
  return x1;
}

ap_uint<64> concat_32b_to_64b_coreC(float in0, float in1) {
  ap_uint<64> out;
  UNION_FP_UINT32 temp0, temp1;
  temp0.float_val = in0;
  temp1.float_val = in1;
  out(31, 0) = temp0.uint32_val;
  out(63, 32) = temp1.uint32_val;
  return out;
}

void split_64b_to_32b_to_mesh(ap_uint<64> in, float &out0, float &out1) {
  UNION_FP_UINT32 temp0, temp1;
  temp0.uint32_val = in(31, 0);
  temp1.uint32_val = in(63, 32);

  out0 = temp0.float_val;
  out1 = temp1.float_val;
}

void init_C_to_mesh(float buf_C[BUFC_DIM1][BUFC_DIM2 / 2][2], ap_uint<3> compute_tile_recv_access_A,
                    ap_uint<3> compute_tile_recv_access_B) {
init_C_to_mesh:
  for (uint16_t row_addr = 0; row_addr < compute_tile_recv_access_A * 128; row_addr += 8) {
    for (uint16_t col_addr = 0; col_addr < compute_tile_recv_access_A * 64; col_addr += 4) {
#pragma HLS pipeline II = 1
      buf_C[row_addr + 0][col_addr + 0][0] = 0;
      buf_C[row_addr + 0][col_addr + 0][1] = 0;
      buf_C[row_addr + 0][col_addr + 1][0] = 0;
      buf_C[row_addr + 0][col_addr + 1][1] = 0;
      buf_C[row_addr + 0][col_addr + 2][0] = 0;
      buf_C[row_addr + 0][col_addr + 2][1] = 0;
      buf_C[row_addr + 0][col_addr + 3][0] = 0;
      buf_C[row_addr + 0][col_addr + 3][1] = 0;
      buf_C[row_addr + 1][col_addr + 0][0] = 0;
      buf_C[row_addr + 1][col_addr + 0][1] = 0;
      buf_C[row_addr + 1][col_addr + 1][0] = 0;
      buf_C[row_addr + 1][col_addr + 1][1] = 0;
      buf_C[row_addr + 1][col_addr + 2][0] = 0;
      buf_C[row_addr + 1][col_addr + 2][1] = 0;
      buf_C[row_addr + 1][col_addr + 3][0] = 0;
      buf_C[row_addr + 1][col_addr + 3][1] = 0;
      buf_C[row_addr + 2][col_addr + 0][0] = 0;
      buf_C[row_addr + 2][col_addr + 0][1] = 0;
      buf_C[row_addr + 2][col_addr + 1][0] = 0;
      buf_C[row_addr + 2][col_addr + 1][1] = 0;
      buf_C[row_addr + 2][col_addr + 2][0] = 0;
      buf_C[row_addr + 2][col_addr + 2][1] = 0;
      buf_C[row_addr + 2][col_addr + 3][0] = 0;
      buf_C[row_addr + 2][col_addr + 3][1] = 0;
      buf_C[row_addr + 3][col_addr + 0][0] = 0;
      buf_C[row_addr + 3][col_addr + 0][1] = 0;
      buf_C[row_addr + 3][col_addr + 1][0] = 0;
      buf_C[row_addr + 3][col_addr + 1][1] = 0;
      buf_C[row_addr + 3][col_addr + 2][0] = 0;
      buf_C[row_addr + 3][col_addr + 2][1] = 0;
      buf_C[row_addr + 3][col_addr + 3][0] = 0;
      buf_C[row_addr + 3][col_addr + 3][1] = 0;

      buf_C[row_addr + 4][col_addr + 0][0] = 0;
      buf_C[row_addr + 4][col_addr + 0][1] = 0;
      buf_C[row_addr + 4][col_addr + 1][0] = 0;
      buf_C[row_addr + 4][col_addr + 1][1] = 0;
      buf_C[row_addr + 4][col_addr + 2][0] = 0;
      buf_C[row_addr + 4][col_addr + 2][1] = 0;
      buf_C[row_addr + 4][col_addr + 3][0] = 0;
      buf_C[row_addr + 4][col_addr + 3][1] = 0;
      buf_C[row_addr + 5][col_addr + 0][0] = 0;
      buf_C[row_addr + 5][col_addr + 0][1] = 0;
      buf_C[row_addr + 5][col_addr + 1][0] = 0;
      buf_C[row_addr + 5][col_addr + 1][1] = 0;
      buf_C[row_addr + 5][col_addr + 2][0] = 0;
      buf_C[row_addr + 5][col_addr + 2][1] = 0;
      buf_C[row_addr + 5][col_addr + 3][0] = 0;
      buf_C[row_addr + 5][col_addr + 3][1] = 0;
      buf_C[row_addr + 6][col_addr + 0][0] = 0;
      buf_C[row_addr + 6][col_addr + 0][1] = 0;
      buf_C[row_addr + 6][col_addr + 1][0] = 0;
      buf_C[row_addr + 6][col_addr + 1][1] = 0;
      buf_C[row_addr + 6][col_addr + 2][0] = 0;
      buf_C[row_addr + 6][col_addr + 2][1] = 0;
      buf_C[row_addr + 6][col_addr + 3][0] = 0;
      buf_C[row_addr + 6][col_addr + 3][1] = 0;
      buf_C[row_addr + 7][col_addr + 0][0] = 0;
      buf_C[row_addr + 7][col_addr + 0][1] = 0;
      buf_C[row_addr + 7][col_addr + 1][0] = 0;
      buf_C[row_addr + 7][col_addr + 1][1] = 0;
      buf_C[row_addr + 7][col_addr + 2][0] = 0;
      buf_C[row_addr + 7][col_addr + 2][1] = 0;
      buf_C[row_addr + 7][col_addr + 3][0] = 0;
      buf_C[row_addr + 7][col_addr + 3][1] = 0;
    }
  }
}

void storeC_to_dramStream_to_mesh(

    float buf_C[BUFC_DIM1][BUFC_DIM2 / 2][2], bool enable_store_to_dram, ap_uint<9> size_dim1,
    ap_uint<10> size_dim2, hls::stream<ap_uint<1024>> &stream_to_ddr, bool enable_layer_norm,
    bool enable_gelu, hls::stream<ap_uint<1024>> &stream_from_ddr,
    hls::stream<float> &data_channel_to_neighbour,
    hls::stream<float> &data_channel_from_neighbour) {


  if (enable_store_to_dram) {

    if (enable_gelu == true) {
    GELU0:
      for (int row = 0; row < size_dim1; row++) {
      GELU1:
        for (int col = 0; col < 256; col++) {
#pragma HLS PIPELINE II = 2
#pragma HLS UNROLL factor = 4
          //   #pragma HLS latency min=200
          buf_C[row][col][0] = gelu_to_mesh(buf_C[row][col][0]);
          buf_C[row][col][1] = gelu_to_mesh(buf_C[row][col][1]);
        }
      }
    }

    if (enable_layer_norm) {
#pragma HLS STREAM variable = data_channel_to_neighbour depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_from_neighbour depth = 256 type = fifo

      float mean_buf[256];
#pragma HLS ARRAY_PARTITION variable = mean_buf dim = 1 cyclic factor = 4
      float var_buf[256];
#pragma HLS ARRAY_PARTITION variable = var_buf dim = 1 cyclic factor = 4

    INIT_MEAN:
      for (uint16_t row = 0; row < size_dim1; row = row + 4) {
#pragma HLS PIPELINE II = 1
        mean_buf[row] = 0.0;
        mean_buf[row + 1] = 0.0;
        mean_buf[row + 2] = 0.0;
        mean_buf[row + 3] = 0.0;
      }
    INIT_VAR:
      for (uint16_t row = 0; row < size_dim1; row = row + 4) {
#pragma HLS PIPELINE II = 1
        var_buf[row] = 0.0;
        var_buf[row + 1] = 0.0;
        var_buf[row + 2] = 0.0;
        var_buf[row + 3] = 0.0;
      }
    // calculate mean
    CAL_MEAN:
      for (uint16_t row = 0; row < size_dim1; row = row + 4) {
        for (uint16_t col = 0; col < 256; col = col + 1) {
#pragma HLS PIPELINE II = 1
          mean_buf[row] += buf_C[row][col][0] + buf_C[row][col][1];
          mean_buf[row + 1] += buf_C[row + 1][col][0] + buf_C[row + 1][col][1];
          mean_buf[row + 2] += buf_C[row + 2][col][0] + buf_C[row + 2][col][1];
          mean_buf[row + 3] += buf_C[row + 3][col][0] + buf_C[row + 3][col][1];
        }
      }
    SEND_MEAN:
      for (uint16_t row = 0; row < size_dim1; row = row + 1) {
#pragma HLS PIPELINE II = 1
        float v0 = mean_buf[row] / 1024;
        mean_buf[row] = v0;
        data_channel_to_neighbour.write(v0);
      }


    RECV_MEAN:
      for (uint16_t row = 0; row < size_dim1; row = row + 1) {
#pragma HLS PIPELINE II = 1
        mean_buf[row] += data_channel_from_neighbour.read();
      }



    // calculate variance
    CAL_VAR:
      for (uint16_t row = 0; row < size_dim1; row = row + 4) {
        for (uint16_t col = 0; col < 256; col = col + 1) {
#pragma HLS PIPELINE II = 1
          float mean_r0 = mean_buf[row];
          float mean_r1 = mean_buf[row + 1];
          float mean_r2 = mean_buf[row + 2];
          float mean_r3 = mean_buf[row + 3];
          var_buf[row] += ((buf_C[row][col][0] - mean_r0) * (buf_C[row][col][0] - mean_r0) +
                           (buf_C[row][col][1] - mean_r0) * (buf_C[row][col][1] - mean_r0));
          var_buf[row + 1] +=
              ((buf_C[row + 1][col][0] - mean_r1) * (buf_C[row + 1][col][0] - mean_r1) +
               (buf_C[row + 1][col][1] - mean_r1) * (buf_C[row + 1][col][1] - mean_r1));
          var_buf[row + 2] +=
              ((buf_C[row + 2][col][0] - mean_r2) * (buf_C[row + 2][col][0] - mean_r2) +
               (buf_C[row + 2][col][1] - mean_r2) * (buf_C[row + 2][col][1] - mean_r2));
          var_buf[row + 3] +=
              ((buf_C[row + 3][col][0] - mean_r3) * (buf_C[row + 3][col][0] - mean_r3) +
               (buf_C[row + 3][col][1] - mean_r3) * (buf_C[row + 3][col][1] - mean_r3));
        }
      }



    SEND_VAR:
      for (uint16_t row = 0; row < size_dim1; row = row + 1) {
#pragma HLS PIPELINE II = 1
        float v0 = var_buf[row] / 1024;
        var_buf[row] = v0;
        data_channel_to_neighbour.write(v0);
      }

    RECV_VAR:
      for (uint16_t row = 0; row < size_dim1; row = row + 1) {
#pragma HLS PIPELINE II = 1
        float v0 = data_channel_from_neighbour.read();
        v0 += var_buf[row];
#ifdef SW_EMU_PRINT
        var_buf[row] = sqrt(v0 + 1e-6);
#else
        var_buf[row] = hls::sqrtf(v0 + 1e-6);
#endif
      }



    // normalize
    NROM:
      for (uint16_t row = 0; row < size_dim1; row = row + 4) {
        for (uint16_t col = 0; col < 256; col = col + 4) {
#pragma HLS PIPELINE II = 2
          buf_C[row][col][0] = (buf_C[row][col][0] - mean_buf[row]) / var_buf[row];
          buf_C[row][col][1] = (buf_C[row][col][1] - mean_buf[row]) / var_buf[row];
          buf_C[row + 1][col][0] = (buf_C[row + 1][col][0] - mean_buf[row + 1]) / var_buf[row + 1];
          buf_C[row + 1][col][1] = (buf_C[row + 1][col][1] - mean_buf[row + 1]) / var_buf[row + 1];
          buf_C[row + 2][col][0] = (buf_C[row + 2][col][0] - mean_buf[row + 2]) / var_buf[row + 2];
          buf_C[row + 2][col][1] = (buf_C[row + 2][col][1] - mean_buf[row + 2]) / var_buf[row + 2];
          buf_C[row + 3][col][0] = (buf_C[row + 3][col][0] - mean_buf[row + 3]) / var_buf[row + 3];
          buf_C[row + 3][col][1] = (buf_C[row + 3][col][1] - mean_buf[row + 3]) / var_buf[row + 3];

          buf_C[row][col + 1][0] = (buf_C[row][col + 1][0] - mean_buf[row]) / var_buf[row];
          buf_C[row][col + 1][1] = (buf_C[row][col + 1][1] - mean_buf[row]) / var_buf[row];
          buf_C[row + 1][col + 1][0] =
              (buf_C[row + 1][col + 1][0] - mean_buf[row + 1]) / var_buf[row + 1];
          buf_C[row + 1][col + 1][1] =
              (buf_C[row + 1][col + 1][1] - mean_buf[row + 1]) / var_buf[row + 1];
          buf_C[row + 2][col + 1][0] =
              (buf_C[row + 2][col + 1][0] - mean_buf[row + 2]) / var_buf[row + 2];
          buf_C[row + 2][col + 1][1] =
              (buf_C[row + 2][col + 1][1] - mean_buf[row + 2]) / var_buf[row + 2];
          buf_C[row + 3][col + 1][0] =
              (buf_C[row + 3][col + 1][0] - mean_buf[row + 3]) / var_buf[row + 3];
          buf_C[row + 3][col + 1][1] =
              (buf_C[row + 3][col + 1][1] - mean_buf[row + 3]) / var_buf[row + 3];

          buf_C[row][col + 2][0] = (buf_C[row][col + 2][0] - mean_buf[row]) / var_buf[row];
          buf_C[row][col + 2][1] = (buf_C[row][col + 2][1] - mean_buf[row]) / var_buf[row];
          buf_C[row + 1][col + 2][0] =
              (buf_C[row + 1][col + 2][0] - mean_buf[row + 1]) / var_buf[row + 1];
          buf_C[row + 1][col + 2][1] =
              (buf_C[row + 1][col + 2][1] - mean_buf[row + 1]) / var_buf[row + 1];
          buf_C[row + 2][col + 2][0] =
              (buf_C[row + 2][col + 2][0] - mean_buf[row + 2]) / var_buf[row + 2];
          buf_C[row + 2][col + 2][1] =
              (buf_C[row + 2][col + 2][1] - mean_buf[row + 2]) / var_buf[row + 2];
          buf_C[row + 3][col + 2][0] =
              (buf_C[row + 3][col + 2][0] - mean_buf[row + 3]) / var_buf[row + 3];
          buf_C[row + 3][col + 2][1] =
              (buf_C[row + 3][col + 2][1] - mean_buf[row + 3]) / var_buf[row + 3];

          buf_C[row][col + 3][0] = (buf_C[row][col + 3][0] - mean_buf[row]) / var_buf[row];
          buf_C[row][col + 3][1] = (buf_C[row][col + 3][1] - mean_buf[row]) / var_buf[row];
          buf_C[row + 1][col + 3][0] =
              (buf_C[row + 1][col + 3][0] - mean_buf[row + 1]) / var_buf[row + 1];
          buf_C[row + 1][col + 3][1] =
              (buf_C[row + 1][col + 3][1] - mean_buf[row + 1]) / var_buf[row + 1];
          buf_C[row + 2][col + 3][0] =
              (buf_C[row + 2][col + 3][0] - mean_buf[row + 2]) / var_buf[row + 2];
          buf_C[row + 2][col + 3][1] =
              (buf_C[row + 2][col + 3][1] - mean_buf[row + 2]) / var_buf[row + 2];
          buf_C[row + 3][col + 3][0] =
              (buf_C[row + 3][col + 3][0] - mean_buf[row + 3]) / var_buf[row + 3];
          buf_C[row + 3][col + 3][1] =
              (buf_C[row + 3][col + 3][1] - mean_buf[row + 3]) / var_buf[row + 3];
        }
      }


    }


    for (uint16_t dim1 = 0; dim1 < size_dim1; dim1 += 128) {
      for (uint16_t dim2 = 0; dim2 < size_dim2 / 2; dim2 += 32) {
        for (uint16_t block_r = 0; block_r < (128); block_r += 2) {
          for (uint16_t block_c = 0; block_c < (64 / 2); block_c += 8) {
#pragma HLS PIPELINE II = 1
            ap_uint<1024> data_1024b;

            UNION_FP_UINT32 temp;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 0][0];
            data_1024b(31, 0) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 1][0];
            data_1024b(63, 32) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 2][0];
            data_1024b(95, 64) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 3][0];
            data_1024b(127, 96) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 0][1];
            data_1024b(159, 128) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 1][1];
            data_1024b(191, 160) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 2][1];
            data_1024b(223, 192) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 3][1];
            data_1024b(255, 224) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 4][0];
            data_1024b(287, 256) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 5][0];
            data_1024b(319, 288) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 6][0];
            data_1024b(351, 320) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 7][0];
            data_1024b(383, 352) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 4][1];
            data_1024b(415, 384) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 5][1];
            data_1024b(447, 416) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 6][1];
            data_1024b(479, 448) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r][dim2 + block_c + 7][1];
            data_1024b(511, 480) = temp.uint32_val;

            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 0][0];
            data_1024b(543, 512) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 1][0];
            data_1024b(575, 544) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 2][0];
            data_1024b(607, 576) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 3][0];
            data_1024b(639, 608) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 0][1];
            data_1024b(671, 640) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 1][1];
            data_1024b(703, 672) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 2][1];
            data_1024b(735, 704) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 3][1];
            data_1024b(767, 736) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 4][0];
            data_1024b(799, 768) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 5][0];
            data_1024b(831, 800) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 6][0];
            data_1024b(863, 832) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 7][0];
            data_1024b(895, 864) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 4][1];
            data_1024b(927, 896) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 5][1];
            data_1024b(959, 928) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 6][1];
            data_1024b(991, 960) = temp.uint32_val;
            temp.float_val = buf_C[dim1 + block_r + 1][dim2 + block_c + 7][1];
            data_1024b(1023, 992) = temp.uint32_val;

            stream_to_ddr.write(data_1024b);

          }
        }
      }
    }
    // init_C_to_mesh(buf_C, 2, 4);
  }


}

void recvC_from_aie_to_mesh(

    float buf_C[BUFC_DIM1][BUFC_DIM2 / 2][2], bool enable_recv_aie, bool enable_softmax,
    bool enable_gelu, uint16_t k_iter, uint16_t size_dim1, uint16_t size_dim2,
    ap_uint<2> compute_tile_recv_access_A, ap_uint<3> compute_tile_recv_access_B,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C00,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C01,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C02,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C03,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C10,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C11,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C12,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C13,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C20,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C21,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C22,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C23,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C30,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C31,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C32,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C33,
    hls::stream<float> &data_channel_to_neighbour,
    hls::stream<float> &data_channel_from_neighbour) {


  if (enable_recv_aie) {
  RECV0:
    for (uint16_t k = 0; k < k_iter; k++) {
    RECV1:
      for (uint16_t reuse_a = 0; reuse_a < compute_tile_recv_access_A * 128;
           reuse_a = reuse_a + 128) {
      RECV2:
        for (uint16_t reuse_b = 0; reuse_b < compute_tile_recv_access_B * 64;
             reuse_b = reuse_b + 64) {
        RECV3:
          for (uint16_t dim2 = 0; dim2 < 64;
               dim2 = dim2 + 16) {  // loop 4 times to sweep 1 row (4 x 8 float)
          RECV4:
            for (uint16_t dim1 = 0; dim1 < 128;
                 dim1 = dim1 + 4) {  // loop 32 times to sweep 1 column (32 float)
            RECV5:
              for (uint16_t col8_id = 0; col8_id < 16;
                   col8_id =
                       col8_id + 4) {  // 2 columns of 4x4 blocks, 4 read to get 8 float (1 SIMD)
                uint16_t row_addr = reuse_a + dim1;
                uint16_t col_addr = reuse_b + dim2 + col8_id;
#pragma HLS dependence variable = buf_C type = inter distance = 128 true
#pragma HLS PIPELINE II = 1
                float data0_C00, data0_C01, data0_C02, data0_C03;
                float data0_C10, data0_C11, data0_C12, data0_C13;
                float data0_C20, data0_C21, data0_C22, data0_C23;
                float data0_C30, data0_C31, data0_C32, data0_C33;
                float data1_C00, data1_C01, data1_C02, data1_C03;
                float data1_C10, data1_C11, data1_C12, data1_C13;
                float data1_C20, data1_C21, data1_C22, data1_C23;
                float data1_C30, data1_C31, data1_C32, data1_C33;
                split_64b_to_32b_to_mesh(from_computeCore0_C00.read().data, data0_C00, data1_C00);
                split_64b_to_32b_to_mesh(from_computeCore0_C01.read().data, data0_C01, data1_C01);
                split_64b_to_32b_to_mesh(from_computeCore0_C02.read().data, data0_C02, data1_C02);
                split_64b_to_32b_to_mesh(from_computeCore0_C03.read().data, data0_C03, data1_C03);
                split_64b_to_32b_to_mesh(from_computeCore0_C10.read().data, data0_C10, data1_C10);
                split_64b_to_32b_to_mesh(from_computeCore0_C11.read().data, data0_C11, data1_C11);
                split_64b_to_32b_to_mesh(from_computeCore0_C12.read().data, data0_C12, data1_C12);
                split_64b_to_32b_to_mesh(from_computeCore0_C13.read().data, data0_C13, data1_C13);
                split_64b_to_32b_to_mesh(from_computeCore0_C20.read().data, data0_C20, data1_C20);
                split_64b_to_32b_to_mesh(from_computeCore0_C21.read().data, data0_C21, data1_C21);
                split_64b_to_32b_to_mesh(from_computeCore0_C22.read().data, data0_C22, data1_C22);
                split_64b_to_32b_to_mesh(from_computeCore0_C23.read().data, data0_C23, data1_C23);
                split_64b_to_32b_to_mesh(from_computeCore0_C30.read().data, data0_C30, data1_C30);
                split_64b_to_32b_to_mesh(from_computeCore0_C31.read().data, data0_C31, data1_C31);
                split_64b_to_32b_to_mesh(from_computeCore0_C32.read().data, data0_C32, data1_C32);
                split_64b_to_32b_to_mesh(from_computeCore0_C33.read().data, data0_C33, data1_C33);

                if (k == 0) {
                  buf_C[row_addr + 0][col_addr + 0][0] = data0_C00;
                  buf_C[row_addr + 0][col_addr + 0][1] = data1_C00;
                  buf_C[row_addr + 0][col_addr + 1][0] = data0_C01;
                  buf_C[row_addr + 0][col_addr + 1][1] = data1_C01;
                  buf_C[row_addr + 0][col_addr + 2][0] = data0_C02;
                  buf_C[row_addr + 0][col_addr + 2][1] = data1_C02;
                  buf_C[row_addr + 0][col_addr + 3][0] = data0_C03;
                  buf_C[row_addr + 0][col_addr + 3][1] = data1_C03;
                  buf_C[row_addr + 1][col_addr + 0][0] = data0_C10;
                  buf_C[row_addr + 1][col_addr + 0][1] = data1_C10;
                  buf_C[row_addr + 1][col_addr + 1][0] = data0_C11;
                  buf_C[row_addr + 1][col_addr + 1][1] = data1_C11;
                  buf_C[row_addr + 1][col_addr + 2][0] = data0_C12;
                  buf_C[row_addr + 1][col_addr + 2][1] = data1_C12;
                  buf_C[row_addr + 1][col_addr + 3][0] = data0_C13;
                  buf_C[row_addr + 1][col_addr + 3][1] = data1_C13;
                  buf_C[row_addr + 2][col_addr + 0][0] = data0_C20;
                  buf_C[row_addr + 2][col_addr + 0][1] = data1_C20;
                  buf_C[row_addr + 2][col_addr + 1][0] = data0_C21;
                  buf_C[row_addr + 2][col_addr + 1][1] = data1_C21;
                  buf_C[row_addr + 2][col_addr + 2][0] = data0_C22;
                  buf_C[row_addr + 2][col_addr + 2][1] = data1_C22;
                  buf_C[row_addr + 2][col_addr + 3][0] = data0_C23;
                  buf_C[row_addr + 2][col_addr + 3][1] = data1_C23;
                  buf_C[row_addr + 3][col_addr + 0][0] = data0_C30;
                  buf_C[row_addr + 3][col_addr + 0][1] = data1_C30;
                  buf_C[row_addr + 3][col_addr + 1][0] = data0_C31;
                  buf_C[row_addr + 3][col_addr + 1][1] = data1_C31;
                  buf_C[row_addr + 3][col_addr + 2][0] = data0_C32;
                  buf_C[row_addr + 3][col_addr + 2][1] = data1_C32;
                  buf_C[row_addr + 3][col_addr + 3][0] = data0_C33;
                  buf_C[row_addr + 3][col_addr + 3][1] = data1_C33;
                } else {
                  buf_C[row_addr + 0][col_addr + 0][0] += data0_C00;
                  buf_C[row_addr + 0][col_addr + 0][1] += data1_C00;
                  buf_C[row_addr + 0][col_addr + 1][0] += data0_C01;
                  buf_C[row_addr + 0][col_addr + 1][1] += data1_C01;
                  buf_C[row_addr + 0][col_addr + 2][0] += data0_C02;
                  buf_C[row_addr + 0][col_addr + 2][1] += data1_C02;
                  buf_C[row_addr + 0][col_addr + 3][0] += data0_C03;
                  buf_C[row_addr + 0][col_addr + 3][1] += data1_C03;
                  buf_C[row_addr + 1][col_addr + 0][0] += data0_C10;
                  buf_C[row_addr + 1][col_addr + 0][1] += data1_C10;
                  buf_C[row_addr + 1][col_addr + 1][0] += data0_C11;
                  buf_C[row_addr + 1][col_addr + 1][1] += data1_C11;
                  buf_C[row_addr + 1][col_addr + 2][0] += data0_C12;
                  buf_C[row_addr + 1][col_addr + 2][1] += data1_C12;
                  buf_C[row_addr + 1][col_addr + 3][0] += data0_C13;
                  buf_C[row_addr + 1][col_addr + 3][1] += data1_C13;
                  buf_C[row_addr + 2][col_addr + 0][0] += data0_C20;
                  buf_C[row_addr + 2][col_addr + 0][1] += data1_C20;
                  buf_C[row_addr + 2][col_addr + 1][0] += data0_C21;
                  buf_C[row_addr + 2][col_addr + 1][1] += data1_C21;
                  buf_C[row_addr + 2][col_addr + 2][0] += data0_C22;
                  buf_C[row_addr + 2][col_addr + 2][1] += data1_C22;
                  buf_C[row_addr + 2][col_addr + 3][0] += data0_C23;
                  buf_C[row_addr + 2][col_addr + 3][1] += data1_C23;
                  buf_C[row_addr + 3][col_addr + 0][0] += data0_C30;
                  buf_C[row_addr + 3][col_addr + 0][1] += data1_C30;
                  buf_C[row_addr + 3][col_addr + 1][0] += data0_C31;
                  buf_C[row_addr + 3][col_addr + 1][1] += data1_C31;
                  buf_C[row_addr + 3][col_addr + 2][0] += data0_C32;
                  buf_C[row_addr + 3][col_addr + 2][1] += data1_C32;
                  buf_C[row_addr + 3][col_addr + 3][0] += data0_C33;
                  buf_C[row_addr + 3][col_addr + 3][1] += data1_C33;
                }


              }
            }
          }


        }
      }
    }


    if (enable_softmax) {
      // size_dim1 = 128 * compute_tile_recv_access_A; // note that size_dim1 is set to be 128 at
      // the outside of the function

      float accum_buf[256];  // 8 row, 2 col
#pragma HLS ARRAY_RESHAPE variable = accum_buf dim = 1 cyclic factor = 4
#pragma HLS bind_storage variable = accum_buf type = RAM_T2P impl = BRAM

      // INIT_ACCUMBUF: for (int i=0; i<128 * compute_tile_recv_access_A; i = i+4){
      //    accum_buf[i + 0] = 0;
      //    accum_buf[i + 1] = 0;
      //    accum_buf[i + 2] = 0;
      //    accum_buf[i + 3] = 0;
      // }

      float accum0, accum1, accum2, accum3;
      float accum0_q, accum1_q, accum2_q, accum3_q;

      accum0 = 0;
      accum1 = 0;
      accum2 = 0;
      accum3 = 0;

      bool skip_first_row =
          false;  // flag used to skip the first row to push data_channel_to_neighbour

      uint8_t col_track = 0;

    expf0:
      for (uint16_t row = 0; row < 128 * compute_tile_recv_access_A; row = row + 4) {
      expf1:
        for (uint16_t col = 0; col < 64 * compute_tile_recv_access_B; col = col + 4) {  // 128/2
#pragma HLS PIPELINE II = 1
          float data0_C00, data0_C01, data0_C02, data0_C03;
          float data0_C10, data0_C11, data0_C12, data0_C13;
          float data0_C20, data0_C21, data0_C22, data0_C23;
          float data0_C30, data0_C31, data0_C32, data0_C33;
          float data1_C00, data1_C01, data1_C02, data1_C03;
          float data1_C10, data1_C11, data1_C12, data1_C13;
          float data1_C20, data1_C21, data1_C22, data1_C23;
          float data1_C30, data1_C31, data1_C32, data1_C33;

#pragma HLS bind_op variable = data0_C00 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C01 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C02 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C03 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C10 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C11 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C12 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C13 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C20 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C21 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C22 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C23 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C30 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C31 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C32 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data0_C33 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C00 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C01 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C02 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C03 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C10 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C11 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C12 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C13 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C20 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C21 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C22 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C23 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C30 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C31 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C32 op = fexp impl = meddsp latency = 21
#pragma HLS bind_op variable = data1_C33 op = fexp impl = meddsp latency = 21

          data0_C00 = expf(buf_C[row + 0][col + 0][0]);
          data1_C00 = expf(buf_C[row + 0][col + 0][1]);
          data0_C01 = expf(buf_C[row + 0][col + 1][0]);
          data1_C01 = expf(buf_C[row + 0][col + 1][1]);
          data0_C02 = expf(buf_C[row + 0][col + 2][0]);
          data1_C02 = expf(buf_C[row + 0][col + 2][1]);
          data0_C03 = expf(buf_C[row + 0][col + 3][0]);
          data1_C03 = expf(buf_C[row + 0][col + 3][1]);
          data0_C10 = expf(buf_C[row + 1][col + 0][0]);
          data1_C10 = expf(buf_C[row + 1][col + 0][1]);
          data0_C11 = expf(buf_C[row + 1][col + 1][0]);
          data1_C11 = expf(buf_C[row + 1][col + 1][1]);
          data0_C12 = expf(buf_C[row + 1][col + 2][0]);
          data1_C12 = expf(buf_C[row + 1][col + 2][1]);
          data0_C13 = expf(buf_C[row + 1][col + 3][0]);
          data1_C13 = expf(buf_C[row + 1][col + 3][1]);
          data0_C20 = expf(buf_C[row + 2][col + 0][0]);
          data1_C20 = expf(buf_C[row + 2][col + 0][1]);
          data0_C21 = expf(buf_C[row + 2][col + 1][0]);
          data1_C21 = expf(buf_C[row + 2][col + 1][1]);
          data0_C22 = expf(buf_C[row + 2][col + 2][0]);
          data1_C22 = expf(buf_C[row + 2][col + 2][1]);
          data0_C23 = expf(buf_C[row + 2][col + 3][0]);
          data1_C23 = expf(buf_C[row + 2][col + 3][1]);
          data0_C30 = expf(buf_C[row + 3][col + 0][0]);
          data1_C30 = expf(buf_C[row + 3][col + 0][1]);
          data0_C31 = expf(buf_C[row + 3][col + 1][0]);
          data1_C31 = expf(buf_C[row + 3][col + 1][1]);
          data0_C32 = expf(buf_C[row + 3][col + 2][0]);
          data1_C32 = expf(buf_C[row + 3][col + 2][1]);
          data0_C33 = expf(buf_C[row + 3][col + 3][0]);
          data1_C33 = expf(buf_C[row + 3][col + 3][1]);

          buf_C[row + 0][col + 0][0] = data0_C00;
          buf_C[row + 0][col + 0][1] = data1_C00;
          buf_C[row + 0][col + 1][0] = data0_C01;
          buf_C[row + 0][col + 1][1] = data1_C01;
          buf_C[row + 0][col + 2][0] = data0_C02;
          buf_C[row + 0][col + 2][1] = data1_C02;
          buf_C[row + 0][col + 3][0] = data0_C03;
          buf_C[row + 0][col + 3][1] = data1_C03;
          buf_C[row + 1][col + 0][0] = data0_C10;
          buf_C[row + 1][col + 0][1] = data1_C10;
          buf_C[row + 1][col + 1][0] = data0_C11;
          buf_C[row + 1][col + 1][1] = data1_C11;
          buf_C[row + 1][col + 2][0] = data0_C12;
          buf_C[row + 1][col + 2][1] = data1_C12;
          buf_C[row + 1][col + 3][0] = data0_C13;
          buf_C[row + 1][col + 3][1] = data1_C13;
          buf_C[row + 2][col + 0][0] = data0_C20;
          buf_C[row + 2][col + 0][1] = data1_C20;
          buf_C[row + 2][col + 1][0] = data0_C21;
          buf_C[row + 2][col + 1][1] = data1_C21;
          buf_C[row + 2][col + 2][0] = data0_C22;
          buf_C[row + 2][col + 2][1] = data1_C22;
          buf_C[row + 2][col + 3][0] = data0_C23;
          buf_C[row + 2][col + 3][1] = data1_C23;
          buf_C[row + 3][col + 0][0] = data0_C30;
          buf_C[row + 3][col + 0][1] = data1_C30;
          buf_C[row + 3][col + 1][0] = data0_C31;
          buf_C[row + 3][col + 1][1] = data1_C31;
          buf_C[row + 3][col + 2][0] = data0_C32;
          buf_C[row + 3][col + 2][1] = data1_C32;
          buf_C[row + 3][col + 3][0] = data0_C33;
          buf_C[row + 3][col + 3][1] = data1_C33;

          accum0 += data0_C00 + data1_C00 + data0_C01 + data1_C01 + data0_C02 + data1_C02 +
                    data0_C03 + data1_C03;
          accum1 += data0_C10 + data1_C10 + data0_C11 + data1_C11 + data0_C12 + data1_C12 +
                    data0_C13 + data1_C13;
          accum2 += data0_C20 + data1_C20 + data0_C21 + data1_C21 + data0_C22 + data1_C22 +
                    data0_C23 + data1_C23;
          accum3 += data0_C30 + data1_C30 + data0_C31 + data1_C31 + data0_C32 + data1_C32 +
                    data0_C33 + data1_C33;

          if (col_track == 0 && skip_first_row) {
            data_channel_to_neighbour.write(accum0_q);
          } else if (col_track == 1 && skip_first_row) {
            data_channel_to_neighbour.write(accum1_q);
          } else if (col_track == 2 && skip_first_row) {
            data_channel_to_neighbour.write(accum2_q);
          } else if (col_track == 3 && skip_first_row) {
            data_channel_to_neighbour.write(accum3_q);
          }

          if (col_track == 4 && skip_first_row == false) {
            skip_first_row = true;
          }

          if (col_track == 16 * compute_tile_recv_access_B - 1) {
            col_track = 0;
          } else {
            col_track++;
          }

          if (col == 64 * compute_tile_recv_access_B - 4) {
            accum_buf[row + 0] = accum0;
            accum_buf[row + 1] = accum1;
            accum_buf[row + 2] = accum2;
            accum_buf[row + 3] = accum3;
            accum0_q = accum0;
            accum1_q = accum1;
            accum2_q = accum2;
            accum3_q = accum3;
            accum0 = 0;
            accum1 = 0;
            accum2 = 0;
            accum3 = 0;
          }
        }
      }

      data_channel_to_neighbour.write(accum0_q);
      data_channel_to_neighbour.write(accum1_q);
      data_channel_to_neighbour.write(accum2_q);
      data_channel_to_neighbour.write(accum3_q);

#pragma HLS STREAM variable = data_channel_to_neighbour depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_from_neighbour depth = 256 type = fifo



      float rcv_accum0, rcv_accum1, rcv_accum2, rcv_accum3;
      float rcv_accum0_q, rcv_accum1_q, rcv_accum2_q, rcv_accum3_q;
      rcv_accum0 = 0;
      rcv_accum1 = 0;
      rcv_accum2 = 0;
      rcv_accum3 = 0;
      bool rcv_skip_last_row = false;
      rcv_accum0 = accum_buf[0] + data_channel_from_neighbour.read();
      rcv_accum1 = accum_buf[1] + data_channel_from_neighbour.read();
      rcv_accum2 = accum_buf[2] + data_channel_from_neighbour.read();
      rcv_accum3 = accum_buf[3] + data_channel_from_neighbour.read();

      uint8_t col_track2 = 0;

    SFTX_DIV0:
      for (uint16_t row = 0; row < 128 * compute_tile_recv_access_A; row = row + 4) {
      SFTX_DIV1:
        for (uint16_t col = 0; col < 64 * compute_tile_recv_access_B; col = col + 4) {
#pragma HLS PIPELINE II = 1
          buf_C[row][col][0] = buf_C[row][col][0] / rcv_accum0;
          buf_C[row][col][1] = buf_C[row][col][1] / rcv_accum0;
          buf_C[row][col + 1][0] = buf_C[row][col + 1][0] / rcv_accum0;
          buf_C[row][col + 1][1] = buf_C[row][col + 1][1] / rcv_accum0;
          buf_C[row][col + 2][0] = buf_C[row][col + 2][0] / rcv_accum0;
          buf_C[row][col + 2][1] = buf_C[row][col + 2][1] / rcv_accum0;
          buf_C[row][col + 3][0] = buf_C[row][col + 3][0] / rcv_accum0;
          buf_C[row][col + 3][1] = buf_C[row][col + 3][1] / rcv_accum0;
          buf_C[row + 1][col][0] = buf_C[row + 1][col][0] / rcv_accum1;
          buf_C[row + 1][col][1] = buf_C[row + 1][col][1] / rcv_accum1;
          buf_C[row + 1][col + 1][0] = buf_C[row + 1][col + 1][0] / rcv_accum1;
          buf_C[row + 1][col + 1][1] = buf_C[row + 1][col + 1][1] / rcv_accum1;
          buf_C[row + 1][col + 2][0] = buf_C[row + 1][col + 2][0] / rcv_accum1;
          buf_C[row + 1][col + 2][1] = buf_C[row + 1][col + 2][1] / rcv_accum1;
          buf_C[row + 1][col + 3][0] = buf_C[row + 1][col + 3][0] / rcv_accum1;
          buf_C[row + 1][col + 3][1] = buf_C[row + 1][col + 3][1] / rcv_accum1;
          buf_C[row + 2][col][0] = buf_C[row + 2][col][0] / rcv_accum2;
          buf_C[row + 2][col][1] = buf_C[row + 2][col][1] / rcv_accum2;
          buf_C[row + 2][col + 1][0] = buf_C[row + 2][col + 1][0] / rcv_accum2;
          buf_C[row + 2][col + 1][1] = buf_C[row + 2][col + 1][1] / rcv_accum2;
          buf_C[row + 2][col + 2][0] = buf_C[row + 2][col + 2][0] / rcv_accum2;
          buf_C[row + 2][col + 2][1] = buf_C[row + 2][col + 2][1] / rcv_accum2;
          buf_C[row + 2][col + 3][0] = buf_C[row + 2][col + 3][0] / rcv_accum2;
          buf_C[row + 2][col + 3][1] = buf_C[row + 2][col + 3][1] / rcv_accum2;
          buf_C[row + 3][col][0] = buf_C[row + 3][col][0] / rcv_accum3;
          buf_C[row + 3][col][1] = buf_C[row + 3][col][1] / rcv_accum3;
          buf_C[row + 3][col + 1][0] = buf_C[row + 3][col + 1][0] / rcv_accum3;
          buf_C[row + 3][col + 1][1] = buf_C[row + 3][col + 1][1] / rcv_accum3;
          buf_C[row + 3][col + 2][0] = buf_C[row + 3][col + 2][0] / rcv_accum3;
          buf_C[row + 3][col + 2][1] = buf_C[row + 3][col + 2][1] / rcv_accum3;
          buf_C[row + 3][col + 3][0] = buf_C[row + 3][col + 3][0] / rcv_accum3;
          buf_C[row + 3][col + 3][1] = buf_C[row + 3][col + 3][1] / rcv_accum3;

          if (rcv_skip_last_row == false) {
            if (col_track2 == 1) {
              rcv_accum0_q = accum_buf[row + 4] + data_channel_from_neighbour.read();
            } else if (col_track2 == 2) {
              rcv_accum1_q = accum_buf[row + 5] + data_channel_from_neighbour.read();
            } else if (col_track2 == 3) {
              rcv_accum2_q = accum_buf[row + 6] + data_channel_from_neighbour.read();
            } else if (col_track2 == 4) {
              rcv_accum3_q = accum_buf[row + 7] + data_channel_from_neighbour.read();
            }
          }

          if (col_track2 == 16 * compute_tile_recv_access_B - 1) {
            col_track2 = 0;
          } else {
            col_track2++;
          }

          if (row == 128 * compute_tile_recv_access_A - 4) {
            rcv_skip_last_row = true;
          }

          if (col == 64 * compute_tile_recv_access_B - 4) {
            rcv_accum0 = rcv_accum0_q;
            rcv_accum1 = rcv_accum1_q;
            rcv_accum2 = rcv_accum2_q;
            rcv_accum3 = rcv_accum3_q;
          }
        }
      }
    }




  }

};

void sendC_to_meshA(

    float buf_C[BUFC_DIM1][BUFC_DIM2 / 2][2], bool enable_send_to_aie, uint16_t k_iter,
    uint16_t size_dim1, uint16_t size_dim2, ap_uint<3> compute_tile_send_access_A,
    ap_uint<3> compute_tile_send_access_B, ap_uint<2> compute_tile_send_access_K,
    hls::stream<ap_uint<64>> &to_meshA_C00, hls::stream<ap_uint<64>> &to_meshA_C01,
    hls::stream<ap_uint<64>> &to_meshA_C02, hls::stream<ap_uint<64>> &to_meshA_C03,
    hls::stream<ap_uint<64>> &to_meshA_C10, hls::stream<ap_uint<64>> &to_meshA_C11,
    hls::stream<ap_uint<64>> &to_meshA_C12, hls::stream<ap_uint<64>> &to_meshA_C13,
    hls::stream<ap_uint<64>> &to_meshA_C20, hls::stream<ap_uint<64>> &to_meshA_C21,
    hls::stream<ap_uint<64>> &to_meshA_C22, hls::stream<ap_uint<64>> &to_meshA_C23,
    hls::stream<ap_uint<64>> &to_meshA_C30, hls::stream<ap_uint<64>> &to_meshA_C31,
    hls::stream<ap_uint<64>> &to_meshA_C32, hls::stream<ap_uint<64>> &to_meshA_C33) {


  if (enable_send_to_aie) {
    // compute_tile_send_access_K = 2; // compute_tile_send_access_K only be assigned with value 2


    for (uint16_t reuse_a = 0; reuse_a < compute_tile_send_access_A * 128; reuse_a += 128) {
      for (uint16_t reuse_b = 0; reuse_b < compute_tile_send_access_B; reuse_b++) {
        for (uint16_t reuse_k = 0; reuse_k < compute_tile_send_access_K * 64; reuse_k += 64) {
          for (uint16_t dim1 = 0; dim1 < 128; dim1 += 8) {
            for (uint16_t dim2 = 0; dim2 < 64; dim2 += 8) {
              for (uint16_t row2_id = 0; row2_id < 8; row2_id += 4) {
                for (uint16_t col4_id = 0; col4_id < 8;
                     col4_id = col4_id + 4) {  // 2 columns of 4x4 blocks

                  uint16_t row_addr = reuse_a + dim1 + row2_id;
                  uint16_t col_addr = reuse_k + dim2 + col4_id;

#pragma HLS PIPELINE II = 1
                  ap_uint<64> data_A0_casc0, data_A0_casc1, data_A0_casc2, data_A0_casc3;
                  ap_uint<64> data_A1_casc0, data_A1_casc1, data_A1_casc2, data_A1_casc3;
                  ap_uint<64> data_A2_casc0, data_A2_casc1, data_A2_casc2, data_A2_casc3;
                  ap_uint<64> data_A3_casc0, data_A3_casc1, data_A3_casc2, data_A3_casc3;


                  data_A0_casc0 = concat_32b_to_64b_coreC(buf_C[row_addr + 0][col_addr + 0][0],
                                                          buf_C[row_addr + 0][col_addr + 0][1]);
                  data_A0_casc1 = concat_32b_to_64b_coreC(buf_C[row_addr + 0][col_addr + 1][0],
                                                          buf_C[row_addr + 0][col_addr + 1][1]);
                  data_A0_casc2 = concat_32b_to_64b_coreC(buf_C[row_addr + 0][col_addr + 2][0],
                                                          buf_C[row_addr + 0][col_addr + 2][1]);
                  data_A0_casc3 = concat_32b_to_64b_coreC(buf_C[row_addr + 0][col_addr + 3][0],
                                                          buf_C[row_addr + 0][col_addr + 3][1]);
                  data_A1_casc0 = concat_32b_to_64b_coreC(buf_C[row_addr + 1][col_addr + 0][0],
                                                          buf_C[row_addr + 1][col_addr + 0][1]);
                  data_A1_casc1 = concat_32b_to_64b_coreC(buf_C[row_addr + 1][col_addr + 1][0],
                                                          buf_C[row_addr + 1][col_addr + 1][1]);
                  data_A1_casc2 = concat_32b_to_64b_coreC(buf_C[row_addr + 1][col_addr + 2][0],
                                                          buf_C[row_addr + 1][col_addr + 2][1]);
                  data_A1_casc3 = concat_32b_to_64b_coreC(buf_C[row_addr + 1][col_addr + 3][0],
                                                          buf_C[row_addr + 1][col_addr + 3][1]);
                  data_A2_casc0 = concat_32b_to_64b_coreC(buf_C[row_addr + 2][col_addr + 0][0],
                                                          buf_C[row_addr + 2][col_addr + 0][1]);
                  data_A2_casc1 = concat_32b_to_64b_coreC(buf_C[row_addr + 2][col_addr + 1][0],
                                                          buf_C[row_addr + 2][col_addr + 1][1]);
                  data_A2_casc2 = concat_32b_to_64b_coreC(buf_C[row_addr + 2][col_addr + 2][0],
                                                          buf_C[row_addr + 2][col_addr + 2][1]);
                  data_A2_casc3 = concat_32b_to_64b_coreC(buf_C[row_addr + 2][col_addr + 3][0],
                                                          buf_C[row_addr + 2][col_addr + 3][1]);
                  data_A3_casc0 = concat_32b_to_64b_coreC(buf_C[row_addr + 3][col_addr + 0][0],
                                                          buf_C[row_addr + 3][col_addr + 0][1]);
                  data_A3_casc1 = concat_32b_to_64b_coreC(buf_C[row_addr + 3][col_addr + 1][0],
                                                          buf_C[row_addr + 3][col_addr + 1][1]);
                  data_A3_casc2 = concat_32b_to_64b_coreC(buf_C[row_addr + 3][col_addr + 2][0],
                                                          buf_C[row_addr + 3][col_addr + 2][1]);
                  data_A3_casc3 = concat_32b_to_64b_coreC(buf_C[row_addr + 3][col_addr + 3][0],
                                                          buf_C[row_addr + 3][col_addr + 3][1]);

                  to_meshA_C00.write(data_A0_casc0);
                  to_meshA_C01.write(data_A0_casc1);
                  to_meshA_C02.write(data_A0_casc2);
                  to_meshA_C03.write(data_A0_casc3);
                  to_meshA_C10.write(data_A1_casc0);
                  to_meshA_C11.write(data_A1_casc1);
                  to_meshA_C12.write(data_A1_casc2);
                  to_meshA_C13.write(data_A1_casc3);
                  to_meshA_C20.write(data_A2_casc0);
                  to_meshA_C21.write(data_A2_casc1);
                  to_meshA_C22.write(data_A2_casc2);
                  to_meshA_C23.write(data_A2_casc3);
                  to_meshA_C30.write(data_A3_casc0);
                  to_meshA_C31.write(data_A3_casc1);
                  to_meshA_C32.write(data_A3_casc2);
                  to_meshA_C33.write(data_A3_casc3);
                }
              }
            }
          }
        }
      }
    }
  }


};

void memcore_C_to_mesh(

    hls::stream<uop_memcore_C_type> &stream_uOP_memcore_C,
    hls::stream<ap_uint<1024>> &stream_to_ddr, hls::stream<ap_uint<1024>> &stream_from_ddr,

    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C00,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C01,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C02,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C03,

    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C10,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C11,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C12,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C13,

    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C20,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C21,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C22,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C23,

    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C30,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C31,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C32,
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C33,

    hls::stream<ap_uint<64>> &to_meshA_C00, hls::stream<ap_uint<64>> &to_meshA_C01,
    hls::stream<ap_uint<64>> &to_meshA_C02, hls::stream<ap_uint<64>> &to_meshA_C03,

    hls::stream<ap_uint<64>> &to_meshA_C10, hls::stream<ap_uint<64>> &to_meshA_C11,
    hls::stream<ap_uint<64>> &to_meshA_C12, hls::stream<ap_uint<64>> &to_meshA_C13,

    hls::stream<ap_uint<64>> &to_meshA_C20, hls::stream<ap_uint<64>> &to_meshA_C21,
    hls::stream<ap_uint<64>> &to_meshA_C22, hls::stream<ap_uint<64>> &to_meshA_C23,

    hls::stream<ap_uint<64>> &to_meshA_C30, hls::stream<ap_uint<64>> &to_meshA_C31,
    hls::stream<ap_uint<64>> &to_meshA_C32, hls::stream<ap_uint<64>> &to_meshA_C33,

    hls::stream<float> &data_channel_to_neighbour_storedram,
    hls::stream<float> &data_channel_to_neighbour_recvmesh,
    hls::stream<float> &data_channel_from_neighbour_storedram,
    hls::stream<float> &data_channel_from_neighbour_recvmesh

) {

#pragma HLS INLINE off

  float buf0_C[BUFC_DIM1][BUFC_DIM2 / 2][2];
  float buf1_C[BUFC_DIM1][BUFC_DIM2 / 2][2];
#pragma HLS bind_storage variable = buf0_C type = RAM_T2P impl = URAM
// for capacity only need ARRAY_RESHAPE 2
#pragma HLS ARRAY_PARTITION variable = buf0_C dim = 1 cyclic factor = 4  
#pragma HLS ARRAY_PARTITION variable = buf0_C dim = 2 cyclic factor = 4
#pragma HLS ARRAY_RESHAPE variable = buf0_C dim = 3 complete

#pragma HLS bind_storage variable = buf1_C type = RAM_T2P impl = URAM
// for capacity only need ARRAY_RESHAPE 2
#pragma HLS ARRAY_PARTITION variable = buf1_C dim = 1 cyclic factor = 4  
#pragma HLS ARRAY_PARTITION variable = buf1_C dim = 2 cyclic factor = 4
#pragma HLS ARRAY_RESHAPE variable = buf1_C dim = 3 complete

  bool is_computing_buf1 = 0;

  uop_memcore_C_type uOP;
  uOP = stream_uOP_memcore_C.read();
  bool is_last_uOP = uOP.is_last_uOP;
WHILE_LOOP:
  while (is_last_uOP == false) {
    bool enable_store_to_dram = uOP.enable_store_to_dram;
    bool enable_send_to_aie = uOP.enable_send_to_aie;
    bool enable_recv_from_aie = uOP.enable_recv_from_aie;
    bool enable_softmax = uOP.enable_softmax;
    bool enable_layer_norm = uOP.enable_layer_norm;
    bool enable_gelu = uOP.enable_gelu;

    ap_uint<9> one_mem_tile_dim1 = uOP.one_mem_tile_dim1;
    ap_uint<10> one_mem_tile_dim2 = uOP.one_mem_tile_dim2;
    ap_uint<3> compute_tile_recv_access_A = uOP.compute_tile_recv_access_A;
    ap_uint<3> compute_tile_recv_access_B = uOP.compute_tile_recv_access_B;
    ap_uint<3> compute_tile_recv_access_K = uOP.compute_tile_recv_access_K;
    ap_uint<3> compute_tile_send_access_A = uOP.compute_tile_send_access_A;
    ap_uint<3> compute_tile_send_access_B = uOP.compute_tile_send_access_B;
    ap_uint<3> compute_tile_send_access_K = uOP.compute_tile_send_access_K;
    uint16_t k_iter = uOP.k_iter;

    uint16_t one_compute_tile_dim1 = 128;
    uint16_t one_compute_tile_dim2 = 128;

    if (is_computing_buf1 == 1 && enable_send_to_aie == 0) {
      storeC_to_dramStream_to_mesh(

          buf0_C, enable_store_to_dram, one_mem_tile_dim1, one_mem_tile_dim2, stream_to_ddr,
          enable_layer_norm, enable_gelu, stream_from_ddr, data_channel_to_neighbour_storedram,
          data_channel_from_neighbour_storedram);
      recvC_from_aie_to_mesh(

          buf1_C, enable_recv_from_aie, enable_softmax, enable_gelu, k_iter, one_compute_tile_dim1,
          one_compute_tile_dim2, compute_tile_recv_access_A, compute_tile_recv_access_B,
          from_computeCore0_C00, from_computeCore0_C01, from_computeCore0_C02,
          from_computeCore0_C03, from_computeCore0_C10, from_computeCore0_C11,
          from_computeCore0_C12, from_computeCore0_C13, from_computeCore0_C20,
          from_computeCore0_C21, from_computeCore0_C22, from_computeCore0_C23,
          from_computeCore0_C30, from_computeCore0_C31, from_computeCore0_C32,
          from_computeCore0_C33, data_channel_to_neighbour_recvmesh,
          data_channel_from_neighbour_recvmesh);
    } else if (is_computing_buf1 == 0 && enable_send_to_aie == 0) {
      storeC_to_dramStream_to_mesh(

          buf1_C, enable_store_to_dram, one_mem_tile_dim1, one_mem_tile_dim2, stream_to_ddr,
          enable_layer_norm, enable_gelu, stream_from_ddr, data_channel_to_neighbour_storedram,
          data_channel_from_neighbour_storedram);
      recvC_from_aie_to_mesh(

          buf0_C, enable_recv_from_aie, enable_softmax, enable_gelu, k_iter, one_compute_tile_dim1,
          one_compute_tile_dim2, compute_tile_recv_access_A, compute_tile_recv_access_B,
          from_computeCore0_C00, from_computeCore0_C01, from_computeCore0_C02,
          from_computeCore0_C03, from_computeCore0_C10, from_computeCore0_C11,
          from_computeCore0_C12, from_computeCore0_C13, from_computeCore0_C20,
          from_computeCore0_C21, from_computeCore0_C22, from_computeCore0_C23,
          from_computeCore0_C30, from_computeCore0_C31, from_computeCore0_C32,
          from_computeCore0_C33, data_channel_to_neighbour_recvmesh,
          data_channel_from_neighbour_recvmesh);
    } else if (is_computing_buf1 == 1 && enable_send_to_aie == 1) {
      sendC_to_meshA(

          buf0_C, enable_send_to_aie, k_iter, one_compute_tile_dim1, one_compute_tile_dim2,
          compute_tile_send_access_A, compute_tile_send_access_B, compute_tile_send_access_K,
          to_meshA_C00, to_meshA_C01, to_meshA_C02, to_meshA_C03, to_meshA_C10, to_meshA_C11,
          to_meshA_C12, to_meshA_C13, to_meshA_C20, to_meshA_C21, to_meshA_C22, to_meshA_C23,
          to_meshA_C30, to_meshA_C31, to_meshA_C32, to_meshA_C33);
      recvC_from_aie_to_mesh(

          buf1_C, enable_recv_from_aie, enable_softmax, enable_gelu, k_iter, one_compute_tile_dim1,
          one_compute_tile_dim2, compute_tile_recv_access_A, compute_tile_recv_access_B,
          from_computeCore0_C00, from_computeCore0_C01, from_computeCore0_C02,
          from_computeCore0_C03, from_computeCore0_C10, from_computeCore0_C11,
          from_computeCore0_C12, from_computeCore0_C13, from_computeCore0_C20,
          from_computeCore0_C21, from_computeCore0_C22, from_computeCore0_C23,
          from_computeCore0_C30, from_computeCore0_C31, from_computeCore0_C32,
          from_computeCore0_C33, data_channel_to_neighbour_recvmesh,
          data_channel_from_neighbour_recvmesh);

    } else if (is_computing_buf1 == 0 && enable_send_to_aie == 1) {
      sendC_to_meshA(

          buf1_C, enable_send_to_aie, k_iter, one_compute_tile_dim1, one_compute_tile_dim2,
          compute_tile_send_access_A, compute_tile_send_access_B, compute_tile_send_access_K,
          to_meshA_C00, to_meshA_C01, to_meshA_C02, to_meshA_C03, to_meshA_C10, to_meshA_C11,
          to_meshA_C12, to_meshA_C13, to_meshA_C20, to_meshA_C21, to_meshA_C22, to_meshA_C23,
          to_meshA_C30, to_meshA_C31, to_meshA_C32, to_meshA_C33);
      recvC_from_aie_to_mesh(

          buf0_C, enable_recv_from_aie, enable_softmax, enable_gelu, k_iter, one_compute_tile_dim1,
          one_compute_tile_dim2, compute_tile_recv_access_A, compute_tile_recv_access_B,
          from_computeCore0_C00, from_computeCore0_C01, from_computeCore0_C02,
          from_computeCore0_C03, from_computeCore0_C10, from_computeCore0_C11,
          from_computeCore0_C12, from_computeCore0_C13, from_computeCore0_C20,
          from_computeCore0_C21, from_computeCore0_C22, from_computeCore0_C23,
          from_computeCore0_C30, from_computeCore0_C31, from_computeCore0_C32,
          from_computeCore0_C33, data_channel_to_neighbour_recvmesh,
          data_channel_from_neighbour_recvmesh);
    }

    if (is_computing_buf1 == 1) {
      is_computing_buf1 = 0;
    } else {
      is_computing_buf1 = 1;
    }

    uOP = stream_uOP_memcore_C.read();
    is_last_uOP = uOP.is_last_uOP;
  }
}
