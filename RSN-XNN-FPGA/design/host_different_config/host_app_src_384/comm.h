#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include "adf/adf_api/XRTConfig.h"
#include "experimental/xrt_aie.h"
#include "experimental/xrt_kernel.h"
#include "experimental/xrt_bo.h"
#include "experimental/xrt_graph.h"
#include "experimental/xrt_ip.h"
#include "xrt/xrt_aie.h"
#include "xrt.h"
#include <chrono>
#include <ctime>
#include <bitset>
#include <vector>
#include <iomanip>
#include "assert.h"
#include <math.h>

#include <unistd.h>

using namespace std;

#define ENABLE_TEST_Q
#define ENABLE_TEST_K
#define ENABLE_TEST_V
#define ENABLE_TEST_ATTENTION
#define ENABLE_TEST_NORM1
#define ENABLE_TEST_GELU
#define ENABLE_TEST_NORM2

#define INPUT_LEN 384
#define BATCH_SIZE 8

// #define SW_EMU_PRINT


class Timer {
	std::chrono::high_resolution_clock::time_point mTimeStart;
   public:
  	Timer() { reset(); }
  	long long stop() {
    	std::chrono::high_resolution_clock::time_point timeEnd =
        	std::chrono::high_resolution_clock::now();
    	return std::chrono::duration_cast<std::chrono::microseconds>(timeEnd -mTimeStart).count();
	}
  	void reset() { mTimeStart = std::chrono::high_resolution_clock::now(); }
};



static std::vector<char>
load_xclbin(xrtDeviceHandle device, const std::string& fnm)
{
   if (fnm.empty())
      throw std::runtime_error("No xclbin speified");

   // load bit stream
   std::ifstream stream(fnm);
   stream.seekg(0,stream.end);
   size_t size = stream.tellg();
   stream.seekg(0,stream.beg);

   std::vector<char> header(size);
   stream.read(header.data(),size);

   auto top = reinterpret_cast<const axlf*>(header.data());
   if (xrtDeviceLoadXclbin(device, top))
      throw std::runtime_error("Bitstream download failed");

   return header;
}


class ParamsOneLayer {
private:


   uint32_t aie_dim_a = 32;
   uint32_t aie_dim_b = 32;
   uint32_t aie_dim_ab = 32;

   uint32_t one_computecore_tile_a = 128;
   uint32_t one_computecore_tile_b = 128;
   uint32_t one_computecore_tile_k = 128;

   uint32_t one_memcore_tile_a = 256;
   uint32_t one_memcore_tile_b = 512;
   uint32_t one_memcore_tile_k = 128;

   uint32_t compute_tile_access_A = 2;
   uint32_t compute_tile_access_B = 4;

   uint32_t pl_tile_a = 3 * 256;
   uint32_t pl_tile_b = 2 * 512;
   uint32_t pl_tile_k = 128;

   // uint32_t matrix_size_a = pl_tile_a * a_iter;
   // uint32_t matrix_size_b = pl_tile_b * b_iter;
   // uint32_t matrix_size_k = pl_tile_k * k_iter;

public:

   uint32_t a_iter = 1;
   uint32_t b_iter = 1;
   uint32_t k_iter = 1;
   bool enable_bias = false;
   bool enable_norm = false;
   bool enable_addmul_pre_layer = false;
   bool enable_gelu = false;

   size_t lpddr_offset_512b_weight = 0;
   size_t lpddr_offset_512b_bias = 0;
   size_t ddr_offset_512b_input = 0;
   size_t ddr_offset_512b_output = 0;
   
   size_t lpddr_offset_512b_pre_layer_weight = 0;
   size_t ddr_offset_512b_pre_layer = 0;


   size_t ddr_size_for_inA, ddr_size_for_outC, lpddr_size_for_inB;


   // Constructor
   ParamsOneLayer() = default;

   void set_iter (uint32_t a_iter, uint32_t b_iter, uint32_t k_iter) {
      this->a_iter = a_iter;
      this->b_iter = b_iter;
      this->k_iter = k_iter;
   }

   void set_ddr_size_for_inA (size_t size) {
      this->ddr_size_for_inA = size;
   }
   void set_ddr_size_for_outC (size_t size) {
      this->ddr_size_for_outC = size;
   }

   void set_lpddr_size_for_inB (size_t size) {
      this->lpddr_size_for_inB = size;
   }

   // Computed attributes
   uint32_t getMatrixDim_A() { return pl_tile_a * a_iter; }
   uint32_t getMatrixDim_B() { return pl_tile_b * b_iter; }
   uint32_t getMatrixDim_K() { return pl_tile_k * k_iter; }
   uint32_t getAIE_round()   { return k_iter * a_iter * b_iter * compute_tile_access_A * compute_tile_access_B; }
   uint32_t getAIE_k_iter()  { return 1; } 
   double getTotalOps () { return 2 * pl_tile_a * a_iter * pl_tile_b * b_iter * pl_tile_k * k_iter; }
   double calThroughput (double time) { return ((2*getMatrixDim_A()*getMatrixDim_B()/1000) * getMatrixDim_K())/time; }

   size_t getDDR_outC_offset_in_size () { return ddr_size_for_inA; }

   size_t getDDR_Bytes () { 
      return 4*ddr_size_for_inA + 4*ddr_size_for_outC; 
   }
   size_t getLPDDR_Bytes () { return 4*lpddr_size_for_inB; }
   

   void print() {
      std::cout << "A_ITER = " << a_iter << " B_ITER = " << b_iter << " K_ITER = " << k_iter << std::endl;
      std::cout << "MATRIX_A = " << getMatrixDim_A() << " MATRIX_B = " << getMatrixDim_B() << " MATRIX_K = " << getMatrixDim_K() << std::endl;
      std::cout << "AIE: round = " << getAIE_round() << " k_iter = " << getAIE_k_iter() << std::endl;
   }

};





class ParamsFusedLayer {
private:


public:

   uint32_t num_layer;

   size_t ddr_size_for_L1_inA, ddr_size_for_L2_outC, ddr_size_for_L1_inB, ddr_size_for_L2_inB ;

   size_t ddr_offset_512b_inA_L1 = 0;
   size_t ddr_offset_512b_inB_L1 = 0;
   size_t ddr_offset_512b_inB_L2 = 0;
   size_t ddr_offset_512b_outC_L2 = 0;




   // Constructor
   ParamsFusedLayer() = default;

   void set_num_layer (uint32_t num_layer) {
      this->num_layer = num_layer;
   }
   void set_ddr_size_for_L1_inA (size_t size) {
      this->ddr_size_for_L1_inA = size;
   }
   void set_ddr_size_for_L1_inB (size_t size) {
      this->ddr_size_for_L1_inB = size;
   }
   void set_ddr_size_for_L2_inB (size_t size) {
      this->ddr_size_for_L2_inB = size;
   }
   void set_ddr_size_for_L2_outC (size_t size) {
      this->ddr_size_for_L2_outC = size;
   }

   // Computed attributes
   uint32_t getMatrixDim_L1_A() { return 512 ; }
   uint32_t getMatrixDim_L1_K() { return 64; }
   uint32_t getMatrixDim_L1_B() { return 512; }
   uint32_t getMatrixDim_L2_A() { return 512; }
   uint32_t getMatrixDim_L2_K() { return 512; }
   uint32_t getMatrixDim_L2_B() { return 64; }

   size_t getDDR_L1_inA_offset_in_size(){
      return 0;
   }
   size_t getDDR_L1_inB_offset_in_size(){
      return ddr_size_for_L1_inA;
   }
   size_t getDDR_L2_inB_offset_in_size(){
      return ddr_size_for_L1_inA + ddr_size_for_L1_inB;
   }
   size_t getDDR_L2_outC_offset_in_size(){
      return ddr_size_for_L1_inA + ddr_size_for_L1_inB + ddr_size_for_L2_inB;
   }

   uint32_t getAIEIterL1() { return num_layer * 4; }
   uint32_t getAIEIterL2() { return num_layer * 2; }
   double getTotalOps () { return num_layer*(512*64*512 + 512*512*64); }
   double calThroughput (double time) { return ((512*64*512+512*512*64)/1000)*num_layer*2/time; }

   size_t getDDR_Bytes() { 
      return 4*ddr_size_for_L1_inA + 4*ddr_size_for_L1_inB + 4*ddr_size_for_L2_inB + 4*ddr_size_for_L2_outC; 
   }
   size_t getLPDDR_Bytes() { return 1024;} // size 0 will cause fail in allocatation 
   

   void print() {
      std::cout << "NUM_LAYER = " << num_layer << std::endl;
      std::cout << "MATRIX_L1_A = " << getMatrixDim_L1_A() << " MATRIX_L1_K = " << getMatrixDim_L1_K() << " MATRIX_L1_B = " << getMatrixDim_L1_B() << std::endl;
      std::cout << "AIE_ITER_L1 = " << getAIEIterL1() << " AIE_ITER_L2 = " << getAIEIterL2() << std::endl;
   }

};



