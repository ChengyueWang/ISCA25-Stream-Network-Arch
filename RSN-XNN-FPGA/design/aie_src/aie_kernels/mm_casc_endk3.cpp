#include "aie_kernels.h"

float k3_local_buf[128] = {0.0};

void mm_casc_endk3(input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_A>>& __restrict matA,
                   input_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_B>>& __restrict matB,
                   output_async_buffer<float, adf::extents<NSAMPLES_WINDOW_F_C>>& __restrict matC,
                   input_cascade<accfloat>* __restrict partial_C, uint32_t (&opcode_mem)[512]) {
  uint32_t print_code = opcode_mem[0];
  uint32_t opcode_len = opcode_mem[1];

#ifdef SW_EMU_PRINT
  std::ofstream outFile("/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/aie" +
                            std::to_string(print_code) + "_mm_casc_end.txt",
                        std::ios_base::app);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file for writing." << std::endl;
  }

  if (print_code > 0) {
    outFile << "ENTER mm_casc_end =================== " << std::endl;
    outFile << " opcode_len = " << opcode_len << std::endl;
  }
  float k3_local_buf[128] = {0.0};
  for (int i = 0; i < 128; i++) {
    k3_local_buf[i] = 0.0;
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

    int round, accum_kiter, b_round;

    if (dimb_is_32 == 1) {
      b_round = 32 / 8;
    } else {
      b_round = 16 / 8;
    }

#ifdef SW_EMU_PRINT
    std::ofstream outFile(
        "/home/cw4/github/versal-float32/20-inputlen384/design/pl_src/output/aie" +
            std::to_string(print_code) + "_mm_casc_end.txt",
        std::ios_base::app);
    if (!outFile.is_open()) {
      std::cerr << "Unable to open file for writing." << std::endl;
    }
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
      outFile << "round = " << round << " accum_kiter = " << accum_kiter << " b_round = " << b_round
              << std::endl;
      outFile << "enable_muladd_pre_layer = " << enable_muladd_pre_layer << std::endl;
      outFile << "need_muladd_pre_layer_in_cur_aie = " << need_muladd_pre_layer_in_cur_aie
              << std::endl;
    }
#endif

    if (enable_load_pre_norm_weight == true) {
      matB.acquire();
      matB.release();
#ifdef SW_EMU_PRINT
      if (print_code > 0) {
        outFile << "before load_pre_norm_weight = " << std::endl;
        outFile << "k3_local_buf (declare inside kernel in simulation)= " << std::endl;
        auto local_buf_print = begin(k3_local_buf);
        for (int row = 0; row < 4; row++) {
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

      if (need_muladd_pre_layer_in_cur_aie == true) {
        auto ptrv8_local_buf = begin_vector_random_circular<8>(k3_local_buf);
        for (int i = 0; i < 128 / 8; i++) {  // always 1024 / 4 aie per core / 2 core = 128 weight
          vector<float, 8> temp = readincr_v<8>(partial_C);
          *ptrv8_local_buf = temp;
          ptrv8_local_buf++;
        }
      } else {
        auto ptrv8_local_buf = begin_vector_random_circular<8>(k3_local_buf);
        for (int i = 0; i < 128 / 8; i++) {  // always 1024 / 4 aie per core / 2 core = 128 weight
          vector<float, 8> temp = readincr_v<8>(partial_C);
          *ptrv8_local_buf = zeros<float, 8>();
          ptrv8_local_buf++;
        }
      }
#ifdef SW_EMU_PRINT
      if (print_code > 0) {
        outFile << "after load_pre_norm_weight = " << std::endl;
        outFile << "k3_local_buf = " << std::endl;
        auto local_buf_print = begin(k3_local_buf);
        for (int row = 0; row < 4; row++) {
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
    }

    if (enable_bias == true) {
      matB.acquire();
      matB.release();
    }

    if (enable_accum_kiter == 1) {
      round = compute_tile_access_B * compute_tile_access_A;
      accum_kiter = k_iter;
    } else {
      round = k_iter * compute_tile_access_B * compute_tile_access_A;
      accum_kiter = 1;
    }

    if (dimk_is_32 == 1) {
    L_AI:
      for (int ai = 0; ai < a_iter; ai++) {
      L_BI:
        for (int bi = 0; bi < b_iter; bi++) {
          if (enable_muladd_pre_layer == true) {
            for (int access_a = 0; access_a < compute_tile_access_A; access_a++) {
              for (int access_b = 0; access_b < compute_tile_access_B; access_b++) {
                matC.acquire();
                matA.acquire();
                auto pC = begin_vector_random_circular<8>(matC);
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

#ifdef SW_EMU_PRINT
                    if (print_code > 0) {
                      outFile << "local_buf_offset = " << local_buf_offset << std::endl;
                    }
#endif

                    auto ptrv8_local_buf = begin_vector_random_circular<8>(k3_local_buf);
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

                        vector<float, 8> acc_partial;
                        acc_partial = readincr_v<8>(partial_C);
                        acc1 = fpadd(acc1, acc_partial);
                        acc_partial = readincr_v<8>(partial_C);
                        acc2 = fpadd(acc2, acc_partial);
                        *pC++ = acc1;
                        *pC++ = acc2;
                      }
                  }

#ifdef SW_EMU_PRINT
                if (print_code > 0) {
                  outFile << "access_a = " << access_a << " access_b = " << access_b
                          << " ai = " << ai << " bi = " << bi << std::endl;
                  outFile << "matC.release(); = " << std::endl;
                  auto pC_print = begin(matC);
                  for (int row = 0; row < 32; row++) {
                    for (int col = 0; col < 32; col++) {
                      float val = *pC_print++;
                      outFile << val << " ";
                    }
                    outFile << std::endl;
                  }
                }
#endif

                matA.release();
                matC.release();
              }
            }
          }

          for (int r = 0; r < round; r++) {
            matC.acquire();
            auto pC = begin_vector_random_circular<8>(matC);
            matA.acquire();
            matB.acquire();
            auto pA = begin_vector_random_circular<8>(matA);
            auto pB = begin_vector_random_circular<8>(matB);

            for (int b = 0; b < b_round; b++) chess_prepare_for_pipelining chess_loop_range(4, ) {
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

                    vector<float, 8> chess_storage(wc1) acc_partial;
                    acc_partial = readincr_v<8>(partial_C);
                    acc1 = fpadd(acc1, acc_partial);
                    acc_partial = readincr_v<8>(partial_C);
                    acc2 = fpadd(acc2, acc_partial);
                    *pC++ = acc1;
                    *pC++ = acc2;
                    pB -= AIE_TILE_AB;
                  }
                pB = pB + AIE_TILE_AB;
                pA = pA - (AIE_TILE_A * AIE_TILE_AB / 8);
              }

#ifdef SW_EMU_PRINT
            if (print_code > 0) {
              if (r == 0) {
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

                outFile << "matC = " << std::endl;
                auto pC_print = begin(matC);
                for (int row = 0; row < 32; row++) {
                  for (int col = 0; col < 32; col++) {
                    float val = *pC_print++;
                    outFile << val << " ";
                  }
                  outFile << std::endl;
                }
              }
            }
#endif

            matA.release();
            matB.release();

            pC = pC - (AIE_TILE_A * b_round);

            for (int k_round = 1; k_round < accum_kiter; k_round++) {
              matA.acquire();
              matB.acquire();

              auto pA = begin_vector_random_circular<8>(matA);
              auto pB = begin_vector_random_circular<8>(matB);
              for (int b = 0; b < b_round; b++) chess_prepare_for_pipelining chess_loop_range(4, ) {
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

                      vector<float, 8> chess_storage(wd0) acc_partial;
                      acc_partial = readincr_v<8>(partial_C);
                      buf_matA = *pC;
                      acc1 = fpadd(acc1, buf_matA);
                      buf_matA = *(pC + 1);
                      acc2 = fpadd(acc2, buf_matA);

                      acc1 = fpadd(acc1, acc_partial);
                      acc_partial = readincr_v<8>(partial_C);
                      acc2 = fpadd(acc2, acc_partial);

                      *pC++ = acc1;
                      *pC++ = acc2;

                      pB -= AIE_TILE_AB;
                    }
                  pB = pB + AIE_TILE_AB;
                  pA = pA - (AIE_TILE_A * AIE_TILE_AB / 8);
                }

#ifdef SW_EMU_PRINT
              if (print_code > 0) {
                if (r == 0) {
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

                  outFile << "matC = " << std::endl;
                  auto pC_print = begin(matC);
                  for (int row = 0; row < 32; row++) {
                    for (int col = 0; col < 32; col++) {
                      float val = *pC_print++;
                      outFile << val << " ";
                    }
                    outFile << std::endl;
                  }
                }
              }
#endif

              matA.release();
              matB.release();
              pC = pC - (AIE_TILE_A * b_round);
            }

#ifdef SW_EMU_PRINT
            if (print_code > 0) {
              outFile << "matC.release(); = " << std::endl;
              auto pC_print = begin(matC);
              for (int row = 0; row < 32; row++) {
                for (int col = 0; col < 32; col++) {
                  float val = *pC_print++;
                  outFile << val << " ";
                }
                outFile << std::endl;
              }
            }
#endif

            matC.release();
          }
        }
      }

    } else {
      for (int r = 0; r < a_iter * b_iter * round; r++) {
        matC.acquire();
        auto pC = begin_vector_random_circular<8>(matC);
        matA.acquire();
        matB.acquire();
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

                vector<float, 8> chess_storage(wc1) acc_partial;
                acc_partial = readincr_v<8>(partial_C);
                acc1 = fpadd(acc1, acc_partial);
                acc_partial = readincr_v<8>(partial_C);
                acc2 = fpadd(acc2, acc_partial);
                *pC++ = acc1;
                *pC++ = acc2;
                pB -= 16;
                pA += 4;
              }
            pB = pB + AIE_TILE_AB;
            pA = pA - (AIE_TILE_A * AIE_TILE_AB / 8);
          }

#ifdef SW_EMU_PRINT
        if (print_code > 0) {
          if (r == 0) {
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

            outFile << "matC = " << std::endl;
            auto pC_print = begin(matC);
            for (int row = 0; row < 32; row++) {
              for (int col = 0; col < 32; col++) {
                float val = *pC_print++;
                outFile << val << " ";
              }
              outFile << std::endl;
            }
          }
        }
#endif

        matA.release();
        matB.release();
        matC.release();
      }
    }
  }

#ifdef SW_EMU_PRINT
  if (print_code > 0) {
    outFile << "EXIT mm_casc_start ================= \n" << std::endl;
    outFile.close();
  }
#endif
}