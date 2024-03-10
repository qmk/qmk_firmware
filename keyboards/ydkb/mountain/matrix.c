// Copyright 2023 Mathias Andersson (@Wraul)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

void pulse_registers(void) {
    writePinHigh(B1);
    asm("nop");
    writePinLow(B1);
}

void matrix_read_mode(void) {
    setPinInputHigh(B3);
    wait_us(5);
}

void matrix_write_mode(void) {
    setPinOutput(B3);
}

void reset_registers(void) {
    matrix_write_mode();
    for (uint8_t i = 0; i < 40; i++) {
        writePinHigh(B3);
        pulse_registers();
    }
    writePinLow(B3);
    pulse_registers();
    matrix_read_mode();
}

void shift_registers(void) {
    matrix_write_mode();
    writePinHigh(B3);
    pulse_registers();
    matrix_read_mode();
}

void matrix_init_custom(void) {
    setPinOutput(B1);
    setPinInputHigh(B2);
    setPinOutput(B3);

    writePinHigh(B1);
    writePinHigh(B3);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool         matrix_has_changed = false;
    matrix_row_t current_row_value;

    reset_registers();

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        current_row_value = 0;

        for (uint8_t current_col = 0; current_col < MATRIX_COLS / 2; current_col++) {
            /* Left hand scan (Bank U1) */
            if (!readPin(B3)) {
                current_row_value |= (matrix_row_t)1 << current_col;
            }
            /* Right hand scan (Bank U2) */
            if (!readPin(B2)) {
                current_row_value |= (matrix_row_t)1 << (current_col + 8);
            }
            shift_registers();
        }

        if (current_matrix[current_row] != current_row_value) {
            current_matrix[current_row] = current_row_value;
            matrix_has_changed          = true;
        }
    }

    return matrix_has_changed;
}
