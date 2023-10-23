/* Copyright 2023 RephlexZero (@RephlexZero) peepeetee (@peepeetee)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "print.h"
#include "quantum.h"
#include "analog.h"
#include "lut.h"
#include "scanfunctions.h"

pin_t         matrix_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;

key_t         keys[MATRIX_ROWS][MATRIX_COLS]        = {0};


#    define ROWS_PER_HAND (MATRIX_ROWS)

extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values


void matrix_init_pins(void) {
    //default implementation for rows 0 and 2 only
    for (int row = 0; row < ROWS_PER_HAND; row++) {
        if (row != 1){
            for (int col = 0; col < MATRIX_COLS; col++) {
                pin_t pin = matrix_pins[row][col];
                if (pin != NO_PIN) {
                    setPinInputHigh(pin);
                }
            }
        }
    }
}

void matrix_init_custom(void) {
    generate_lut();
    get_sensor_offsets();
    wait_ms(100); // Let ADC reach steady state
    get_sensor_offsets();




    //default implementation for rows 0 and 2
    matrix_init_pins();

    // initialize matrix state: all keys off
    memset(matrix, 0, sizeof(matrix));
    memset(raw_matrix, 0, sizeof(raw_matrix));

    // debounce_init(ROWS_PER_HAND);

    // matrix_init_kb();
}

matrix_row_t previous_matrix[MATRIX_ROWS];

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (readPin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        if (current_row != 1) {
            //default implementation for rows 0 and 2
            for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
                    // Start with a clear matrix row
                    matrix_row_t current_row_value = 0;

                    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
                    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
                        // pin_t pin = direct_pins[current_row][col_index];
                        pin_t pin = matrix_pins[current_row][col_index];

                        current_row_value |= readMatrixPin(pin) ? 0 : row_shifter;
                    }

                    // Update the matrix
                    current_matrix[current_row] = current_row_value;
            }
        }
        if (current_row == 1) {
            //use ADC for row 1
            for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            key_t *key = &keys[current_row][current_col];
            key->value = lut[analogReadPin(matrix_pins[current_row][current_col]) + key->offset];
            key->value = MIN((key->value << 8) / lut[1100 + key->offset], 255);

            switch (g_config.mode) {
                case dynamic_actuation:
                    matrix_read_cols_dynamic_actuation(&current_matrix[current_row], current_col, key);
                    break;
                case continuous_dynamic_actuation:
                    matrix_read_cols_continuous_dynamic_actuation(&current_matrix[current_row], current_col, key);
                    break;
                case static_actuation:
                    matrix_read_cols_static_actuation(&current_matrix[current_row], current_col, key);
                    break;
                case flashing:
                default:
                    bootloader_jump();
                    break;
            }
        }
        }

    }
    return memcmp(previous_matrix, current_matrix, sizeof(previous_matrix)) != 0;
}
