#pragma once

#include "comm.h"


// header, payload, trailer
// header: 
// Total length
// Destination
// Flags These are various control flags.


// instructions = >  multiple kernels to 1 kernels SIMD control
// mop to patterns for 1 kernel  streaming pattern control
// uop to 1 kernel

//  ========================================================================
// bit[0:3]: opcode for the instruction type
#define OPCODE_NULL 0
#define OPCODE_DDR_DRAM 1
#define OPCODE_LOADB_DRAM 2
#define OPCODE_MEMCORE_A 3
#define OPCODE_MEMCORE_B 4
#define OPCODE_MEMCORE_C 5
#define OPCODE_MESH_SEND_A 6
#define OPCODE_MESH_SEND_B 7
// bit[4:9]: mask for enabling different instances of the same instruction type
//          if opcode == mop_memcore_A_type: 
//               000: memcoreA0 memcoreA1 memcoreA2
//          if opcode == mop_memcore_B_type:
//               000: memcoreB0 memcoreB1 memcoreB2
//          if opcode == mop_memcore_C_type:
//               000000: memcoreC0 memcoreC1 memcoreC2 memcoreC3 memcoreC4 memcoreC5
// bit[10:10]: is_last_mOP
// bit[11:15] mop_buffer_window_size
// bit[16:31]: repeat_num
//  ========================================================================
// header is 32 bits
// data is varying length according to opcode, and the number of data depends on LEN_MOP_BUFFER_WINDOW_SIZE


#define LEN_OPCODE 4
#define LEN_MASK 6
#define LEN_IS_LAST_MOP 1
#define LEN_MOP_BUFFER_WINDOW_SIZE 5
#define LEN_REPEAT_NUM 16
#define LEN_HEADER (LEN_OPCODE + LEN_MASK + LEN_IS_LAST_MOP + LEN_MOP_BUFFER_WINDOW_SIZE + LEN_REPEAT_NUM)

#define CNT4B_HEADER 1
#define CNT4B_DDR 6
#define CNT4B_LOAD_B_DRAM 5
#define CNT4B_MEMCORE_A 1
#define CNT4B_MEMCORE_B 2
#define CNT4B_MEMCORE_C 2
#define CNT4B_MESH_A 2
#define CNT4B_MESH_B 2




// 1 32-bit
struct INST_HEADER_TYPE{
    uint32_t opcode      : LEN_OPCODE;                  // 4 bits for opcode
    uint32_t mask        : LEN_MASK;                    // 6 bits for mask
    uint32_t is_last_mOP : LEN_IS_LAST_MOP;             // 1 bit for is_last_mOP
    uint32_t mop_buffer_window_size : LEN_MOP_BUFFER_WINDOW_SIZE;  // 5 bits for window size
    uint32_t repeat_num  : LEN_REPEAT_NUM;             // 16 bits for repeat_num
};

struct INST_DDR_TYPE{
    uint32_t start_address; 
    uint32_t address_offset; // address offset for loop at the level of repeat_num
    uint32_t chunck_size; // the size of data that is accessed contiguously
    uint32_t stride_offset; // the gap between the start of two chunk of data
    uint32_t chunk_count      :16; // the number of chunks of data
    uint32_t is_store: 1;
    uint32_t is_load: 1;
    uint32_t load_to_memcoreA0: 1;
    uint32_t load_to_memcoreA1: 1;
    uint32_t load_to_memcoreA2: 1;
    uint32_t load_to_memcoreB0: 1; 
    uint32_t load_to_memcoreB1: 1;
    uint32_t load_to_memcoreB2: 1;
    uint32_t load_to_memcoreC0: 1;
    uint32_t load_to_memcoreC1: 1;
    uint32_t load_to_memcoreC2: 1;
    uint32_t load_to_memcoreC3: 1;
    uint32_t load_to_memcoreC4: 1;
    uint32_t load_to_memcoreC5: 1;
    uint32_t store_from_memcoreC0 : 1; 
    uint32_t store_from_memcoreC1 : 1; 
    uint32_t store_from_memcoreC2 : 1; 
    uint32_t store_from_memcoreC3 : 1; 
    uint32_t store_from_memcoreC4 : 1; 
    uint32_t store_from_memcoreC5 : 1; 
    uint32_t zero_padding  : 28; 
};


// 5 32-bit
struct INST_LOAD_B_DRAM_TYPE{
    uint32_t start_address; 
    uint32_t address_offset; // address offset for loop at the level of repeat_num
    uint32_t chunck_size; // the size of data that is accessed contiguously
    uint32_t stride_offset ; // the gap between the start of two chunk of data
    uint32_t chunk_count :16; // the number of chunks of data
    uint32_t load_to_memcoreB0 :1; 
    uint32_t load_to_memcoreB1 :1;
    uint32_t is_loading_bias :1;
    uint32_t zero_padding  : 13; 
} ;



// 1 32-bit  => 25 bits
struct INST_MEMCORE_A_TYPE{
    // first 32-bit
    uint32_t one_mem_tile_dim1     :9;  // max 256
    uint32_t one_mem_tile_dim2     :8;  // max 128
    uint32_t compute_tile_access_A :3;  // max 4
    uint32_t compute_tile_access_B :3;  // max 4
    uint32_t enable_load_from_dram :1;
    uint32_t enable_send_to_aie    :1;
    uint32_t zero_padding          :7;

    // second 32-bit
    // uint32_t one_compute_tile_dim1 :8;  // max 128
    // uint32_t one_compute_tile_dim2 :8;  // max 128

} ;


// 2 32-bit => 33 bits
struct INST_MEMCORE_B_TYPE{
    // first 32-bit
    uint32_t one_mem_tile_dim1     :10; // max 512
    uint32_t one_mem_tile_dim2     :10; // max 512
    uint32_t compute_tile_access_A :3;  // max 4
    uint32_t compute_tile_access_B :3;  // max 4
    uint32_t compute_tile_access_K :3;  // max 4
    uint32_t enable_load_from_dram :1;
    uint32_t enable_send_to_aie    :1;
    uint32_t enable_transpose      :1;

    // second 32-bit
    uint32_t is_loading_bias       :1;
    uint32_t zero_padding          :31; 

    // uint32_t one_compute_tile_dim1 :8;  // max 128
    // uint32_t one_compute_tile_dim2 :8;  // max 128    
} ;

// 2 32-bit => 59 bits
struct INST_MEMCORE_C_TYPE{
    // first 32-bit
    uint32_t one_mem_tile_dim1            :9; // max 256
    uint32_t one_mem_tile_dim2            :10; // max 512
    uint32_t compute_tile_recv_access_A   :3; // max 4
    uint32_t compute_tile_recv_access_B   :3; // max 4
    uint32_t compute_tile_recv_access_K   :3; // max 4
    uint32_t compute_tile_send_access_A   :3; // max 4
    uint32_t enable_store_to_dram         :1;
    // second 32-bit
    uint32_t k_iter                       :16;
    uint32_t compute_tile_send_access_B   :3; // max 4
    uint32_t compute_tile_send_access_K   :3; // max 4
    uint32_t enable_send_to_aie           :1;
    uint32_t enable_recv_from_aie         :1;
    uint32_t enable_softmax               :1;
    uint32_t enable_gelu                  :1;
    uint32_t enable_layer_norm            :1;
    uint32_t zero_padding                 :5;
    // uint32_t one_compute_tile_dim1   :16; 
    // uint32_t one_compute_tile_dim2   :16;
} ;

// 2 32-bit
struct INST_MESH_A_TYPE{
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
    uint32_t zero_padding  : 22; 
} ;

// 2 32-bit
struct INST_MESH_B_TYPE{
    uint32_t size;
    uint32_t memcore0_to_computecore0 : 1;
    uint32_t memcore0_to_computecore2 : 1; 
    uint32_t memcore0_to_computecore4 : 1;
    uint32_t memcore1_to_computecore1 : 1;
    uint32_t memcore1_to_computecore3 : 1;
    uint32_t memcore1_to_computecore5 : 1;
    uint32_t memcore2_to_computecore4 : 1;
    uint32_t memcore2_to_computecore5 : 1;
    uint32_t zero_padding  : 24; 
} ;


typedef union{
   INST_HEADER_TYPE inst_val;
   uint32_t raw_32b;
} union_inst_header;


typedef union{
   INST_DDR_TYPE inst_val;
   uint32_t raw_32b[CNT4B_DDR];
} union_inst_ddr;


typedef union{
   INST_LOAD_B_DRAM_TYPE inst_val;
   uint32_t raw_32b[CNT4B_LOAD_B_DRAM];
} union_inst_load_B_dram;


typedef union{
   INST_MEMCORE_A_TYPE inst_val;
   uint32_t raw_32b[CNT4B_MEMCORE_A];
} union_inst_memcore_A;

typedef union{
   INST_MEMCORE_B_TYPE inst_val;
   uint32_t raw_32b[CNT4B_MEMCORE_B];
} union_inst_memcore_B;

typedef union{
   INST_MEMCORE_C_TYPE inst_val;
   uint32_t raw_32b[CNT4B_MEMCORE_C];
} union_inst_memcore_C;

typedef union{
   INST_MESH_A_TYPE inst_val;
   uint32_t raw_32b[CNT4B_MESH_A];
} union_inst_mesh_A;

typedef union{
   INST_MESH_B_TYPE inst_val;
   uint32_t raw_32b[CNT4B_MESH_B];
} union_inst_mesh_B;



void printOpcode ( uint32_t opcode) {
    switch (opcode) {
        case OPCODE_NULL:
            std::cout << "OPCODE_NULL" << std::endl;
            break;
        case OPCODE_DDR_DRAM:
            std::cout << "OPCODE_DDR_DRAM" << std::endl;
            break;
        case OPCODE_LOADB_DRAM:
            std::cout << "OPCODE_LOADB_DRAM" << std::endl;
            break;
        case OPCODE_MEMCORE_A:
            std::cout << "OPCODE_MEMCORE_A" << std::endl;
            break;
        case OPCODE_MEMCORE_B:
            std::cout << "OPCODE_MEMCORE_B" << std::endl;
            break;
        case OPCODE_MEMCORE_C:
            std::cout << "OPCODE_MEMCORE_C" << std::endl;
            break;
        case OPCODE_MESH_SEND_A:
            std::cout << "OPCODE_MESH_SEND_A" << std::endl;
            break;
        case OPCODE_MESH_SEND_B:
            std::cout << "OPCODE_MESH_SEND_B" << std::endl;
            break;
        default:
            std::cout << "OPCODE_UNKNOWN" << std::endl;
            break;
    }
}


void printHeaderInst (INST_HEADER_TYPE inst_val, uint32_t countInstPkt) {

    std::cout << "inst_pkt : " << countInstPkt << " " ;
    printOpcode(inst_val.opcode);
    std::cout << "mask: " << inst_val.mask << " is_last_mOP: " << inst_val.is_last_mOP << " mop_buffer_window_size: " << inst_val.mop_buffer_window_size << " repeat_num: " << inst_val.repeat_num << std::endl;
}


void generate_last_inst_for_all_modules ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt){
    union_inst_header inst_header;

    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = true;
    inst_header.inst_val.mop_buffer_window_size = false;
    inst_header.inst_val.repeat_num = false;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;

    inst_header.inst_val.opcode = OPCODE_LOADB_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = true;
    inst_header.inst_val.mop_buffer_window_size = false;
    inst_header.inst_val.repeat_num = false;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    
    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = true;
    inst_header.inst_val.mop_buffer_window_size = false;
    inst_header.inst_val.repeat_num = false;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;

    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = true;
    inst_header.inst_val.mop_buffer_window_size = false;
    inst_header.inst_val.repeat_num = false;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;

    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b111111;
    inst_header.inst_val.is_last_mOP = true;
    inst_header.inst_val.mop_buffer_window_size = false;
    inst_header.inst_val.repeat_num = false;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = true;
    inst_header.inst_val.mop_buffer_window_size = false;
    inst_header.inst_val.repeat_num = false;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = true;
    inst_header.inst_val.mop_buffer_window_size = false;
    inst_header.inst_val.repeat_num = false;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
}





void generate_instruction_onelayer_cores_meshes ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    inst_header.inst_val.opcode = OPCODE_MEMCORE_A;
    inst_header.inst_val.mask = 0b000111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter * a_iter * b_iter ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_A.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_A.inst_val.one_mem_tile_dim2 = 128;
    // inst_memcore_A.inst_val.one_compute_tile_dim1 = 128;
    // inst_memcore_A.inst_val.one_compute_tile_dim2 = 128;
    inst_memcore_A.inst_val.compute_tile_access_A = 2;
    inst_memcore_A.inst_val.compute_tile_access_B = 4;  
    for (int i = 0; i < CNT4B_MEMCORE_A ; i++) { inst_sequence[count4B++] = inst_memcore_A.raw_32b[i]; }

    inst_header.inst_val.opcode = OPCODE_MEMCORE_B;
    inst_header.inst_val.mask = 0b000011;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = k_iter * a_iter * b_iter ;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_B.inst_val.is_loading_bias = false;
    inst_memcore_B.inst_val.enable_transpose    = false;
    inst_memcore_B.inst_val.one_mem_tile_dim1 = 128;
    inst_memcore_B.inst_val.one_mem_tile_dim2 = 512;
    // inst_memcore_B.inst_val.one_compute_tile_dim1 = 128;
    // inst_memcore_B.inst_val.one_compute_tile_dim2 = 128;
    inst_memcore_B.inst_val.compute_tile_access_A = 2;
    inst_memcore_B.inst_val.compute_tile_access_B = 4;
    inst_memcore_B.inst_val.compute_tile_access_K = 1;
    for (int i = 0; i < CNT4B_MEMCORE_B ; i++) { inst_sequence[count4B++] = inst_memcore_B.raw_32b[i];}



    inst_header.inst_val.opcode = OPCODE_MESH_SEND_A;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_A.inst_val.size = k_iter * a_iter * b_iter*2*4*32*32/2 ;
    inst_mesh_A.inst_val.memcoreA0_to_computecore0 = true;
    inst_mesh_A.inst_val.memcoreA0_to_computecore1 = true; 
    inst_mesh_A.inst_val.memcoreA1_to_computecore2 = true;
    inst_mesh_A.inst_val.memcoreA1_to_computecore3 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore4 = true;
    inst_mesh_A.inst_val.memcoreA2_to_computecore5 = true;
    inst_mesh_A.inst_val.memcoreC0_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC1_to_computecore4 = false;
    inst_mesh_A.inst_val.memcoreC2_to_computecore5 = false;
    inst_mesh_A.inst_val.memcoreC3_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_A ; i++) { inst_sequence[count4B++] = inst_mesh_A.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_MESH_SEND_B;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_mesh_B.inst_val.size = k_iter * a_iter * b_iter*2*4*32*32/2 ;
    inst_mesh_B.inst_val.memcore0_to_computecore0 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore2 = true;
    inst_mesh_B.inst_val.memcore0_to_computecore4 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore1 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore3 = true;
    inst_mesh_B.inst_val.memcore1_to_computecore5 = true;
    inst_mesh_B.inst_val.memcore2_to_computecore4 = false;
    inst_mesh_B.inst_val.memcore2_to_computecore5 = false;
    for (int i = 0; i < CNT4B_MESH_B ; i++) { inst_sequence[count4B++] = inst_mesh_B.raw_32b[i];}


    inst_header.inst_val.opcode = OPCODE_MEMCORE_C;
    inst_header.inst_val.mask = 0b111111;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 1;
    inst_header.inst_val.repeat_num = a_iter * b_iter;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_memcore_C.inst_val.enable_store_to_dram = true;
    inst_memcore_C.inst_val.enable_send_to_aie = false;
    inst_memcore_C.inst_val.enable_recv_from_aie = true;
    inst_memcore_C.inst_val.enable_softmax = false;
    inst_memcore_C.inst_val.one_mem_tile_dim1 = 256;
    inst_memcore_C.inst_val.one_mem_tile_dim2 = 512;
    // inst_memcore_C.inst_val.one_compute_tile_dim1 = 128;
    // inst_memcore_C.inst_val.one_compute_tile_dim2 = 128;
    inst_memcore_C.inst_val.compute_tile_recv_access_A = 2;
    inst_memcore_C.inst_val.compute_tile_recv_access_B = 4;
    inst_memcore_C.inst_val.compute_tile_recv_access_K = 1;
    inst_memcore_C.inst_val.compute_tile_send_access_A = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_B = 0;
    inst_memcore_C.inst_val.compute_tile_send_access_K = 0;
    inst_memcore_C.inst_val.k_iter =  k_iter;
    for (int i = 0; i < CNT4B_MEMCORE_C ; i++) { inst_sequence[count4B++] = inst_memcore_C.raw_32b[i]; }
}


void generate_instruction_loadB (int a, int b, uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;
    uint32_t loadA_address, loadB_address, storeC_address;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    loadB_address = params.lpddr_offset_512b_weight;
    
    loadB_address += b * 128 * 1024 / 16;
    inst_header.inst_val.opcode = OPCODE_LOADB_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num = k_iter;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++; 
    inst_loadB_dram.inst_val.start_address = loadB_address + 0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_loadB_dram.inst_val.address_offset = 128*512*2*b_iter / 16; 
    inst_loadB_dram.inst_val.chunck_size = 128*512; // 8 tiles, each 128x64
    inst_loadB_dram.inst_val.stride_offset = 0;
    inst_loadB_dram.inst_val.chunk_count = 1;
    inst_loadB_dram.inst_val.load_to_memcoreB0 = true;
    inst_loadB_dram.inst_val.load_to_memcoreB1 = false;
    inst_loadB_dram.inst_val.is_loading_bias   = false;
    for (int i = 0; i < CNT4B_LOAD_B_DRAM ; i++) { inst_sequence[count4B++] = inst_loadB_dram.raw_32b[i];}
    inst_loadB_dram.inst_val.start_address = loadB_address + 1*128*512 / 16;
    inst_loadB_dram.inst_val.address_offset = 128*512*2*b_iter / 16;
    inst_loadB_dram.inst_val.chunck_size = 128*512; // 8 tiles, each 128x64
    inst_loadB_dram.inst_val.stride_offset = 0;
    inst_loadB_dram.inst_val.chunk_count = 1;
    inst_loadB_dram.inst_val.load_to_memcoreB0 = false;
    inst_loadB_dram.inst_val.load_to_memcoreB1 = true;
    inst_loadB_dram.inst_val.is_loading_bias   = false;
    for (int i = 0; i < CNT4B_LOAD_B_DRAM ; i++) { inst_sequence[count4B++] = inst_loadB_dram.raw_32b[i];}
}

void generate_instruction_loadA (int a, int b, int offset, int repeat_num, uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;
    uint32_t loadA_address, loadB_address, storeC_address;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    loadA_address = params.ddr_offset_512b_input;
    loadA_address += a * 768 * 128 * k_iter / 16 + offset;
    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 3;
    inst_header.inst_val.repeat_num = repeat_num;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
}


void generate_instruction_storeC(int a, int b, uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;
    uint32_t loadA_address, loadB_address, storeC_address;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;
 
    storeC_address = params.ddr_offset_512b_output;
    storeC_address += (a * 768 * 1024 * b_iter + b * 128 * 1024) / 16;       
    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 6;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = storeC_address + 0;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = true;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
    inst_ddr.inst_val.start_address = storeC_address + 128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = true;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = true;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter+1)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = true;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = true;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter+1)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = true;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
}




void generate_instruction_K8_steady_ddr (int loadA_a, int loadA_b, int storeC_a, int storeC_b, uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;
    uint32_t loadA_address, loadB_address, storeC_address;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    loadA_address = params.ddr_offset_512b_input +  loadA_a * 768 * 128 * k_iter / 16 ; 
    storeC_address = params.ddr_offset_512b_output;
    storeC_address += (storeC_a * 768 * 1024 * b_iter + storeC_b * 128 * 1024) / 16;   


    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 2;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 31;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + 0;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = true;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
 
    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + 0 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = true;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
 
    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + 128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = true;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}





    inst_ddr.inst_val.start_address = storeC_address + 128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = true;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = true;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}




    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter)*128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = true;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter+1)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = true;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = true;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter+1)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = true;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


}








void generate_instruction_Klarger16_steady_ddr (int loadA_a, int loadA_b, int storeC_a, int storeC_b, uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){

    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;
    uint32_t loadA_address, loadB_address, storeC_address;
    union_inst_header inst_header;
    union_inst_ddr inst_ddr;
    union_inst_load_B_dram inst_loadB_dram;
    union_inst_memcore_A inst_memcore_A;
    union_inst_memcore_B inst_memcore_B;
    union_inst_memcore_C inst_memcore_C;
    union_inst_mesh_A inst_mesh_A;
    union_inst_mesh_B inst_mesh_B;

    loadA_address = params.ddr_offset_512b_input + loadA_a * 768 * 128 * k_iter / 16 ; 
    storeC_address = params.ddr_offset_512b_output;
    storeC_address += (storeC_a * 768 * 1024 * b_iter + storeC_b * 128 * 1024) / 16;   


    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 30;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + 0;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = true;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
 
    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + 0 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = true;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }
 
    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + 128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = true;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}





    inst_ddr.inst_val.start_address = storeC_address + 128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = true;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = true;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}




    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter)*128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = true;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }


    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 21;
    inst_header.inst_val.repeat_num = 1;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;

    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter+1)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = true;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (4*b_iter+1)*128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = true;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = true;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter)*128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = true;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}

    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter+1)*128*512/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = true;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}


    inst_ddr.inst_val.start_address = storeC_address + (8*b_iter+1)*128*512/16 + 128*1024*b_iter/16;
    inst_ddr.inst_val.address_offset = 0; 
    inst_ddr.inst_val.chunck_size = 128*512;
    inst_ddr.inst_val.stride_offset = 128*1024*b_iter/16;
    inst_ddr.inst_val.chunk_count = 1; 
    inst_ddr.inst_val.is_store = true; 
    inst_ddr.inst_val.is_load = false;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = true;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i]; }



    inst_header.inst_val.opcode = OPCODE_DDR_DRAM;
    inst_header.inst_val.mask = false;
    inst_header.inst_val.is_last_mOP = false;
    inst_header.inst_val.mop_buffer_window_size = 3;
    inst_header.inst_val.repeat_num = k_iter - 13;
    inst_sequence[count4B++] = inst_header.raw_32b;
    printHeaderInst(inst_header.inst_val, countInstPkt);
    countInstPkt ++;

    loadA_address = loadA_address + 128*128 / 16; 
    inst_ddr.inst_val.start_address = loadA_address +  0 / 16; // divided by 16 because 1 address hold 16 32float (512bit)
    inst_ddr.inst_val.address_offset =  128*128 / 16; 
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each tile 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = true;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2;
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = true;
    inst_ddr.inst_val.load_to_memcoreA2 = false;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}
    inst_ddr.inst_val.start_address = loadA_address + k_iter*256*128 * 2 / 16;
    inst_ddr.inst_val.address_offset = 128*128 / 16;
    inst_ddr.inst_val.chunck_size = 128*128; // 2 tiles, each 128x64
    inst_ddr.inst_val.stride_offset = 128*128*k_iter /16;
    inst_ddr.inst_val.chunk_count = 2; 
    inst_ddr.inst_val.is_store = false; 
    inst_ddr.inst_val.is_load = true;
    inst_ddr.inst_val.load_to_memcoreA0 = false;
    inst_ddr.inst_val.load_to_memcoreA1 = false;
    inst_ddr.inst_val.load_to_memcoreA2 = true;
    inst_ddr.inst_val.load_to_memcoreB0 = false;
    inst_ddr.inst_val.load_to_memcoreB1 = false;
    inst_ddr.inst_val.load_to_memcoreB2 = false;
    inst_ddr.inst_val.load_to_memcoreC0 = false;
    inst_ddr.inst_val.load_to_memcoreC1 = false;
    inst_ddr.inst_val.load_to_memcoreC2 = false;
    inst_ddr.inst_val.load_to_memcoreC3 = false;
    inst_ddr.inst_val.load_to_memcoreC4 = false;
    inst_ddr.inst_val.load_to_memcoreC5 = false;
    inst_ddr.inst_val.store_from_memcoreC0 = false;
    inst_ddr.inst_val.store_from_memcoreC1 = false;
    inst_ddr.inst_val.store_from_memcoreC2 = false;
    inst_ddr.inst_val.store_from_memcoreC3 = false;
    inst_ddr.inst_val.store_from_memcoreC4 = false;
    inst_ddr.inst_val.store_from_memcoreC5 = false;
    for (int i = 0; i < CNT4B_DDR ; i++) { inst_sequence[count4B++] = inst_ddr.raw_32b[i];}



}






void generate_instruction_onelayer ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

    for (int a = 0; a < a_iter; a++){
        for (int b = 0; b< b_iter; b++){
            generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
            generate_instruction_loadA(a, b, 0, k_iter, inst_sequence, count4B, countInstPkt, params);
            generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);
        }
    }

    generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}

void generate_instruction_onelayer_overlap_A1B4K2 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(a_iter == 1);
    assert(b_iter == 4);
    assert(k_iter == 2);

    generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

    int a, b, offset, repeat_num;

    a = 0; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 0; offset = 0; repeat_num = k_iter; generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt, params);
    
    a = 0; b = 1; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 1; offset = 0; repeat_num = k_iter; generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 0; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    a = 0; b = 2; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 2; offset = 0; repeat_num = k_iter; generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 1; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    a = 0; b = 3; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 3; offset = 0; repeat_num = k_iter; generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 2; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    a = 0; b = 3; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}




void generate_instruction_onelayer_overlap_128_512_A4B1K8 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(a_iter == 4);
    assert(b_iter == 1);
    assert(k_iter == 8);

    generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

    int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

    a = 0; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 0; offset = 0; repeat_num = k_iter; 
    generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt, params);
    
    a = 1; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 1; loadA_b = 0; storeC_a = 0; storeC_b = 0; 
    generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a = 2; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 2; loadA_b = 0; storeC_a = 1; storeC_b = 0;
    generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a = 3; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 3; loadA_b = 0; storeC_a = 2; storeC_b = 0;
    generate_instruction_K8_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a = 3; b = 0; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}



void generate_instruction_onelayer_overlap_128_512_A4B1_Klarger16 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(a_iter == 4);
    assert(b_iter == 1);
    assert(k_iter >= 16);

    generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

    int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

    a = 0; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 0; offset = 0; repeat_num = k_iter; 
    generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt, params);
    
    a = 1; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 1; loadA_b = 0; storeC_a = 0; storeC_b = 0; 
    generate_instruction_Klarger16_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a = 2; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 2; loadA_b = 0; storeC_a = 1; storeC_b = 0;
    generate_instruction_Klarger16_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a = 3; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    loadA_a = 3; loadA_b = 0; storeC_a = 2; storeC_b = 0;
    generate_instruction_Klarger16_steady_ddr(loadA_a, loadA_b, storeC_a, storeC_b, inst_sequence, count4B, countInstPkt, params);

    a = 3; b = 0; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}



void generate_instruction_onelayer_overlap_128_512_A4B4K8 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(a_iter == 4);
    assert(b_iter == 4);
    assert(k_iter == 8);

    generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

    int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

    a = 0; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 0; offset = 0; repeat_num = k_iter; 
    generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt, params);
    
    for (int a=0; a<4; a++){
        for (int b=0; b<4; b++){
            if (a == 0 && b == 0) continue;
            int a_last, b_last;
            if (b==0){
                a_last = a-1; b_last = 3;
            }else{
                a_last = a; b_last = b-1;
            }

            generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
            generate_instruction_K8_steady_ddr(a, b, a_last, b_last, inst_sequence, count4B, countInstPkt, params);

        }
    }
    a = 3; b = 3; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}




void generate_instruction_onelayer_overlap_128_512_Klarger16 ( uint32_t *inst_sequence, uint32_t & count4B,  uint32_t & countInstPkt, ParamsOneLayer params){
    uint32_t a_iter = params.a_iter;
    uint32_t b_iter = params.b_iter;
    uint32_t k_iter = params.k_iter;

    assert(k_iter >= 16);

    generate_instruction_onelayer_cores_meshes(inst_sequence, count4B, countInstPkt, params);

    int a, b, offset, repeat_num, loadA_a, loadA_b, storeC_a, storeC_b;

    a = 0; b = 0; generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
    a = 0; b = 0; offset = 0; repeat_num = k_iter; 
    generate_instruction_loadA(a, b, offset, repeat_num, inst_sequence, count4B, countInstPkt, params);
    
    for (int a=0; a<a_iter; a++){
        for (int b=0; b<b_iter; b++){
            if (a == 0 && b == 0) continue;
            int a_last, b_last;
            if (b==0){ a_last = a-1; b_last = 3;
            }else{ a_last = a; b_last = b-1;}
            
            generate_instruction_loadB(a, b, inst_sequence, count4B, countInstPkt, params);
            generate_instruction_Klarger16_steady_ddr(a, b, a_last, b_last, inst_sequence, count4B, countInstPkt, params);
        }
    }

    a = a_iter-1; b = b_iter-1; generate_instruction_storeC(a, b, inst_sequence, count4B, countInstPkt, params);

    generate_last_inst_for_all_modules(inst_sequence, count4B, countInstPkt);
}



