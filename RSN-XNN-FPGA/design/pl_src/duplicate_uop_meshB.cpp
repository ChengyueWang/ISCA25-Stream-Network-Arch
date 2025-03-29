#pragma once
#include "duplicate_uop_meshB.h"

void duplicate_uop_meshB(hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB,
                         hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB_split_casc0,
                         hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB_split_casc1,
                         hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB_split_casc2,
                         hls::stream<uop_mesh_sendB_type> &stream_uOP_mesh_sendB_split_casc3) {
  uop_mesh_sendB_type temp = stream_uOP_mesh_sendB.read();
  stream_uOP_mesh_sendB_split_casc0.write(temp);
  stream_uOP_mesh_sendB_split_casc1.write(temp);
  stream_uOP_mesh_sendB_split_casc2.write(temp);
  stream_uOP_mesh_sendB_split_casc3.write(temp);
}
