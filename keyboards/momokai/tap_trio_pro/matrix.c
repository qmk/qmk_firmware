/* Copyright 2023 RephlexZero (@RephlexZero)
   Copyright 2023 peepeetee
   SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "quantum.h"
#include "analog.h"
#include "lut.h"
#include "scanfunctions.h"
#include "quantum/matrix.h"


#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

// Pin and key matrix definitions
pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
hybrid_key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};

static uint16_t pressedAdcValue = 0;
static uint16_t restAdcValue = 0;


static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (gpio_read_pin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
        pin_t pin = matrix_pins[current_row][col_index];
        current_row_value |= readMatrixPin(pin) ? 0 : row_shifter;
    }

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}



// Setup only rows 1, leave row 0 untouched (for analog)
void matrix_init_pins(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        if (row != 0) {
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
    // Analog row setup (should ideally be done at compile time)
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        keys[0][i].is_analog = true;
        // initialize_SMA_filter(&keys[1][i], SMA_FILTER_SAMPLE_EXPONENT);
    }

    // eeconfig_init_kb();
    matrix_init_pins();
    generate_lut();
    pressedAdcValue = distance_to_adc(255);
    restAdcValue = distance_to_adc(0);
    wait_ms(100); // Let ADC reach steady state
    get_sensor_offsets();
}





static matrix_row_t previous_matrix[MATRIX_ROWS];

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        if (current_row == 1) {
            matrix_read_cols_on_row(current_matrix, current_row);
        } else {
            for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
                hybrid_key_t *key = &keys[current_row][current_col];
                key->value = lut[analogReadPin(matrix_pins[current_row][current_col]) + key->offset];

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
