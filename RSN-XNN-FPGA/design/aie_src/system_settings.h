#pragma once

/* Matrix Multiply C = A x B

Floating-Point case
  Dimensions
    A: Ra x Ca    With Ra = 2.ra   and Ca = 8.ca
    B: Rb x Cb    With  Rb = Ca (= 8.ca)  and Cb = 8.cb

    C: Ra x Cb
*/

// Floating point example
#define AIE_TILE_A 32
#define AIE_TILE_B 32
#define AIE_TILE_AB 32

// Window size
#define NSAMPLES_WINDOW_F_A (AIE_TILE_A * AIE_TILE_AB)
#define NSAMPLES_WINDOW_F_B (AIE_TILE_B * AIE_TILE_AB)
#define NSAMPLES_WINDOW_F_C (AIE_TILE_A * AIE_TILE_B)
