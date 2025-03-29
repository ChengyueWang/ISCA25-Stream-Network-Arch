#include "aie_kernels.h"

float k0_local_buf_1K[1024] = {0.0};

void mm_casc_startk0(input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_A>>& __restrict matA,
                     input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_B>>& __restrict matB,
                     output_cascade<accfloat>* __restrict partial_C, uint32_t (&opcode_mem)[512]) {
  uint32_t print_code = opcode_mem[0];
  uint32_t opcode_len = opcode_mem[1];

#ifdef SW_EMU_PRINT
  std::ofstream outFile("/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/aie" +
                            std::to_string(print_code) + "_mm_casc_start.txt",
                        std::ios_base::app);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file for writing." << std::endl;
  }

  if (print_code > 0) {
    outFile << "ENTER mm_casc_start =================== " << std::endl;
    outFile << " opcode_len = " << opcode_len << std::endl;
  }

  float k0_local_buf_1K[1024] = {0.0};  // double declare as vitis-tutorial
  for (int i = 0; i < 1024; i++) {
    k0_local_buf_1K[i] = 0.0;
  }

#endif

  for (int op_id = 2; op_id < opcode_len + 2; op_id++) {
    uint32_t opcode = opcode_mem[op_id];

    // # last 4 bit 0x80000000 , jump , loop back until is 0
    bool is_jump_op = (opcode & 0x80000000) >> 31;
    uint32_t jump_dest_id = (opcode & 0x7F000000) >> 24;
    uint32_t jump_count = opcode & 0x00FFFFFF;

    if (is_jump_op == true) {
      if (jump_count > 0) {
        jump_count = jump_count - 1;
        opcode = (opcode & 0xFF000000) | jump_dest_id;
        opcode_mem[op_id] = opcode;
        opcode = opcode_mem[jump_dest_id];
      } else {
        continue;
      }
    }

    int a_iter = opcode & 0x0000000F;
    int b_iter = (opcode & 0x000000F0) >> 4;
    int k_iter = (opcode & 0x00007F00) >> 8;
    int compute_tile_access_A = (opcode & 0x00018000) >> 15;
    int compute_tile_access_B = (opcode & 0x000E0000) >> 17;
    bool enable_load_pre_norm_weight = (opcode & 0x00100000) >> 20;
    bool enable_bias = (opcode & 0x00200000) >> 21;
    bool dimb_is_32 = (opcode & 0x00400000) >> 22;
    bool dimk_is_32 = (opcode & 0x00800000) >> 23;
    bool enable_accum_kiter = (opcode & 0x01000000) >> 24;
    bool enable_muladd_pre_layer = (opcode & 0x02000000) >> 25;
    bool need_muladd_pre_layer_in_cur_aie = (opcode & 0x04000000) >> 26;

    int round, b_round;

    if (dimk_is_32 == false) {
      round = k_iter * a_iter * b_iter * compute_tile_access_B * compute_tile_access_A;
    }

    if (dimb_is_32 == 1) {
      b_round = 32 / 8;
    } else {
      b_round = 16 / 8;
    }

#ifdef SW_EMU_PRINT
    if (print_code > 0) {
      outFile << "op_id = " << op_id << std::endl;
      outFile << "opcode = " << opcode << std::endl;
      outFile << "a_iter = " << a_iter << "b_iter = " << b_iter << " k_iter = " << k_iter
              << " compute_tile_access_A = " << compute_tile_access_A
              << " compute_tile_access_B = " << compute_tile_access_B
              << " enable_load_pre_norm_weight = " << enable_load_pre_norm_weight
              << " enable_bias = " << enable_bias << " dimb_is_32 = " << dimb_is_32
              << " dimk_is_32 = " << dimk_is_32 << " enable_accum_kiter = " << enable_accum_kiter
              << " print_code = " << print_code << std::endl;
      outFile << "round = " << round << " b_round = " << b_round << std::endl;
      outFile << "enable_muladd_pre_layer = " << enable_muladd_pre_layer << std::endl;
      outFile << "need_muladd_pre_layer_in_cur_aie = " << need_muladd_pre_layer_in_cur_aie
              << std::endl;
    }
#endif

    // first load norm, pass to k2, then load bias

    if (enable_load_pre_norm_weight == true) {
      matB.acquire();

#ifdef SW_EMU_PRINT
      // NOTE that different functions calls probably will be reordered
      if (print_code > 0) {
        outFile << "before load_pre_norm_weight = " << std::endl;
        outFile << "k0_local_buf_1K (declare inside kernel in simulation)= " << std::endl;
        auto local_buf_print = begin(k0_local_buf_1K);
        for (int row = 0; row < 32; row++) {
          for (int col = 0; col < 32; col++) {
            float val = *local_buf_print++;
            outFile << val << " ";
          }
          outFile << std::endl;
        }
        outFile << std::endl;
        outFile << std::endl;
        outFile << std::endl;

        outFile << "matB = " << std::endl;
        auto pB_print = begin(matB);
        for (int row = 0; row < 32; row++) {
          for (int col = 0; col < 32; col++) {
            float val = *pB_print++;
            outFile << val << " ";
          }
          outFile << std::endl;
        }
      }
#endif

      auto ptrv8_local_buf = begin_vector_random_circular<8>(k0_local_buf_1K);
      auto bias_portB = begin_vector_random_circular<8>(matB);
      for (int i = 0; i < 128 / 8; i++) {
        aie::vector<float, 8> temp = *bias_portB;
        if (need_muladd_pre_layer_in_cur_aie == true) {
          *ptrv8_local_buf = temp;
        } else {
          *ptrv8_local_buf = zeros<float, 8>();
        }
        accum<accfloat, 8> temp_acc;
        temp_acc = fpadd(aie::zeros<float, 8>(), temp);
        writeincr(partial_C, temp_acc);
        ptrv8_local_buf++;
        bias_portB++;
      }

#ifdef SW_EMU_PRINT
      // NOTE that different functions calls probably will be reordered
      if (print_code > 0) {
        outFile << "after load_pre_norm_weight = " << std::endl;
        outFile << "k0_local_buf_1K = " << std::endl;
        auto local_buf_print = begin(k0_local_buf_1K);
        for (int row = 0; row < 32; row++) {
          for (int col = 0; col < 32; col++) {
            float val = *local_buf_print++;
            outFile << val << " ";
          }
          outFile << std::endl;
        }
        outFile << std::endl;
        outFile << std::endl;
        outFile << std::endl;
      }
#endif

      matB.release();
    }

    if (enable_bias == true) {
      auto ptrv16_local_buf = begin_vector_random_circular<16>(k0_local_buf_1K) + 512 / 16;
      matB.acquire();

#ifdef SW_EMU_PRINT
      // NOTE that different functions calls probably will be reordered
      if (print_code > 0) {
        outFile << "before bias loading = " << std::endl;
        outFile << "k0_local_buf_1K (declare inside kernel in simulation)= " << std::endl;
        auto local_buf_print = begin(k0_local_buf_1K);
        for (int row = 0; row < 32; row++) {
          for (int col = 0; col < 32; col++) {
            float val = *local_buf_print++;
            outFile << val << " ";
          }
          outFile << std::endl;
        }
        outFile << std::endl;
        outFile << std::endl;
        outFile << std::endl;

        outFile << "matB = " << std::endl;
        auto pB_print = begin(matB);
        for (int row = 0; row < 32; row++) {
          for (int col = 0; col < 32; col++) {
            float val = *pB_print++;
            outFile << val << " ";
          }
          outFile << std::endl;
        }
      }
#endif

      auto bias_portB = begin_vector_random_circular<16>(matB);
      for (int i = 0; i < b_iter * compute_tile_access_B * 32 / 16; i++) {
        *ptrv16_local_buf = *bias_portB;
        ptrv16_local_buf++;
        bias_portB++;
      }

#ifdef SW_EMU_PRINT
      // NOTE that different functions calls probably will be reordered
      if (print_code > 0) {
        outFile << "after bias loading = " << std::endl;
        outFile << "k0_local_buf_1K = " << std::endl;
        auto local_buf_print = begin(k0_local_buf_1K);
        for (int row = 0; row < 32; row++) {
          for (int col = 0; col < 32; col++) {
            float val = *local_buf_print++;
            outFile << val << " ";
          }
          outFile << std::endl;
        }
        outFile << std::endl;
        outFile << std::endl;
        outFile << std::endl;
      }
#endif

      matB.release();
    }

    int loop_k_iter;
    if (enable_bias == true) {
      loop_k_iter = k_iter - 1;
    } else {
      loop_k_iter = k_iter;
    }

    if (dimk_is_32 == 1) {
    L_AI:
      for (int ai = 0; ai < a_iter; ai++) {
      L_BI:
        for (int bi = 0; bi < b_iter; bi++) {
          if (enable_muladd_pre_layer == true) {
            for (int access_a = 0; access_a < compute_tile_access_A; access_a++) {
              for (int access_b = 0; access_b < compute_tile_access_B; access_b++) {
                matA.acquire();
                auto pA = begin_vector_random_circular<8>(matA);
#ifdef SW_EMU_PRINT
                if (print_code > 0) {
                  outFile << "access_a = " << access_a << " access_b = " << access_b
                          << " ai = " << ai << " bi = " << bi << std::endl;
                  outFile << "matA.acquire(); = " << std::endl;
                  auto pA_print = begin(matA);
                  for (int row = 0; row < 32; row++) {
                    for (int col = 0; col < 32; col++) {
                      float val = *pA_print++;
                      outFile << val << " ";
                    }
                    outFile << std::endl;
                  }
                }
#endif

                for (int b = 0; b < b_round; b++)
                  chess_prepare_for_pipelining chess_loop_range(4, ) {
                    pA = begin_vector_random_circular<8>(matA) + 2 * b;
                    int local_buf_offset = bi * compute_tile_access_B * 32 / 8 + access_b * 4 + b;
                    auto ptrv8_local_buf = begin_vector_random_circular<8>(k0_local_buf_1K);
                    vector<float, 8> cur_norm_weight;
                    cur_norm_weight = *(ptrv8_local_buf + local_buf_offset);

                    for (int i = 0; i < AIE_TILE_A / 2; i++)  // Each iteration computes 2 rows of C
                      chess_prepare_for_pipelining chess_unroll_loop(4) chess_loop_range(16, ) {
                        accum<accfloat, 8> chess_storage(wr2) acc1;
                        accum<accfloat, 8> chess_storage(wr3) acc2;
                        vector<float, 8> chess_storage(wr0) buf_matA1;
                        vector<float, 8> chess_storage(wc0) buf_matA2;
                        vector<float, 4> temp1_v4;
                        vector<float, 4> temp2_v4;
                        buf_matA1 = *pA;
                        pA = pA + 1;
                        buf_matA2 = *pA;
                        pA = pA + 7;
                        temp1_v4 = ext_v(buf_matA1, 1);
                        temp2_v4 = ext_v(buf_matA2, 0);
                        buf_matA1 = upd_v(buf_matA1, 1, temp2_v4);
                        buf_matA2 = upd_v(buf_matA2, 0, temp1_v4);
                        acc1 = fpmul(buf_matA1, 0, 0x76543210, cur_norm_weight, 0, 0x76543210);
                        acc2 = fpmul(buf_matA2, 0, 0x76543210, cur_norm_weight, 0, 0x76543210);
                        writeincr(partial_C, acc1);
                        writeincr(partial_C, acc2);
                      }
                  }
                matA.release();
              }
            }
          }

          if (enable_bias == true) {
            for (int access_a = 0; access_a < compute_tile_access_A; access_a++) {
              for (int access_b = 0; access_b < compute_tile_access_B; access_b++) {
                matA.acquire();
                matB.acquire();
                auto pA = begin_vector_random_circular<8>(matA);
                auto pB = begin_vector_random_circular<8>(matB);

#ifdef SW_EMU_PRINT
                // NOTE that different functions calls probably will be reordered
                if (print_code > 0) {
                  outFile << "enable bias loop  " << std::endl;
                  outFile << "matA = " << std::endl;
                  auto pA_print = begin(matA);
                  for (int row = 0; row < 32; row++) {
                    for (int col = 0; col < 32; col++) {
                      float val = *pA_print++;
                      outFile << val << " ";
                    }
                    outFile << std::endl;
                  }
                  outFile << "matB = " << std::endl;
                  auto pB_print = begin(matB);
                  for (int row = 0; row < 32; row++) {
                    for (int col = 0; col < 32; col++) {
                      float val = *pB_print++;
                      outFile << val << " ";
                    }
                    outFile << std::endl;
                  }
                  outFile << std::endl;
                  outFile << std::endl;
                  outFile << std::endl;
                }
#endif

                for (int b = 0; b < 4; b++) chess_prepare_for_pipelining chess_loop_range(4, ) {
                    int local_buf_offset = bi * compute_tile_access_B * 32 / 8 + access_b * 4 + b;
                    auto ptrv8_local_buf =
                        begin_vector_random_circular<8>(k0_local_buf_1K) + 512 / 8;
                    vector<float, 8> cur_bias;
                    cur_bias = *(ptrv8_local_buf + local_buf_offset);

                    for (int i = 0; i < AIE_TILE_A / 2; i++)  // Each iteration computes 2 rows of C
                      chess_prepare_for_pipelining chess_unroll_loop(2) chess_loop_range(16, ) {
                        accum<accfloat, 8> chess_storage(wr2) acc1;
                        accum<accfloat, 8> chess_storage(wr3) acc2;
                        vector<float, 8> chess_storage(wr0) buf_matA;
                        vector<float, 8> chess_storage(wc0) buf_matB;

                        buf_matA = *pA++;
                        buf_matB = *pB++;

                        acc1 = cur_bias;
                        acc2 = cur_bias;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        // acc1 = fpmul(buf_matA,0,0x00000000,buf_matB,0,0x76543210);
                        // acc2 = fpmul(buf_matA,4,0x00000000,buf_matB,0,0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        writeincr(partial_C, acc1);
                        writeincr(partial_C, acc2);

                        pB -= AIE_TILE_AB;
                      }
                    pB = pB + AIE_TILE_AB;
                    pA = pA - (AIE_TILE_A * AIE_TILE_AB / 8);
                  }

                matA.release();
                matB.release();
              }
            }
          }

          for (int k = 0; k < loop_k_iter; k++) {
            for (int access_a = 0; access_a < compute_tile_access_A; access_a++) {
              for (int access_b = 0; access_b < compute_tile_access_B; access_b++) {
                matA.acquire();
                matB.acquire();
                auto pA = begin_vector_random_circular<8>(matA);
                auto pB = begin_vector_random_circular<8>(matB);

#ifdef SW_EMU_PRINT
                // NOTE that different functions calls probably will be reordered
                if (print_code > 0) {
                  outFile << "no bias loop  " << std::endl;
                  outFile << "matA = " << std::endl;
                  auto pA_print = begin(matA);
                  for (int row = 0; row < 32; row++) {
                    for (int col = 0; col < 32; col++) {
                      float val = *pA_print++;
                      outFile << val << " ";
                    }
                    outFile << std::endl;
                  }
                  outFile << "matB = " << std::endl;
                  auto pB_print = begin(matB);
                  for (int row = 0; row < 32; row++) {
                    for (int col = 0; col < 32; col++) {
                      float val = *pB_print++;
                      outFile << val << " ";
                    }
                    outFile << std::endl;
                  }
                  outFile << std::endl;
                  outFile << std::endl;
                  outFile << std::endl;
                }
#endif

                for (int b = 0; b < b_round; b++)
                  chess_prepare_for_pipelining chess_loop_range(4, ) {
                    for (int i = 0; i < AIE_TILE_A / 2; i++)  // Each iteration computes 2 rows of C
                      chess_prepare_for_pipelining chess_unroll_loop(4) chess_loop_range(16, ) {
                        accum<accfloat, 8> chess_storage(wr2) acc1;
                        accum<accfloat, 8> chess_storage(wr3) acc2;
                        vector<float, 8> chess_storage(wr0) buf_matA;
                        vector<float, 8> chess_storage(wc0) buf_matB;

                        buf_matA = *pA++;
                        buf_matB = *pB++;

                        acc1 = fpmul(buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmul(buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        buf_matA = *pA++;
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                        buf_matB = *pB++;
                        acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                        acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                        writeincr(partial_C, acc1);
                        writeincr(partial_C, acc2);

                        pB -= AIE_TILE_AB;
                      }
                    pB = pB + AIE_TILE_AB;
                    pA = pA - (AIE_TILE_A * AIE_TILE_AB / 8);
                  }

                matA.release();
                matB.release();
              }
            }
          }
        }
      }
    } else {
      for (int r = 0; r < round; r++) {
        matA.acquire();
        matB.acquire();

#ifdef SW_EMU_PRINT
        if (print_code > 0) {
          outFile << "r = " << r << std::endl;
          outFile << "matA = " << std::endl;
          auto pA_print = begin(matA);
          for (int row = 0; row < 32; row++) {
            for (int col = 0; col < 32; col++) {
              float val = *pA_print++;
              outFile << val << " ";
            }
            outFile << std::endl;
          }
          outFile << "matB = " << std::endl;
          auto pB_print = begin(matB);
          for (int row = 0; row < 32; row++) {
            for (int col = 0; col < 32; col++) {
              float val = *pB_print++;
              outFile << val << " ";
            }
            outFile << std::endl;
          }
          outFile << std::endl;
          outFile << std::endl;
          outFile << std::endl;
        }
#endif

        auto pA = begin_vector_random_circular<8>(matA);
        auto pB = begin_vector_random_circular<8>(matB);

        for (int b = 0; b < (AIE_TILE_B / 8); b++)
          chess_prepare_for_pipelining chess_loop_range(4, ) {
            for (int i = 0; i < AIE_TILE_A / 2; i++)  // Each iteration computes 2 rows of C
              chess_prepare_for_pipelining chess_unroll_loop(4) chess_loop_range(16, ) {
                accum<accfloat, 8> chess_storage(wr2) acc1;
                accum<accfloat, 8> chess_storage(wr3) acc2;
                vector<float, 8> chess_storage(wr0) buf_matA;
                vector<float, 8> chess_storage(wc0) buf_matB;

                buf_matA = *pA++;
                buf_matB = *pB++;
                acc1 = fpmul(buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmul(buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                buf_matA = *pA++;
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                buf_matA = *pA++;
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                buf_matA = *pA++;
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 0, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 4, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 1, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 5, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 2, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 6, 0x00000000, buf_matB, 0, 0x76543210);
                buf_matB = *pB++;
                acc1 = fpmac(acc1, buf_matA, 3, 0x00000000, buf_matB, 0, 0x76543210);
                acc2 = fpmac(acc2, buf_matA, 7, 0x00000000, buf_matB, 0, 0x76543210);

                writeincr(partial_C, acc1);
                writeincr(partial_C, acc2);

                pB -= 16;
                pA += 4;
              }
            pB = pB + AIE_TILE_AB;
            pA = pA - (AIE_TILE_A * AIE_TILE_AB / 8);
          }

        matA.release();
        matB.release();
      }
    }
  }

#ifdef SW_EMU_PRINT
  if (print_code > 0) {
    outFile << "EXIT mm_casc_start ================= \n" << std::endl;
  }
  outFile.close();
#endif
}