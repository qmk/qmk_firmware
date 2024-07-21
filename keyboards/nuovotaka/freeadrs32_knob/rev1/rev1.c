// SPDX-FileCopyrightText: 2024 Takahiro Natsume ( @nuovotaka )
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "lib/freeadrs32/freeadrs32.h"

// clang-format off
matrix_row_t matrix_mask[MATRIX_ROWS] = {
//0でマスクされた交点は無視される
//  9876543210:column
  0b1111101111,
  0b1111101110,
  0b1111101111,
  0b1111101111,
};

// clang-format on
