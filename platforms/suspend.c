// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "suspend.h"
#include "matrix.h"

static matrix_row_t wakeup_matrix[MATRIX_ROWS];

// TODO: Move to more correct location
__attribute__((weak)) void matrix_power_up(void) {}
__attribute__((weak)) void matrix_power_down(void) {}

/** \brief Run user level Power down
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_power_down_user(void) {}

/** \brief Run keyboard level Power down
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_power_down_kb(void) {
    suspend_power_down_user();
}

/** \brief run user level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_wakeup_init_user(void) {}

/** \brief run keyboard level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_wakeup_init_kb(void) {
    suspend_wakeup_init_user();
}

/** \brief suspend wakeup condition
 *
 * FIXME: needs doc
 */
bool suspend_wakeup_condition(void) {
    matrix_power_up();
    matrix_scan();
    matrix_power_down();

    bool wakeup = false;
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        wakeup_matrix[r] = matrix_get_row(r);
        wakeup |= wakeup_matrix[r] != 0;
    }

    return wakeup;
}

void wakeup_matrix_update(void) {
    matrix_power_up();
    matrix_scan();
    matrix_power_down();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t matrix_row = matrix_get_row(row);
        matrix_row_t col_mask   = 1;
        for (uint8_t col = 0; col < MATRIX_COLS; col++, col_mask <<= 1) {
            wakeup_matrix_handle_key_event(row, col, matrix_row & col_mask);
        }
    }
}

bool keypress_is_wakeup_key(uint8_t row, uint8_t col) {
    return (wakeup_matrix[row] & ((matrix_row_t)1 << col));
}

void wakeup_matrix_handle_key_event(uint8_t row, uint8_t col, bool pressed) {
    if (!pressed) {
        wakeup_matrix[row] &= ~((matrix_row_t)1 << col);
    }
}
