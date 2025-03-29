#pragma once
#include "mesh_sendB_split.h"

void meshB_write_to_computecore_split(ap_uint<64> from_memCore,
                                      hls::stream<ap_axiu<64, 0, 0, 0>> &to_axi) {
  ap_axiu<64, 0, 0, 0> axi_data;
  axi_data.data = from_memCore;
  axi_data.keep = 0xFF;
  to_axi.write(axi_data);
}

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

) {
#ifdef SW_EMU_PRINT
  std::ofstream outFile(
      "/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/mesh_sendB_split" +
          std::to_string(core_id) + ".txt",
      std::ios_base::app);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file for writing." << std::endl;
  }
#endif
  uop_mesh_sendB_type uOP;
  bool is_last_uOP = false;

WHILE_LOOP:
  while (is_last_uOP == false) {
    uOP = stream_uOP_mesh_sendB.read();
    is_last_uOP = uOP.is_last_uOP;

  FOR_UOPSIZE:
    for (ap_int<32> i = 0; i < uOP.size; i++) {
#ifdef SW_EMU_PRINT
      outFile << "i: " << i << std::endl;
#endif
#pragma HLS PIPELINE II = 1
      ap_uint<64> memCore0_B0_CASC0;
      ap_uint<64> memCore0_B1_CASC0;
      ap_uint<64> memCore0_B2_CASC0;
      ap_uint<64> memCore0_B3_CASC0;
      ap_uint<64> memCore1_B0_CASC0;
      ap_uint<64> memCore1_B1_CASC0;
      ap_uint<64> memCore1_B2_CASC0;
      ap_uint<64> memCore1_B3_CASC0;
      ap_uint<64> memCore2_B0_CASC0;
      ap_uint<64> memCore2_B1_CASC0;
      ap_uint<64> memCore2_B2_CASC0;
      ap_uint<64> memCore2_B3_CASC0;

      ap_uint<64> computeCore0_B0_CASC0;
      ap_uint<64> computeCore0_B1_CASC0;
      ap_uint<64> computeCore0_B2_CASC0;
      ap_uint<64> computeCore0_B3_CASC0;
      ap_uint<64> computeCore1_B0_CASC0;
      ap_uint<64> computeCore1_B1_CASC0;
      ap_uint<64> computeCore1_B2_CASC0;
      ap_uint<64> computeCore1_B3_CASC0;
      ap_uint<64> computeCore2_B0_CASC0;
      ap_uint<64> computeCore2_B1_CASC0;
      ap_uint<64> computeCore2_B2_CASC0;
      ap_uint<64> computeCore2_B3_CASC0;
      ap_uint<64> computeCore3_B0_CASC0;
      ap_uint<64> computeCore3_B1_CASC0;
      ap_uint<64> computeCore3_B2_CASC0;
      ap_uint<64> computeCore3_B3_CASC0;
      ap_uint<64> computeCore4_B0_CASC0;
      ap_uint<64> computeCore4_B1_CASC0;
      ap_uint<64> computeCore4_B2_CASC0;
      ap_uint<64> computeCore4_B3_CASC0;
      ap_uint<64> computeCore5_B0_CASC0;
      ap_uint<64> computeCore5_B1_CASC0;
      ap_uint<64> computeCore5_B2_CASC0;
      ap_uint<64> computeCore5_B3_CASC0;

      if (uOP.memcore0_to_computecore0 || uOP.memcore0_to_computecore2 ||
          uOP.memcore0_to_computecore4) {
        memCore0_B0_CASC0 = from_memCore0_to_mesh_B0_CASC0.read();
        memCore0_B1_CASC0 = from_memCore0_to_mesh_B1_CASC0.read();
        memCore0_B2_CASC0 = from_memCore0_to_mesh_B2_CASC0.read();
        memCore0_B3_CASC0 = from_memCore0_to_mesh_B3_CASC0.read();
      }

      if (uOP.memcore1_to_computecore1 || uOP.memcore1_to_computecore3 ||
          uOP.memcore1_to_computecore5) {
        memCore1_B0_CASC0 = from_memCore1_to_mesh_B0_CASC0.read();
        memCore1_B1_CASC0 = from_memCore1_to_mesh_B1_CASC0.read();
        memCore1_B2_CASC0 = from_memCore1_to_mesh_B2_CASC0.read();
        memCore1_B3_CASC0 = from_memCore1_to_mesh_B3_CASC0.read();
      }

      if (uOP.memcore2_to_computecore4 || uOP.memcore2_to_computecore5) {
        memCore2_B0_CASC0 = from_memCore2_to_mesh_B0_CASC0.read();
        memCore2_B1_CASC0 = from_memCore2_to_mesh_B1_CASC0.read();
        memCore2_B2_CASC0 = from_memCore2_to_mesh_B2_CASC0.read();
        memCore2_B3_CASC0 = from_memCore2_to_mesh_B3_CASC0.read();
      }

      computeCore0_B0_CASC0 = memCore0_B0_CASC0;
      computeCore0_B1_CASC0 = memCore0_B1_CASC0;
      computeCore0_B2_CASC0 = memCore0_B2_CASC0;
      computeCore0_B3_CASC0 = memCore0_B3_CASC0;

      computeCore1_B0_CASC0 = memCore1_B0_CASC0;
      computeCore1_B1_CASC0 = memCore1_B1_CASC0;
      computeCore1_B2_CASC0 = memCore1_B2_CASC0;
      computeCore1_B3_CASC0 = memCore1_B3_CASC0;

      computeCore2_B0_CASC0 = memCore0_B0_CASC0;
      computeCore2_B1_CASC0 = memCore0_B1_CASC0;
      computeCore2_B2_CASC0 = memCore0_B2_CASC0;
      computeCore2_B3_CASC0 = memCore0_B3_CASC0;

      computeCore3_B0_CASC0 = memCore1_B0_CASC0;
      computeCore3_B1_CASC0 = memCore1_B1_CASC0;
      computeCore3_B2_CASC0 = memCore1_B2_CASC0;
      computeCore3_B3_CASC0 = memCore1_B3_CASC0;

      if (uOP.memcore0_to_computecore4 == 1) {
        computeCore4_B0_CASC0 = memCore0_B0_CASC0;
        computeCore4_B1_CASC0 = memCore0_B1_CASC0;
        computeCore4_B2_CASC0 = memCore0_B2_CASC0;
        computeCore4_B3_CASC0 = memCore0_B3_CASC0;
      } else {  // memcore2_to_computecore4 == 0 or memcore2_to_computecore4 == 1
        computeCore4_B0_CASC0 = memCore2_B0_CASC0;
        computeCore4_B1_CASC0 = memCore2_B1_CASC0;
        computeCore4_B2_CASC0 = memCore2_B2_CASC0;
        computeCore4_B3_CASC0 = memCore2_B3_CASC0;
      }

      if (uOP.memcore1_to_computecore5 == 1) {
        computeCore5_B0_CASC0 = memCore1_B0_CASC0;
        computeCore5_B1_CASC0 = memCore1_B1_CASC0;
        computeCore5_B2_CASC0 = memCore1_B2_CASC0;
        computeCore5_B3_CASC0 = memCore1_B3_CASC0;
      } else {  // memcore2_to_computecore5 == 0 or memcore2_to_computecore5 == 1
        computeCore5_B0_CASC0 = memCore2_B0_CASC0;
        computeCore5_B1_CASC0 = memCore2_B1_CASC0;
        computeCore5_B2_CASC0 = memCore2_B2_CASC0;
        computeCore5_B3_CASC0 = memCore2_B3_CASC0;
      }

      if (uOP.memcore0_to_computecore0) {
#ifdef SW_EMU_PRINT
        outFile << "core0 ";
        UNION_FP_UINT32 temp_union;
        temp_union.uint32_val = computeCore0_B0_CASC0(31, 0);
        outFile << temp_union.float_val << " ";
        temp_union.uint32_val = computeCore0_B0_CASC0(63, 32);
        outFile << temp_union.float_val << " ";

        temp_union.uint32_val = computeCore0_B1_CASC0(31, 0);
        outFile << temp_union.float_val << " ";
        temp_union.uint32_val = computeCore0_B1_CASC0(63, 32);
        outFile << temp_union.float_val << " ";

        temp_union.uint32_val = computeCore0_B2_CASC0(31, 0);
        outFile << temp_union.float_val << " ";
        temp_union.uint32_val = computeCore0_B2_CASC0(63, 32);
        outFile << temp_union.float_val << " ";

        temp_union.uint32_val = computeCore0_B3_CASC0(31, 0);
        outFile << temp_union.float_val << " ";
        temp_union.uint32_val = computeCore0_B3_CASC0(63, 32);
        outFile << temp_union.float_val << " ";

#endif

        meshB_write_to_computecore_split(computeCore0_B0_CASC0, to_computeCore0_B0_CASC0);
        meshB_write_to_computecore_split(computeCore0_B1_CASC0, to_computeCore0_B1_CASC0);
        meshB_write_to_computecore_split(computeCore0_B2_CASC0, to_computeCore0_B2_CASC0);
        meshB_write_to_computecore_split(computeCore0_B3_CASC0, to_computeCore0_B3_CASC0);
      }
      if (uOP.memcore1_to_computecore1) {
#ifdef SW_EMU_PRINT
        outFile << "core1 ";
        UNION_FP_UINT32 temp_union;
        temp_union.uint32_val = computeCore1_B0_CASC0(31, 0);
        outFile << temp_union.float_val << " ";
#endif

        meshB_write_to_computecore_split(computeCore1_B0_CASC0, to_computeCore1_B0_CASC0);
        meshB_write_to_computecore_split(computeCore1_B1_CASC0, to_computeCore1_B1_CASC0);
        meshB_write_to_computecore_split(computeCore1_B2_CASC0, to_computeCore1_B2_CASC0);
        meshB_write_to_computecore_split(computeCore1_B3_CASC0, to_computeCore1_B3_CASC0);
      }
      if (uOP.memcore0_to_computecore2) {
#ifdef SW_EMU_PRINT
        outFile << "core2 ";
        UNION_FP_UINT32 temp_union;
        temp_union.uint32_val = computeCore2_B0_CASC0(31, 0);
        outFile << temp_union.float_val << " ";
#endif

        meshB_write_to_computecore_split(computeCore2_B0_CASC0, to_computeCore2_B0_CASC0);
        meshB_write_to_computecore_split(computeCore2_B1_CASC0, to_computeCore2_B1_CASC0);
        meshB_write_to_computecore_split(computeCore2_B2_CASC0, to_computeCore2_B2_CASC0);
        meshB_write_to_computecore_split(computeCore2_B3_CASC0, to_computeCore2_B3_CASC0);
      }
      if (uOP.memcore1_to_computecore3) {
#ifdef SW_EMU_PRINT
        outFile << "core3 ";
        UNION_FP_UINT32 temp_union;
        temp_union.uint32_val = computeCore3_B0_CASC0(31, 0);
        outFile << temp_union.float_val << " ";
#endif

        meshB_write_to_computecore_split(computeCore3_B0_CASC0, to_computeCore3_B0_CASC0);
        meshB_write_to_computecore_split(computeCore3_B1_CASC0, to_computeCore3_B1_CASC0);
        meshB_write_to_computecore_split(computeCore3_B2_CASC0, to_computeCore3_B2_CASC0);
        meshB_write_to_computecore_split(computeCore3_B3_CASC0, to_computeCore3_B3_CASC0);
      }
      if (uOP.memcore0_to_computecore4 || uOP.memcore2_to_computecore4) {
#ifdef SW_EMU_PRINT
        outFile << "core4 ";
        UNION_FP_UINT32 temp_union;
        temp_union.uint32_val = computeCore4_B0_CASC0(31, 0);
        outFile << temp_union.float_val << " ";
#endif

        meshB_write_to_computecore_split(computeCore4_B0_CASC0, to_computeCore4_B0_CASC0);
        meshB_write_to_computecore_split(computeCore4_B1_CASC0, to_computeCore4_B1_CASC0);
        meshB_write_to_computecore_split(computeCore4_B2_CASC0, to_computeCore4_B2_CASC0);
        meshB_write_to_computecore_split(computeCore4_B3_CASC0, to_computeCore4_B3_CASC0);
      }
      if (uOP.memcore1_to_computecore5 || uOP.memcore2_to_computecore5) {
#ifdef SW_EMU_PRINT
        outFile << "core5 ";
        UNION_FP_UINT32 temp_union;
        temp_union.uint32_val = computeCore5_B0_CASC0(31, 0);
        outFile << temp_union.float_val << " ";
#endif

        meshB_write_to_computecore_split(computeCore5_B0_CASC0, to_computeCore5_B0_CASC0);
        meshB_write_to_computecore_split(computeCore5_B1_CASC0, to_computeCore5_B1_CASC0);
        meshB_write_to_computecore_split(computeCore5_B2_CASC0, to_computeCore5_B2_CASC0);
        meshB_write_to_computecore_split(computeCore5_B3_CASC0, to_computeCore5_B3_CASC0);
      }
    }
  }
#ifdef SW_EMU_PRINT
  outFile << "EXIT mesh_sendB   ==========================   ";
  outFile.close();
#endif
}
