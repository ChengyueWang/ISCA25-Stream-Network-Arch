#pragma once
#include "common.h"

void memcore_C(
#ifdef SW_EMU_PRINT
    int core_id,
#endif

    hls::stream<uop_memcore_C_type> &stream_uOP_memcore_C,
    hls::stream<ap_uint<1024>> &stream_to_dramC, hls::stream<ap_uint<1024>> &stream_from_ddr,

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

    hls::stream<float> &data_channel_to_neighbour, hls::stream<float> &data_channel_from_neighbour

);
