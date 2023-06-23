// Copyright 2018-2021
// ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
// David Philip Barr <@davidphilipbarr>
// Pierre Chevalier <pierrechevalier83@gmail.com>
// SPDX-License-Identifier: GPL-2.0+ 

#include "quantum.h"

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    // Left
    {{4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}},
    {{4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}},
    {{4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}},
    {{1, 7}, {0, 7}, {2, 7}, {3, 7}, {4, 7}},
    // Right
    {{4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
    {{4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
    {{4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
    {{1, 3}, {0, 3}, {2, 3}, {3, 3}, {4, 3}}
};
#endif
