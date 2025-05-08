#pragma once
#include "common.h"

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

);
