// SPDX-FileCopyrightText: 2024 Takahiro Natsume ( @nuovotaka )
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>
#include "quantum.h"
#include "matrix.h"
#include "debounce.h"

#define PINNUM_ROW (MATRIX_ROWS)
#define ROWS_PER_HAND (MATRIX_ROWS)

#define PINNUM_COL (MATRIX_COLS / 2)

#define MATRIXSIZE_PER_HAND (ROWS_PER_HAND * sizeof(matrix_row_t))

#define MATRIX_INPUT_PRESSED_STATE 0

static pin_t row_pins[PINNUM_ROW] = MATRIX_ROW_PINS;
static pin_t col_pins[PINNUM_COL] = MATRIX_COL_PINS;

static inline void set_pin_input(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

static void set_pins_input(pin_t* pins, uint8_t n) {
    for (uint8_t i = 0; i < n; i++) {
        if (pins[i] != NO_PIN) {
            set_pin_input(pins[i]);
        }
    }
}

static inline void set_pin_output(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline bool read_pin(pin_t pin) {
    if (pin != NO_PIN) {
        return (gpio_read_pin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

__attribute__((weak)) void duplex_scan_post_kb(matrix_row_t current_matrix[]) {}

static void duplex_scan(matrix_row_t current_matrix[]) {
    // scan column to row
    for (uint8_t row = 0; row < PINNUM_ROW; row++) {
        if (row_pins[row] != NO_PIN) {
        set_pin_output(row_pins[row]);
        }
        matrix_output_select_delay();
        for (uint8_t col = 0; col < PINNUM_COL; col++) {
            if (!read_pin(col_pins[col])) {
                current_matrix[row] |= 1 << col;
            }
        }
        if (row_pins[row] != NO_PIN) {
        set_pin_input(row_pins[row]);
        }
        matrix_output_unselect_delay(row, false);
    }

    // scan row to column.
    matrix_row_t shifter = ((matrix_row_t)1) << PINNUM_COL;
    for (uint8_t col = 0; col < PINNUM_COL; col++, shifter <<= 1) {
        if (col_pins[col] != NO_PIN) {
        set_pin_output(col_pins[col]);
        }
        matrix_output_select_delay();
        for (uint8_t row = 0; row < PINNUM_ROW; row++) {
            if (!read_pin(row_pins[row])) {
                current_matrix[row] |= shifter;
            }
        }
        if (col_pins[col] != NO_PIN) {
        set_pin_input(col_pins[col]);
        }
        matrix_output_unselect_delay(col, false);
    }

    duplex_scan_post_kb(current_matrix);
}

void matrix_init_custom(void) {
    set_pins_input(col_pins, PINNUM_COL);
    set_pins_input(row_pins, PINNUM_ROW);
}

// declare matrix buffers which defined in quantum/matrix_common.c
extern matrix_row_t raw_matrix[MATRIX_ROWS];
extern matrix_row_t matrix[MATRIX_ROWS];

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    matrix_row_t tmp[MATRIX_ROWS] = {0};

    duplex_scan(tmp);
    for (uint8_t row = 0; row < PINNUM_ROW; row++) {
        if (tmp[row] != current_matrix[row]) {
            changed = true;
            current_matrix[row] = tmp[row];
        }
    }

    return changed;
}