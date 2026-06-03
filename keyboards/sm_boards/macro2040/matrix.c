// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Macro2040 keyboard-level matrix scan override.
//
// Why this file exists
// --------------------
// QMK's default RP2040 matrix scan calls waitInputPinDelay() between
// driving a row LOW and reading the columns. That delay is computed
// from GPIO_INPUT_PIN_DELAY which defaults to about 31 CPU cycles
// (~250 ns at 125 MHz). On this PCB the row 3 trace (GP11) needs
// noticeably longer than that to settle from HIGH → LOW after a row
// is selected, so the column read happens before the line is stable
// and SW9 (the only key wired on row 3) is never detected.
//
// We tried setting `#define GPIO_INPUT_PIN_DELAY 12500` in config.h
// (= 100 µs at 125 MHz). It did not fix the issue on this hardware,
// presumably because the override is not honoured by the chibios
// platform headers in the order they get included for this build.
//
// As a keyboard-level fix we override QMK's weak
// matrix_read_cols_on_row() with a copy that uses an explicit
// `wait_us(100)` between selecting the row and reading the cols.
// 100 µs matches the working Arduino reference sketch and is plenty
// for any GPIO on this board to settle.
//
// This file is built unconditionally for the macro2040 keyboard
// (see keyboards/sm_boards/macro2040/rules.mk: `SRC += matrix.c`),
// so every keymap (default, via, custom user keymaps...) gets the
// fix automatically.

#include "quantum.h"
#include "matrix.h"
#include "wait.h"

// Local copies of the row/col pin arrays. We can't reference the
// `row_pins` / `col_pins` symbols in quantum/matrix.c because they
// are `static`, but the underlying MATRIX_ROW_PINS / MATRIX_COL_PINS
// macros are public so we can build identical arrays here.
static const pin_t macro2040_row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t macro2040_col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t current_row_value = 0;

    pin_t row_pin = macro2040_row_pins[current_row];
    if (row_pin == NO_PIN) return;

    // Drive the selected row LOW so any pressed key on this row pulls
    // its column input LOW through the matrix diode.
    gpio_set_pin_output(row_pin);
    gpio_write_pin_low(row_pin);
    wait_us(100);  // long enough for any GPIO on this PCB to settle

    // Each column is INPUT_PULLUP. A LOW reading means the key at this
    // [row, col] intersection is currently pressed.
    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
        if (gpio_read_pin(macro2040_col_pins[c]) == 0) {
            current_row_value |= (matrix_row_t)(1u << c);
        }
    }

    // Actively drive the row HIGH on the way out so it doesn't slowly
    // float back via the internal pullup before the next scan.
    gpio_write_pin_high(row_pin);

    current_matrix[current_row] = current_row_value;
}
