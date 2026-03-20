// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "suspend.h"
#include "matrix.h"

extern matrix_row_t matrix_previous[MATRIX_ROWS];
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
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        wakeup_matrix[row] = matrix_get_row(row);
        wakeup |= wakeup_matrix[row] != 0;
    }

    return wakeup;
}

void update_matrix_state_after_wakeup(void) {
    matrix_power_up();
    matrix_scan();
    matrix_power_down();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        const matrix_row_t current_row = matrix_get_row(row);
        wakeup_matrix[row] |= current_row & ~matrix_previous[row];
        matrix_previous[row] |= current_row;
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
