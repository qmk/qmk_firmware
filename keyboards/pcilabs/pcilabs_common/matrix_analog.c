/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "analogkeys.h"
#include "config.h"
#include "quantum.h"
#include "custom_analog.h"
#include "lut.h"
#include "scanfunctions.h"
#include <ch.h>
#include <hal.h>
#include "gpio.h"
#include "sma.h"
#include "rawhid.h";

#if MUXES == 0
pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
#endif

analog_key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};

void matrix_init_common(void){
    generate_lut();
    lut_init();
    key_init();
    get_sensor_offsets();
    wait_ms(500);
    get_sensor_offsets();
    SMA_init();
}

__attribute__((weak)) void matrix_init_custom(void) {
    matrix_init_common();
}

matrix_row_t previous_matrix[MATRIX_ROWS];

#if MUXES == 0
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            analog_key_t *key = &keys[current_row][current_col];
            key->raw = analogReadPin(matrix_pins[current_row][current_col]);
            SMA_filter(key);
            key->value = (*key->lut)[key->offset + key->raw];
            matrix_read_mode_array[key->mode](&current_matrix[current_row], current_col, key);
            raw_hid_send_debug_key_state(current_row, current_col, key->raw, key->value, &current_matrix[current_row] & (1 << current_col));
        }
    }
    return memcmp(previous_matrix, current_matrix, sizeof(previous_matrix)) != 0;
}
#endif
