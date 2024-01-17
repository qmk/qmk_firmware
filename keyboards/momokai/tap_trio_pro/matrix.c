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

pin_t         matrix_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;

hybrid_key_t         keys[MATRIX_ROWS][MATRIX_COLS]        = {0};

void matrix_init_custom(void) {
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
            keys[1][i].is_analog = true;
    }
    generate_lut();
    get_sensor_offsets();
    wait_ms(100); // Let ADC reach steady state
    get_sensor_offsets();
}

matrix_row_t previous_matrix[MATRIX_ROWS];

//matrix_row_t is an alias for u_int8_t


bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            hybrid_key_t *key = &keys[current_row][current_col];

            // TODO: current row has to be 1!!!!!!!!!!


            key->value = lut[analogReadPin(matrix_pins[current_row][current_col]) + key->offset];
            //limits our options, I would like to change hybrid_key_t to include weather it is a hall effect key

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
    return memcmp(previous_matrix, current_matrix, sizeof(previous_matrix)) != 0;
}
