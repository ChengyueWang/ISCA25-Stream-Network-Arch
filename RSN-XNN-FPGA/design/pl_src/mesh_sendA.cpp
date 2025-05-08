#pragma once
#include "mesh_sendA.h"

void meshA_1to1stream(hls::stream<ap_uint<64>> &from_memCore,
                      hls::stream<ap_axiu<64, 0, 0, 0>> &to_axi) {
  ap_axiu<64, 0, 0, 0> axi_data;
  axi_data.data = from_memCore.read();
  axi_data.keep = 0xFF;
  to_axi.write(axi_data);
}

void meshA_1to2stream(hls::stream<ap_uint<64>> &from_memCore,
                      hls::stream<ap_axiu<64, 0, 0, 0>> &to_axi0,
                      hls::stream<ap_axiu<64, 0, 0, 0>> &to_axi1) {
  ap_axiu<64, 0, 0, 0> axi_data;
  axi_data.data = from_memCore.read();
  axi_data.keep = 0xFF;
  to_axi0.write(axi_data);
  to_axi1.write(axi_data);
}

void meshA_write_to_computecore(ap_uint<64> from_memCore,
                                hls::stream<ap_axiu<64, 0, 0, 0>> &to_axi) {
  ap_axiu<64, 0, 0, 0> axi_data;
  axi_data.data = from_memCore;
  axi_data.keep = 0xFF;
  to_axi.write(axi_data);
}

void mesh_sendA(hls::stream<uop_mesh_sendA_type> &stream_uOP_mesh_sendA,

                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A0_CASC0,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A0_CASC1,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A0_CASC2,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A0_CASC3,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A1_CASC0,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A1_CASC1,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A1_CASC2,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A1_CASC3,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A2_CASC0,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A2_CASC1,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A2_CASC2,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A2_CASC3,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A3_CASC0,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A3_CASC1,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A3_CASC2,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_A3_CASC3,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A0_CASC0,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A0_CASC1,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A0_CASC2,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A0_CASC3,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A1_CASC0,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A1_CASC1,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A1_CASC2,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A1_CASC3,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A2_CASC0,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A2_CASC1,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A2_CASC2,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A2_CASC3,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A3_CASC0,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A3_CASC1,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A3_CASC2,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_A3_CASC3,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A0_CASC0,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A0_CASC1,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A0_CASC2,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A0_CASC3,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A1_CASC0,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A1_CASC1,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A1_CASC2,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A1_CASC3,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A2_CASC0,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A2_CASC1,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A2_CASC2,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A2_CASC3,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A3_CASC0,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A3_CASC1,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A3_CASC2,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_A3_CASC3,

                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C0_CASC0,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C0_CASC1,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C0_CASC2,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C0_CASC3,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C1_CASC0,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C1_CASC1,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C1_CASC2,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C1_CASC3,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C2_CASC0,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C2_CASC1,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C2_CASC2,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C2_CASC3,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C3_CASC0,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C3_CASC1,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C3_CASC2,
                hls::stream<ap_uint<64>> &from_memCore0_to_mesh_C3_CASC3,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C0_CASC0,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C0_CASC1,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C0_CASC2,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C0_CASC3,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C1_CASC0,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C1_CASC1,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C1_CASC2,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C1_CASC3,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C2_CASC0,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C2_CASC1,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C2_CASC2,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C2_CASC3,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C3_CASC0,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C3_CASC1,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C3_CASC2,
                hls::stream<ap_uint<64>> &from_memCore1_to_mesh_C3_CASC3,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C0_CASC0,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C0_CASC1,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C0_CASC2,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C0_CASC3,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C1_CASC0,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C1_CASC1,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C1_CASC2,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C1_CASC3,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C2_CASC0,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C2_CASC1,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C2_CASC2,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C2_CASC3,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C3_CASC0,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C3_CASC1,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C3_CASC2,
                hls::stream<ap_uint<64>> &from_memCore2_to_mesh_C3_CASC3,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C0_CASC0,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C0_CASC1,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C0_CASC2,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C0_CASC3,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C1_CASC0,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C1_CASC1,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C1_CASC2,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C1_CASC3,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C2_CASC0,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C2_CASC1,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C2_CASC2,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C2_CASC3,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C3_CASC0,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C3_CASC1,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C3_CASC2,
                hls::stream<ap_uint<64>> &from_memCore3_to_mesh_C3_CASC3,

                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A0_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A0_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A0_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A0_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A1_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A1_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A1_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A1_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A2_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A2_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A2_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A2_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A3_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A3_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A3_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore0_A3_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A0_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A0_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A0_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A0_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A1_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A1_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A1_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A1_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A2_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A2_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A2_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A2_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A3_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A3_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A3_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore1_A3_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A0_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A0_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A0_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A0_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A1_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A1_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A1_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A1_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A2_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A2_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A2_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A2_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A3_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A3_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A3_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore2_A3_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A0_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A0_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A0_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A0_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A1_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A1_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A1_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A1_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A2_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A2_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A2_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A2_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A3_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A3_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A3_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore3_A3_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A0_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A0_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A0_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A0_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A1_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A1_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A1_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A1_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A2_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A2_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A2_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A2_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A3_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A3_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A3_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore4_A3_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A0_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A0_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A0_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A0_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A1_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A1_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A1_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A1_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A2_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A2_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A2_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A2_CASC3,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A3_CASC0,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A3_CASC1,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A3_CASC2,
                hls::stream<ap_axiu<64, 0, 0, 0>> &to_computeCore5_A3_CASC3

) {


  uop_mesh_sendA_type uOP;
  bool is_last_uOP = false;

WHILE_LOOP:
  while (is_last_uOP == false) {
    uOP = stream_uOP_mesh_sendA.read();
    is_last_uOP = uOP.is_last_uOP;
  FOR_UOPSIZE:
    for (ap_int<32> i = 0; i < uOP.size; i++) {

#pragma HLS PIPELINE II = 1
      ap_uint<64> memCore0_A0_CASC0, memCore0_A0_CASC1, memCore0_A0_CASC2, memCore0_A0_CASC3;
      ap_uint<64> memCore0_A1_CASC0, memCore0_A1_CASC1, memCore0_A1_CASC2, memCore0_A1_CASC3;
      ap_uint<64> memCore0_A2_CASC0, memCore0_A2_CASC1, memCore0_A2_CASC2, memCore0_A2_CASC3;
      ap_uint<64> memCore0_A3_CASC0, memCore0_A3_CASC1, memCore0_A3_CASC2, memCore0_A3_CASC3;
      ap_uint<64> memCore1_A0_CASC0, memCore1_A0_CASC1, memCore1_A0_CASC2, memCore1_A0_CASC3;
      ap_uint<64> memCore1_A1_CASC0, memCore1_A1_CASC1, memCore1_A1_CASC2, memCore1_A1_CASC3;
      ap_uint<64> memCore1_A2_CASC0, memCore1_A2_CASC1, memCore1_A2_CASC2, memCore1_A2_CASC3;
      ap_uint<64> memCore1_A3_CASC0, memCore1_A3_CASC1, memCore1_A3_CASC2, memCore1_A3_CASC3;
      ap_uint<64> memCore2_A0_CASC0, memCore2_A0_CASC1, memCore2_A0_CASC2, memCore2_A0_CASC3;
      ap_uint<64> memCore2_A1_CASC0, memCore2_A1_CASC1, memCore2_A1_CASC2, memCore2_A1_CASC3;
      ap_uint<64> memCore2_A2_CASC0, memCore2_A2_CASC1, memCore2_A2_CASC2, memCore2_A2_CASC3;
      ap_uint<64> memCore2_A3_CASC0, memCore2_A3_CASC1, memCore2_A3_CASC2, memCore2_A3_CASC3;

      ap_uint<64> memCore0_C0_CASC0, memCore0_C0_CASC1, memCore0_C0_CASC2, memCore0_C0_CASC3;
      ap_uint<64> memCore0_C1_CASC0, memCore0_C1_CASC1, memCore0_C1_CASC2, memCore0_C1_CASC3;
      ap_uint<64> memCore0_C2_CASC0, memCore0_C2_CASC1, memCore0_C2_CASC2, memCore0_C2_CASC3;
      ap_uint<64> memCore0_C3_CASC0, memCore0_C3_CASC1, memCore0_C3_CASC2, memCore0_C3_CASC3;
      ap_uint<64> memCore1_C0_CASC0, memCore1_C0_CASC1, memCore1_C0_CASC2, memCore1_C0_CASC3;
      ap_uint<64> memCore1_C1_CASC0, memCore1_C1_CASC1, memCore1_C1_CASC2, memCore1_C1_CASC3;
      ap_uint<64> memCore1_C2_CASC0, memCore1_C2_CASC1, memCore1_C2_CASC2, memCore1_C2_CASC3;
      ap_uint<64> memCore1_C3_CASC0, memCore1_C3_CASC1, memCore1_C3_CASC2, memCore1_C3_CASC3;
      ap_uint<64> memCore2_C0_CASC0, memCore2_C0_CASC1, memCore2_C0_CASC2, memCore2_C0_CASC3;
      ap_uint<64> memCore2_C1_CASC0, memCore2_C1_CASC1, memCore2_C1_CASC2, memCore2_C1_CASC3;
      ap_uint<64> memCore2_C2_CASC0, memCore2_C2_CASC1, memCore2_C2_CASC2, memCore2_C2_CASC3;
      ap_uint<64> memCore2_C3_CASC0, memCore2_C3_CASC1, memCore2_C3_CASC2, memCore2_C3_CASC3;
      ap_uint<64> memCore3_C0_CASC0, memCore3_C0_CASC1, memCore3_C0_CASC2, memCore3_C0_CASC3;
      ap_uint<64> memCore3_C1_CASC0, memCore3_C1_CASC1, memCore3_C1_CASC2, memCore3_C1_CASC3;
      ap_uint<64> memCore3_C2_CASC0, memCore3_C2_CASC1, memCore3_C2_CASC2, memCore3_C2_CASC3;
      ap_uint<64> memCore3_C3_CASC0, memCore3_C3_CASC1, memCore3_C3_CASC2, memCore3_C3_CASC3;

      ap_uint<64> computeCore0_A0_CASC0, computeCore0_A0_CASC1, computeCore0_A0_CASC2,
          computeCore0_A0_CASC3;
      ap_uint<64> computeCore0_A1_CASC0, computeCore0_A1_CASC1, computeCore0_A1_CASC2,
          computeCore0_A1_CASC3;
      ap_uint<64> computeCore0_A2_CASC0, computeCore0_A2_CASC1, computeCore0_A2_CASC2,
          computeCore0_A2_CASC3;
      ap_uint<64> computeCore0_A3_CASC0, computeCore0_A3_CASC1, computeCore0_A3_CASC2,
          computeCore0_A3_CASC3;
      ap_uint<64> computeCore1_A0_CASC0, computeCore1_A0_CASC1, computeCore1_A0_CASC2,
          computeCore1_A0_CASC3;
      ap_uint<64> computeCore1_A1_CASC0, computeCore1_A1_CASC1, computeCore1_A1_CASC2,
          computeCore1_A1_CASC3;
      ap_uint<64> computeCore1_A2_CASC0, computeCore1_A2_CASC1, computeCore1_A2_CASC2,
          computeCore1_A2_CASC3;
      ap_uint<64> computeCore1_A3_CASC0, computeCore1_A3_CASC1, computeCore1_A3_CASC2,
          computeCore1_A3_CASC3;
      ap_uint<64> computeCore2_A0_CASC0, computeCore2_A0_CASC1, computeCore2_A0_CASC2,
          computeCore2_A0_CASC3;
      ap_uint<64> computeCore2_A1_CASC0, computeCore2_A1_CASC1, computeCore2_A1_CASC2,
          computeCore2_A1_CASC3;
      ap_uint<64> computeCore2_A2_CASC0, computeCore2_A2_CASC1, computeCore2_A2_CASC2,
          computeCore2_A2_CASC3;
      ap_uint<64> computeCore2_A3_CASC0, computeCore2_A3_CASC1, computeCore2_A3_CASC2,
          computeCore2_A3_CASC3;
      ap_uint<64> computeCore3_A0_CASC0, computeCore3_A0_CASC1, computeCore3_A0_CASC2,
          computeCore3_A0_CASC3;
      ap_uint<64> computeCore3_A1_CASC0, computeCore3_A1_CASC1, computeCore3_A1_CASC2,
          computeCore3_A1_CASC3;
      ap_uint<64> computeCore3_A2_CASC0, computeCore3_A2_CASC1, computeCore3_A2_CASC2,
          computeCore3_A2_CASC3;
      ap_uint<64> computeCore3_A3_CASC0, computeCore3_A3_CASC1, computeCore3_A3_CASC2,
          computeCore3_A3_CASC3;
      ap_uint<64> computeCore4_A0_CASC0, computeCore4_A0_CASC1, computeCore4_A0_CASC2,
          computeCore4_A0_CASC3;
      ap_uint<64> computeCore4_A1_CASC0, computeCore4_A1_CASC1, computeCore4_A1_CASC2,
          computeCore4_A1_CASC3;
      ap_uint<64> computeCore4_A2_CASC0, computeCore4_A2_CASC1, computeCore4_A2_CASC2,
          computeCore4_A2_CASC3;
      ap_uint<64> computeCore4_A3_CASC0, computeCore4_A3_CASC1, computeCore4_A3_CASC2,
          computeCore4_A3_CASC3;
      ap_uint<64> computeCore5_A0_CASC0, computeCore5_A0_CASC1, computeCore5_A0_CASC2,
          computeCore5_A0_CASC3;
      ap_uint<64> computeCore5_A1_CASC0, computeCore5_A1_CASC1, computeCore5_A1_CASC2,
          computeCore5_A1_CASC3;
      ap_uint<64> computeCore5_A2_CASC0, computeCore5_A2_CASC1, computeCore5_A2_CASC2,
          computeCore5_A2_CASC3;
      ap_uint<64> computeCore5_A3_CASC0, computeCore5_A3_CASC1, computeCore5_A3_CASC2,
          computeCore5_A3_CASC3;

      if (uOP.memcoreA0_to_computecore0 || uOP.memcoreA0_to_computecore1) {
        memCore0_A0_CASC0 = from_memCore0_to_mesh_A0_CASC0.read();
        memCore0_A0_CASC1 = from_memCore0_to_mesh_A0_CASC1.read();
        memCore0_A0_CASC2 = from_memCore0_to_mesh_A0_CASC2.read();
        memCore0_A0_CASC3 = from_memCore0_to_mesh_A0_CASC3.read();
        memCore0_A1_CASC0 = from_memCore0_to_mesh_A1_CASC0.read();
        memCore0_A1_CASC1 = from_memCore0_to_mesh_A1_CASC1.read();
        memCore0_A1_CASC2 = from_memCore0_to_mesh_A1_CASC2.read();
        memCore0_A1_CASC3 = from_memCore0_to_mesh_A1_CASC3.read();
        memCore0_A2_CASC0 = from_memCore0_to_mesh_A2_CASC0.read();
        memCore0_A2_CASC1 = from_memCore0_to_mesh_A2_CASC1.read();
        memCore0_A2_CASC2 = from_memCore0_to_mesh_A2_CASC2.read();
        memCore0_A2_CASC3 = from_memCore0_to_mesh_A2_CASC3.read();
        memCore0_A3_CASC0 = from_memCore0_to_mesh_A3_CASC0.read();
        memCore0_A3_CASC1 = from_memCore0_to_mesh_A3_CASC1.read();
        memCore0_A3_CASC2 = from_memCore0_to_mesh_A3_CASC2.read();
        memCore0_A3_CASC3 = from_memCore0_to_mesh_A3_CASC3.read();
      }

      if (uOP.memcoreA1_to_computecore2 || uOP.memcoreA1_to_computecore3) {
        memCore1_A0_CASC0 = from_memCore1_to_mesh_A0_CASC0.read();
        memCore1_A0_CASC1 = from_memCore1_to_mesh_A0_CASC1.read();
        memCore1_A0_CASC2 = from_memCore1_to_mesh_A0_CASC2.read();
        memCore1_A0_CASC3 = from_memCore1_to_mesh_A0_CASC3.read();
        memCore1_A1_CASC0 = from_memCore1_to_mesh_A1_CASC0.read();
        memCore1_A1_CASC1 = from_memCore1_to_mesh_A1_CASC1.read();
        memCore1_A1_CASC2 = from_memCore1_to_mesh_A1_CASC2.read();
        memCore1_A1_CASC3 = from_memCore1_to_mesh_A1_CASC3.read();
        memCore1_A2_CASC0 = from_memCore1_to_mesh_A2_CASC0.read();
        memCore1_A2_CASC1 = from_memCore1_to_mesh_A2_CASC1.read();
        memCore1_A2_CASC2 = from_memCore1_to_mesh_A2_CASC2.read();
        memCore1_A2_CASC3 = from_memCore1_to_mesh_A2_CASC3.read();
        memCore1_A3_CASC0 = from_memCore1_to_mesh_A3_CASC0.read();
        memCore1_A3_CASC1 = from_memCore1_to_mesh_A3_CASC1.read();
        memCore1_A3_CASC2 = from_memCore1_to_mesh_A3_CASC2.read();
        memCore1_A3_CASC3 = from_memCore1_to_mesh_A3_CASC3.read();
      }

      if (uOP.memcoreA2_to_computecore4 || uOP.memcoreA2_to_computecore5) {
        memCore2_A0_CASC0 = from_memCore2_to_mesh_A0_CASC0.read();
        memCore2_A0_CASC1 = from_memCore2_to_mesh_A0_CASC1.read();
        memCore2_A0_CASC2 = from_memCore2_to_mesh_A0_CASC2.read();
        memCore2_A0_CASC3 = from_memCore2_to_mesh_A0_CASC3.read();
        memCore2_A1_CASC0 = from_memCore2_to_mesh_A1_CASC0.read();
        memCore2_A1_CASC1 = from_memCore2_to_mesh_A1_CASC1.read();
        memCore2_A1_CASC2 = from_memCore2_to_mesh_A1_CASC2.read();
        memCore2_A1_CASC3 = from_memCore2_to_mesh_A1_CASC3.read();
        memCore2_A2_CASC0 = from_memCore2_to_mesh_A2_CASC0.read();
        memCore2_A2_CASC1 = from_memCore2_to_mesh_A2_CASC1.read();
        memCore2_A2_CASC2 = from_memCore2_to_mesh_A2_CASC2.read();
        memCore2_A2_CASC3 = from_memCore2_to_mesh_A2_CASC3.read();
        memCore2_A3_CASC0 = from_memCore2_to_mesh_A3_CASC0.read();
        memCore2_A3_CASC1 = from_memCore2_to_mesh_A3_CASC1.read();
        memCore2_A3_CASC2 = from_memCore2_to_mesh_A3_CASC2.read();
        memCore2_A3_CASC3 = from_memCore2_to_mesh_A3_CASC3.read();
      }

      if (uOP.memcoreC0_to_computecore4) {
        memCore0_C0_CASC0 = from_memCore0_to_mesh_C0_CASC0.read();
        memCore0_C0_CASC1 = from_memCore0_to_mesh_C0_CASC1.read();
        memCore0_C0_CASC2 = from_memCore0_to_mesh_C0_CASC2.read();
        memCore0_C0_CASC3 = from_memCore0_to_mesh_C0_CASC3.read();
        memCore0_C1_CASC0 = from_memCore0_to_mesh_C1_CASC0.read();
        memCore0_C1_CASC1 = from_memCore0_to_mesh_C1_CASC1.read();
        memCore0_C1_CASC2 = from_memCore0_to_mesh_C1_CASC2.read();
        memCore0_C1_CASC3 = from_memCore0_to_mesh_C1_CASC3.read();
        memCore0_C2_CASC0 = from_memCore0_to_mesh_C2_CASC0.read();
        memCore0_C2_CASC1 = from_memCore0_to_mesh_C2_CASC1.read();
        memCore0_C2_CASC2 = from_memCore0_to_mesh_C2_CASC2.read();
        memCore0_C2_CASC3 = from_memCore0_to_mesh_C2_CASC3.read();
        memCore0_C3_CASC0 = from_memCore0_to_mesh_C3_CASC0.read();
        memCore0_C3_CASC1 = from_memCore0_to_mesh_C3_CASC1.read();
        memCore0_C3_CASC2 = from_memCore0_to_mesh_C3_CASC2.read();
        memCore0_C3_CASC3 = from_memCore0_to_mesh_C3_CASC3.read();
      }

      if (uOP.memcoreC1_to_computecore4) {
        memCore1_C0_CASC0 = from_memCore1_to_mesh_C0_CASC0.read();
        memCore1_C0_CASC1 = from_memCore1_to_mesh_C0_CASC1.read();
        memCore1_C0_CASC2 = from_memCore1_to_mesh_C0_CASC2.read();
        memCore1_C0_CASC3 = from_memCore1_to_mesh_C0_CASC3.read();
        memCore1_C1_CASC0 = from_memCore1_to_mesh_C1_CASC0.read();
        memCore1_C1_CASC1 = from_memCore1_to_mesh_C1_CASC1.read();
        memCore1_C1_CASC2 = from_memCore1_to_mesh_C1_CASC2.read();
        memCore1_C1_CASC3 = from_memCore1_to_mesh_C1_CASC3.read();
        memCore1_C2_CASC0 = from_memCore1_to_mesh_C2_CASC0.read();
        memCore1_C2_CASC1 = from_memCore1_to_mesh_C2_CASC1.read();
        memCore1_C2_CASC2 = from_memCore1_to_mesh_C2_CASC2.read();
        memCore1_C2_CASC3 = from_memCore1_to_mesh_C2_CASC3.read();
        memCore1_C3_CASC0 = from_memCore1_to_mesh_C3_CASC0.read();
        memCore1_C3_CASC1 = from_memCore1_to_mesh_C3_CASC1.read();
        memCore1_C3_CASC2 = from_memCore1_to_mesh_C3_CASC2.read();
        memCore1_C3_CASC3 = from_memCore1_to_mesh_C3_CASC3.read();
      }

      if (uOP.memcoreC2_to_computecore5) {
        memCore2_C0_CASC0 = from_memCore2_to_mesh_C0_CASC0.read();
        memCore2_C0_CASC1 = from_memCore2_to_mesh_C0_CASC1.read();
        memCore2_C0_CASC2 = from_memCore2_to_mesh_C0_CASC2.read();
        memCore2_C0_CASC3 = from_memCore2_to_mesh_C0_CASC3.read();
        memCore2_C1_CASC0 = from_memCore2_to_mesh_C1_CASC0.read();
        memCore2_C1_CASC1 = from_memCore2_to_mesh_C1_CASC1.read();
        memCore2_C1_CASC2 = from_memCore2_to_mesh_C1_CASC2.read();
        memCore2_C1_CASC3 = from_memCore2_to_mesh_C1_CASC3.read();
        memCore2_C2_CASC0 = from_memCore2_to_mesh_C2_CASC0.read();
        memCore2_C2_CASC1 = from_memCore2_to_mesh_C2_CASC1.read();
        memCore2_C2_CASC2 = from_memCore2_to_mesh_C2_CASC2.read();
        memCore2_C2_CASC3 = from_memCore2_to_mesh_C2_CASC3.read();
        memCore2_C3_CASC0 = from_memCore2_to_mesh_C3_CASC0.read();
        memCore2_C3_CASC1 = from_memCore2_to_mesh_C3_CASC1.read();
        memCore2_C3_CASC2 = from_memCore2_to_mesh_C3_CASC2.read();
        memCore2_C3_CASC3 = from_memCore2_to_mesh_C3_CASC3.read();
      }

      if (uOP.memcoreC3_to_computecore5) {
        memCore3_C0_CASC0 = from_memCore3_to_mesh_C0_CASC0.read();
        memCore3_C0_CASC1 = from_memCore3_to_mesh_C0_CASC1.read();
        memCore3_C0_CASC2 = from_memCore3_to_mesh_C0_CASC2.read();
        memCore3_C0_CASC3 = from_memCore3_to_mesh_C0_CASC3.read();
        memCore3_C1_CASC0 = from_memCore3_to_mesh_C1_CASC0.read();
        memCore3_C1_CASC1 = from_memCore3_to_mesh_C1_CASC1.read();
        memCore3_C1_CASC2 = from_memCore3_to_mesh_C1_CASC2.read();
        memCore3_C1_CASC3 = from_memCore3_to_mesh_C1_CASC3.read();
        memCore3_C2_CASC0 = from_memCore3_to_mesh_C2_CASC0.read();
        memCore3_C2_CASC1 = from_memCore3_to_mesh_C2_CASC1.read();
        memCore3_C2_CASC2 = from_memCore3_to_mesh_C2_CASC2.read();
        memCore3_C2_CASC3 = from_memCore3_to_mesh_C2_CASC3.read();
        memCore3_C3_CASC0 = from_memCore3_to_mesh_C3_CASC0.read();
        memCore3_C3_CASC1 = from_memCore3_to_mesh_C3_CASC1.read();
        memCore3_C3_CASC2 = from_memCore3_to_mesh_C3_CASC2.read();
        memCore3_C3_CASC3 = from_memCore3_to_mesh_C3_CASC3.read();
      }

      computeCore0_A0_CASC0 = memCore0_A0_CASC0;
      computeCore0_A0_CASC1 = memCore0_A0_CASC1;
      computeCore0_A0_CASC2 = memCore0_A0_CASC2;
      computeCore0_A0_CASC3 = memCore0_A0_CASC3;
      computeCore0_A1_CASC0 = memCore0_A1_CASC0;
      computeCore0_A1_CASC1 = memCore0_A1_CASC1;
      computeCore0_A1_CASC2 = memCore0_A1_CASC2;
      computeCore0_A1_CASC3 = memCore0_A1_CASC3;
      computeCore0_A2_CASC0 = memCore0_A2_CASC0;
      computeCore0_A2_CASC1 = memCore0_A2_CASC1;
      computeCore0_A2_CASC2 = memCore0_A2_CASC2;
      computeCore0_A2_CASC3 = memCore0_A2_CASC3;
      computeCore0_A3_CASC0 = memCore0_A3_CASC0;
      computeCore0_A3_CASC1 = memCore0_A3_CASC1;
      computeCore0_A3_CASC2 = memCore0_A3_CASC2;
      computeCore0_A3_CASC3 = memCore0_A3_CASC3;

      computeCore1_A0_CASC0 = memCore0_A0_CASC0;
      computeCore1_A0_CASC1 = memCore0_A0_CASC1;
      computeCore1_A0_CASC2 = memCore0_A0_CASC2;
      computeCore1_A0_CASC3 = memCore0_A0_CASC3;
      computeCore1_A1_CASC0 = memCore0_A1_CASC0;
      computeCore1_A1_CASC1 = memCore0_A1_CASC1;
      computeCore1_A1_CASC2 = memCore0_A1_CASC2;
      computeCore1_A1_CASC3 = memCore0_A1_CASC3;
      computeCore1_A2_CASC0 = memCore0_A2_CASC0;
      computeCore1_A2_CASC1 = memCore0_A2_CASC1;
      computeCore1_A2_CASC2 = memCore0_A2_CASC2;
      computeCore1_A2_CASC3 = memCore0_A2_CASC3;
      computeCore1_A3_CASC0 = memCore0_A3_CASC0;
      computeCore1_A3_CASC1 = memCore0_A3_CASC1;
      computeCore1_A3_CASC2 = memCore0_A3_CASC2;
      computeCore1_A3_CASC3 = memCore0_A3_CASC3;

      computeCore2_A0_CASC0 = memCore1_A0_CASC0;
      computeCore2_A0_CASC1 = memCore1_A0_CASC1;
      computeCore2_A0_CASC2 = memCore1_A0_CASC2;
      computeCore2_A0_CASC3 = memCore1_A0_CASC3;
      computeCore2_A1_CASC0 = memCore1_A1_CASC0;
      computeCore2_A1_CASC1 = memCore1_A1_CASC1;
      computeCore2_A1_CASC2 = memCore1_A1_CASC2;
      computeCore2_A1_CASC3 = memCore1_A1_CASC3;
      computeCore2_A2_CASC0 = memCore1_A2_CASC0;
      computeCore2_A2_CASC1 = memCore1_A2_CASC1;
      computeCore2_A2_CASC2 = memCore1_A2_CASC2;
      computeCore2_A2_CASC3 = memCore1_A2_CASC3;
      computeCore2_A3_CASC0 = memCore1_A3_CASC0;
      computeCore2_A3_CASC1 = memCore1_A3_CASC1;
      computeCore2_A3_CASC2 = memCore1_A3_CASC2;
      computeCore2_A3_CASC3 = memCore1_A3_CASC3;

      computeCore3_A0_CASC0 = memCore1_A0_CASC0;
      computeCore3_A0_CASC1 = memCore1_A0_CASC1;
      computeCore3_A0_CASC2 = memCore1_A0_CASC2;
      computeCore3_A0_CASC3 = memCore1_A0_CASC3;
      computeCore3_A1_CASC0 = memCore1_A1_CASC0;
      computeCore3_A1_CASC1 = memCore1_A1_CASC1;
      computeCore3_A1_CASC2 = memCore1_A1_CASC2;
      computeCore3_A1_CASC3 = memCore1_A1_CASC3;
      computeCore3_A2_CASC0 = memCore1_A2_CASC0;
      computeCore3_A2_CASC1 = memCore1_A2_CASC1;
      computeCore3_A2_CASC2 = memCore1_A2_CASC2;
      computeCore3_A2_CASC3 = memCore1_A2_CASC3;
      computeCore3_A3_CASC0 = memCore1_A3_CASC0;
      computeCore3_A3_CASC1 = memCore1_A3_CASC1;
      computeCore3_A3_CASC2 = memCore1_A3_CASC2;
      computeCore3_A3_CASC3 = memCore1_A3_CASC3;

      if (uOP.memcoreA2_to_computecore4 == true) {
        computeCore4_A0_CASC0 = memCore2_A0_CASC0;
        computeCore4_A0_CASC1 = memCore2_A0_CASC1;
        computeCore4_A0_CASC2 = memCore2_A0_CASC2;
        computeCore4_A0_CASC3 = memCore2_A0_CASC3;
        computeCore4_A1_CASC0 = memCore2_A1_CASC0;
        computeCore4_A1_CASC1 = memCore2_A1_CASC1;
        computeCore4_A1_CASC2 = memCore2_A1_CASC2;
        computeCore4_A1_CASC3 = memCore2_A1_CASC3;
        computeCore4_A2_CASC0 = memCore2_A2_CASC0;
        computeCore4_A2_CASC1 = memCore2_A2_CASC1;
        computeCore4_A2_CASC2 = memCore2_A2_CASC2;
        computeCore4_A2_CASC3 = memCore2_A2_CASC3;
        computeCore4_A3_CASC0 = memCore2_A3_CASC0;
        computeCore4_A3_CASC1 = memCore2_A3_CASC1;
        computeCore4_A3_CASC2 = memCore2_A3_CASC2;
        computeCore4_A3_CASC3 = memCore2_A3_CASC3;
      } else if (uOP.memcoreC0_to_computecore4 == true) {
        computeCore4_A0_CASC0 = memCore0_C0_CASC0;
        computeCore4_A0_CASC1 = memCore0_C0_CASC1;
        computeCore4_A0_CASC2 = memCore0_C0_CASC2;
        computeCore4_A0_CASC3 = memCore0_C0_CASC3;
        computeCore4_A1_CASC0 = memCore0_C1_CASC0;
        computeCore4_A1_CASC1 = memCore0_C1_CASC1;
        computeCore4_A1_CASC2 = memCore0_C1_CASC2;
        computeCore4_A1_CASC3 = memCore0_C1_CASC3;
        computeCore4_A2_CASC0 = memCore0_C2_CASC0;
        computeCore4_A2_CASC1 = memCore0_C2_CASC1;
        computeCore4_A2_CASC2 = memCore0_C2_CASC2;
        computeCore4_A2_CASC3 = memCore0_C2_CASC3;
        computeCore4_A3_CASC0 = memCore0_C3_CASC0;
        computeCore4_A3_CASC1 = memCore0_C3_CASC1;
        computeCore4_A3_CASC2 = memCore0_C3_CASC2;
        computeCore4_A3_CASC3 = memCore0_C3_CASC3;
      } else {  // memcoreC1_to_computecore4 == true or false
        computeCore4_A0_CASC0 = memCore1_C0_CASC0;
        computeCore4_A0_CASC1 = memCore1_C0_CASC1;
        computeCore4_A0_CASC2 = memCore1_C0_CASC2;
        computeCore4_A0_CASC3 = memCore1_C0_CASC3;
        computeCore4_A1_CASC0 = memCore1_C1_CASC0;
        computeCore4_A1_CASC1 = memCore1_C1_CASC1;
        computeCore4_A1_CASC2 = memCore1_C1_CASC2;
        computeCore4_A1_CASC3 = memCore1_C1_CASC3;
        computeCore4_A2_CASC0 = memCore1_C2_CASC0;
        computeCore4_A2_CASC1 = memCore1_C2_CASC1;
        computeCore4_A2_CASC2 = memCore1_C2_CASC2;
        computeCore4_A2_CASC3 = memCore1_C2_CASC3;
        computeCore4_A3_CASC0 = memCore1_C3_CASC0;
        computeCore4_A3_CASC1 = memCore1_C3_CASC1;
        computeCore4_A3_CASC2 = memCore1_C3_CASC2;
        computeCore4_A3_CASC3 = memCore1_C3_CASC3;
      }

      if (uOP.memcoreA2_to_computecore5 == true) {
        computeCore5_A0_CASC0 = memCore2_A0_CASC0;
        computeCore5_A0_CASC1 = memCore2_A0_CASC1;
        computeCore5_A0_CASC2 = memCore2_A0_CASC2;
        computeCore5_A0_CASC3 = memCore2_A0_CASC3;
        computeCore5_A1_CASC0 = memCore2_A1_CASC0;
        computeCore5_A1_CASC1 = memCore2_A1_CASC1;
        computeCore5_A1_CASC2 = memCore2_A1_CASC2;
        computeCore5_A1_CASC3 = memCore2_A1_CASC3;
        computeCore5_A2_CASC0 = memCore2_A2_CASC0;
        computeCore5_A2_CASC1 = memCore2_A2_CASC1;
        computeCore5_A2_CASC2 = memCore2_A2_CASC2;
        computeCore5_A2_CASC3 = memCore2_A2_CASC3;
        computeCore5_A3_CASC0 = memCore2_A3_CASC0;
        computeCore5_A3_CASC1 = memCore2_A3_CASC1;
        computeCore5_A3_CASC2 = memCore2_A3_CASC2;
        computeCore5_A3_CASC3 = memCore2_A3_CASC3;
      } else if (uOP.memcoreC2_to_computecore5 == true) {
        computeCore5_A0_CASC0 = memCore2_C0_CASC0;
        computeCore5_A0_CASC1 = memCore2_C0_CASC1;
        computeCore5_A0_CASC2 = memCore2_C0_CASC2;
        computeCore5_A0_CASC3 = memCore2_C0_CASC3;
        computeCore5_A1_CASC0 = memCore2_C1_CASC0;
        computeCore5_A1_CASC1 = memCore2_C1_CASC1;
        computeCore5_A1_CASC2 = memCore2_C1_CASC2;
        computeCore5_A1_CASC3 = memCore2_C1_CASC3;
        computeCore5_A2_CASC0 = memCore2_C2_CASC0;
        computeCore5_A2_CASC1 = memCore2_C2_CASC1;
        computeCore5_A2_CASC2 = memCore2_C2_CASC2;
        computeCore5_A2_CASC3 = memCore2_C2_CASC3;
        computeCore5_A3_CASC0 = memCore2_C3_CASC0;
        computeCore5_A3_CASC1 = memCore2_C3_CASC1;
        computeCore5_A3_CASC2 = memCore2_C3_CASC2;
        computeCore5_A3_CASC3 = memCore2_C3_CASC3;
      } else {  // memcoreC3_to_computecore5 == true or false
        computeCore5_A0_CASC0 = memCore3_C0_CASC0;
        computeCore5_A0_CASC1 = memCore3_C0_CASC1;
        computeCore5_A0_CASC2 = memCore3_C0_CASC2;
        computeCore5_A0_CASC3 = memCore3_C0_CASC3;
        computeCore5_A1_CASC0 = memCore3_C1_CASC0;
        computeCore5_A1_CASC1 = memCore3_C1_CASC1;
        computeCore5_A1_CASC2 = memCore3_C1_CASC2;
        computeCore5_A1_CASC3 = memCore3_C1_CASC3;
        computeCore5_A2_CASC0 = memCore3_C2_CASC0;
        computeCore5_A2_CASC1 = memCore3_C2_CASC1;
        computeCore5_A2_CASC2 = memCore3_C2_CASC2;
        computeCore5_A2_CASC3 = memCore3_C2_CASC3;
        computeCore5_A3_CASC0 = memCore3_C3_CASC0;
        computeCore5_A3_CASC1 = memCore3_C3_CASC1;
        computeCore5_A3_CASC2 = memCore3_C3_CASC2;
        computeCore5_A3_CASC3 = memCore3_C3_CASC3;
      }

      if (uOP.memcoreA0_to_computecore0) {

        meshA_write_to_computecore(computeCore0_A0_CASC0, to_computeCore0_A0_CASC0);
        meshA_write_to_computecore(computeCore0_A0_CASC1, to_computeCore0_A0_CASC1);
        meshA_write_to_computecore(computeCore0_A0_CASC2, to_computeCore0_A0_CASC2);
        meshA_write_to_computecore(computeCore0_A0_CASC3, to_computeCore0_A0_CASC3);
        meshA_write_to_computecore(computeCore0_A1_CASC0, to_computeCore0_A1_CASC0);
        meshA_write_to_computecore(computeCore0_A1_CASC1, to_computeCore0_A1_CASC1);
        meshA_write_to_computecore(computeCore0_A1_CASC2, to_computeCore0_A1_CASC2);
        meshA_write_to_computecore(computeCore0_A1_CASC3, to_computeCore0_A1_CASC3);
        meshA_write_to_computecore(computeCore0_A2_CASC0, to_computeCore0_A2_CASC0);
        meshA_write_to_computecore(computeCore0_A2_CASC1, to_computeCore0_A2_CASC1);
        meshA_write_to_computecore(computeCore0_A2_CASC2, to_computeCore0_A2_CASC2);
        meshA_write_to_computecore(computeCore0_A2_CASC3, to_computeCore0_A2_CASC3);
        meshA_write_to_computecore(computeCore0_A3_CASC0, to_computeCore0_A3_CASC0);
        meshA_write_to_computecore(computeCore0_A3_CASC1, to_computeCore0_A3_CASC1);
        meshA_write_to_computecore(computeCore0_A3_CASC2, to_computeCore0_A3_CASC2);
        meshA_write_to_computecore(computeCore0_A3_CASC3, to_computeCore0_A3_CASC3);
      }
      if (uOP.memcoreA0_to_computecore1) {


        meshA_write_to_computecore(computeCore1_A0_CASC0, to_computeCore1_A0_CASC0);
        meshA_write_to_computecore(computeCore1_A0_CASC1, to_computeCore1_A0_CASC1);
        meshA_write_to_computecore(computeCore1_A0_CASC2, to_computeCore1_A0_CASC2);
        meshA_write_to_computecore(computeCore1_A0_CASC3, to_computeCore1_A0_CASC3);
        meshA_write_to_computecore(computeCore1_A1_CASC0, to_computeCore1_A1_CASC0);
        meshA_write_to_computecore(computeCore1_A1_CASC1, to_computeCore1_A1_CASC1);
        meshA_write_to_computecore(computeCore1_A1_CASC2, to_computeCore1_A1_CASC2);
        meshA_write_to_computecore(computeCore1_A1_CASC3, to_computeCore1_A1_CASC3);
        meshA_write_to_computecore(computeCore1_A2_CASC0, to_computeCore1_A2_CASC0);
        meshA_write_to_computecore(computeCore1_A2_CASC1, to_computeCore1_A2_CASC1);
        meshA_write_to_computecore(computeCore1_A2_CASC2, to_computeCore1_A2_CASC2);
        meshA_write_to_computecore(computeCore1_A2_CASC3, to_computeCore1_A2_CASC3);
        meshA_write_to_computecore(computeCore1_A3_CASC0, to_computeCore1_A3_CASC0);
        meshA_write_to_computecore(computeCore1_A3_CASC1, to_computeCore1_A3_CASC1);
        meshA_write_to_computecore(computeCore1_A3_CASC2, to_computeCore1_A3_CASC2);
        meshA_write_to_computecore(computeCore1_A3_CASC3, to_computeCore1_A3_CASC3);
      }

      if (uOP.memcoreA1_to_computecore2) {

        meshA_write_to_computecore(computeCore2_A0_CASC0, to_computeCore2_A0_CASC0);
        meshA_write_to_computecore(computeCore2_A0_CASC1, to_computeCore2_A0_CASC1);
        meshA_write_to_computecore(computeCore2_A0_CASC2, to_computeCore2_A0_CASC2);
        meshA_write_to_computecore(computeCore2_A0_CASC3, to_computeCore2_A0_CASC3);
        meshA_write_to_computecore(computeCore2_A1_CASC0, to_computeCore2_A1_CASC0);
        meshA_write_to_computecore(computeCore2_A1_CASC1, to_computeCore2_A1_CASC1);
        meshA_write_to_computecore(computeCore2_A1_CASC2, to_computeCore2_A1_CASC2);
        meshA_write_to_computecore(computeCore2_A1_CASC3, to_computeCore2_A1_CASC3);
        meshA_write_to_computecore(computeCore2_A2_CASC0, to_computeCore2_A2_CASC0);
        meshA_write_to_computecore(computeCore2_A2_CASC1, to_computeCore2_A2_CASC1);
        meshA_write_to_computecore(computeCore2_A2_CASC2, to_computeCore2_A2_CASC2);
        meshA_write_to_computecore(computeCore2_A2_CASC3, to_computeCore2_A2_CASC3);
        meshA_write_to_computecore(computeCore2_A3_CASC0, to_computeCore2_A3_CASC0);
        meshA_write_to_computecore(computeCore2_A3_CASC1, to_computeCore2_A3_CASC1);
        meshA_write_to_computecore(computeCore2_A3_CASC2, to_computeCore2_A3_CASC2);
        meshA_write_to_computecore(computeCore2_A3_CASC3, to_computeCore2_A3_CASC3);
      }

      if (uOP.memcoreA1_to_computecore3) {


        meshA_write_to_computecore(computeCore3_A0_CASC0, to_computeCore3_A0_CASC0);
        meshA_write_to_computecore(computeCore3_A0_CASC1, to_computeCore3_A0_CASC1);
        meshA_write_to_computecore(computeCore3_A0_CASC2, to_computeCore3_A0_CASC2);
        meshA_write_to_computecore(computeCore3_A0_CASC3, to_computeCore3_A0_CASC3);
        meshA_write_to_computecore(computeCore3_A1_CASC0, to_computeCore3_A1_CASC0);
        meshA_write_to_computecore(computeCore3_A1_CASC1, to_computeCore3_A1_CASC1);
        meshA_write_to_computecore(computeCore3_A1_CASC2, to_computeCore3_A1_CASC2);
        meshA_write_to_computecore(computeCore3_A1_CASC3, to_computeCore3_A1_CASC3);
        meshA_write_to_computecore(computeCore3_A2_CASC0, to_computeCore3_A2_CASC0);
        meshA_write_to_computecore(computeCore3_A2_CASC1, to_computeCore3_A2_CASC1);
        meshA_write_to_computecore(computeCore3_A2_CASC2, to_computeCore3_A2_CASC2);
        meshA_write_to_computecore(computeCore3_A2_CASC3, to_computeCore3_A2_CASC3);
        meshA_write_to_computecore(computeCore3_A3_CASC0, to_computeCore3_A3_CASC0);
        meshA_write_to_computecore(computeCore3_A3_CASC1, to_computeCore3_A3_CASC1);
        meshA_write_to_computecore(computeCore3_A3_CASC2, to_computeCore3_A3_CASC2);
        meshA_write_to_computecore(computeCore3_A3_CASC3, to_computeCore3_A3_CASC3);
      }

      if (uOP.memcoreA2_to_computecore4 || uOP.memcoreC0_to_computecore4 ||
          uOP.memcoreC1_to_computecore4) {


        meshA_write_to_computecore(computeCore4_A0_CASC0, to_computeCore4_A0_CASC0);
        meshA_write_to_computecore(computeCore4_A0_CASC1, to_computeCore4_A0_CASC1);
        meshA_write_to_computecore(computeCore4_A0_CASC2, to_computeCore4_A0_CASC2);
        meshA_write_to_computecore(computeCore4_A0_CASC3, to_computeCore4_A0_CASC3);
        meshA_write_to_computecore(computeCore4_A1_CASC0, to_computeCore4_A1_CASC0);
        meshA_write_to_computecore(computeCore4_A1_CASC1, to_computeCore4_A1_CASC1);
        meshA_write_to_computecore(computeCore4_A1_CASC2, to_computeCore4_A1_CASC2);
        meshA_write_to_computecore(computeCore4_A1_CASC3, to_computeCore4_A1_CASC3);
        meshA_write_to_computecore(computeCore4_A2_CASC0, to_computeCore4_A2_CASC0);
        meshA_write_to_computecore(computeCore4_A2_CASC1, to_computeCore4_A2_CASC1);
        meshA_write_to_computecore(computeCore4_A2_CASC2, to_computeCore4_A2_CASC2);
        meshA_write_to_computecore(computeCore4_A2_CASC3, to_computeCore4_A2_CASC3);
        meshA_write_to_computecore(computeCore4_A3_CASC0, to_computeCore4_A3_CASC0);
        meshA_write_to_computecore(computeCore4_A3_CASC1, to_computeCore4_A3_CASC1);
        meshA_write_to_computecore(computeCore4_A3_CASC2, to_computeCore4_A3_CASC2);
        meshA_write_to_computecore(computeCore4_A3_CASC3, to_computeCore4_A3_CASC3);
      }
      if (uOP.memcoreA2_to_computecore5 || uOP.memcoreC2_to_computecore5 ||
          uOP.memcoreC3_to_computecore5) {

        meshA_write_to_computecore(computeCore5_A0_CASC0, to_computeCore5_A0_CASC0);
        meshA_write_to_computecore(computeCore5_A0_CASC1, to_computeCore5_A0_CASC1);
        meshA_write_to_computecore(computeCore5_A0_CASC2, to_computeCore5_A0_CASC2);
        meshA_write_to_computecore(computeCore5_A0_CASC3, to_computeCore5_A0_CASC3);
        meshA_write_to_computecore(computeCore5_A1_CASC0, to_computeCore5_A1_CASC0);
        meshA_write_to_computecore(computeCore5_A1_CASC1, to_computeCore5_A1_CASC1);
        meshA_write_to_computecore(computeCore5_A1_CASC2, to_computeCore5_A1_CASC2);
        meshA_write_to_computecore(computeCore5_A1_CASC3, to_computeCore5_A1_CASC3);
        meshA_write_to_computecore(computeCore5_A2_CASC0, to_computeCore5_A2_CASC0);
        meshA_write_to_computecore(computeCore5_A2_CASC1, to_computeCore5_A2_CASC1);
        meshA_write_to_computecore(computeCore5_A2_CASC2, to_computeCore5_A2_CASC2);
        meshA_write_to_computecore(computeCore5_A2_CASC3, to_computeCore5_A2_CASC3);
        meshA_write_to_computecore(computeCore5_A3_CASC0, to_computeCore5_A3_CASC0);
        meshA_write_to_computecore(computeCore5_A3_CASC1, to_computeCore5_A3_CASC1);
        meshA_write_to_computecore(computeCore5_A3_CASC2, to_computeCore5_A3_CASC2);
        meshA_write_to_computecore(computeCore5_A3_CASC3, to_computeCore5_A3_CASC3);
      }
    }
  }

}
