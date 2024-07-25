// SPDX-FileCopyrightText: 2024 Takahiro Natsume ( @nuovotaka )
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "rev1.h"

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

bool oled_task_user(void) {
    oledkit_render_mylogo();
    free32knob_oled_render_keyinfo();
    free32knob_oled_render_layerinfo();
    return false;
}