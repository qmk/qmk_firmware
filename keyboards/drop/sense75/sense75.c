// Copyright 2022 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
// top underglow sd2-sd17
    { 0, B_2,  A_2,  C_2  },
    { 0, B_3,  A_3,  C_3  },
    { 0, B_5,  A_5,  C_5  },
    { 0, B_6,  A_6,  C_6  },
    { 0, B_7,  A_7,  C_7  },
    { 0, B_9,  A_9,  C_9  },
    { 0, B_10, A_10, C_10 },
    { 0, B_12, A_12, C_12 },
    { 0, B_13, A_13, C_13 },
    { 0, B_14, A_14, C_14 },
    { 0, B_16, A_16, C_16 },
    { 1, B_12, A_12, C_12 },

// sd1 + function + sd18
    { 0, B_1,  A_1,  C_1  },
    { 0, E_2,  D_2,  F_2  },
    { 0, E_3,  D_3,  F_3  },
    { 0, E_4,  D_4,  F_4  },
    { 0, E_5,  D_5,  F_5  },
    { 0, E_6,  D_6,  F_6  },
    { 0, E_7,  D_7,  F_7  },
    { 0, E_8,  D_8,  F_8  },
    { 0, E_9,  D_9,  F_9  },
    { 0, E_10, D_10, F_10 },
    { 0, E_11, D_11, F_11 },
    { 0, E_12, D_12, F_12 },
    { 0, E_13, D_13, F_13 },
    { 0, E_14, D_14, F_14 },
    { 0, E_15, D_15, F_15 },
    // <enc gap>
    { 1, B_13, A_13, C_13 },

// sd45 + num + sd20
    { 0, H_1,  G_1,  I_1  },
    { 0, H_2,  G_2,  I_2  },
    { 0, H_3,  G_3,  I_3  },
    { 0, H_4,  G_4,  I_4  },
    { 0, H_5,  G_5,  I_5  },
    { 0, H_6,  G_6,  I_6  },
    { 0, H_7,  G_7,  I_7  },
    { 0, H_8,  G_8,  I_8  },
    { 0, H_9,  G_9,  I_9  },
    { 0, H_10, G_10, I_10 },
    { 0, H_11, G_11, I_11 },
    { 0, H_12, G_12, I_12 },
    { 0, H_13, G_13, I_13 },
    { 0, H_14, G_14, I_14 },
    { 0, H_15, G_15, I_15 },
    { 0, H_16, G_16, I_16 },
    { 1, B_15, A_15, C_15 },

// 44+ qwer 21
    { 0, K_1,  J_1,  L_1  },
    { 0, K_2,  J_2,  L_2  },
    { 0, K_3,  J_3,  L_3  },
    { 0, K_4,  J_4,  L_4  },
    { 0, K_5,  J_5,  L_5  },
    { 0, K_6,  J_6,  L_6  },
    { 0, K_7,  J_7,  L_7  },
    { 0, K_8,  J_8,  L_8  },
    { 0, K_9,  J_9,  L_9  },
    { 0, K_10, J_10, L_10 },
    { 0, K_11, J_11, L_11 },
    { 0, K_12, J_12, L_12 },
    { 0, K_13, J_13, L_13 },
    { 0, K_14, J_14, L_14 },
    { 0, K_15, J_15, L_15 },
    { 0, K_16, J_16, L_16 },
    { 1, B_16, A_16, C_16 },

// asdf
    { 1, B_2,  A_2,  C_2  },
    { 1, B_3,  A_3,  C_3  },
    { 1, B_4,  A_4,  C_4  },
    { 1, B_5,  A_5,  C_5  },
    { 1, B_6,  A_6,  C_6  },
    { 1, B_7,  A_7,  C_7  },
    { 1, B_8,  A_8,  C_8  },
    { 1, B_9,  A_9,  C_9  },
    { 1, B_10, A_10, C_10 },
    { 1, B_11, A_11, C_11 },
    { 1, E_12, D_12, F_12 },
    { 1, E_13, D_13, F_13 },
    { 1, E_14, D_14, F_14 },
    { 1, H_15, G_15, I_15 },

// 43 + zxcv + 22
    { 1, B_1,  A_1,  C_1  },
    { 1, E_2,  D_2,  F_2  },
    { 1, E_3,  D_3,  F_3  },
    { 1, E_4,  D_4,  F_4  },
    { 1, E_5,  D_5,  F_5  },
    { 1, E_6,  D_6,  F_6  },
    { 1, E_7,  D_7,  F_7  },
    { 1, E_8,  D_8,  F_8  },
    { 1, E_9,  D_9,  F_9  },
    { 1, E_10, D_10, F_10 },
    { 1, E_11, D_11, F_11 },
    { 1, H_12, G_12, I_12 },
    { 1, H_13, G_13, I_13 },
    { 1, H_14, G_14, I_14 },
    { 1, E_15, D_15, F_15 },

// 41 + mods + 23
    { 1, H_1,  G_1,  I_1  },
    { 1, H_2,  G_2,  I_2  },
    { 1, H_3,  G_3,  I_3  },
    { 1, H_4,  G_4,  I_4  },
    { 1, H_5,  G_5,  I_5  },
    { 1, H_6,  G_6,  I_6  },
    { 1, H_7,  G_7,  I_7  },
    { 1, H_8,  G_8,  I_8  },
    { 1, H_9,  G_9,  I_9  },
    { 1, H_10, G_10, I_10 },
    { 1, H_11, G_11, I_11 },
    { 1, E_16, D_16, F_16 },

// bottom underglow 24 - 39
    { 1, K_2,  J_2,  L_2  },
    { 1, K_3,  J_3,  L_3  },
    { 1, K_4,  J_4,  L_4  },
    { 1, K_6,  J_6,  L_6  },
    { 1, K_10, J_10, L_10 },
    { 1, K_13, J_13, L_13 },
    { 1, K_15, J_15, L_15 },
    { 1, H_16, G_16, I_16 }
};
#endif
