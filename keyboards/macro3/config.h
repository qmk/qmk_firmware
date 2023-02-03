/* Copyright 2020 David Philip Barr <@davidphilipbarr>
 * Copyright 2021 @filterpaper
 * SPDX-License-Identifier: GPL-2.0+
 */

#pragma once

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

/* key matrix pins */
#define DIRECT_PINS {   \
    { D7, C6, D4, D1 }, \
    { B1, B4, B5, B3 }  \
}

#define ENCODERS_PAD_A { D2, F7 }
#define ENCODERS_PAD_B { D3, F6 }
