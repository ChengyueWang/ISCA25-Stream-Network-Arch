#include "memcore_C.h"

float my_tanh(float t_in) {
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


float gelu(float x) {
  float x1;

  x1 = 0.5f * x * (1.0f + my_tanh(0.7978845608f * (x + 0.044715f * x * x * x)));
  return x1;
}

ap_uint<64> concat_32b_to_64b_coreC(ap_uint<32> in0, ap_uint<32> in1) {
  ap_uint<64> out;
  out(31, 0) = in0;
  out(63, 32) = in1;
  return out;
}

void split_64b_to_32b(ap_uint<64> in, float &out0, float &out1) {
  UNION_FP_UINT32 temp0, temp1;
  temp0.uint32_val = in(31, 0);
  temp1.uint32_val = in(63, 32);
  out0 = temp0.float_val;
  out1 = temp1.float_val;
}

void init_C(float buf_C[BUFC_DIM1][BUFC_DIM2 / 2][2], ap_uint<3> compute_tile_recv_access_A,
            ap_uint<3> compute_tile_recv_access_B) {
init_C:
  for (uint16_t row_addr = 0; row_addr < compute_tile_recv_access_A * 128; row_addr += 4) {
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

void storeC_to_dramStream(

    float buf_C[BUFC_DIM1][BUFC_DIM2 / 2][2], bool enable_store_to_dram, ap_uint<9> size_dim1,
    ap_uint<10> size_dim2, hls::stream<ap_uint<1024>> &stream_to_ddr, bool enable_layer_norm,
    bool enable_gelu, hls::stream<ap_uint<1024>> &stream_from_ddr,
    hls::stream<float> &data_channel_to_neighbour,
    hls::stream<float> &data_channel_from_neighbour) {


#pragma HLS STREAM variable = data_channel_to_neighbour depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_from_neighbour depth = 256 type = fifo

  if (enable_store_to_dram) {
    if (enable_gelu == true) {
    GELU0:
      for (int row = 0; row < size_dim1; row++) {
      GELU1:
        for (int col = 0; col < 256; col++) {
#pragma HLS PIPELINE II = 2
#pragma HLS UNROLL factor = 4
#pragma HLS latency min = 200
          buf_C[row][col][0] = gelu(buf_C[row][col][0]);
          buf_C[row][col][1] = gelu(buf_C[row][col][1]);
        }
      }
    }

    if (enable_layer_norm) {

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

        var_buf[row] = hls::sqrtf(v0 + 1e-6);
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

#ifdef SW_EMU_PRINT
      outFile << "Size: (" << BUFC_DIM1 << "," << BUFC_DIM2 << ")\n";
      // Print column headers
      outFile << "   ";  // Indentation for row headers
      for (int j = 0; j < BUFC_DIM2; j++) {
        outFile << std::setw(3) << j;
      }
      outFile << "\n";

      // Print matrix data with row headers
      for (int i = 0; i < BUFC_DIM1; i++) {
        outFile << i << " ";  // Row header
        for (int j = 0; j < BUFC_DIM2 / 2; j++) {
          outFile << " " << buf_C[i][j][0] << " " << buf_C[i][j][1];
        }
        outFile << "\n";
      }
#endif
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
#ifdef SW_EMU_PRINT
            for (int word = 0; word < 16; word++) {  // outFile
              UNION_FP_UINT32 temp_union;
              temp_union.uint32_val = data_1024b(word * 32 + 31, word * 32);  // outFile
              outFile << temp_union.float_val << " ";
            }
            outFile << std::endl;
#endif
          }
        }
      }
    }
    // init_C(buf_C, size_dim1/128, size_dim2/128);
  }

#ifdef SW_EMU_PRINT
  outFile << "EXIT storeC_to_dramStream   ==========================   ";
  outFile.close();
#endif
}

void recvC_from_aie(
#ifdef SW_EMU_PRINT
    int core_id,
#endif
    float buf_C[BUFC_DIM1][BUFC_DIM2 / 2][2], bool enable_sendrecv_aie, bool enable_gelu,
    uint16_t k_iter, uint16_t size_dim1, uint16_t size_dim2, ap_uint<3> compute_tile_recv_access_A,
    ap_uint<3> compute_tile_recv_access_B, hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C00,
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
    hls::stream<ap_axiu<64, 0, 0, 0>> &from_computeCore0_C33) {
#ifdef SW_EMU_PRINT
  std::ofstream outFile(
      "/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/memcoreC" +
          std::to_string(core_id) + "_recvC_from_aie.txt",
      std::ios_base::app);
  outFile << "ENTER recvC_from_aie enable_sendrecv_aie " << enable_sendrecv_aie << " k_iter "
          << k_iter << " size_dim1 " << size_dim1 << " size_dim2 " << size_dim2
          << " compute_tile_recv_access_A " << compute_tile_recv_access_A
          << " compute_tile_recv_access_B " << compute_tile_recv_access_B
          << " ========================  ";
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file for writing." << std::endl;
  }
#endif

  if (enable_sendrecv_aie) {
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

                split_64b_to_32b(from_computeCore0_C00.read().data, data0_C00, data1_C00);
                split_64b_to_32b(from_computeCore0_C01.read().data, data0_C01, data1_C01);
                split_64b_to_32b(from_computeCore0_C02.read().data, data0_C02, data1_C02);
                split_64b_to_32b(from_computeCore0_C03.read().data, data0_C03, data1_C03);
                split_64b_to_32b(from_computeCore0_C10.read().data, data0_C10, data1_C10);
                split_64b_to_32b(from_computeCore0_C11.read().data, data0_C11, data1_C11);
                split_64b_to_32b(from_computeCore0_C12.read().data, data0_C12, data1_C12);
                split_64b_to_32b(from_computeCore0_C13.read().data, data0_C13, data1_C13);
                split_64b_to_32b(from_computeCore0_C20.read().data, data0_C20, data1_C20);
                split_64b_to_32b(from_computeCore0_C21.read().data, data0_C21, data1_C21);
                split_64b_to_32b(from_computeCore0_C22.read().data, data0_C22, data1_C22);
                split_64b_to_32b(from_computeCore0_C23.read().data, data0_C23, data1_C23);
                split_64b_to_32b(from_computeCore0_C30.read().data, data0_C30, data1_C30);
                split_64b_to_32b(from_computeCore0_C31.read().data, data0_C31, data1_C31);
                split_64b_to_32b(from_computeCore0_C32.read().data, data0_C32, data1_C32);
                split_64b_to_32b(from_computeCore0_C33.read().data, data0_C33, data1_C33);

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

#ifdef SW_EMU_PRINT
                outFile << "row_addr " << row_addr << " col_addr " << col_addr << "  ";
                for (int i = 0; i < 4; i++) {
                  for (int j = 0; j < 4; j++) {
                    float temp0 = buf_C[row_addr + i][col_addr + j][0];
                    float temp1 = buf_C[row_addr + i][col_addr + j][1];
                    outFile << temp0 << " " << temp1 << " ";
                  }
                }
                outFile << std::endl;
#endif
              }
            }
          }
#ifdef SW_EMU_PRINT
          // print loop
          outFile << "k: " << k << " reuse_a: " << reuse_a << " reuse_b: " << reuse_b << "\n";
          outFile << "Size: (" << BUFC_DIM1 << "," << BUFC_DIM2 << ")\n";
          // Print column headers
          outFile << "   ";  // Indentation for row headers
          for (int j = 0; j < BUFC_DIM2; j++) {
            outFile << std::setw(3) << j;
          }
          outFile << "\n";

          // Print matrix data with row headers
          for (int i = 0; i < BUFC_DIM1; i++) {
            outFile << i << " ";  // Row header
            for (int j = 0; j < BUFC_DIM2 / 2; j++) {
              outFile << " " << buf_C[i][j][0] << " " << buf_C[i][j][1];
            }
            outFile << "\n";
          }
#endif
        }
      }
    }

#ifdef SW_EMU_PRINT
    outFile << "Size: (" << BUFC_DIM1 << "," << BUFC_DIM2 << ")\n";
    // Print column headers
    outFile << "   ";  // Indentation for row headers
    for (int j = 0; j < BUFC_DIM2; j++) {
      outFile << std::setw(3) << j;
    }
    outFile << "\n";

    // Print matrix data with row headers
    for (int i = 0; i < BUFC_DIM1; i++) {
      outFile << i << " ";  // Row header
      for (int j = 0; j < BUFC_DIM2 / 2; j++) {
        outFile << " " << buf_C[i][j][0] << " " << buf_C[i][j][1];
      }
      outFile << "\n";
    }
#endif
  }
#ifdef SW_EMU_PRINT
  outFile << "EXIT recvC_from_aie   ==========================   ";
  outFile.close();
#endif
};

void memcore_C(
#ifdef SW_EMU_PRINT
    int core_id,
#endif

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

    hls::stream<float> &data_channel_to_neighbour,
    hls::stream<float> &data_channel_from_neighbour) {

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

#ifdef SW_EMU_PRINT
  std::ofstream outFile(
      "/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/memcoreC" +
          std::to_string(core_id) + ".txt",
      std::ios_base::app);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file for writing." << std::endl;
  }
  outFile << "ENTER memcore_C   ==========================   ";
#endif

  bool is_computing_buf1 = 0;

  uop_memcore_C_type uOP;
  bool is_last_uOP = false;
WHILE_LOOP:
  while (is_last_uOP == false) {
    uOP = stream_uOP_memcore_C.read();

#ifdef SW_EMU_PRINT
    outFile << "stream_uOP_memcore_C uOP.is_last_uOP " << uOP.is_last_uOP
            << " uOP.enable_store_to_dram " << uOP.enable_store_to_dram
            << " uOP.enable_send_to_aie " << uOP.enable_send_to_aie << " uOP.enable_recv_from_aie "
            << uOP.enable_recv_from_aie << " uOP.one_mem_tile_dim1 " << uOP.one_mem_tile_dim1
            << " uOP.one_mem_tile_dim2 " << uOP.one_mem_tile_dim2
            << " uOP.compute_tile_recv_access_A " << uOP.compute_tile_recv_access_A
            << " uOP.compute_tile_recv_access_B " << uOP.compute_tile_recv_access_B
            << " uOP.compute_tile_recv_access_K " << uOP.compute_tile_recv_access_K
            << " uOP.k_iter " << uOP.k_iter << " ========================  ";
#endif

    is_last_uOP = uOP.is_last_uOP;

    bool enable_store_to_dram = uOP.enable_store_to_dram;
    bool enable_send_to_aie = uOP.enable_send_to_aie;
    bool enable_recv_from_aie = uOP.enable_recv_from_aie;
    bool enable_layer_norm = uOP.enable_layer_norm;
    bool enable_gelu = uOP.enable_gelu;

    ap_uint<9> one_mem_tile_dim1 = uOP.one_mem_tile_dim1;
    ap_uint<10> one_mem_tile_dim2 = uOP.one_mem_tile_dim2;
    ap_uint<3> compute_tile_recv_access_A = uOP.compute_tile_recv_access_A;
    ap_uint<3> compute_tile_recv_access_B = uOP.compute_tile_recv_access_B;
    ap_uint<3> compute_tile_recv_access_K = uOP.compute_tile_recv_access_K;
    uint16_t k_iter = uOP.k_iter;

    uint16_t one_compute_tile_dim1 = 128;
    uint16_t one_compute_tile_dim2 = 128;

    if (is_computing_buf1 == 1) {
      storeC_to_dramStream(

          buf0_C, enable_store_to_dram, one_mem_tile_dim1, one_mem_tile_dim2, stream_to_ddr,
          enable_layer_norm, enable_gelu, stream_from_ddr, data_channel_to_neighbour,
          data_channel_from_neighbour);
      recvC_from_aie(

          buf1_C, enable_recv_from_aie, enable_gelu, k_iter, one_compute_tile_dim1,
          one_compute_tile_dim2, compute_tile_recv_access_A, compute_tile_recv_access_B,
          from_computeCore0_C00, from_computeCore0_C01, from_computeCore0_C02,
          from_computeCore0_C03, from_computeCore0_C10, from_computeCore0_C11,
          from_computeCore0_C12, from_computeCore0_C13, from_computeCore0_C20,
          from_computeCore0_C21, from_computeCore0_C22, from_computeCore0_C23,
          from_computeCore0_C30, from_computeCore0_C31, from_computeCore0_C32,
          from_computeCore0_C33);
    } else {
      storeC_to_dramStream(

          buf1_C, enable_store_to_dram, one_mem_tile_dim1, one_mem_tile_dim2, stream_to_ddr,
          enable_layer_norm, enable_gelu, stream_from_ddr, data_channel_to_neighbour,
          data_channel_from_neighbour);
      recvC_from_aie(

          buf0_C, enable_recv_from_aie, enable_gelu, k_iter, one_compute_tile_dim1,
          one_compute_tile_dim2, compute_tile_recv_access_A, compute_tile_recv_access_B,
          from_computeCore0_C00, from_computeCore0_C01, from_computeCore0_C02,
          from_computeCore0_C03, from_computeCore0_C10, from_computeCore0_C11,
          from_computeCore0_C12, from_computeCore0_C13, from_computeCore0_C20,
          from_computeCore0_C21, from_computeCore0_C22, from_computeCore0_C23,
          from_computeCore0_C30, from_computeCore0_C31, from_computeCore0_C32,
          from_computeCore0_C33);
    }

    if (is_computing_buf1 == 1) {
      is_computing_buf1 = 0;
    } else {
      is_computing_buf1 = 1;
    }
  }

}
