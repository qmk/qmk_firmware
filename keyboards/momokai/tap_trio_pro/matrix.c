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
// #include "matrix_helpers.c"

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif


// //configuration for the SMA filter, default is 4 for 2^4 = 16 samples
// #ifndef SMA_FILTER_SAMPLE_EXPONENT
// #    define SMA_FILTER_SAMPLE_EXPONENT 4
// #endif

pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;

hybrid_key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};

static uint16_t pressedAdcValue = 0;
static uint16_t restAdcValue = 0;

/* matrix state(1:on, 0:off) */
matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
matrix_row_t matrix[MATRIX_ROWS];     // debounced values




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
        //should really be done at compile time
        // initialize_SMA_filter(keys[1][i], SMA_FILTER_SAMPLE_EXPONENT);
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
    pressedAdcValue = distance_to_adc(400);
    restAdcValue = distance_to_adc(0);
    // get_sensor_offsets();
    wait_ms(200); // Let ADC reach steady state
    get_sensor_offsets();
}



//setup only rows 0 and 2, leave row 1 untouched
__attribute__((weak)) void matrix_init_pins(void) {
    // if (keys[row][0].is_analog == false)
    for (int row = 0; row < MATRIX_ROWS; row++) {
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

// user-defined overridable functions
__attribute__((weak)) void matrix_init_pins(void);
__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
__attribute__((weak)) void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter);


// static inline uint8_t readMatrixPin(pin_t pin) {
//     if (pin != NO_PIN) {
//         return (readPin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
//     } else {
//         return 1;
//     }
// }

matrix_row_t matrix_get_row(uint8_t row) {

    // TODO: return the requested row data
    //matrix_common.c row 68

    return matrix[row];
}


#    define print_matrix_header() print("\nr/c 01234567\n")
#    define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))

void matrix_print(void) {
    // TODO: use print() to dump the current matrix state to console
    //matrix_common.c row 84

    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_matrix_row(row);
        print("\n");
    }

}


void matrix_init(void) {
    // TODO: initialize hardware and global matrix state here
    //matrix.c row 274
    //matrix_common.c row 149


    // initialize key pins
    matrix_init_pins();
    matrix_init_custom();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    // Unless hardware debouncing - Init the configured debounce routine
    // debounce_init(MATRIX_ROWS);

    // This *must* be called for correct keyboard behavior
    matrix_init_kb();
}



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

matrix_row_t previous_matrix[MATRIX_ROWS];

bool matrix_scan_custom(matrix_row_t current_matrix[]) {


    // matrix_row_t is an alias for u_int8_t

    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        if (keys[current_row][0].is_analog == false) {
            matrix_read_cols_on_row(current_matrix, current_row);
            
        } else {
            for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
                hybrid_key_t *key = &keys[current_row][current_col];

                // TODO: current row has to be 1!!!!!!!!!!

                key->value = lut[analogReadPin(matrix_pins[current_row][current_col]) + key->offset];
                // limits our options, I would like to change hybrid_key_t to include weather it is a hall effect key

                // key->value = MIN((key->value << 8) / lut[1100 + key->offset], 400);

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
    // TODO: add matrix scanning routine here
    //matrix.c row 324
    //matrix_common.c row 169

    bool changed = matrix_scan_custom(raw_matrix);

    // Unless hardware debouncing - use the configured debounce routine
    changed = debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    // This *must* be called for correct keyboard behavior
    matrix_scan_kb();

    return (uint8_t)changed;
}


__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}


