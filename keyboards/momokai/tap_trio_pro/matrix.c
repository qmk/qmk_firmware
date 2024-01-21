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

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;

hybrid_key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};

void matrix_init_custom(void) {

    wait_ms(3500); //give time to try to have hid_listen spin up

    printf("%s\n", "test print at start of matrix init");
    wait_ms(250);


    // printf("%s\n", "2nd test print at start of matrix init");
    // wait_ms(250);
    // printf("%u\n", MATRIX_COLS);
    // wait_ms(250);
    // printf("%u\n", MATRIX_ROWS);
    // wait_ms(250);
    // for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    //     for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    //         printf("%lu\n", matrix_pins[row][col]);
    //         wait_ms(250);
    //     }
    //     wait_ms(250);
    //     printf("\n");
    // }

    // wait_ms(250);



    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        keys[1][i].is_analog = true;
    }

    // for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    //     for (uint8_t col = 0; col < MATRIX_COLS; col++) {

    //         printf("keys[%u][%u].value = %u\n", row, col, keys[row][col].value);
    //         wait_ms(250);
    //         printf("keys[%u][%u].extremum = %u\n", row, col, keys[row][col].extremum);
    //         wait_ms(250);
    //         printf("keys[%u][%u].offset = %u\n", row, col, keys[row][col].offset);
    //         wait_ms(250);
    //         printf("keys[%u][%u].is_analog = %s\n", row, col, keys[row][col].is_analog ? "true" : "false");
    //         wait_ms(250);
    //         printf("keys[%u][%u].dynamic_actuation_bool = %s\n", row, col, keys[row][col].dynamic_actuation_bool ? "true" : "false");
    //     }
    //     wait_ms(250);
    //     printf("\n");
    // }

    generate_lut();
    get_sensor_offsets();
    wait_ms(200); // Let ADC reach steady state
    get_sensor_offsets();
}

matrix_row_t previous_matrix[MATRIX_ROWS];

// matrix_row_t is an alias for u_int8_t

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (readPin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
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

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        if (keys[current_row][0].is_analog == false) {
            // matrix_read_cols_on_row(current_matrix, current_row);

        }

        else {
            for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
                hybrid_key_t *key = &keys[current_row][current_col];

                // TODO: current row has to be 1!!!!!!!!!!

                key->value = lut[analogReadPin(matrix_pins[current_row][current_col]) + key->offset];
                // limits our options, I would like to change hybrid_key_t to include weather it is a hall effect key

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
