#include "loadB_from_dram.h"

void loadB_from_dram(hls::stream<uop_loadB_dram_type>& stream_uOP_loadB_dram,
                     ap_uint<512>* inB_port0, ap_uint<512>* inB_port1,
                     hls::stream<ap_uint<1024>>& stream_from_dramB_to_memCoreB0,
                     hls::stream<ap_uint<1024>>& stream_from_dramB_to_memCoreB1) {

  uop_loadB_dram_type uOP;
  bool is_last_uOP = false;
WHILE_LOOP:
  while (is_last_uOP == false) {
    uOP = stream_uOP_loadB_dram.read();
    is_last_uOP = uOP.is_last_uOP;


    if (uOP.is_loading_bias == true) {
    LOOP_BIAS:
      for (ap_uint<10> e = 0; e < uOP.chunck_size / 16; e = e + 1) {  // max e is 4096/16 -1  = 255
#pragma HLS pipeline II = 4
        ap_uint<1024> temp;
        temp(511, 0) = inB_port0[uOP.start_address + e];
        if (uOP.load_to_memcoreB0 == true) {
          stream_from_dramB_to_memCoreB0.write(temp);
        } else {
          stream_from_dramB_to_memCoreB1.write(temp);
        }

      }
    } else {
      for (uint32_t e = 0; e < uOP.chunck_size / 16; e = e + 128) {
        for (uint16_t s = 0; s < 64; s++) {
#pragma HLS pipeline II = 1
          ap_uint<1024> temp;
          temp(511, 0) = inB_port0[uOP.start_address + e + s];
          temp(1023, 512) = inB_port1[uOP.start_address + e + s + 64];

          if (uOP.load_to_memcoreB0 == true) {
            stream_from_dramB_to_memCoreB0.write(temp);
          } else if (uOP.load_to_memcoreB1 == true) {
            stream_from_dramB_to_memCoreB1.write(temp);
          }

        }
      }
    }
  }

};
