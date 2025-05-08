#include "decoder_uop.h"

void mop2uop_memcore_A(
    hls::stream<mop_memcore_A_type> &stream_mOP_memcore_A,
    hls::stream<uop_memcore_A_type> &stream_uOP_memcore_A) {

  mop_memcore_A_type mOP;

  bool is_last_mOP = false;

  while (is_last_mOP == false) {
    mOP = stream_mOP_memcore_A.read();
    is_last_mOP = mOP.is_last_mOP;
    if (is_last_mOP == false) {
      for (uint32_t iter = 0; iter < mOP.repeat_num; iter++) {
#pragma HLS PIPELINE II = 8
        uop_memcore_A_type uop;
        uop.enable_load_from_dram = mOP.enable_load_from_dram;
        uop.enable_send_to_aie = mOP.enable_send_to_aie;
        uop.is_last_uOP = false;
        uop.one_mem_tile_dim1 = mOP.one_mem_tile_dim1;
        uop.one_mem_tile_dim2 = mOP.one_mem_tile_dim2;
        uop.compute_tile_access_A = mOP.compute_tile_access_A;
        uop.compute_tile_access_B = mOP.compute_tile_access_B;

        stream_uOP_memcore_A.write(uop);
      }

    }
  }

  uop_memcore_A_type uop;
  uop.enable_load_from_dram = 0;
  uop.enable_send_to_aie = 0;
  uop.is_last_uOP = true;
  stream_uOP_memcore_A.write(uop);

}

void mop2uop_memcore_B(

    hls::stream<mop_memcore_B_type> &stream_mOP_memcore_B,
    hls::stream<uop_memcore_B_type> &stream_uOP_memcore_B) {


  mop_memcore_B_type mOP;

  bool is_last_mOP = false;

  while (is_last_mOP == false) {
    mOP = stream_mOP_memcore_B.read();

    is_last_mOP = mOP.is_last_mOP;
    if (is_last_mOP == false) {
      for (uint32_t iter = 0; iter < mOP.repeat_num; iter++) {
#pragma HLS PIPELINE II = 8
        uop_memcore_B_type uop;
        uop.enable_load_from_dram = mOP.enable_load_from_dram;
        uop.enable_send_to_aie = mOP.enable_send_to_aie;
        uop.is_last_uOP = false;
        uop.is_loading_bias = mOP.is_loading_bias;
        uop.enable_transpose = mOP.enable_transpose;
        uop.one_mem_tile_dim1 = mOP.one_mem_tile_dim1;
        uop.one_mem_tile_dim2 = mOP.one_mem_tile_dim2;
        uop.compute_tile_access_A = mOP.compute_tile_access_A;
        uop.compute_tile_access_B = mOP.compute_tile_access_B;
        uop.compute_tile_access_K = mOP.compute_tile_access_K;

        stream_uOP_memcore_B.write(uop);
      }
    }
  }

  uop_memcore_B_type uop;
  uop.enable_load_from_dram = 0;
  uop.enable_send_to_aie = 0;
  uop.is_last_uOP = true;
  stream_uOP_memcore_B.write(uop);

}

void mop2uop_memcore_C(

    hls::stream<mop_memcore_C_type> &stream_mOP_memcore_C,
    hls::stream<uop_memcore_C_type> &stream_uOP_memcore_C) {



  mop_memcore_C_type mOP;

  bool is_last_mOP = false;

  while (is_last_mOP == false) {
    mOP = stream_mOP_memcore_C.read();

    is_last_mOP = mOP.is_last_mOP;
    if (is_last_mOP == false) {
      for (uint32_t iter = 0; iter < mOP.repeat_num; iter++) {
#pragma HLS PIPELINE II = 8
        uop_memcore_C_type uop;

        uop.enable_store_to_dram = mOP.enable_store_to_dram;
        uop.enable_send_to_aie = mOP.enable_send_to_aie;
        uop.enable_recv_from_aie = mOP.enable_recv_from_aie;
        uop.enable_softmax = mOP.enable_softmax;
        uop.enable_layer_norm = mOP.enable_layer_norm;
        uop.enable_gelu = mOP.enable_gelu;

        uop.one_mem_tile_dim1 = mOP.one_mem_tile_dim1;
        uop.one_mem_tile_dim2 = mOP.one_mem_tile_dim2;
        uop.compute_tile_recv_access_A = mOP.compute_tile_recv_access_A;
        uop.compute_tile_recv_access_B = mOP.compute_tile_recv_access_B;
        uop.compute_tile_recv_access_K = mOP.compute_tile_recv_access_K;
        uop.compute_tile_send_access_A = mOP.compute_tile_send_access_A;
        uop.compute_tile_send_access_B = mOP.compute_tile_send_access_B;
        uop.compute_tile_send_access_K = mOP.compute_tile_send_access_K;
        uop.k_iter = mOP.k_iter;
        uop.is_last_uOP = false;

        stream_uOP_memcore_C.write(uop);
      }
    }
  }

  uop_memcore_C_type uop;
  uop.enable_store_to_dram = 0;
  uop.enable_send_to_aie = 0;
  uop.enable_recv_from_aie = 0;
  uop.is_last_uOP = true;
  stream_uOP_memcore_C.write(uop);


}

void mop2uop_ddr(hls::stream<mop_ddr_type> &stream_mOP_ddr,
                 hls::stream<uop_ddr_type> &stream_uOP_ddr) {


  bool is_last_mOP = false;

  while (is_last_mOP == false) {
    uint32_t mops_buffer_window[512];
#pragma HLS bind_storage variable = mops_buffer_window type = RAM_1P impl = BRAM

    union_mop_ddr_dram mOP_union;
    mOP_union.val = stream_mOP_ddr.read();

    is_last_mOP = mOP_union.val.is_last_mOP;
    uint16_t mop_buffer_window_size = mOP_union.val.mop_buffer_window_size;
    uint32_t repeat_num = mOP_union.val.repeat_num;

    if (is_last_mOP == false) {
      for (uint8_t window_id = 0; window_id < mop_buffer_window_size; window_id++) {
#pragma HLS PIPELINE II = 8
        if (window_id != 0) {
          mOP_union.val = stream_mOP_ddr.read();
        }
        mops_buffer_window[window_id * MOP_CNT4B_DDR + 0] = mOP_union.raw_32b[0];
        mops_buffer_window[window_id * MOP_CNT4B_DDR + 1] = mOP_union.raw_32b[1];
        mops_buffer_window[window_id * MOP_CNT4B_DDR + 2] = mOP_union.raw_32b[2];
        mops_buffer_window[window_id * MOP_CNT4B_DDR + 3] = mOP_union.raw_32b[3];
        mops_buffer_window[window_id * MOP_CNT4B_DDR + 4] = mOP_union.raw_32b[4];
        mops_buffer_window[window_id * MOP_CNT4B_DDR + 5] = mOP_union.raw_32b[5];
      }

      for (uint16_t iter = 0; iter < repeat_num; iter++) {
        for (uint8_t window_id = 0; window_id < mop_buffer_window_size; window_id++) {
          union_mop_ddr_dram mOP_union_read;
          for (uint8_t mop_id = 0; mop_id < MOP_CNT4B_DDR; mop_id++) {
#pragma HLS PIPELINE II = 8
            mOP_union_read.raw_32b[mop_id] = mops_buffer_window[window_id * MOP_CNT4B_DDR + mop_id];
          }
          mop_ddr_type mOP = mOP_union_read.val;

          for (uint8_t chunk_id = 0; chunk_id < mOP.chunk_count; chunk_id++) {
#pragma HLS PIPELINE II = 8
            uop_ddr_type uop;
            uop.start_address =
                mOP.start_address + iter * mOP.address_offset + chunk_id * mOP.stride_offset;
            uop.chunck_size = mOP.chunck_size;

            uop.is_load = mOP.is_load;
            uop.is_store = mOP.is_store;

            uop.load_to_memcoreA0 = mOP.load_to_memcoreA0;
            uop.load_to_memcoreA1 = mOP.load_to_memcoreA1;
            uop.load_to_memcoreA2 = mOP.load_to_memcoreA2;
            uop.load_to_memcoreB0 = mOP.load_to_memcoreB0;
            uop.load_to_memcoreB1 = mOP.load_to_memcoreB1;
            uop.load_to_memcoreB2 = mOP.load_to_memcoreB2;

            uop.store_from_memcoreC0 = mOP.store_from_memcoreC0;
            uop.store_from_memcoreC1 = mOP.store_from_memcoreC1;
            uop.store_from_memcoreC2 = mOP.store_from_memcoreC2;
            uop.store_from_memcoreC3 = mOP.store_from_memcoreC3;
            uop.store_from_memcoreC4 = mOP.store_from_memcoreC4;
            uop.store_from_memcoreC5 = mOP.store_from_memcoreC5;

            uop.is_last_uOP = false;
            stream_uOP_ddr.write(uop);

          }
        }
      }
    }
  }

  uop_ddr_type uop;
  uop.chunck_size = 0;
  uop.is_load = false;
  uop.is_store = false;
  uop.load_to_memcoreA0 = false;
  uop.load_to_memcoreA1 = false;
  uop.load_to_memcoreA2 = false;
  uop.load_to_memcoreB0 = false;
  uop.load_to_memcoreB1 = false;
  uop.load_to_memcoreB2 = false;
  uop.store_from_memcoreC0 = false;
  uop.store_from_memcoreC1 = false;
  uop.store_from_memcoreC2 = false;
  uop.store_from_memcoreC3 = false;
  uop.store_from_memcoreC4 = false;
  uop.store_from_memcoreC5 = false;
  uop.is_last_uOP = true;
  stream_uOP_ddr.write(uop);


}

void mop2uop_loadB_dram(hls::stream<mop_loadB_dram_type> &stream_mOP_loadB_dram,
                        hls::stream<uop_loadB_dram_type> &stream_uOP_loadB_dram) {


  bool is_last_mOP = false;

  while (is_last_mOP == false) {
    uint32_t mops_buffer_window[512];
#pragma HLS bind_storage variable = mops_buffer_window type = RAM_1P impl = BRAM

    union_mop_load_B_dram mOP_union;
    mOP_union.val = stream_mOP_loadB_dram.read();

    is_last_mOP = mOP_union.val.is_last_mOP;
    uint16_t mop_buffer_window_size = mOP_union.val.mop_buffer_window_size;
    uint32_t repeat_num = mOP_union.val.repeat_num;

    if (is_last_mOP == false) {
      for (uint8_t window_id = 0; window_id < mop_buffer_window_size; window_id++) {
#pragma HLS PIPELINE II = 8
        if (window_id != 0) {
          mOP_union.val = stream_mOP_loadB_dram.read();
        }
        mops_buffer_window[window_id * MOP_CNT4B_LOAD_B_DRAM + 0] = mOP_union.raw_32b[0];
        mops_buffer_window[window_id * MOP_CNT4B_LOAD_B_DRAM + 1] = mOP_union.raw_32b[1];
        mops_buffer_window[window_id * MOP_CNT4B_LOAD_B_DRAM + 2] = mOP_union.raw_32b[2];
        mops_buffer_window[window_id * MOP_CNT4B_LOAD_B_DRAM + 3] = mOP_union.raw_32b[3];
        mops_buffer_window[window_id * MOP_CNT4B_LOAD_B_DRAM + 4] = mOP_union.raw_32b[4];
        mops_buffer_window[window_id * MOP_CNT4B_LOAD_B_DRAM + 5] = mOP_union.raw_32b[5];
      }

      for (uint16_t iter = 0; iter < repeat_num; iter++) {
        for (uint8_t window_id = 0; window_id < mop_buffer_window_size; window_id++) {
          union_mop_load_B_dram mOP_union_read;
          for (uint8_t mop_id = 0; mop_id < MOP_CNT4B_LOAD_B_DRAM; mop_id++) {
#pragma HLS PIPELINE II = 8
            mOP_union_read.raw_32b[mop_id] =
                mops_buffer_window[window_id * MOP_CNT4B_LOAD_B_DRAM + mop_id];
          }
          mop_loadB_dram_type mOP = mOP_union_read.val;

          for (uint8_t chunk_id = 0; chunk_id < mOP.chunk_count; chunk_id++) {
#pragma HLS PIPELINE II = 8
            uop_loadB_dram_type uop;
            uop.start_address =
                mOP.start_address + iter * mOP.address_offset + chunk_id * mOP.stride_offset;
            uop.chunck_size = mOP.chunck_size;
            uop.load_to_memcoreB0 = mOP.load_to_memcoreB0;
            uop.load_to_memcoreB1 = mOP.load_to_memcoreB1;
            uop.is_loading_bias = mOP.is_loading_bias;
            uop.is_last_uOP = false;
            stream_uOP_loadB_dram.write(uop);

          }
        }
      }
    }
  }

  uop_loadB_dram_type uop;
  uop.chunck_size = 0;
  uop.load_to_memcoreB0 = false;
  uop.load_to_memcoreB1 = false;
  uop.is_loading_bias = false;
  uop.is_last_uOP = true;
  stream_uOP_loadB_dram.write(uop);


}

void mop2uop_mesh_sendA(hls::stream<mop_mesh_sendA_type> &stream_mOP_mesh_sendA,
                        hls::stream<uop_mesh_sendA_type> &stream_uOP_mesh_sendA) {


  bool is_last_mOP = false;
WHILE_LOOP:
  while (is_last_mOP == false) {
    uint32_t mops_buffer_window[512];
#pragma HLS bind_storage variable = mops_buffer_window type = RAM_1P impl = BRAM

    union_mop_meshA mOP_union;
    mOP_union.val = stream_mOP_mesh_sendA.read();

    is_last_mOP = mOP_union.val.is_last_mOP;
    uint8_t mop_buffer_window_size = mOP_union.val.mop_buffer_window_size;
    uint16_t repeat_num = mOP_union.val.repeat_num;
    if (is_last_mOP == false) {
      for (uint8_t window_id = 0; window_id < mop_buffer_window_size; window_id++) {
#pragma HLS PIPELINE II = 8
        if (window_id != 0) {
          mOP_union.val = stream_mOP_mesh_sendA.read();
        }
        mops_buffer_window[window_id * MOP_CNT4B_MESHA + 0] = mOP_union.raw_32b[0];
        mops_buffer_window[window_id * MOP_CNT4B_MESHA + 1] = mOP_union.raw_32b[1];
      }

    REPEAT_NUM:
      for (uint16_t iter = 0; iter < repeat_num; iter++) {
      WINDOW:
        for (uint8_t window_id = 0; window_id < mop_buffer_window_size; window_id++) {
#pragma HLS PIPELINE II = 4
#pragma HLS latency min = 6
          union_mop_meshA mOP_union_read;
          mOP_union_read.raw_32b[0] = mops_buffer_window[window_id * 2 + 0];
          mOP_union_read.raw_32b[1] = mops_buffer_window[window_id * 2 + 1];
          mop_mesh_sendA_type mOP = mOP_union_read.val;
          uop_mesh_sendA_type uop;
          uop.size = mOP.size;
          uop.memcoreA0_to_computecore0 = mOP.memcoreA0_to_computecore0;
          uop.memcoreA0_to_computecore1 = mOP.memcoreA0_to_computecore1;
          uop.memcoreA1_to_computecore2 = mOP.memcoreA1_to_computecore2;
          uop.memcoreA1_to_computecore3 = mOP.memcoreA1_to_computecore3;
          uop.memcoreA2_to_computecore4 = mOP.memcoreA2_to_computecore4;
          uop.memcoreA2_to_computecore5 = mOP.memcoreA2_to_computecore5;
          uop.memcoreC0_to_computecore4 = mOP.memcoreC0_to_computecore4;
          uop.memcoreC1_to_computecore4 = mOP.memcoreC1_to_computecore4;
          uop.memcoreC2_to_computecore5 = mOP.memcoreC2_to_computecore5;
          uop.memcoreC3_to_computecore5 = mOP.memcoreC3_to_computecore5;
          uop.is_last_uOP = false;
          stream_uOP_mesh_sendA.write(uop);

        }
      }
    }
  }

  uop_mesh_sendA_type uop;
  uop.size = 0;
  uop.memcoreA0_to_computecore0 = false;
  uop.memcoreA0_to_computecore1 = false;
  uop.memcoreA1_to_computecore2 = false;
  uop.memcoreA1_to_computecore3 = false;
  uop.memcoreA2_to_computecore4 = false;
  uop.memcoreA2_to_computecore5 = false;
  uop.memcoreC0_to_computecore4 = false;
  uop.memcoreC1_to_computecore4 = false;
  uop.memcoreC2_to_computecore5 = false;
  uop.memcoreC3_to_computecore5 = false;
  uop.is_last_uOP = true;
  stream_uOP_mesh_sendA.write(uop);

}

void mop2uop_mesh_sendB(hls::stream<mop_mesh_sendB_type> &stream_mOP_mesh_sendB,
                        hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB) {


  mop_mesh_sendB_type mOP;
  bool is_last_mOP = false;
  while (is_last_mOP == false) {
    uint32_t mops_buffer_window[512];
#pragma HLS bind_storage variable = mops_buffer_window type = RAM_1P impl = BRAM

    union_mop_meshB mOP_union;
    mOP_union.val = stream_mOP_mesh_sendB.read();

    is_last_mOP = mOP_union.val.is_last_mOP;
    uint8_t mop_buffer_window_size = mOP_union.val.mop_buffer_window_size;
    uint32_t repeat_num = mOP_union.val.repeat_num;

    if (is_last_mOP == false) {
      for (uint8_t window_id = 0; window_id < mop_buffer_window_size; window_id++) {
#pragma HLS PIPELINE II = 8
        if (window_id != 0) {
          mOP_union.val = stream_mOP_mesh_sendB.read();
        }
        mops_buffer_window[window_id * MOP_CNT4B_MESHB + 0] = mOP_union.raw_32b[0];
        mops_buffer_window[window_id * MOP_CNT4B_MESHB + 1] = mOP_union.raw_32b[1];
      }

      for (uint16_t iter = 0; iter < repeat_num; iter++) {
        for (uint8_t window_id = 0; window_id < mop_buffer_window_size; window_id++) {
#pragma HLS PIPELINE II = 4
#pragma HLS latency min = 6
          union_mop_meshB mOP_union_read;
          mOP_union_read.raw_32b[0] = mops_buffer_window[window_id * 2 + 0];
          mOP_union_read.raw_32b[1] = mops_buffer_window[window_id * 2 + 1];

          mop_mesh_sendB_type mOP = mOP_union_read.val;
          uop_mesh_sendB_type uop;
          uop.size = mOP.size;
          uop.memcore0_to_computecore0 = mOP.memcore0_to_computecore0;
          uop.memcore0_to_computecore2 = mOP.memcore0_to_computecore2;
          uop.memcore0_to_computecore4 = mOP.memcore0_to_computecore4;
          uop.memcore1_to_computecore1 = mOP.memcore1_to_computecore1;
          uop.memcore1_to_computecore3 = mOP.memcore1_to_computecore3;
          uop.memcore1_to_computecore5 = mOP.memcore1_to_computecore5;
          uop.memcore2_to_computecore4 = mOP.memcore2_to_computecore4;
          uop.memcore2_to_computecore5 = mOP.memcore2_to_computecore5;
          uop.is_last_uOP = false;
          stream_uOP_mesh_sendB.write(uop);

        }
      }
    }
  }

  uop_mesh_sendB_type uop;
  uop.size = 0;
  uop.memcore0_to_computecore0 = false;
  uop.memcore0_to_computecore2 = false;
  uop.memcore0_to_computecore4 = false;
  uop.memcore1_to_computecore1 = false;
  uop.memcore1_to_computecore3 = false;
  uop.memcore1_to_computecore5 = false;
  uop.memcore2_to_computecore4 = false;
  uop.memcore2_to_computecore5 = false;
  uop.is_last_uOP = true;
  stream_uOP_mesh_sendB.write(uop);

}

void read_instructions_from_offchip(uint32_t *vliw_memory,
                                    hls::stream<uint32_t> &stream_instruction_sequence) {
  uint32_t count4B = vliw_memory[0];

  for (int inst_4B_id = 0; inst_4B_id < count4B + 1; inst_4B_id++) {
#pragma HLS PIPELINE II = 1
    stream_instruction_sequence.write(vliw_memory[inst_4B_id + 1]);
  }
}

void instructions_to_mop_dispenser(hls::stream<uint32_t> &stream_instruction_sequence,
                                   hls::stream<mop_ddr_type> &stream_mOP_ddr,
                                   hls::stream<mop_loadB_dram_type> &stream_mOP_loadB_dram,
                                   hls::stream<mop_memcore_A_type> &stream_mOP_memcore0_A,
                                   hls::stream<mop_memcore_A_type> &stream_mOP_memcore1_A,
                                   hls::stream<mop_memcore_A_type> &stream_mOP_memcore2_A,
                                   hls::stream<mop_memcore_B_type> &stream_mOP_memcore0_B,
                                   hls::stream<mop_memcore_B_type> &stream_mOP_memcore1_B,
                                   hls::stream<mop_memcore_B_type> &stream_mOP_memcore2_B,
                                   hls::stream<mop_memcore_C_type> &stream_mOP_memcore0_C,
                                   hls::stream<mop_memcore_C_type> &stream_mOP_memcore1_C,
                                   hls::stream<mop_memcore_C_type> &stream_mOP_memcore2_C,
                                   hls::stream<mop_memcore_C_type> &stream_mOP_memcore3_C,
                                   hls::stream<mop_memcore_C_type> &stream_mOP_memcore4_C,
                                   hls::stream<mop_memcore_C_type> &stream_mOP_memcore5_C,
                                   hls::stream<mop_mesh_sendA_type> &stream_mOP_mesh_sendA,
                                   hls::stream<mop_mesh_sendB_type> &stream_mOP_mesh_sendB) {


  uint32_t countInstPkt = stream_instruction_sequence.read();

  union_inst_header inst_header;
  inst_header.raw_32b = stream_instruction_sequence.read();

INST_PKT:
  for (uint32_t inst_pkt_id = 0; inst_pkt_id < countInstPkt; inst_pkt_id++) {


    ap_uint<LEN_OPCODE> opcode = inst_header.inst_val.opcode;
    ap_uint<LEN_MASK> mask = inst_header.inst_val.mask;
    ap_uint<LEN_REPEAT_NUM> repeat_num = inst_header.inst_val.repeat_num;
    ap_uint<LEN_MOP_BUFFER_WINDOW_SIZE> mop_buffer_window_size =
        inst_header.inst_val.mop_buffer_window_size;
    bool is_last_mOP = inst_header.inst_val.is_last_mOP;

    if (opcode == OPCODE_DDR_DRAM) {
      if (is_last_mOP == false) {
      CASE_DDR:
        for (uint16_t w = 0; w < mop_buffer_window_size; w++) {
#pragma HLS PIPELINE II = 8
          union_inst_ddr inst;
          inst.raw_32b[0] = stream_instruction_sequence.read();
          inst.raw_32b[1] = stream_instruction_sequence.read();
          inst.raw_32b[2] = stream_instruction_sequence.read();
          inst.raw_32b[3] = stream_instruction_sequence.read();
          mop_ddr_type mOP;
          mOP.repeat_num = repeat_num;
          mOP.mop_buffer_window_size = mop_buffer_window_size;
          mOP.start_address = inst.inst_val.start_address;
          mOP.address_offset = inst.inst_val.address_offset;
          mOP.chunck_size = inst.inst_val.chunck_size;
          mOP.stride_offset = inst.inst_val.stride_offset;
          mOP.chunk_count = inst.inst_val.chunk_count;

          mOP.is_store = inst.inst_val.is_store;
          mOP.is_load = inst.inst_val.is_load;

          mOP.load_to_memcoreA0 = inst.inst_val.load_to_memcoreA0;
          mOP.load_to_memcoreA1 = inst.inst_val.load_to_memcoreA1;
          mOP.load_to_memcoreA2 = inst.inst_val.load_to_memcoreA2;
          mOP.load_to_memcoreB0 = inst.inst_val.load_to_memcoreB0;
          mOP.load_to_memcoreB1 = inst.inst_val.load_to_memcoreB1;
          mOP.load_to_memcoreB2 = inst.inst_val.load_to_memcoreB2;

          mOP.store_from_memcoreC0 = inst.inst_val.store_from_memcoreC0;
          mOP.store_from_memcoreC1 = inst.inst_val.store_from_memcoreC1;
          mOP.store_from_memcoreC2 = inst.inst_val.store_from_memcoreC2;
          mOP.store_from_memcoreC3 = inst.inst_val.store_from_memcoreC3;
          mOP.store_from_memcoreC4 = inst.inst_val.store_from_memcoreC4;
          mOP.store_from_memcoreC5 = inst.inst_val.store_from_memcoreC5;

          mOP.is_last_mOP = false;

          stream_mOP_ddr.write(mOP);
        }
      } else {
        mop_ddr_type mOP;
        mOP.is_last_mOP = true;
        stream_mOP_ddr.write(mOP);
      }
    } else if (opcode == OPCODE_LOADB_DRAM) {
      if (is_last_mOP == false) {
      CASE_LOADB:
        for (uint16_t w = 0; w < mop_buffer_window_size; w++) {
#pragma HLS PIPELINE II = 8
          union_inst_load_B_dram inst;
          inst.raw_32b[0] = stream_instruction_sequence.read();
          inst.raw_32b[1] = stream_instruction_sequence.read();
          inst.raw_32b[2] = stream_instruction_sequence.read();
          inst.raw_32b[3] = stream_instruction_sequence.read();
          mop_loadB_dram_type mOP;
          mOP.repeat_num = repeat_num;
          mOP.mop_buffer_window_size = mop_buffer_window_size;
          mOP.start_address = inst.inst_val.start_address;
          mOP.address_offset = inst.inst_val.address_offset;
          mOP.chunck_size = inst.inst_val.chunck_size;
          mOP.stride_offset = inst.inst_val.stride_offset;
          mOP.chunk_count = inst.inst_val.chunk_count;
          mOP.load_to_memcoreB0 = inst.inst_val.load_to_memcoreB0;
          mOP.load_to_memcoreB1 = inst.inst_val.load_to_memcoreB1;
          mOP.is_loading_bias = inst.inst_val.is_loading_bias;
          mOP.is_last_mOP = false;

          stream_mOP_loadB_dram.write(mOP);
        }
      } else {
        mop_loadB_dram_type mOP;
        mOP.is_last_mOP = true;
        stream_mOP_loadB_dram.write(mOP);
      }
    } else if (opcode == OPCODE_MEMCORE_A) {
      if (is_last_mOP == false) {
      CASE_MEMCOREA:
        for (uint16_t w = 0; w < mop_buffer_window_size; w++) {
#pragma HLS PIPELINE II = 8
          union_inst_memcore_A inst;
          inst.raw_32b[0] = stream_instruction_sequence.read();
          mop_memcore_A_type mOP;
          mOP.repeat_num = repeat_num;
          mOP.one_mem_tile_dim1 = inst.inst_val.one_mem_tile_dim1;
          mOP.one_mem_tile_dim2 = inst.inst_val.one_mem_tile_dim2;
          mOP.enable_load_from_dram = inst.inst_val.enable_load_from_dram;
          mOP.enable_send_to_aie = inst.inst_val.enable_send_to_aie;
          mOP.compute_tile_access_A = inst.inst_val.compute_tile_access_A;
          mOP.compute_tile_access_B = inst.inst_val.compute_tile_access_B;
          mOP.is_last_mOP = false;

          if (mask(0, 0) == true) {
            stream_mOP_memcore0_A.write(mOP);
          }
          if (mask(1, 1) == true) {
            stream_mOP_memcore1_A.write(mOP);
          }
          if (mask(2, 2) == true) {
            stream_mOP_memcore2_A.write(mOP);
          }
        }
      } else {
        mop_memcore_A_type mOP;
        mOP.is_last_mOP = true;
        if (mask(0, 0) == true) {
          stream_mOP_memcore0_A.write(mOP);
        }
        if (mask(1, 1) == true) {
          stream_mOP_memcore1_A.write(mOP);
        }
        if (mask(2, 2) == true) {
          stream_mOP_memcore2_A.write(mOP);
        }
      }
    } else if (opcode == OPCODE_MEMCORE_B) {
      if (is_last_mOP == false) {
      CASE_MEMCOREB:
        for (uint16_t w = 0; w < mop_buffer_window_size; w++) {
#pragma HLS PIPELINE II = 8
          union_inst_memcore_B inst;
          inst.raw_32b[0] = stream_instruction_sequence.read();
          inst.raw_32b[1] = stream_instruction_sequence.read();
          mop_memcore_B_type mOP;
          mOP.repeat_num = repeat_num;
          mOP.one_mem_tile_dim1 = inst.inst_val.one_mem_tile_dim1;
          mOP.one_mem_tile_dim2 = inst.inst_val.one_mem_tile_dim2;
          mOP.enable_load_from_dram = inst.inst_val.enable_load_from_dram;
          mOP.enable_send_to_aie = inst.inst_val.enable_send_to_aie;
          mOP.compute_tile_access_A = inst.inst_val.compute_tile_access_A;
          mOP.compute_tile_access_B = inst.inst_val.compute_tile_access_B;
          mOP.compute_tile_access_K = inst.inst_val.compute_tile_access_K;
          mOP.is_loading_bias = inst.inst_val.is_loading_bias;
          mOP.enable_transpose = inst.inst_val.enable_transpose;
          mOP.is_last_mOP = false;

          if (mask(0, 0) == true) {
            stream_mOP_memcore0_B.write(mOP);
          }
          if (mask(1, 1) == true) {
            stream_mOP_memcore1_B.write(mOP);
          }
          if (mask(2, 2) == true) {
            stream_mOP_memcore2_B.write(mOP);
          }
        }
      } else {
        mop_memcore_B_type mOP;
        mOP.is_last_mOP = true;
        if (mask(0, 0) == true) {
          stream_mOP_memcore0_B.write(mOP);
        }
        if (mask(1, 1) == true) {
          stream_mOP_memcore1_B.write(mOP);
        }
        if (mask(2, 2) == true) {
          stream_mOP_memcore2_B.write(mOP);
        }
      }
    } else if (opcode == OPCODE_MEMCORE_C) {
      if (is_last_mOP == false) {
      CASE_MEMCOREC:
        for (uint16_t w = 0; w < mop_buffer_window_size; w++) {
#pragma HLS PIPELINE II = 8
          union_inst_memcore_C inst;
          inst.raw_32b[0] = stream_instruction_sequence.read();
          inst.raw_32b[1] = stream_instruction_sequence.read();

          mop_memcore_C_type mOP;
          mOP.repeat_num = repeat_num;
          mOP.enable_store_to_dram = inst.inst_val.enable_store_to_dram;
          mOP.enable_send_to_aie = inst.inst_val.enable_send_to_aie;
          mOP.enable_recv_from_aie = inst.inst_val.enable_recv_from_aie;
          mOP.enable_softmax = inst.inst_val.enable_softmax;
          mOP.enable_layer_norm = inst.inst_val.enable_layer_norm;
          mOP.enable_gelu = inst.inst_val.enable_gelu;
          mOP.one_mem_tile_dim1 = inst.inst_val.one_mem_tile_dim1;
          mOP.one_mem_tile_dim2 = inst.inst_val.one_mem_tile_dim2;
          mOP.compute_tile_recv_access_A = inst.inst_val.compute_tile_recv_access_A;
          mOP.compute_tile_recv_access_B = inst.inst_val.compute_tile_recv_access_B;
          mOP.compute_tile_recv_access_K = inst.inst_val.compute_tile_recv_access_K;
          mOP.compute_tile_send_access_A = inst.inst_val.compute_tile_send_access_A;
          mOP.compute_tile_send_access_B = inst.inst_val.compute_tile_send_access_B;
          mOP.compute_tile_send_access_K = inst.inst_val.compute_tile_send_access_K;
          mOP.k_iter = inst.inst_val.k_iter;
          mOP.is_last_mOP = false;

          if (mask(0, 0) == true) {
            stream_mOP_memcore0_C.write(mOP);
          }
          if (mask(1, 1) == true) {
            stream_mOP_memcore1_C.write(mOP);
          }
          if (mask(2, 2) == true) {
            stream_mOP_memcore2_C.write(mOP);
          }
          if (mask(3, 3) == true) {
            stream_mOP_memcore3_C.write(mOP);
          }
          if (mask(4, 4) == true) {
            stream_mOP_memcore4_C.write(mOP);
          }
          if (mask(5, 5) == true) {
            stream_mOP_memcore5_C.write(mOP);
          }
        }
      } else {
        mop_memcore_C_type mOP;
        mOP.is_last_mOP = true;
        if (mask(0, 0) == true) {
          stream_mOP_memcore0_C.write(mOP);
        }
        if (mask(1, 1) == true) {
          stream_mOP_memcore1_C.write(mOP);
        }
        if (mask(2, 2) == true) {
          stream_mOP_memcore2_C.write(mOP);
        }
        if (mask(3, 3) == true) {
          stream_mOP_memcore3_C.write(mOP);
        }
        if (mask(4, 4) == true) {
          stream_mOP_memcore4_C.write(mOP);
        }
        if (mask(5, 5) == true) {
          stream_mOP_memcore5_C.write(mOP);
        }
      }
    } else if (opcode == OPCODE_MESH_SEND_A) {
      if (is_last_mOP == false) {
      CASE_MESHA:
        for (uint16_t w = 0; w < mop_buffer_window_size; w++) {
#pragma HLS PIPELINE II = 8
          union_inst_mesh_A inst;

          inst.raw_32b[0] = stream_instruction_sequence.read();
          inst.raw_32b[1] = stream_instruction_sequence.read();

          mop_mesh_sendA_type mOP;
          mOP.repeat_num = repeat_num;
          mOP.mop_buffer_window_size = mop_buffer_window_size;
          mOP.size = inst.inst_val.size;
          mOP.memcoreA0_to_computecore0 = inst.inst_val.memcoreA0_to_computecore0;
          mOP.memcoreA0_to_computecore1 = inst.inst_val.memcoreA0_to_computecore1;
          mOP.memcoreA1_to_computecore2 = inst.inst_val.memcoreA1_to_computecore2;
          mOP.memcoreA1_to_computecore3 = inst.inst_val.memcoreA1_to_computecore3;
          mOP.memcoreA2_to_computecore4 = inst.inst_val.memcoreA2_to_computecore4;
          mOP.memcoreA2_to_computecore5 = inst.inst_val.memcoreA2_to_computecore5;
          mOP.memcoreC0_to_computecore4 = inst.inst_val.memcoreC0_to_computecore4;
          mOP.memcoreC1_to_computecore4 = inst.inst_val.memcoreC1_to_computecore4;
          mOP.memcoreC2_to_computecore5 = inst.inst_val.memcoreC2_to_computecore5;
          mOP.memcoreC3_to_computecore5 = inst.inst_val.memcoreC3_to_computecore5;
          mOP.is_last_mOP = false;

          stream_mOP_mesh_sendA.write(mOP);
        }
      } else {
        mop_mesh_sendA_type mOP;
        mOP.is_last_mOP = true;
        stream_mOP_mesh_sendA.write(mOP);
      }
    } else if (opcode == OPCODE_MESH_SEND_B) {
      if (is_last_mOP == false) {
      CASE_MESHB:
        for (uint16_t w = 0; w < mop_buffer_window_size; w++) {
#pragma HLS PIPELINE II = 8
          union_inst_mesh_B inst;
          inst.raw_32b[0] = stream_instruction_sequence.read();
          inst.raw_32b[1] = stream_instruction_sequence.read();

          mop_mesh_sendB_type mOP;
          mOP.repeat_num = repeat_num;
          mOP.mop_buffer_window_size = mop_buffer_window_size;
          mOP.size = inst.inst_val.size;
          mOP.memcore0_to_computecore0 = inst.inst_val.memcore0_to_computecore0;
          mOP.memcore0_to_computecore2 = inst.inst_val.memcore0_to_computecore2;
          mOP.memcore0_to_computecore4 = inst.inst_val.memcore0_to_computecore4;
          mOP.memcore1_to_computecore1 = inst.inst_val.memcore1_to_computecore1;
          mOP.memcore1_to_computecore3 = inst.inst_val.memcore1_to_computecore3;
          mOP.memcore1_to_computecore5 = inst.inst_val.memcore1_to_computecore5;
          mOP.memcore2_to_computecore4 = inst.inst_val.memcore2_to_computecore4;
          mOP.memcore2_to_computecore5 = inst.inst_val.memcore2_to_computecore5;
          mOP.is_last_mOP = false;

          stream_mOP_mesh_sendB.write(mOP);
        }
      } else {
        mop_mesh_sendB_type mOP;
        mOP.is_last_mOP = true;
        stream_mOP_mesh_sendB.write(mOP);
      }
    }
    if (inst_pkt_id != countInstPkt - 1) {
      inst_header.raw_32b = stream_instruction_sequence.read();
    }
  }


}

void decoder_uop(uint32_t *vliw_memory, hls::stream<uop_ddr_type> &stream_uOP_ddr,
                 hls::stream<uop_loadB_dram_type> &stream_uOP_loadB_dram,
                 hls::stream<uop_memcore_A_type> &stream_uOP_memcore0_A,
                 hls::stream<uop_memcore_A_type> &stream_uOP_memcore1_A,
                 hls::stream<uop_memcore_A_type> &stream_uOP_memcore2_A,
                 hls::stream<uop_memcore_B_type> &stream_uOP_memcore0_B,
                 hls::stream<uop_memcore_B_type> &stream_uOP_memcore1_B,
                 hls::stream<uop_memcore_B_type> &stream_uOP_memcore2_B,
                 hls::stream<uop_memcore_C_type> &stream_uOP_memcore0_C,
                 hls::stream<uop_memcore_C_type> &stream_uOP_memcore1_C,
                 hls::stream<uop_memcore_C_type> &stream_uOP_memcore2_C,
                 hls::stream<uop_memcore_C_type> &stream_uOP_memcore3_C,
                 hls::stream<uop_memcore_C_type> &stream_uOP_memcore4_C,
                 hls::stream<uop_memcore_C_type> &stream_uOP_memcore5_C,
                 hls::stream<uop_mesh_sendA_type> &stream_uOP_mesh_sendA,
                 hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB) {
#pragma HLS dataflow



  hls::stream<mop_ddr_type> stream_mOP_ddr;
  hls::stream<mop_loadB_dram_type> stream_mOP_loadB_dram;
  hls::stream<mop_memcore_A_type> stream_mOP_memcore0_A, stream_mOP_memcore1_A,
      stream_mOP_memcore2_A;
  hls::stream<mop_memcore_B_type> stream_mOP_memcore0_B, stream_mOP_memcore1_B,
      stream_mOP_memcore2_B;
  hls::stream<mop_memcore_C_type> stream_mOP_memcore0_C, stream_mOP_memcore1_C,
      stream_mOP_memcore2_C, stream_mOP_memcore3_C, stream_mOP_memcore4_C, stream_mOP_memcore5_C;

  hls::stream<mop_mesh_sendA_type> stream_mOP_mesh_sendA;
  hls::stream<mop_mesh_sendB_type> stream_mOP_mesh_sendB;

#pragma HLS STREAM variable = stream_mOP_ddr depth = 6
#pragma HLS STREAM variable = stream_mOP_loadB_dram depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore0_A depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore1_A depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore2_A depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore0_B depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore1_B depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore2_B depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore0_C depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore1_C depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore2_C depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore3_C depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore4_C depth = 6
#pragma HLS STREAM variable = stream_mOP_memcore5_C depth = 6
#pragma HLS STREAM variable = stream_mOP_mesh_sendA depth = 6
#pragma HLS STREAM variable = stream_mOP_mesh_sendB depth = 6

  hls::stream<uint32_t> stream_instruction_sequence;
#pragma HLS STREAM variable = stream_instruction_sequence depth = 8

#pragma HLS dataflow

  read_instructions_from_offchip(vliw_memory, stream_instruction_sequence);

  instructions_to_mop_dispenser(stream_instruction_sequence, stream_mOP_ddr, stream_mOP_loadB_dram,
                                stream_mOP_memcore0_A, stream_mOP_memcore1_A, stream_mOP_memcore2_A,
                                stream_mOP_memcore0_B, stream_mOP_memcore1_B, stream_mOP_memcore2_B,
                                stream_mOP_memcore0_C, stream_mOP_memcore1_C, stream_mOP_memcore2_C,
                                stream_mOP_memcore3_C, stream_mOP_memcore4_C, stream_mOP_memcore5_C,
                                stream_mOP_mesh_sendA, stream_mOP_mesh_sendB);

  mop2uop_ddr(stream_mOP_ddr, stream_uOP_ddr);
  mop2uop_loadB_dram(stream_mOP_loadB_dram, stream_uOP_loadB_dram);

  mop2uop_memcore_A(

      stream_mOP_memcore0_A, stream_uOP_memcore0_A);
  mop2uop_memcore_A(

      stream_mOP_memcore1_A, stream_uOP_memcore1_A);
  mop2uop_memcore_A(

      stream_mOP_memcore2_A, stream_uOP_memcore2_A);
  mop2uop_memcore_B(

      stream_mOP_memcore0_B, stream_uOP_memcore0_B);
  mop2uop_memcore_B(
      
      stream_mOP_memcore1_B, stream_uOP_memcore1_B);
  mop2uop_memcore_B(

      stream_mOP_memcore2_B, stream_uOP_memcore2_B);

  mop2uop_memcore_C(

      stream_mOP_memcore0_C, stream_uOP_memcore0_C);
  mop2uop_memcore_C(

      stream_mOP_memcore1_C, stream_uOP_memcore1_C);
  mop2uop_memcore_C(

      stream_mOP_memcore2_C, stream_uOP_memcore2_C);
  mop2uop_memcore_C(

      stream_mOP_memcore3_C, stream_uOP_memcore3_C);
  mop2uop_memcore_C(

      stream_mOP_memcore4_C, stream_uOP_memcore4_C);
  mop2uop_memcore_C(

      stream_mOP_memcore5_C, stream_uOP_memcore5_C);

  mop2uop_mesh_sendA(stream_mOP_mesh_sendA, stream_uOP_mesh_sendA);
  mop2uop_mesh_sendB(stream_mOP_mesh_sendB, stream_uOP_mesh_sendB);


}
