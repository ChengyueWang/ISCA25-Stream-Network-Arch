#include "ddr.h"

void ddr(hls::stream<uop_ddr_type> &stream_uOP_ddr, ap_uint<512> *ddr_port0,
         ap_uint<512> *ddr_port1,

         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreA0,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreA1,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreA2,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreB0,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreB1,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreB2,

         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreC0,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreC1,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreC2,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreC3,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreC4,
         hls::stream<ap_uint<1024>> &stream_from_dramA_to_memCoreC5,

         hls::stream<ap_uint<1024>> &stream_to_dramC_from_memCore0,
         hls::stream<ap_uint<1024>> &stream_to_dramC_from_memCore1,
         hls::stream<ap_uint<1024>> &stream_to_dramC_from_memCore2,
         hls::stream<ap_uint<1024>> &stream_to_dramC_from_memCore3,
         hls::stream<ap_uint<1024>> &stream_to_dramC_from_memCore4,
         hls::stream<ap_uint<1024>> &stream_to_dramC_from_memCore5
#ifdef SW_EMU_PRINT
         ,
         hls::stream<bool> &return_stream
#endif
) {

#ifdef SW_EMU_PRINT
  std::ofstream outFile(
      "/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/ddr.txt",
      std::ios_base::app);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file for writing." << std::endl;
  }
#endif

  uop_ddr_type uOP;
  bool is_last_uOP = false;
WHILE_LOOP:
  while (is_last_uOP == false) {
    uOP = stream_uOP_ddr.read();
    is_last_uOP = uOP.is_last_uOP;

#ifdef SW_EMU_PRINT
    outFile << "uOP.is_load = " << uOP.is_load << " uOP.is_store = " << uOP.is_store
            << " uOP.start_address = " << uOP.start_address
            << " uOP.chunck_size = " << uOP.chunck_size << std::endl;
#endif

    if (uOP.is_load == true) {
      for (uint32_t e = 0; e < uOP.chunck_size / 16; e = e + 128) {
        for (uint16_t s = 0; s < 64; s++) {
#pragma HLS pipeline II = 1
          ap_uint<1024> temp;

          // 64 512b AXI read is 4KB, each port reads 4KB stride data alternatively
          // port 0 reads element 0, 1, 2, ... 63
          // port 1 reads element 64, 65, 66, ... 127

          temp(511, 0) = ddr_port0[uOP.start_address + e + s];
          temp(1023, 512) = ddr_port1[uOP.start_address + e + s + 64];

          if (uOP.load_to_memcoreA0 == true) {
            stream_from_dramA_to_memCoreA0.write(temp);
          } else if (uOP.load_to_memcoreA1 == true) {
            stream_from_dramA_to_memCoreA1.write(temp);
          } else if (uOP.load_to_memcoreA2 == true) {
            stream_from_dramA_to_memCoreA2.write(temp);
          } else if (uOP.load_to_memcoreB0 == true) {
            stream_from_dramA_to_memCoreB0.write(temp);
          } else if (uOP.load_to_memcoreB1 == true) {
            stream_from_dramA_to_memCoreB1.write(temp);
          } else if (uOP.load_to_memcoreB2 == true) {
            stream_from_dramA_to_memCoreB2.write(temp);
          }

#ifdef SW_EMU_PRINT
          for (int word = 0; word < 32; word++) {  // outFile
            UNION_FP_UINT32 temp_union;
            temp_union.uint32_val = temp(word * 32 + 31, word * 32);  // outFile
            outFile << temp_union.float_val << " ";
          }
          outFile << std::endl;
#endif
        }
      }
    } else if (uOP.is_store == true) {
      for (uint32_t e = 0; e < uOP.chunck_size / 16; e = e + 128) {
        for (uint16_t s = 0; s < 64; s++) {
#pragma HLS pipeline II = 1
          ap_uint<1024> temp;

          if (uOP.store_from_memcoreC0 == true) {
            temp = stream_to_dramC_from_memCore0.read();
          } else if (uOP.store_from_memcoreC1 == true) {
            temp = stream_to_dramC_from_memCore1.read();
          } else if (uOP.store_from_memcoreC2 == true) {
            temp = stream_to_dramC_from_memCore2.read();
          } else if (uOP.store_from_memcoreC3 == true) {
            temp = stream_to_dramC_from_memCore3.read();
          } else if (uOP.store_from_memcoreC4 == true) {
            temp = stream_to_dramC_from_memCore4.read();
          } else if (uOP.store_from_memcoreC5 == true) {
            temp = stream_to_dramC_from_memCore5.read();
          }

          ddr_port0[uOP.start_address + e + s] = temp(511, 0);
          ddr_port1[uOP.start_address + e + s + 64] = temp(1023, 512);

#ifdef SW_EMU_PRINT
          for (int word = 0; word < 32; word++) {  // outFile
            UNION_FP_UINT32 temp_union;
            temp_union.uint32_val = temp(word * 32 + 31, word * 32);  // outFile
            outFile << temp_union.float_val << " ";
          }
          outFile << std::endl;
#endif
        }
      }
    }
  }

#ifdef SW_EMU_PRINT
  return_stream.write(true);
#endif

#ifdef SW_EMU_PRINT
  outFile << "EXIT ddr  ==========================   ";
  outFile.close();
#endif
}