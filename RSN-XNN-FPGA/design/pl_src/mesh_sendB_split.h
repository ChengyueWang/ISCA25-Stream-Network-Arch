#pragma once
#include "common.h"

void mesh_sendB_split(
#ifdef SW_EMU_PRINT
    int core_id,
#endif

    hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB,
    hls::stream<ap_uint<64>> &from_memCore0_to_mesh_B0_CASC0,
    hls::stream<ap_uint<64>> &from_memCore0_to_mesh_B1_CASC0,
    hls::stream<ap_uint<64>> &from_memCore0_to_mesh_B2_CASC0,
    hls::stream<ap_uint<64>> &from_memCore0_to_mesh_B3_CASC0,
    hls::stream<ap_uint<64>> &from_memCore1_to_mesh_B0_CASC0,
    hls::stream<ap_uint<64>> &from_memCore1_to_mesh_B1_CASC0,
    hls::stream<ap_uint<64>> &from_memCore1_to_mesh_B2_CASC0,
    hls::stream<ap_uint<64>> &from_memCore1_to_mesh_B3_CASC0,
    hls::stream<ap_uint<64>> &from_memCore2_to_mesh_B0_CASC0,
    hls::stream<ap_uint<64>> &from_memCore2_to_mesh_B1_CASC0,
    hls::stream<ap_uint<64>> &from_memCore2_to_mesh_B2_CASC0,
    hls::stream<ap_uint<64>> &from_memCore2_to_mesh_B3_CASC0,

    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_B3_CASC0,

    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_B3_CASC0,

    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_B3_CASC0,

    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_B3_CASC0,

    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_B3_CASC0,

    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_B3_CASC0

);
