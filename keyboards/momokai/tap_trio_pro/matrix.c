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
#include "debounce.h"
#include "scanfunctions.h"
#include "sma.c"

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

// Pin and key matrix definitions
pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
hybrid_key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};

static uint16_t pressedAdcValue = 0;
static uint16_t restAdcValue = 0;

/* Matrix state: 1 = on, 0 = off */
matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
matrix_row_t matrix[MATRIX_ROWS];     // debounced values

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

    matrix_init_pins();
    generate_lut();
    pressedAdcValue = distance_to_adc(400);
    restAdcValue = distance_to_adc(0);
    wait_ms(100); // Let ADC reach steady state
    get_sensor_offsets();
}

// User-defined overridable functions
__attribute__((weak)) void matrix_init_pins(void);
__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
__attribute__((weak)) void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter);




static matrix_row_t previous_matrix[MATRIX_ROWS];

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        if (!keys[current_row][0].is_analog) {
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

uint8_t matrix_scan(void) {
    bool changed = matrix_scan_custom(raw_matrix);
    changed = debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
    matrix_scan_kb();
    return (uint8_t)changed;
}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }
__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }
__attribute__((weak)) void matrix_init_user(void) {}
__attribute__((weak)) void matrix_scan_user(void) {}


