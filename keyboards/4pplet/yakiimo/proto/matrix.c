/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "debug.h"
#include "matrix.h"

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_COLS];
static bool         debouncing      = false;
static uint16_t     debouncing_time = 0;

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

void matrix_init(void) {
    palSetPadMode(GPIOB, 0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 5, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 3, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 15, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 9, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(GPIOB, 10, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 1, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 13, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 14, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 14, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 12, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 9, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 8, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 4, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 15, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 3, PAL_MODE_INPUT_PULLDOWN);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // actual matrix
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;
        switch (col) {
            case 0:
                palSetPad(GPIOB, 0);
                break;
            case 1:
                palSetPad(GPIOA, 5);
                break;
            case 2:
                palSetPad(GPIOA, 4);
                break;
            case 3:
                palSetPad(GPIOA, 3);
                break;
            case 4:
                palSetPad(GPIOA, 2);
                break;
            case 5:
                palSetPad(GPIOA, 1);
                break;
            case 6:
                palSetPad(GPIOA, 0);
                break;
            case 7:
                palSetPad(GPIOC, 15);
                break;
            case 8:
                palSetPad(GPIOA, 9);
                break;
        }

        // need wait to settle pin state
        wait_us(20);
        // read row data { B10, B1, C13, C14, B14, B12, B9, B8, B5, B4, A15, B3  }
        data = ((palReadPad(GPIOB, 10) << 0) | (palReadPad(GPIOB, 1) << 1) | (palReadPad(GPIOC, 13) << 2) | (palReadPad(GPIOC, 14) << 3) | (palReadPad(GPIOB, 14) << 4) | (palReadPad(GPIOB, 12) << 5) | (palReadPad(GPIOB, 9) << 6) | (palReadPad(GPIOB, 8) << 7) | (palReadPad(GPIOB, 5) << 8) | (palReadPad(GPIOB, 4) << 9) | (palReadPad(GPIOA, 15) << 10) | (palReadPad(GPIOB, 3) << 11));
        // unstrobe  col { B0, A5, A4, A3, A2, A1, A0, C15, A9 }
        switch (col) {
            case 0:
                palClearPad(GPIOB, 0);
                break;
            case 1:
                palClearPad(GPIOA, 5);
                break;
            case 2:
                palClearPad(GPIOA, 4);
                break;
            case 3:
                palClearPad(GPIOA, 3);
                break;
            case 4:
                palClearPad(GPIOA, 2);
                break;
            case 5:
                palClearPad(GPIOA, 1);
                break;
            case 6:
                palClearPad(GPIOA, 0);
                break;
            case 7:
                palClearPad(GPIOC, 15);
                break;
            case 8:
                palClearPad(GPIOA, 9);
                break;
        }

        if (matrix_debouncing[col] != data) {
            matrix_debouncing[col] = data;
            debouncing             = true;
            debouncing_time        = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = 0;
            for (int col = 0; col < MATRIX_COLS; col++) {
                matrix[row] |= ((matrix_debouncing[col] & (1 << row) ? 1 : 0) << col);
            }
        }
        debouncing = false;
    }

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & (1 << col)); }

matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
    dprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        dprintf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1 << col))
                dprintf("1");
            else
                dprintf("0");
        }
        dprintf("\n");
    }
}
