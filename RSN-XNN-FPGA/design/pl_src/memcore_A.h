#pragma once
#include "common.h"

void memcore_A(
#ifdef SW_EMU_PRINT
    int core_id,
#endif

    hls::stream<uop_memcore_A_type>& stream_uOP_memcore_A,
    hls::stream<ap_uint<1024>>& stream_from_dramA,

    hls::stream<ap_uint<64>>& to_computeCore0_A0_CASC0,
    hls::stream<ap_uint<64>>& to_computeCore0_A0_CASC1,
    hls::stream<ap_uint<64>>& to_computeCore0_A0_CASC2,
    hls::stream<ap_uint<64>>& to_computeCore0_A0_CASC3,

    hls::stream<ap_uint<64>>& to_computeCore0_A1_CASC0,
    hls::stream<ap_uint<64>>& to_computeCore0_A1_CASC1,
    hls::stream<ap_uint<64>>& to_computeCore0_A1_CASC2,
    hls::stream<ap_uint<64>>& to_computeCore0_A1_CASC3,

    hls::stream<ap_uint<64>>& to_computeCore0_A2_CASC0,
    hls::stream<ap_uint<64>>& to_computeCore0_A2_CASC1,
    hls::stream<ap_uint<64>>& to_computeCore0_A2_CASC2,
    hls::stream<ap_uint<64>>& to_computeCore0_A2_CASC3,

    hls::stream<ap_uint<64>>& to_computeCore0_A3_CASC0,
    hls::stream<ap_uint<64>>& to_computeCore0_A3_CASC1,
    hls::stream<ap_uint<64>>& to_computeCore0_A3_CASC2,
    hls::stream<ap_uint<64>>& to_computeCore0_A3_CASC3);
