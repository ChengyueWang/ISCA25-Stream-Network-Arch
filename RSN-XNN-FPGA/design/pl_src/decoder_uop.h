#pragma once
#include "common.h"

void mop2uop_memcore_A(
#ifdef SW_EMU_PRINT
    int core_id,
#endif
    hls::stream<mop_memcore_A_type> &stream_mOP_memcore_A,
    hls::stream<uop_memcore_A_type> &stream_uOP_memcore_A);

void mop2uop_memcore_B(
#ifdef SW_EMU_PRINT
    int core_id,
#endif
    hls::stream<mop_memcore_B_type> &stream_mOP_memcore_B,
    hls::stream<uop_memcore_B_type> &stream_uOP_memcore_B);

void mop2uop_memcore_C(
#ifdef SW_EMU_PRINT
    int core_id,
#endif
    hls::stream<mop_memcore_C_type> &stream_mOP_memcore_C,
    hls::stream<uop_memcore_C_type> &stream_uOP_memcore_C);

void mop2uop_ddr(hls::stream<mop_ddr_type> &stream_mOP_ddr,
                 hls::stream<uop_ddr_type> &stream_uOP_ddr);

void mop2uop_loadB_dram(hls::stream<mop_loadB_dram_type> &stream_mOP_loadB_dram,
                        hls::stream<uop_loadB_dram_type> &stream_uOP_loadB_dram);

void mop2uop_mesh_sendA(hls::stream<mop_mesh_sendA_type> &stream_mOP_mesh_sendA,
                        hls::stream<uop_mesh_sendA_type> &stream_uOP_mesh_sendA);

void mop2uop_mesh_sendB(hls::stream<mop_mesh_sendB_type> &stream_mOP_mesh_sendB,
                        hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB);

void read_instructions_from_offchip(uint32_t *vliw_memory,
                                    hls::stream<uint32_t> &stream_instruction_sequence);

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
                                   hls::stream<mop_mesh_sendB_type> &stream_mOP_mesh_sendB);

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
                 hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB);
