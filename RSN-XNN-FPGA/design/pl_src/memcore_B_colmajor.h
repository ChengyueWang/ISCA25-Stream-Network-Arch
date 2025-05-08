#pragma once
#include "common.h"

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
    hls::stream<ap_uint<64>> &to_computeCore0_B3_CASC3);
