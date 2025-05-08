#pragma once
#include <ap_axi_sdata.h>
#include <ap_int.h>
#include <hls_stream.h>
#include <hls_task.h>
#include <stdint.h>
#include <stdio.h>

#include <bitset>
#include <fstream> 
#include <iomanip>
#include <iostream>
#include <vector>

#include "hls_math.h"



#define OPCODE_NULL 0
#define OPCODE_DDR_DRAM 1
#define OPCODE_LOADB_DRAM 2
#define OPCODE_MEMCORE_A 3
#define OPCODE_MEMCORE_B 4
#define OPCODE_MEMCORE_C 5
#define OPCODE_MESH_SEND_A 6
#define OPCODE_MESH_SEND_B 7

#define LEN_OPCODE 4
#define LEN_MASK 6
#define LEN_IS_LAST_MOP 1
#define LEN_MOP_BUFFER_WINDOW_SIZE 5
#define LEN_REPEAT_NUM 16
#define LEN_HEADER \
  (LEN_OPCODE + LEN_MASK + LEN_IS_LAST_MOP + LEN_MOP_BUFFER_WINDOW_SIZE + LEN_REPEAT_NUM)

#define CNT4B_HEADER 1
#define CNT4B_DDR 4
#define CNT4B_LOAD_B_DRAM 4
#define CNT4B_MEMCORE_A 1
#define CNT4B_MEMCORE_B 2
#define CNT4B_MEMCORE_C 2
#define CNT4B_MESH_A 2
#define CNT4B_MESH_B 2

// 1 32-bit
struct INST_HEADER_TYPE {
  uint32_t opcode : LEN_OPCODE;                                  // 4 bits for opcode
  uint32_t mask : LEN_MASK;                                      // 6 bits for mask
  uint32_t is_last_mOP : LEN_IS_LAST_MOP;                        // 1 bit for is_last_mOP
  uint32_t mop_buffer_window_size : LEN_MOP_BUFFER_WINDOW_SIZE;  // 5 bits for window size
  uint32_t repeat_num : LEN_REPEAT_NUM;                          // 16 bits for repeat_num
};

struct INST_DDR_TYPE {
  uint32_t start_address;
  uint32_t chunck_size;          // the size of data that is accessed contiguously
  uint32_t address_offset : 23;  // address offset for loop at the level of repeat_num
  uint32_t chunk_count : 4;      // the number of chunks of data
  uint32_t is_store : 1;
  uint32_t is_load : 1;
  uint32_t load_to_memcoreA0 : 1;
  uint32_t load_to_memcoreA1 : 1;
  uint32_t load_to_memcoreA2 : 1;

  uint32_t stride_offset : 23;  // the gap between the start of two chunk of data
  uint32_t load_to_memcoreB0 : 1;
  uint32_t load_to_memcoreB1 : 1;
  uint32_t load_to_memcoreB2 : 1;
  uint32_t store_from_memcoreC0 : 1;
  uint32_t store_from_memcoreC1 : 1;
  uint32_t store_from_memcoreC2 : 1;
  uint32_t store_from_memcoreC3 : 1;
  uint32_t store_from_memcoreC4 : 1;
  uint32_t store_from_memcoreC5 : 1;

};


// 4 32-bit
struct INST_LOAD_B_DRAM_TYPE {
  uint32_t start_address;
  uint32_t chunck_size;         // the size of data that is accessed contiguously
  uint32_t address_offset;      // address offset for loop at the level of repeat_num
  uint32_t stride_offset : 25;  // the gap between the start of two chunk of data
  uint32_t chunk_count : 4;     // the number of chunks of data
  uint32_t load_to_memcoreB0 : 1;
  uint32_t load_to_memcoreB1 : 1;
  uint32_t is_loading_bias : 1;
};

// 1 32-bit  => 25 bits
struct INST_MEMCORE_A_TYPE {
  // first 32-bit
  uint32_t one_mem_tile_dim1 : 9;      // max 256
  uint32_t one_mem_tile_dim2 : 8;      // max 128
  uint32_t compute_tile_access_A : 3;  // max 4
  uint32_t compute_tile_access_B : 3;  // max 4
  uint32_t enable_load_from_dram : 1;
  uint32_t enable_send_to_aie : 1;
  uint32_t zero_padding : 7;
};

// 2 32-bit => 33 bits
struct INST_MEMCORE_B_TYPE {
  // first 32-bit
  uint32_t one_mem_tile_dim1 : 10;     // max 512
  uint32_t one_mem_tile_dim2 : 10;     // max 512
  uint32_t compute_tile_access_A : 3;  // max 4
  uint32_t compute_tile_access_B : 3;  // max 4
  uint32_t compute_tile_access_K : 3;  // max 4
  uint32_t enable_load_from_dram : 1;
  uint32_t enable_send_to_aie : 1;
  uint32_t enable_transpose : 1;

  // second 32-bit
  uint32_t is_loading_bias : 1;
  uint32_t zero_padding : 31;

};

// 2 32-bit => 59 bits
struct INST_MEMCORE_C_TYPE {
  // first 32-bit
  uint32_t one_mem_tile_dim1 : 9;           // max 256
  uint32_t one_mem_tile_dim2 : 10;          // max 512
  uint32_t compute_tile_recv_access_A : 3;  // max 4
  uint32_t compute_tile_recv_access_B : 3;  // max 4
  uint32_t compute_tile_recv_access_K : 3;  // max 4
  uint32_t compute_tile_send_access_A : 3;  // max 4
  uint32_t enable_store_to_dram : 1;
  // second 32-bit
  uint32_t k_iter : 16;
  uint32_t compute_tile_send_access_B : 3;  // max 4
  uint32_t compute_tile_send_access_K : 3;  // max 4
  uint32_t enable_send_to_aie : 1;
  uint32_t enable_recv_from_aie : 1;
  uint32_t enable_softmax : 1;
  uint32_t enable_gelu : 1;
  uint32_t enable_layer_norm : 1;
  uint32_t zero_padding : 5;

};

// 2 32-bit
struct INST_MESH_A_TYPE {
  uint32_t size;
  uint32_t memcoreA0_to_computecore0 : 1;
  uint32_t memcoreA0_to_computecore1 : 1;
  uint32_t memcoreA1_to_computecore2 : 1;
  uint32_t memcoreA1_to_computecore3 : 1;
  uint32_t memcoreA2_to_computecore4 : 1;
  uint32_t memcoreA2_to_computecore5 : 1;
  uint32_t memcoreC0_to_computecore4 : 1;
  uint32_t memcoreC1_to_computecore4 : 1;
  uint32_t memcoreC2_to_computecore5 : 1;
  uint32_t memcoreC3_to_computecore5 : 1;
  uint32_t zero_padding : 22;
};

// 2 32-bit
struct INST_MESH_B_TYPE {
  uint32_t size;
  uint32_t memcore0_to_computecore0 : 1;
  uint32_t memcore0_to_computecore2 : 1;
  uint32_t memcore0_to_computecore4 : 1;
  uint32_t memcore1_to_computecore1 : 1;
  uint32_t memcore1_to_computecore3 : 1;
  uint32_t memcore1_to_computecore5 : 1;
  uint32_t memcore2_to_computecore4 : 1;
  uint32_t memcore2_to_computecore5 : 1;
  uint32_t zero_padding : 24;
};

typedef union {
  INST_HEADER_TYPE inst_val;
  uint32_t raw_32b;
} union_inst_header;

typedef union {
  INST_DDR_TYPE inst_val;
  uint32_t raw_32b[CNT4B_DDR];
} union_inst_ddr;

typedef union {
  INST_LOAD_B_DRAM_TYPE inst_val;
  uint32_t raw_32b[CNT4B_LOAD_B_DRAM];
} union_inst_load_B_dram;

typedef union {
  INST_MEMCORE_A_TYPE inst_val;
  uint32_t raw_32b[CNT4B_MEMCORE_A];
} union_inst_memcore_A;

typedef union {
  INST_MEMCORE_B_TYPE inst_val;
  uint32_t raw_32b[CNT4B_MEMCORE_B];
} union_inst_memcore_B;

typedef union {
  INST_MEMCORE_C_TYPE inst_val;
  uint32_t raw_32b[CNT4B_MEMCORE_C];
} union_inst_memcore_C;

typedef union {
  INST_MESH_A_TYPE inst_val;
  uint32_t raw_32b[CNT4B_MESH_A];
} union_inst_mesh_A;

typedef union {
  INST_MESH_B_TYPE inst_val;
  uint32_t raw_32b[CNT4B_MESH_B];
} union_inst_mesh_B;

typedef struct {
  float v[4];
} floatv4;

typedef union {
  float float_val;
  uint32_t uint32_val;
} UNION_FP_UINT32;

#define DRAM_TILE_DIM1 256
#define DRAM_TILE_DIM2 64

#define BUFA_DIM1 256
#define BUFA_DIM2 128

#define BUFB_DIM1 128
#define BUFB_DIM2 512

#define BUFC_DIM1 256
#define BUFC_DIM2 512

#define BUFBCORE2_DIM1 512
#define BUFBCORE2_DIM2 64

struct uop_ddr_type {
  uint32_t start_address;
  uint32_t chunck_size;

  bool is_store;
  bool is_load;

  bool load_to_memcoreA0;
  bool load_to_memcoreA1;
  bool load_to_memcoreA2;
  bool load_to_memcoreB0;
  bool load_to_memcoreB1;
  bool load_to_memcoreB2;

  bool load_to_memcoreC0;
  bool load_to_memcoreC1;
  bool load_to_memcoreC2;
  bool load_to_memcoreC3;
  bool load_to_memcoreC4;
  bool load_to_memcoreC5;

  bool store_from_memcoreC0;
  bool store_from_memcoreC1;
  bool store_from_memcoreC2;
  bool store_from_memcoreC3;
  bool store_from_memcoreC4;
  bool store_from_memcoreC5;

  bool is_last_uOP;  // if true, then this is the last uop
};

struct uop_loadB_dram_type {
  uint32_t start_address;
  uint32_t chunck_size;
  bool load_to_memcoreB0;
  bool load_to_memcoreB1;
  bool is_loading_bias;
  bool is_last_uOP;  // if true, then this is the last uop
};

struct uop_memcore_A_type {
  ap_uint<9> one_mem_tile_dim1;  // max 256
  ap_uint<8> one_mem_tile_dim2;  // max 128

  ap_uint<3> compute_tile_access_A;  // max 4
  ap_uint<3> compute_tile_access_B;  // max 4

  bool enable_load_from_dram;
  bool enable_send_to_aie;
  bool is_last_uOP;  // if true, then this is the last uop

};

struct uop_memcore_B_type {
  ap_uint<10> one_mem_tile_dim1;  // max 512
  ap_uint<10> one_mem_tile_dim2;  // max 512

  ap_uint<3> compute_tile_access_A;  // max 4
  ap_uint<3> compute_tile_access_B;  // max 4
  ap_uint<3> compute_tile_access_K;  // max 4

  bool enable_load_from_dram;
  bool enable_send_to_aie;
  bool enable_transpose;
  bool is_loading_bias;  // 1 load from ddr, 0 load from lpddr
  bool is_last_uOP;      // if true, then this is the last uop

};

struct uop_mesh_sendB_type {
  uint32_t size;
  bool memcore0_to_computecore0;
  bool memcore0_to_computecore2;
  bool memcore0_to_computecore4;
  bool memcore1_to_computecore1;
  bool memcore1_to_computecore3;
  bool memcore1_to_computecore5;
  bool memcore2_to_computecore4;
  bool memcore2_to_computecore5;
  bool is_last_uOP;
};

struct uop_mesh_sendA_type {
  uint32_t size;
  bool memcoreA0_to_computecore0;
  bool memcoreA0_to_computecore1;
  bool memcoreA1_to_computecore2;
  bool memcoreA1_to_computecore3;
  bool memcoreA2_to_computecore4;
  bool memcoreA2_to_computecore5;
  bool memcoreC0_to_computecore4;
  bool memcoreC1_to_computecore4;
  bool memcoreC2_to_computecore5;
  bool memcoreC3_to_computecore5;
  bool is_last_uOP;
};

struct uop_memcore_C_type {
  ap_uint<9> one_mem_tile_dim1;           // max 256
  ap_uint<10> one_mem_tile_dim2;          // max 512
  ap_uint<3> compute_tile_recv_access_A;  // max 4
  ap_uint<3> compute_tile_recv_access_B;  // max 4
  ap_uint<3> compute_tile_recv_access_K;  // max 4
  ap_uint<3> compute_tile_send_access_A;  // max 4
  bool enable_store_to_dram;
  // second 32-bit
  ap_uint<16> k_iter;
  ap_uint<3> compute_tile_send_access_B;  // max 4
  ap_uint<3> compute_tile_send_access_K;  // max 4
  bool enable_send_to_aie;
  bool enable_recv_from_aie;
  bool enable_softmax;
  bool enable_gelu;
  bool enable_layer_norm;
  bool is_last_uOP;  // if true, then this is the last uop

};

struct mop_ddr_type {
  uint32_t start_address;
  uint32_t address_offset;    // address offset for loop at the level of repeat_num
  uint32_t chunck_size;       // the size of data that is accessed contiguously
  uint32_t stride_offset;     // the gap between the start of two chunk of data
  uint32_t chunk_count : 16;  // the number of chunks of data

  uint32_t is_store : 1;
  uint32_t is_load : 1;

  uint32_t load_to_memcoreA0 : 1;
  uint32_t load_to_memcoreA1 : 1;
  uint32_t load_to_memcoreA2 : 1;
  uint32_t load_to_memcoreB0 : 1;
  uint32_t load_to_memcoreB1 : 1;
  uint32_t load_to_memcoreB2 : 1;
  uint32_t load_to_memcoreC0 : 1;
  uint32_t load_to_memcoreC1 : 1;
  uint32_t load_to_memcoreC2 : 1;
  uint32_t load_to_memcoreC3 : 1;
  uint32_t load_to_memcoreC4 : 1;
  uint32_t load_to_memcoreC5 : 1;

  uint32_t store_from_memcoreC0 : 1;
  uint32_t store_from_memcoreC1 : 1;
  uint32_t store_from_memcoreC2 : 1;
  uint32_t store_from_memcoreC3 : 1;
  uint32_t store_from_memcoreC4 : 1;
  uint32_t store_from_memcoreC5 : 1;

  uint32_t zero_padding : 3;
  uint32_t is_last_mOP : 1;
  uint32_t mop_buffer_window_size : 8;
  uint32_t repeat_num : 16;
};

struct mop_loadB_dram_type {
  uint32_t start_address;
  uint32_t address_offset;    // address offset for loop at the level of repeat_num
  uint32_t chunck_size;       // the size of data that is accessed contiguously
  uint32_t stride_offset;     // the gap between the start of two chunk of data
  uint32_t chunk_count : 16;  // the number of chunks of data
  uint32_t load_to_memcoreB0 : 1;
  uint32_t load_to_memcoreB1 : 1;
  uint32_t is_loading_bias : 1;
  uint32_t zero_padding : 12;
  uint32_t is_last_mOP : 1;
  uint32_t mop_buffer_window_size : 16;
  uint32_t repeat_num : 16;
};

#define MOP_CNT4B_DDR 6
#define MOP_CNT4B_LOAD_B_DRAM 6

typedef union {
  mop_ddr_type val;
  uint32_t raw_32b[MOP_CNT4B_DDR];
} union_mop_ddr_dram;

typedef union {
  mop_loadB_dram_type val;
  uint32_t raw_32b[MOP_CNT4B_LOAD_B_DRAM];
} union_mop_load_B_dram;

struct mop_memcore_A_type {
  uint32_t one_mem_tile_dim1 : 9;      // max 256
  uint32_t one_mem_tile_dim2 : 8;      // max 128
  uint32_t compute_tile_access_A : 3;  // max 4
  uint32_t compute_tile_access_B : 3;  // max 4
  uint32_t enable_load_from_dram : 1;
  uint32_t enable_send_to_aie : 1;
  uint32_t zero_padding : 7;

  uint16_t repeat_num;
  bool is_last_mOP;
};

struct mop_memcore_B_type {
  uint32_t one_mem_tile_dim1 : 10;     // max 512
  uint32_t one_mem_tile_dim2 : 10;     // max 512
  uint32_t compute_tile_access_A : 3;  // max 4
  uint32_t compute_tile_access_B : 3;  // max 4
  uint32_t compute_tile_access_K : 3;  // max 4
  uint32_t enable_load_from_dram : 1;
  uint32_t enable_send_to_aie : 1;
  uint32_t enable_transpose : 1;

  // second 32-bit
  uint32_t is_loading_bias : 1;

  uint16_t repeat_num;
  bool is_last_mOP;
};

struct mop_memcore_C_type {
  uint32_t one_mem_tile_dim1 : 9;           // max 256
  uint32_t one_mem_tile_dim2 : 10;          // max 512
  uint32_t compute_tile_recv_access_A : 3;  // max 4
  uint32_t compute_tile_recv_access_B : 3;  // max 4
  uint32_t compute_tile_recv_access_K : 3;  // max 4
  uint32_t compute_tile_send_access_A : 3;  // max 4
  uint32_t enable_store_to_dram : 1;
  // second 32-bit
  uint32_t k_iter : 16;
  uint32_t compute_tile_send_access_B : 3;  // max 4
  uint32_t compute_tile_send_access_K : 3;  // max 4
  uint32_t enable_send_to_aie : 1;
  uint32_t enable_recv_from_aie : 1;
  uint32_t enable_softmax : 1;
  uint32_t enable_gelu : 1;
  uint32_t enable_layer_norm : 1;
  uint32_t zero_padding : 5;

  uint16_t repeat_num;
  bool is_last_mOP;
};

struct mop_mesh_sendA_type {
  uint32_t repeat_num : 16;
  uint32_t mop_buffer_window_size : 8;
  uint32_t is_last_mOP : 1;
  uint32_t memcoreA0_to_computecore0 : 1;
  uint32_t memcoreA0_to_computecore1 : 1;
  uint32_t memcoreA1_to_computecore2 : 1;
  uint32_t memcoreA1_to_computecore3 : 1;
  uint32_t memcoreA2_to_computecore4 : 1;
  uint32_t memcoreA2_to_computecore5 : 1;
  uint32_t memcoreC0_to_computecore4 : 1;
  uint32_t memcoreC1_to_computecore4 : 1;
  uint32_t memcoreC2_to_computecore5 : 1;
  uint32_t memcoreC3_to_computecore5 : 1;
  uint32_t size : 29;
};

struct mop_mesh_sendB_type {
  uint32_t size : 32;
  uint32_t repeat_num : 15;
  uint32_t mop_buffer_window_size : 8;
  uint32_t is_last_mOP : 1;
  uint32_t memcore0_to_computecore0 : 1;
  uint32_t memcore0_to_computecore2 : 1;
  uint32_t memcore0_to_computecore4 : 1;
  uint32_t memcore1_to_computecore1 : 1;
  uint32_t memcore1_to_computecore3 : 1;
  uint32_t memcore1_to_computecore5 : 1;
  uint32_t memcore2_to_computecore4 : 1;
  uint32_t memcore2_to_computecore5 : 1;
};

#define MOP_CNT4B_MESHA 2
#define MOP_CNT4B_MESHB 2

typedef union {
  mop_mesh_sendA_type val;
  uint32_t raw_32b[MOP_CNT4B_MESHA];
} union_mop_meshA;

typedef union {
  mop_mesh_sendB_type val;
  uint32_t raw_32b[MOP_CNT4B_MESHB];
} union_mop_meshB;
