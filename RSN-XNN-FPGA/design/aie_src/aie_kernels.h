/*
Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
SPDX-License-Identifier: MIT
*/

#pragma once

#include <adf.h>

#include <aie_api/aie.hpp>

#include "system_settings.h"

using namespace adf;
using namespace aie;

// #define SW_EMU_PRINT

#ifdef SW_EMU_PRINT
#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>
#include <aie_api/utils.hpp>
#include <fstream>  // Include for file operations
#include <iostream>
#endif

void mm_casc_startk0(input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_A>>& __restrict matA,
                     input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_B>>& __restrict matB,
                     output_cascade<accfloat>* __restrict partial_C,
                     const uint32_t (&opcode_mem)[512]);

void mm_casc_middlek1(input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_A>>& __restrict matA,
                      input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_B>>& __restrict matB,
                      input_cascade<accfloat>* __restrict partial_C_in,
                      output_cascade<accfloat>* __restrict partial_C_out,
                      const uint32_t (&opcode_mem)[512]);

void mm_casc_middlek2(input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_A>>& __restrict matA,
                      input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_B>>& __restrict matB,
                      input_cascade<accfloat>* __restrict partial_C_in,
                      output_cascade<accfloat>* __restrict partial_C_out,
                      const uint32_t (&opcode_mem)[512]);

void mm_casc_endk3(input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_A>>& __restrict matA,
                   input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_B>>& __restrict matB,
                   output_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_C>>& __restrict matC,
                   input_cascade<accfloat>* __restrict partial_C,
                   const uint32_t (&opcode_mem)[512]);
