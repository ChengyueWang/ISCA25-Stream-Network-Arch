
#include "common.h"
#include "ddr.h"
#include "decoder_uop.h"
#include "duplicate_uop_meshB.h"
#include "loadB_from_dram.h"
#include "memcore_A.h"
#include "memcore_B.h"
#include "memcore_B_colmajor.h"
#include "memcore_C.h"
#include "memcore_C_to_mesh.h"
#include "mesh_sendA.h"
#include "mesh_sendB.h"
#include "mesh_sendB_split.h"

extern "C" {


void dma_hls(

    ap_uint<512>* inB_port0, ap_uint<512>* inB_port1, ap_uint<512>* ddr_port0,
    ap_uint<512>* ddr_port1, uint32_t* vliw_mem,

    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_A3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore0_B3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C00,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C01,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C02,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C03,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C10,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C11,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C12,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C13,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C20,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C21,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C22,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C23,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C30,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C31,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C32,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore0_C33,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_A3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore1_B3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C00,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C01,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C02,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C03,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C10,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C11,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C12,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C13,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C20,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C21,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C22,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C23,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C30,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C31,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C32,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore1_C33,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_A3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore2_B3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C00,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C01,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C02,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C03,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C10,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C11,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C12,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C13,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C20,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C21,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C22,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C23,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C30,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C31,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C32,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore2_C33,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_A3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore3_B3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C00,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C01,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C02,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C03,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C10,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C11,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C12,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C13,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C20,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C21,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C22,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C23,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C30,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C31,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C32,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore3_C33,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_A3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore4_B3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C00,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C01,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C02,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C03,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C10,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C11,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C12,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C13,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C20,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C21,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C22,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C23,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C30,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C31,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C32,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore4_C33,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_A3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B0_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B0_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B0_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B0_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B1_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B1_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B1_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B1_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B2_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B2_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B2_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B2_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B3_CASC0,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B3_CASC1,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B3_CASC2,
    hls::stream<ap_axiu<64, 0, 0, 0>>& to_computeCore5_B3_CASC3,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C00,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C01,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C02,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C03,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C10,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C11,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C12,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C13,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C20,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C21,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C22,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C23,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C30,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C31,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C32,
    hls::stream<ap_axiu<64, 0, 0, 0>>& from_computeCore5_C33

) {

#pragma HLS INTERFACE axis port = to_computeCore0_A0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore0_A0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore0_A0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore0_A0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore0_A1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore0_A1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore0_A1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore0_A1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore0_A2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore0_A2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore0_A2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore0_A2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore0_A3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore0_A3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore0_A3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore0_A3_CASC3
#pragma HLS INTERFACE axis port = to_computeCore0_B0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore0_B0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore0_B0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore0_B0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore0_B1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore0_B1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore0_B1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore0_B1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore0_B2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore0_B2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore0_B2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore0_B2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore0_B3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore0_B3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore0_B3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore0_B3_CASC3
#pragma HLS INTERFACE axis port = from_computeCore0_C00
#pragma HLS INTERFACE axis port = from_computeCore0_C01
#pragma HLS INTERFACE axis port = from_computeCore0_C02
#pragma HLS INTERFACE axis port = from_computeCore0_C03
#pragma HLS INTERFACE axis port = from_computeCore0_C10
#pragma HLS INTERFACE axis port = from_computeCore0_C11
#pragma HLS INTERFACE axis port = from_computeCore0_C12
#pragma HLS INTERFACE axis port = from_computeCore0_C13
#pragma HLS INTERFACE axis port = from_computeCore0_C20
#pragma HLS INTERFACE axis port = from_computeCore0_C21
#pragma HLS INTERFACE axis port = from_computeCore0_C22
#pragma HLS INTERFACE axis port = from_computeCore0_C23
#pragma HLS INTERFACE axis port = from_computeCore0_C30
#pragma HLS INTERFACE axis port = from_computeCore0_C31
#pragma HLS INTERFACE axis port = from_computeCore0_C32
#pragma HLS INTERFACE axis port = from_computeCore0_C33
#pragma HLS INTERFACE axis port = to_computeCore1_A0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore1_A0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore1_A0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore1_A0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore1_A1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore1_A1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore1_A1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore1_A1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore1_A2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore1_A2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore1_A2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore1_A2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore1_A3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore1_A3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore1_A3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore1_A3_CASC3
#pragma HLS INTERFACE axis port = to_computeCore1_B0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore1_B0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore1_B0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore1_B0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore1_B1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore1_B1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore1_B1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore1_B1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore1_B2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore1_B2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore1_B2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore1_B2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore1_B3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore1_B3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore1_B3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore1_B3_CASC3
#pragma HLS INTERFACE axis port = from_computeCore1_C00
#pragma HLS INTERFACE axis port = from_computeCore1_C01
#pragma HLS INTERFACE axis port = from_computeCore1_C02
#pragma HLS INTERFACE axis port = from_computeCore1_C03
#pragma HLS INTERFACE axis port = from_computeCore1_C10
#pragma HLS INTERFACE axis port = from_computeCore1_C11
#pragma HLS INTERFACE axis port = from_computeCore1_C12
#pragma HLS INTERFACE axis port = from_computeCore1_C13
#pragma HLS INTERFACE axis port = from_computeCore1_C20
#pragma HLS INTERFACE axis port = from_computeCore1_C21
#pragma HLS INTERFACE axis port = from_computeCore1_C22
#pragma HLS INTERFACE axis port = from_computeCore1_C23
#pragma HLS INTERFACE axis port = from_computeCore1_C30
#pragma HLS INTERFACE axis port = from_computeCore1_C31
#pragma HLS INTERFACE axis port = from_computeCore1_C32
#pragma HLS INTERFACE axis port = from_computeCore1_C33
#pragma HLS INTERFACE axis port = to_computeCore2_A0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore2_A0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore2_A0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore2_A0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore2_A1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore2_A1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore2_A1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore2_A1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore2_A2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore2_A2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore2_A2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore2_A2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore2_A3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore2_A3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore2_A3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore2_A3_CASC3
#pragma HLS INTERFACE axis port = to_computeCore2_B0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore2_B0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore2_B0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore2_B0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore2_B1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore2_B1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore2_B1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore2_B1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore2_B2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore2_B2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore2_B2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore2_B2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore2_B3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore2_B3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore2_B3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore2_B3_CASC3
#pragma HLS INTERFACE axis port = from_computeCore2_C00
#pragma HLS INTERFACE axis port = from_computeCore2_C01
#pragma HLS INTERFACE axis port = from_computeCore2_C02
#pragma HLS INTERFACE axis port = from_computeCore2_C03
#pragma HLS INTERFACE axis port = from_computeCore2_C10
#pragma HLS INTERFACE axis port = from_computeCore2_C11
#pragma HLS INTERFACE axis port = from_computeCore2_C12
#pragma HLS INTERFACE axis port = from_computeCore2_C13
#pragma HLS INTERFACE axis port = from_computeCore2_C20
#pragma HLS INTERFACE axis port = from_computeCore2_C21
#pragma HLS INTERFACE axis port = from_computeCore2_C22
#pragma HLS INTERFACE axis port = from_computeCore2_C23
#pragma HLS INTERFACE axis port = from_computeCore2_C30
#pragma HLS INTERFACE axis port = from_computeCore2_C31
#pragma HLS INTERFACE axis port = from_computeCore2_C32
#pragma HLS INTERFACE axis port = from_computeCore2_C33
#pragma HLS INTERFACE axis port = to_computeCore3_A0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore3_A0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore3_A0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore3_A0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore3_A1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore3_A1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore3_A1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore3_A1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore3_A2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore3_A2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore3_A2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore3_A2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore3_A3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore3_A3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore3_A3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore3_A3_CASC3
#pragma HLS INTERFACE axis port = to_computeCore3_B0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore3_B0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore3_B0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore3_B0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore3_B1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore3_B1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore3_B1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore3_B1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore3_B2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore3_B2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore3_B2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore3_B2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore3_B3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore3_B3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore3_B3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore3_B3_CASC3
#pragma HLS INTERFACE axis port = from_computeCore3_C00
#pragma HLS INTERFACE axis port = from_computeCore3_C01
#pragma HLS INTERFACE axis port = from_computeCore3_C02
#pragma HLS INTERFACE axis port = from_computeCore3_C03
#pragma HLS INTERFACE axis port = from_computeCore3_C10
#pragma HLS INTERFACE axis port = from_computeCore3_C11
#pragma HLS INTERFACE axis port = from_computeCore3_C12
#pragma HLS INTERFACE axis port = from_computeCore3_C13
#pragma HLS INTERFACE axis port = from_computeCore3_C20
#pragma HLS INTERFACE axis port = from_computeCore3_C21
#pragma HLS INTERFACE axis port = from_computeCore3_C22
#pragma HLS INTERFACE axis port = from_computeCore3_C23
#pragma HLS INTERFACE axis port = from_computeCore3_C30
#pragma HLS INTERFACE axis port = from_computeCore3_C31
#pragma HLS INTERFACE axis port = from_computeCore3_C32
#pragma HLS INTERFACE axis port = from_computeCore3_C33
#pragma HLS INTERFACE axis port = to_computeCore4_A0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore4_A0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore4_A0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore4_A0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore4_A1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore4_A1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore4_A1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore4_A1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore4_A2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore4_A2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore4_A2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore4_A2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore4_A3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore4_A3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore4_A3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore4_A3_CASC3
#pragma HLS INTERFACE axis port = to_computeCore4_B0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore4_B0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore4_B0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore4_B0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore4_B1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore4_B1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore4_B1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore4_B1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore4_B2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore4_B2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore4_B2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore4_B2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore4_B3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore4_B3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore4_B3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore4_B3_CASC3
#pragma HLS INTERFACE axis port = from_computeCore4_C00
#pragma HLS INTERFACE axis port = from_computeCore4_C01
#pragma HLS INTERFACE axis port = from_computeCore4_C02
#pragma HLS INTERFACE axis port = from_computeCore4_C03
#pragma HLS INTERFACE axis port = from_computeCore4_C10
#pragma HLS INTERFACE axis port = from_computeCore4_C11
#pragma HLS INTERFACE axis port = from_computeCore4_C12
#pragma HLS INTERFACE axis port = from_computeCore4_C13
#pragma HLS INTERFACE axis port = from_computeCore4_C20
#pragma HLS INTERFACE axis port = from_computeCore4_C21
#pragma HLS INTERFACE axis port = from_computeCore4_C22
#pragma HLS INTERFACE axis port = from_computeCore4_C23
#pragma HLS INTERFACE axis port = from_computeCore4_C30
#pragma HLS INTERFACE axis port = from_computeCore4_C31
#pragma HLS INTERFACE axis port = from_computeCore4_C32
#pragma HLS INTERFACE axis port = from_computeCore4_C33
#pragma HLS INTERFACE axis port = to_computeCore5_A0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore5_A0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore5_A0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore5_A0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore5_A1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore5_A1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore5_A1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore5_A1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore5_A2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore5_A2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore5_A2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore5_A2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore5_A3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore5_A3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore5_A3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore5_A3_CASC3
#pragma HLS INTERFACE axis port = to_computeCore5_B0_CASC0
#pragma HLS INTERFACE axis port = to_computeCore5_B0_CASC1
#pragma HLS INTERFACE axis port = to_computeCore5_B0_CASC2
#pragma HLS INTERFACE axis port = to_computeCore5_B0_CASC3
#pragma HLS INTERFACE axis port = to_computeCore5_B1_CASC0
#pragma HLS INTERFACE axis port = to_computeCore5_B1_CASC1
#pragma HLS INTERFACE axis port = to_computeCore5_B1_CASC2
#pragma HLS INTERFACE axis port = to_computeCore5_B1_CASC3
#pragma HLS INTERFACE axis port = to_computeCore5_B2_CASC0
#pragma HLS INTERFACE axis port = to_computeCore5_B2_CASC1
#pragma HLS INTERFACE axis port = to_computeCore5_B2_CASC2
#pragma HLS INTERFACE axis port = to_computeCore5_B2_CASC3
#pragma HLS INTERFACE axis port = to_computeCore5_B3_CASC0
#pragma HLS INTERFACE axis port = to_computeCore5_B3_CASC1
#pragma HLS INTERFACE axis port = to_computeCore5_B3_CASC2
#pragma HLS INTERFACE axis port = to_computeCore5_B3_CASC3
#pragma HLS INTERFACE axis port = from_computeCore5_C00
#pragma HLS INTERFACE axis port = from_computeCore5_C01
#pragma HLS INTERFACE axis port = from_computeCore5_C02
#pragma HLS INTERFACE axis port = from_computeCore5_C03
#pragma HLS INTERFACE axis port = from_computeCore5_C10
#pragma HLS INTERFACE axis port = from_computeCore5_C11
#pragma HLS INTERFACE axis port = from_computeCore5_C12
#pragma HLS INTERFACE axis port = from_computeCore5_C13
#pragma HLS INTERFACE axis port = from_computeCore5_C20
#pragma HLS INTERFACE axis port = from_computeCore5_C21
#pragma HLS INTERFACE axis port = from_computeCore5_C22
#pragma HLS INTERFACE axis port = from_computeCore5_C23
#pragma HLS INTERFACE axis port = from_computeCore5_C30
#pragma HLS INTERFACE axis port = from_computeCore5_C31
#pragma HLS INTERFACE axis port = from_computeCore5_C32
#pragma HLS INTERFACE axis port = from_computeCore5_C33

#pragma HLS INTERFACE s_axilite port = return bundle = control
#pragma HLS INTERFACE ap_ctrl_chain port = return

#pragma HLS INTERFACE s_axilite port = vliw_mem bundle = control
#pragma HLS INTERFACE s_axilite port = inB_port0 bundle = control
#pragma HLS INTERFACE s_axilite port = inB_port1 bundle = control
#pragma HLS INTERFACE s_axilite port = ddr_port0 bundle = control
#pragma HLS INTERFACE s_axilite port = ddr_port1 bundle = control

#pragma HLS INTERFACE m_axi port = inB_port0 offset = slave bundle =                            \
    lpddr_port0_bd max_read_burst_length = 64 num_read_outstanding = 8 max_write_burst_length = \
        1 num_write_outstanding = 1 depth = 8192
#pragma HLS INTERFACE m_axi port = inB_port1 offset = slave bundle =                            \
    lpddr_port1_bd max_read_burst_length = 64 num_read_outstanding = 8 max_write_burst_length = \
        1 num_write_outstanding = 1 depth = 8192
#pragma HLS INTERFACE m_axi port = ddr_port0 offset = slave bundle =                          \
    ddr_port0_bd max_read_burst_length = 64 num_read_outstanding = 8 max_write_burst_length = \
        64 num_write_outstanding = 8 depth = 8192
#pragma HLS INTERFACE m_axi port = ddr_port1 offset = slave bundle =                          \
    ddr_port1_bd max_read_burst_length = 64 num_read_outstanding = 8 max_write_burst_length = \
        64 num_write_outstanding = 8 depth = 8192
#pragma HLS INTERFACE m_axi port = vliw_mem offset = slave bundle =                            \
    lpddr_port3_bd max_read_burst_length = 1 num_read_outstanding = 1 max_write_burst_length = \
        1 num_write_outstanding = 1 depth = 8192

#pragma HLS DATAFLOW

  hls_thread_local hls::stream<ap_uint<1024>> stream_from_ddr_to_memCoreA0,
      stream_from_ddr_to_memCoreA1, stream_from_ddr_to_memCoreA2;
  hls_thread_local hls::stream<ap_uint<1024>> stream_from_ddr_to_memCoreB0,
      stream_from_ddr_to_memCoreB1, stream_from_ddr_to_memCoreB2;
  hls_thread_local hls::stream<ap_uint<1024>> stream_from_lpddr_to_memCoreB0,
      stream_from_lpddr_to_memCoreB1;
  hls_thread_local hls::stream<ap_uint<1024>> stream_to_ddr_from_memCoreC0,
      stream_to_ddr_from_memCoreC1, stream_to_ddr_from_memCoreC2, stream_to_ddr_from_memCoreC3,
      stream_to_ddr_from_memCoreC4, stream_to_ddr_from_memCoreC5;
  hls_thread_local hls::stream<ap_uint<1024>> stream_from_ddr_to_memCoreC0,
      stream_from_ddr_to_memCoreC1, stream_from_ddr_to_memCoreC2, stream_from_ddr_to_memCoreC3,
      stream_from_ddr_to_memCoreC4, stream_from_ddr_to_memCoreC5;

  hls_thread_local hls::stream<uop_ddr_type> stream_uOP_ddr;
  hls_thread_local hls::stream<uop_loadB_dram_type> stream_uOP_loadB_dram;
  hls_thread_local hls::stream<uop_memcore_A_type> stream_uOP_memcore0_A, stream_uOP_memcore1_A,
      stream_uOP_memcore2_A;
  hls_thread_local hls::stream<uop_memcore_B_type> stream_uOP_memcore0_B, stream_uOP_memcore1_B,
      stream_uOP_memcore2_B;
  hls_thread_local hls::stream<uop_memcore_C_type> stream_uOP_memcore0_C, stream_uOP_memcore1_C,
      stream_uOP_memcore2_C, stream_uOP_memcore3_C, stream_uOP_memcore4_C, stream_uOP_memcore5_C;
  hls_thread_local hls::stream<uop_mesh_sendA_type> stream_uOP_mesh_sendA;
  hls_thread_local hls::stream<uop_mesh_sendB_type> stream_uOP_mesh_sendB;



  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_A0_CASC0,
      from_memCore0_to_mesh_A0_CASC1, from_memCore0_to_mesh_A0_CASC2,
      from_memCore0_to_mesh_A0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_A1_CASC0,
      from_memCore0_to_mesh_A1_CASC1, from_memCore0_to_mesh_A1_CASC2,
      from_memCore0_to_mesh_A1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_A2_CASC0,
      from_memCore0_to_mesh_A2_CASC1, from_memCore0_to_mesh_A2_CASC2,
      from_memCore0_to_mesh_A2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_A3_CASC0,
      from_memCore0_to_mesh_A3_CASC1, from_memCore0_to_mesh_A3_CASC2,
      from_memCore0_to_mesh_A3_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_A0_CASC0,
      from_memCore1_to_mesh_A0_CASC1, from_memCore1_to_mesh_A0_CASC2,
      from_memCore1_to_mesh_A0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_A1_CASC0,
      from_memCore1_to_mesh_A1_CASC1, from_memCore1_to_mesh_A1_CASC2,
      from_memCore1_to_mesh_A1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_A2_CASC0,
      from_memCore1_to_mesh_A2_CASC1, from_memCore1_to_mesh_A2_CASC2,
      from_memCore1_to_mesh_A2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_A3_CASC0,
      from_memCore1_to_mesh_A3_CASC1, from_memCore1_to_mesh_A3_CASC2,
      from_memCore1_to_mesh_A3_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_A0_CASC0,
      from_memCore2_to_mesh_A0_CASC1, from_memCore2_to_mesh_A0_CASC2,
      from_memCore2_to_mesh_A0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_A1_CASC0,
      from_memCore2_to_mesh_A1_CASC1, from_memCore2_to_mesh_A1_CASC2,
      from_memCore2_to_mesh_A1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_A2_CASC0,
      from_memCore2_to_mesh_A2_CASC1, from_memCore2_to_mesh_A2_CASC2,
      from_memCore2_to_mesh_A2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_A3_CASC0,
      from_memCore2_to_mesh_A3_CASC1, from_memCore2_to_mesh_A3_CASC2,
      from_memCore2_to_mesh_A3_CASC3;

  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_B0_CASC0,
      from_memCore0_to_mesh_B0_CASC1, from_memCore0_to_mesh_B0_CASC2,
      from_memCore0_to_mesh_B0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_B1_CASC0,
      from_memCore0_to_mesh_B1_CASC1, from_memCore0_to_mesh_B1_CASC2,
      from_memCore0_to_mesh_B1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_B2_CASC0,
      from_memCore0_to_mesh_B2_CASC1, from_memCore0_to_mesh_B2_CASC2,
      from_memCore0_to_mesh_B2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_B3_CASC0,
      from_memCore0_to_mesh_B3_CASC1, from_memCore0_to_mesh_B3_CASC2,
      from_memCore0_to_mesh_B3_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_B0_CASC0,
      from_memCore1_to_mesh_B0_CASC1, from_memCore1_to_mesh_B0_CASC2,
      from_memCore1_to_mesh_B0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_B1_CASC0,
      from_memCore1_to_mesh_B1_CASC1, from_memCore1_to_mesh_B1_CASC2,
      from_memCore1_to_mesh_B1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_B2_CASC0,
      from_memCore1_to_mesh_B2_CASC1, from_memCore1_to_mesh_B2_CASC2,
      from_memCore1_to_mesh_B2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_B3_CASC0,
      from_memCore1_to_mesh_B3_CASC1, from_memCore1_to_mesh_B3_CASC2,
      from_memCore1_to_mesh_B3_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_B0_CASC0,
      from_memCore2_to_mesh_B0_CASC1, from_memCore2_to_mesh_B0_CASC2,
      from_memCore2_to_mesh_B0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_B1_CASC0,
      from_memCore2_to_mesh_B1_CASC1, from_memCore2_to_mesh_B1_CASC2,
      from_memCore2_to_mesh_B1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_B2_CASC0,
      from_memCore2_to_mesh_B2_CASC1, from_memCore2_to_mesh_B2_CASC2,
      from_memCore2_to_mesh_B2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_B3_CASC0,
      from_memCore2_to_mesh_B3_CASC1, from_memCore2_to_mesh_B3_CASC2,
      from_memCore2_to_mesh_B3_CASC3;

  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_C0_CASC0,
      from_memCore0_to_mesh_C0_CASC1, from_memCore0_to_mesh_C0_CASC2,
      from_memCore0_to_mesh_C0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_C1_CASC0,
      from_memCore0_to_mesh_C1_CASC1, from_memCore0_to_mesh_C1_CASC2,
      from_memCore0_to_mesh_C1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_C2_CASC0,
      from_memCore0_to_mesh_C2_CASC1, from_memCore0_to_mesh_C2_CASC2,
      from_memCore0_to_mesh_C2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore0_to_mesh_C3_CASC0,
      from_memCore0_to_mesh_C3_CASC1, from_memCore0_to_mesh_C3_CASC2,
      from_memCore0_to_mesh_C3_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_C0_CASC0,
      from_memCore1_to_mesh_C0_CASC1, from_memCore1_to_mesh_C0_CASC2,
      from_memCore1_to_mesh_C0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_C1_CASC0,
      from_memCore1_to_mesh_C1_CASC1, from_memCore1_to_mesh_C1_CASC2,
      from_memCore1_to_mesh_C1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_C2_CASC0,
      from_memCore1_to_mesh_C2_CASC1, from_memCore1_to_mesh_C2_CASC2,
      from_memCore1_to_mesh_C2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore1_to_mesh_C3_CASC0,
      from_memCore1_to_mesh_C3_CASC1, from_memCore1_to_mesh_C3_CASC2,
      from_memCore1_to_mesh_C3_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_C0_CASC0,
      from_memCore2_to_mesh_C0_CASC1, from_memCore2_to_mesh_C0_CASC2,
      from_memCore2_to_mesh_C0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_C1_CASC0,
      from_memCore2_to_mesh_C1_CASC1, from_memCore2_to_mesh_C1_CASC2,
      from_memCore2_to_mesh_C1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_C2_CASC0,
      from_memCore2_to_mesh_C2_CASC1, from_memCore2_to_mesh_C2_CASC2,
      from_memCore2_to_mesh_C2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore2_to_mesh_C3_CASC0,
      from_memCore2_to_mesh_C3_CASC1, from_memCore2_to_mesh_C3_CASC2,
      from_memCore2_to_mesh_C3_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore3_to_mesh_C0_CASC0,
      from_memCore3_to_mesh_C0_CASC1, from_memCore3_to_mesh_C0_CASC2,
      from_memCore3_to_mesh_C0_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore3_to_mesh_C1_CASC0,
      from_memCore3_to_mesh_C1_CASC1, from_memCore3_to_mesh_C1_CASC2,
      from_memCore3_to_mesh_C1_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore3_to_mesh_C2_CASC0,
      from_memCore3_to_mesh_C2_CASC1, from_memCore3_to_mesh_C2_CASC2,
      from_memCore3_to_mesh_C2_CASC3;
  hls_thread_local hls::stream<ap_uint<64>> from_memCore3_to_mesh_C3_CASC0,
      from_memCore3_to_mesh_C3_CASC1, from_memCore3_to_mesh_C3_CASC2,
      from_memCore3_to_mesh_C3_CASC3;

  hls_thread_local hls::stream<float> data_channel_core0to1, data_channel_core1to0;
  hls_thread_local hls::stream<float> data_channel_core2to3, data_channel_core3to2;
  hls_thread_local hls::stream<float> data_channel_core4to5, data_channel_core5to4;
  hls_thread_local hls::stream<float> data_channel_core0to1_recvmesh,
      data_channel_core1to0_recvmesh;
  hls_thread_local hls::stream<float> data_channel_core2to3_recvmesh,
      data_channel_core3to2_recvmesh;

  hls_thread_local hls::stream<bool> return_stream;

#pragma HLS STREAM variable = data_channel_core0to1 depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_core1to0 depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_core2to3 depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_core3to2 depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_core4to5 depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_core5to4 depth = 256 type = fifo

#pragma HLS STREAM variable = data_channel_core0to1_recvmesh depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_core1to0_recvmesh depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_core2to3_recvmesh depth = 256 type = fifo
#pragma HLS STREAM variable = data_channel_core3to2_recvmesh depth = 256 type = fifo

  decoder_uop(
      vliw_mem, stream_uOP_ddr, stream_uOP_loadB_dram, stream_uOP_memcore0_A, stream_uOP_memcore1_A,
      stream_uOP_memcore2_A, stream_uOP_memcore0_B, stream_uOP_memcore1_B, stream_uOP_memcore2_B,
      stream_uOP_memcore0_C, stream_uOP_memcore1_C, stream_uOP_memcore2_C, stream_uOP_memcore3_C,
      stream_uOP_memcore4_C, stream_uOP_memcore5_C, stream_uOP_mesh_sendA, stream_uOP_mesh_sendB);

  loadB_from_dram(stream_uOP_loadB_dram, inB_port0, inB_port1, stream_from_lpddr_to_memCoreB0,
                  stream_from_lpddr_to_memCoreB1);


  ddr(
      stream_uOP_ddr, ddr_port0, ddr_port1, stream_from_ddr_to_memCoreA0,
      stream_from_ddr_to_memCoreA1, stream_from_ddr_to_memCoreA2, stream_from_ddr_to_memCoreB0,
      stream_from_ddr_to_memCoreB1, stream_from_ddr_to_memCoreB2, stream_from_ddr_to_memCoreC0,
      stream_from_ddr_to_memCoreC1, stream_from_ddr_to_memCoreC2, stream_from_ddr_to_memCoreC3,
      stream_from_ddr_to_memCoreC4, stream_from_ddr_to_memCoreC5, stream_to_ddr_from_memCoreC0,
      stream_to_ddr_from_memCoreC1, stream_to_ddr_from_memCoreC2, stream_to_ddr_from_memCoreC3,
      stream_to_ddr_from_memCoreC4, stream_to_ddr_from_memCoreC5
  );


  memcore_A(
      stream_uOP_memcore0_A, stream_from_ddr_to_memCoreA0, from_memCore0_to_mesh_A0_CASC0,
      from_memCore0_to_mesh_A0_CASC1, from_memCore0_to_mesh_A0_CASC2,
      from_memCore0_to_mesh_A0_CASC3, from_memCore0_to_mesh_A1_CASC0,
      from_memCore0_to_mesh_A1_CASC1, from_memCore0_to_mesh_A1_CASC2,
      from_memCore0_to_mesh_A1_CASC3, from_memCore0_to_mesh_A2_CASC0,
      from_memCore0_to_mesh_A2_CASC1, from_memCore0_to_mesh_A2_CASC2,
      from_memCore0_to_mesh_A2_CASC3, from_memCore0_to_mesh_A3_CASC0,
      from_memCore0_to_mesh_A3_CASC1, from_memCore0_to_mesh_A3_CASC2,
      from_memCore0_to_mesh_A3_CASC3);


  memcore_A(
      stream_uOP_memcore1_A, stream_from_ddr_to_memCoreA1, from_memCore1_to_mesh_A0_CASC0,
      from_memCore1_to_mesh_A0_CASC1, from_memCore1_to_mesh_A0_CASC2,
      from_memCore1_to_mesh_A0_CASC3, from_memCore1_to_mesh_A1_CASC0,
      from_memCore1_to_mesh_A1_CASC1, from_memCore1_to_mesh_A1_CASC2,
      from_memCore1_to_mesh_A1_CASC3, from_memCore1_to_mesh_A2_CASC0,
      from_memCore1_to_mesh_A2_CASC1, from_memCore1_to_mesh_A2_CASC2,
      from_memCore1_to_mesh_A2_CASC3, from_memCore1_to_mesh_A3_CASC0,
      from_memCore1_to_mesh_A3_CASC1, from_memCore1_to_mesh_A3_CASC2,
      from_memCore1_to_mesh_A3_CASC3);


  memcore_A(
      stream_uOP_memcore2_A, stream_from_ddr_to_memCoreA2, from_memCore2_to_mesh_A0_CASC0,
      from_memCore2_to_mesh_A0_CASC1, from_memCore2_to_mesh_A0_CASC2,
      from_memCore2_to_mesh_A0_CASC3, from_memCore2_to_mesh_A1_CASC0,
      from_memCore2_to_mesh_A1_CASC1, from_memCore2_to_mesh_A1_CASC2,
      from_memCore2_to_mesh_A1_CASC3, from_memCore2_to_mesh_A2_CASC0,
      from_memCore2_to_mesh_A2_CASC1, from_memCore2_to_mesh_A2_CASC2,
      from_memCore2_to_mesh_A2_CASC3, from_memCore2_to_mesh_A3_CASC0,
      from_memCore2_to_mesh_A3_CASC1, from_memCore2_to_mesh_A3_CASC2,
      from_memCore2_to_mesh_A3_CASC3);


  memcore_B(
      stream_uOP_memcore0_B, stream_from_ddr_to_memCoreB0, stream_from_lpddr_to_memCoreB0,
      from_memCore0_to_mesh_B0_CASC0, from_memCore0_to_mesh_B0_CASC1,
      from_memCore0_to_mesh_B0_CASC2, from_memCore0_to_mesh_B0_CASC3,
      from_memCore0_to_mesh_B1_CASC0, from_memCore0_to_mesh_B1_CASC1,
      from_memCore0_to_mesh_B1_CASC2, from_memCore0_to_mesh_B1_CASC3,
      from_memCore0_to_mesh_B2_CASC0, from_memCore0_to_mesh_B2_CASC1,
      from_memCore0_to_mesh_B2_CASC2, from_memCore0_to_mesh_B2_CASC3,
      from_memCore0_to_mesh_B3_CASC0, from_memCore0_to_mesh_B3_CASC1,
      from_memCore0_to_mesh_B3_CASC2, from_memCore0_to_mesh_B3_CASC3);

  memcore_B(
      stream_uOP_memcore1_B, stream_from_ddr_to_memCoreB1, stream_from_lpddr_to_memCoreB1,
      from_memCore1_to_mesh_B0_CASC0, from_memCore1_to_mesh_B0_CASC1,
      from_memCore1_to_mesh_B0_CASC2, from_memCore1_to_mesh_B0_CASC3,
      from_memCore1_to_mesh_B1_CASC0, from_memCore1_to_mesh_B1_CASC1,
      from_memCore1_to_mesh_B1_CASC2, from_memCore1_to_mesh_B1_CASC3,
      from_memCore1_to_mesh_B2_CASC0, from_memCore1_to_mesh_B2_CASC1,
      from_memCore1_to_mesh_B2_CASC2, from_memCore1_to_mesh_B2_CASC3,
      from_memCore1_to_mesh_B3_CASC0, from_memCore1_to_mesh_B3_CASC1,
      from_memCore1_to_mesh_B3_CASC2, from_memCore1_to_mesh_B3_CASC3);

  memcore_B_colmajor(
      stream_uOP_memcore2_B, stream_from_ddr_to_memCoreB2, from_memCore2_to_mesh_B0_CASC0,
      from_memCore2_to_mesh_B0_CASC1, from_memCore2_to_mesh_B0_CASC2,
      from_memCore2_to_mesh_B0_CASC3, from_memCore2_to_mesh_B1_CASC0,
      from_memCore2_to_mesh_B1_CASC1, from_memCore2_to_mesh_B1_CASC2,
      from_memCore2_to_mesh_B1_CASC3, from_memCore2_to_mesh_B2_CASC0,
      from_memCore2_to_mesh_B2_CASC1, from_memCore2_to_mesh_B2_CASC2,
      from_memCore2_to_mesh_B2_CASC3, from_memCore2_to_mesh_B3_CASC0,
      from_memCore2_to_mesh_B3_CASC1, from_memCore2_to_mesh_B3_CASC2,
      from_memCore2_to_mesh_B3_CASC3);

  memcore_C_to_mesh(
      stream_uOP_memcore0_C, stream_to_ddr_from_memCoreC0, stream_from_ddr_to_memCoreC0,
      from_computeCore0_C00, from_computeCore0_C01, from_computeCore0_C02, from_computeCore0_C03,
      from_computeCore0_C10, from_computeCore0_C11, from_computeCore0_C12, from_computeCore0_C13,
      from_computeCore0_C20, from_computeCore0_C21, from_computeCore0_C22, from_computeCore0_C23,
      from_computeCore0_C30, from_computeCore0_C31, from_computeCore0_C32, from_computeCore0_C33,
      from_memCore0_to_mesh_C0_CASC0, from_memCore0_to_mesh_C0_CASC1,
      from_memCore0_to_mesh_C0_CASC2, from_memCore0_to_mesh_C0_CASC3,
      from_memCore0_to_mesh_C1_CASC0, from_memCore0_to_mesh_C1_CASC1,
      from_memCore0_to_mesh_C1_CASC2, from_memCore0_to_mesh_C1_CASC3,
      from_memCore0_to_mesh_C2_CASC0, from_memCore0_to_mesh_C2_CASC1,
      from_memCore0_to_mesh_C2_CASC2, from_memCore0_to_mesh_C2_CASC3,
      from_memCore0_to_mesh_C3_CASC0, from_memCore0_to_mesh_C3_CASC1,
      from_memCore0_to_mesh_C3_CASC2, from_memCore0_to_mesh_C3_CASC3, data_channel_core0to1,
      data_channel_core0to1_recvmesh, data_channel_core1to0, data_channel_core1to0_recvmesh);

  memcore_C_to_mesh(
      stream_uOP_memcore1_C, stream_to_ddr_from_memCoreC1, stream_from_ddr_to_memCoreC1,
      from_computeCore1_C00, from_computeCore1_C01, from_computeCore1_C02, from_computeCore1_C03,
      from_computeCore1_C10, from_computeCore1_C11, from_computeCore1_C12, from_computeCore1_C13,
      from_computeCore1_C20, from_computeCore1_C21, from_computeCore1_C22, from_computeCore1_C23,
      from_computeCore1_C30, from_computeCore1_C31, from_computeCore1_C32, from_computeCore1_C33,
      from_memCore1_to_mesh_C0_CASC0, from_memCore1_to_mesh_C0_CASC1,
      from_memCore1_to_mesh_C0_CASC2, from_memCore1_to_mesh_C0_CASC3,
      from_memCore1_to_mesh_C1_CASC0, from_memCore1_to_mesh_C1_CASC1,
      from_memCore1_to_mesh_C1_CASC2, from_memCore1_to_mesh_C1_CASC3,
      from_memCore1_to_mesh_C2_CASC0, from_memCore1_to_mesh_C2_CASC1,
      from_memCore1_to_mesh_C2_CASC2, from_memCore1_to_mesh_C2_CASC3,
      from_memCore1_to_mesh_C3_CASC0, from_memCore1_to_mesh_C3_CASC1,
      from_memCore1_to_mesh_C3_CASC2, from_memCore1_to_mesh_C3_CASC3, data_channel_core1to0,
      data_channel_core1to0_recvmesh, data_channel_core0to1, data_channel_core0to1_recvmesh);

  memcore_C_to_mesh(
      stream_uOP_memcore2_C, stream_to_ddr_from_memCoreC2, stream_from_ddr_to_memCoreC2,
      from_computeCore2_C00, from_computeCore2_C01, from_computeCore2_C02, from_computeCore2_C03,
      from_computeCore2_C10, from_computeCore2_C11, from_computeCore2_C12, from_computeCore2_C13,
      from_computeCore2_C20, from_computeCore2_C21, from_computeCore2_C22, from_computeCore2_C23,
      from_computeCore2_C30, from_computeCore2_C31, from_computeCore2_C32, from_computeCore2_C33,
      from_memCore2_to_mesh_C0_CASC0, from_memCore2_to_mesh_C0_CASC1,
      from_memCore2_to_mesh_C0_CASC2, from_memCore2_to_mesh_C0_CASC3,
      from_memCore2_to_mesh_C1_CASC0, from_memCore2_to_mesh_C1_CASC1,
      from_memCore2_to_mesh_C1_CASC2, from_memCore2_to_mesh_C1_CASC3,
      from_memCore2_to_mesh_C2_CASC0, from_memCore2_to_mesh_C2_CASC1,
      from_memCore2_to_mesh_C2_CASC2, from_memCore2_to_mesh_C2_CASC3,
      from_memCore2_to_mesh_C3_CASC0, from_memCore2_to_mesh_C3_CASC1,
      from_memCore2_to_mesh_C3_CASC2, from_memCore2_to_mesh_C3_CASC3, data_channel_core2to3,
      data_channel_core2to3_recvmesh, data_channel_core3to2, data_channel_core3to2_recvmesh);

  memcore_C_to_mesh(
      stream_uOP_memcore3_C, stream_to_ddr_from_memCoreC3, stream_from_ddr_to_memCoreC3,
      from_computeCore3_C00, from_computeCore3_C01, from_computeCore3_C02, from_computeCore3_C03,
      from_computeCore3_C10, from_computeCore3_C11, from_computeCore3_C12, from_computeCore3_C13,
      from_computeCore3_C20, from_computeCore3_C21, from_computeCore3_C22, from_computeCore3_C23,
      from_computeCore3_C30, from_computeCore3_C31, from_computeCore3_C32, from_computeCore3_C33,
      from_memCore3_to_mesh_C0_CASC0, from_memCore3_to_mesh_C0_CASC1,
      from_memCore3_to_mesh_C0_CASC2, from_memCore3_to_mesh_C0_CASC3,
      from_memCore3_to_mesh_C1_CASC0, from_memCore3_to_mesh_C1_CASC1,
      from_memCore3_to_mesh_C1_CASC2, from_memCore3_to_mesh_C1_CASC3,
      from_memCore3_to_mesh_C2_CASC0, from_memCore3_to_mesh_C2_CASC1,
      from_memCore3_to_mesh_C2_CASC2, from_memCore3_to_mesh_C2_CASC3,
      from_memCore3_to_mesh_C3_CASC0, from_memCore3_to_mesh_C3_CASC1,
      from_memCore3_to_mesh_C3_CASC2, from_memCore3_to_mesh_C3_CASC3, data_channel_core3to2,
      data_channel_core3to2_recvmesh, data_channel_core2to3, data_channel_core2to3_recvmesh);



  mesh_sendB(stream_uOP_mesh_sendB, from_memCore0_to_mesh_B0_CASC0, from_memCore0_to_mesh_B0_CASC1,
             from_memCore0_to_mesh_B0_CASC2, from_memCore0_to_mesh_B0_CASC3,
             from_memCore0_to_mesh_B1_CASC0, from_memCore0_to_mesh_B1_CASC1,
             from_memCore0_to_mesh_B1_CASC2, from_memCore0_to_mesh_B1_CASC3,
             from_memCore0_to_mesh_B2_CASC0, from_memCore0_to_mesh_B2_CASC1,
             from_memCore0_to_mesh_B2_CASC2, from_memCore0_to_mesh_B2_CASC3,
             from_memCore0_to_mesh_B3_CASC0, from_memCore0_to_mesh_B3_CASC1,
             from_memCore0_to_mesh_B3_CASC2, from_memCore0_to_mesh_B3_CASC3,
             from_memCore1_to_mesh_B0_CASC0, from_memCore1_to_mesh_B0_CASC1,
             from_memCore1_to_mesh_B0_CASC2, from_memCore1_to_mesh_B0_CASC3,
             from_memCore1_to_mesh_B1_CASC0, from_memCore1_to_mesh_B1_CASC1,
             from_memCore1_to_mesh_B1_CASC2, from_memCore1_to_mesh_B1_CASC3,
             from_memCore1_to_mesh_B2_CASC0, from_memCore1_to_mesh_B2_CASC1,
             from_memCore1_to_mesh_B2_CASC2, from_memCore1_to_mesh_B2_CASC3,
             from_memCore1_to_mesh_B3_CASC0, from_memCore1_to_mesh_B3_CASC1,
             from_memCore1_to_mesh_B3_CASC2, from_memCore1_to_mesh_B3_CASC3,
             from_memCore2_to_mesh_B0_CASC0, from_memCore2_to_mesh_B0_CASC1,
             from_memCore2_to_mesh_B0_CASC2, from_memCore2_to_mesh_B0_CASC3,
             from_memCore2_to_mesh_B1_CASC0, from_memCore2_to_mesh_B1_CASC1,
             from_memCore2_to_mesh_B1_CASC2, from_memCore2_to_mesh_B1_CASC3,
             from_memCore2_to_mesh_B2_CASC0, from_memCore2_to_mesh_B2_CASC1,
             from_memCore2_to_mesh_B2_CASC2, from_memCore2_to_mesh_B2_CASC3,
             from_memCore2_to_mesh_B3_CASC0, from_memCore2_to_mesh_B3_CASC1,
             from_memCore2_to_mesh_B3_CASC2, from_memCore2_to_mesh_B3_CASC3,
             to_computeCore0_B0_CASC0, to_computeCore0_B0_CASC1, to_computeCore0_B0_CASC2,
             to_computeCore0_B0_CASC3, to_computeCore0_B1_CASC0, to_computeCore0_B1_CASC1,
             to_computeCore0_B1_CASC2, to_computeCore0_B1_CASC3, to_computeCore0_B2_CASC0,
             to_computeCore0_B2_CASC1, to_computeCore0_B2_CASC2, to_computeCore0_B2_CASC3,
             to_computeCore0_B3_CASC0, to_computeCore0_B3_CASC1, to_computeCore0_B3_CASC2,
             to_computeCore0_B3_CASC3, to_computeCore1_B0_CASC0, to_computeCore1_B0_CASC1,
             to_computeCore1_B0_CASC2, to_computeCore1_B0_CASC3, to_computeCore1_B1_CASC0,
             to_computeCore1_B1_CASC1, to_computeCore1_B1_CASC2, to_computeCore1_B1_CASC3,
             to_computeCore1_B2_CASC0, to_computeCore1_B2_CASC1, to_computeCore1_B2_CASC2,
             to_computeCore1_B2_CASC3, to_computeCore1_B3_CASC0, to_computeCore1_B3_CASC1,
             to_computeCore1_B3_CASC2, to_computeCore1_B3_CASC3, to_computeCore2_B0_CASC0,
             to_computeCore2_B0_CASC1, to_computeCore2_B0_CASC2, to_computeCore2_B0_CASC3,
             to_computeCore2_B1_CASC0, to_computeCore2_B1_CASC1, to_computeCore2_B1_CASC2,
             to_computeCore2_B1_CASC3, to_computeCore2_B2_CASC0, to_computeCore2_B2_CASC1,
             to_computeCore2_B2_CASC2, to_computeCore2_B2_CASC3, to_computeCore2_B3_CASC0,
             to_computeCore2_B3_CASC1, to_computeCore2_B3_CASC2, to_computeCore2_B3_CASC3,
             to_computeCore3_B0_CASC0, to_computeCore3_B0_CASC1, to_computeCore3_B0_CASC2,
             to_computeCore3_B0_CASC3, to_computeCore3_B1_CASC0, to_computeCore3_B1_CASC1,
             to_computeCore3_B1_CASC2, to_computeCore3_B1_CASC3, to_computeCore3_B2_CASC0,
             to_computeCore3_B2_CASC1, to_computeCore3_B2_CASC2, to_computeCore3_B2_CASC3,
             to_computeCore3_B3_CASC0, to_computeCore3_B3_CASC1, to_computeCore3_B3_CASC2,
             to_computeCore3_B3_CASC3, to_computeCore4_B0_CASC0, to_computeCore4_B0_CASC1,
             to_computeCore4_B0_CASC2, to_computeCore4_B0_CASC3, to_computeCore4_B1_CASC0,
             to_computeCore4_B1_CASC1, to_computeCore4_B1_CASC2, to_computeCore4_B1_CASC3,
             to_computeCore4_B2_CASC0, to_computeCore4_B2_CASC1, to_computeCore4_B2_CASC2,
             to_computeCore4_B2_CASC3, to_computeCore4_B3_CASC0, to_computeCore4_B3_CASC1,
             to_computeCore4_B3_CASC2, to_computeCore4_B3_CASC3, to_computeCore5_B0_CASC0,
             to_computeCore5_B0_CASC1, to_computeCore5_B0_CASC2, to_computeCore5_B0_CASC3,
             to_computeCore5_B1_CASC0, to_computeCore5_B1_CASC1, to_computeCore5_B1_CASC2,
             to_computeCore5_B1_CASC3, to_computeCore5_B2_CASC0, to_computeCore5_B2_CASC1,
             to_computeCore5_B2_CASC2, to_computeCore5_B2_CASC3, to_computeCore5_B3_CASC0,
             to_computeCore5_B3_CASC1, to_computeCore5_B3_CASC2, to_computeCore5_B3_CASC3);

  mesh_sendA(stream_uOP_mesh_sendA, from_memCore0_to_mesh_A0_CASC0, from_memCore0_to_mesh_A0_CASC1,
             from_memCore0_to_mesh_A0_CASC2, from_memCore0_to_mesh_A0_CASC3,
             from_memCore0_to_mesh_A1_CASC0, from_memCore0_to_mesh_A1_CASC1,
             from_memCore0_to_mesh_A1_CASC2, from_memCore0_to_mesh_A1_CASC3,
             from_memCore0_to_mesh_A2_CASC0, from_memCore0_to_mesh_A2_CASC1,
             from_memCore0_to_mesh_A2_CASC2, from_memCore0_to_mesh_A2_CASC3,
             from_memCore0_to_mesh_A3_CASC0, from_memCore0_to_mesh_A3_CASC1,
             from_memCore0_to_mesh_A3_CASC2, from_memCore0_to_mesh_A3_CASC3,
             from_memCore1_to_mesh_A0_CASC0, from_memCore1_to_mesh_A0_CASC1,
             from_memCore1_to_mesh_A0_CASC2, from_memCore1_to_mesh_A0_CASC3,
             from_memCore1_to_mesh_A1_CASC0, from_memCore1_to_mesh_A1_CASC1,
             from_memCore1_to_mesh_A1_CASC2, from_memCore1_to_mesh_A1_CASC3,
             from_memCore1_to_mesh_A2_CASC0, from_memCore1_to_mesh_A2_CASC1,
             from_memCore1_to_mesh_A2_CASC2, from_memCore1_to_mesh_A2_CASC3,
             from_memCore1_to_mesh_A3_CASC0, from_memCore1_to_mesh_A3_CASC1,
             from_memCore1_to_mesh_A3_CASC2, from_memCore1_to_mesh_A3_CASC3,
             from_memCore2_to_mesh_A0_CASC0, from_memCore2_to_mesh_A0_CASC1,
             from_memCore2_to_mesh_A0_CASC2, from_memCore2_to_mesh_A0_CASC3,
             from_memCore2_to_mesh_A1_CASC0, from_memCore2_to_mesh_A1_CASC1,
             from_memCore2_to_mesh_A1_CASC2, from_memCore2_to_mesh_A1_CASC3,
             from_memCore2_to_mesh_A2_CASC0, from_memCore2_to_mesh_A2_CASC1,
             from_memCore2_to_mesh_A2_CASC2, from_memCore2_to_mesh_A2_CASC3,
             from_memCore2_to_mesh_A3_CASC0, from_memCore2_to_mesh_A3_CASC1,
             from_memCore2_to_mesh_A3_CASC2, from_memCore2_to_mesh_A3_CASC3,

             from_memCore0_to_mesh_C0_CASC0, from_memCore0_to_mesh_C0_CASC1,
             from_memCore0_to_mesh_C0_CASC2, from_memCore0_to_mesh_C0_CASC3,
             from_memCore0_to_mesh_C1_CASC0, from_memCore0_to_mesh_C1_CASC1,
             from_memCore0_to_mesh_C1_CASC2, from_memCore0_to_mesh_C1_CASC3,
             from_memCore0_to_mesh_C2_CASC0, from_memCore0_to_mesh_C2_CASC1,
             from_memCore0_to_mesh_C2_CASC2, from_memCore0_to_mesh_C2_CASC3,
             from_memCore0_to_mesh_C3_CASC0, from_memCore0_to_mesh_C3_CASC1,
             from_memCore0_to_mesh_C3_CASC2, from_memCore0_to_mesh_C3_CASC3,
             from_memCore1_to_mesh_C0_CASC0, from_memCore1_to_mesh_C0_CASC1,
             from_memCore1_to_mesh_C0_CASC2, from_memCore1_to_mesh_C0_CASC3,
             from_memCore1_to_mesh_C1_CASC0, from_memCore1_to_mesh_C1_CASC1,
             from_memCore1_to_mesh_C1_CASC2, from_memCore1_to_mesh_C1_CASC3,
             from_memCore1_to_mesh_C2_CASC0, from_memCore1_to_mesh_C2_CASC1,
             from_memCore1_to_mesh_C2_CASC2, from_memCore1_to_mesh_C2_CASC3,
             from_memCore1_to_mesh_C3_CASC0, from_memCore1_to_mesh_C3_CASC1,
             from_memCore1_to_mesh_C3_CASC2, from_memCore1_to_mesh_C3_CASC3,
             from_memCore2_to_mesh_C0_CASC0, from_memCore2_to_mesh_C0_CASC1,
             from_memCore2_to_mesh_C0_CASC2, from_memCore2_to_mesh_C0_CASC3,
             from_memCore2_to_mesh_C1_CASC0, from_memCore2_to_mesh_C1_CASC1,
             from_memCore2_to_mesh_C1_CASC2, from_memCore2_to_mesh_C1_CASC3,
             from_memCore2_to_mesh_C2_CASC0, from_memCore2_to_mesh_C2_CASC1,
             from_memCore2_to_mesh_C2_CASC2, from_memCore2_to_mesh_C2_CASC3,
             from_memCore2_to_mesh_C3_CASC0, from_memCore2_to_mesh_C3_CASC1,
             from_memCore2_to_mesh_C3_CASC2, from_memCore2_to_mesh_C3_CASC3,
             from_memCore3_to_mesh_C0_CASC0, from_memCore3_to_mesh_C0_CASC1,
             from_memCore3_to_mesh_C0_CASC2, from_memCore3_to_mesh_C0_CASC3,
             from_memCore3_to_mesh_C1_CASC0, from_memCore3_to_mesh_C1_CASC1,
             from_memCore3_to_mesh_C1_CASC2, from_memCore3_to_mesh_C1_CASC3,
             from_memCore3_to_mesh_C2_CASC0, from_memCore3_to_mesh_C2_CASC1,
             from_memCore3_to_mesh_C2_CASC2, from_memCore3_to_mesh_C2_CASC3,
             from_memCore3_to_mesh_C3_CASC0, from_memCore3_to_mesh_C3_CASC1,
             from_memCore3_to_mesh_C3_CASC2, from_memCore3_to_mesh_C3_CASC3,

             to_computeCore0_A0_CASC0, to_computeCore0_A0_CASC1, to_computeCore0_A0_CASC2,
             to_computeCore0_A0_CASC3, to_computeCore0_A1_CASC0, to_computeCore0_A1_CASC1,
             to_computeCore0_A1_CASC2, to_computeCore0_A1_CASC3, to_computeCore0_A2_CASC0,
             to_computeCore0_A2_CASC1, to_computeCore0_A2_CASC2, to_computeCore0_A2_CASC3,
             to_computeCore0_A3_CASC0, to_computeCore0_A3_CASC1, to_computeCore0_A3_CASC2,
             to_computeCore0_A3_CASC3, to_computeCore1_A0_CASC0, to_computeCore1_A0_CASC1,
             to_computeCore1_A0_CASC2, to_computeCore1_A0_CASC3, to_computeCore1_A1_CASC0,
             to_computeCore1_A1_CASC1, to_computeCore1_A1_CASC2, to_computeCore1_A1_CASC3,
             to_computeCore1_A2_CASC0, to_computeCore1_A2_CASC1, to_computeCore1_A2_CASC2,
             to_computeCore1_A2_CASC3, to_computeCore1_A3_CASC0, to_computeCore1_A3_CASC1,
             to_computeCore1_A3_CASC2, to_computeCore1_A3_CASC3, to_computeCore2_A0_CASC0,
             to_computeCore2_A0_CASC1, to_computeCore2_A0_CASC2, to_computeCore2_A0_CASC3,
             to_computeCore2_A1_CASC0, to_computeCore2_A1_CASC1, to_computeCore2_A1_CASC2,
             to_computeCore2_A1_CASC3, to_computeCore2_A2_CASC0, to_computeCore2_A2_CASC1,
             to_computeCore2_A2_CASC2, to_computeCore2_A2_CASC3, to_computeCore2_A3_CASC0,
             to_computeCore2_A3_CASC1, to_computeCore2_A3_CASC2, to_computeCore2_A3_CASC3,
             to_computeCore3_A0_CASC0, to_computeCore3_A0_CASC1, to_computeCore3_A0_CASC2,
             to_computeCore3_A0_CASC3, to_computeCore3_A1_CASC0, to_computeCore3_A1_CASC1,
             to_computeCore3_A1_CASC2, to_computeCore3_A1_CASC3, to_computeCore3_A2_CASC0,
             to_computeCore3_A2_CASC1, to_computeCore3_A2_CASC2, to_computeCore3_A2_CASC3,
             to_computeCore3_A3_CASC0, to_computeCore3_A3_CASC1, to_computeCore3_A3_CASC2,
             to_computeCore3_A3_CASC3, to_computeCore4_A0_CASC0, to_computeCore4_A0_CASC1,
             to_computeCore4_A0_CASC2, to_computeCore4_A0_CASC3, to_computeCore4_A1_CASC0,
             to_computeCore4_A1_CASC1, to_computeCore4_A1_CASC2, to_computeCore4_A1_CASC3,
             to_computeCore4_A2_CASC0, to_computeCore4_A2_CASC1, to_computeCore4_A2_CASC2,
             to_computeCore4_A2_CASC3, to_computeCore4_A3_CASC0, to_computeCore4_A3_CASC1,
             to_computeCore4_A3_CASC2, to_computeCore4_A3_CASC3, to_computeCore5_A0_CASC0,
             to_computeCore5_A0_CASC1, to_computeCore5_A0_CASC2, to_computeCore5_A0_CASC3,
             to_computeCore5_A1_CASC0, to_computeCore5_A1_CASC1, to_computeCore5_A1_CASC2,
             to_computeCore5_A1_CASC3, to_computeCore5_A2_CASC0, to_computeCore5_A2_CASC1,
             to_computeCore5_A2_CASC2, to_computeCore5_A2_CASC3, to_computeCore5_A3_CASC0,
             to_computeCore5_A3_CASC1, to_computeCore5_A3_CASC2, to_computeCore5_A3_CASC3);


  memcore_C(stream_uOP_memcore4_C, stream_to_ddr_from_memCoreC4, stream_from_ddr_to_memCoreC4,
            from_computeCore4_C00, from_computeCore4_C01, from_computeCore4_C02,
            from_computeCore4_C03, from_computeCore4_C10, from_computeCore4_C11,
            from_computeCore4_C12, from_computeCore4_C13, from_computeCore4_C20,
            from_computeCore4_C21, from_computeCore4_C22, from_computeCore4_C23,
            from_computeCore4_C30, from_computeCore4_C31, from_computeCore4_C32,
            from_computeCore4_C33, data_channel_core4to5, data_channel_core5to4);

  memcore_C(stream_uOP_memcore5_C, stream_to_ddr_from_memCoreC5, stream_from_ddr_to_memCoreC5,
            from_computeCore5_C00, from_computeCore5_C01, from_computeCore5_C02,
            from_computeCore5_C03, from_computeCore5_C10, from_computeCore5_C11,
            from_computeCore5_C12, from_computeCore5_C13, from_computeCore5_C20,
            from_computeCore5_C21, from_computeCore5_C22, from_computeCore5_C23,
            from_computeCore5_C30, from_computeCore5_C31, from_computeCore5_C32,
            from_computeCore5_C33, data_channel_core5to4, data_channel_core4to5);



  return;
}
}
