#pragma once
#include "common.h"

void loadB_from_dram(hls::stream<uop_loadB_dram_type>& stream_uOP_loadB_dram,
                     ap_uint<512>* inB_port0, ap_uint<512>* inB_port1,
                     hls::stream<ap_uint<1024>>& stream_from_dramB_to_memCoreB0,
                     hls::stream<ap_uint<1024>>& stream_from_dramB_to_memCoreB1);