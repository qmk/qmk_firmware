// Copyright 2022 Manna Harbour (@manna-harbour)
// https://github.com/manna-harbour/xmk

// SPDX-License-Identifier: GPL-2.0-or-later

#include "xmk_matrix.h"

bool xmk_changed = false;
matrix_row_t xmk_rows[MATRIX_ROWS];

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  if (xmk_changed) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      current_matrix[row] = xmk_rows[row];
    }
    xmk_changed = false;
    return true;
  } else {
    return false;
  }
}

void xmk_matrix_key(bool press, uint8_t key) {
  dprintf("xmk_matrix_key: press: %s, key: %u\n", press?"true":"false", key);
  uint8_t row = key / MATRIX_COLS;
  if (row < MATRIX_ROWS) {
    uint8_t col = key % MATRIX_COLS;
    xmk_changed = true;
    if (press) {
      xmk_rows[row] |= (MATRIX_ROW_SHIFTER << col);
    } else {
      xmk_rows[row] &= ~(MATRIX_ROW_SHIFTER << col);
    }
  }
}
