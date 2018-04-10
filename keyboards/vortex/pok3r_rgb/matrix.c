/*
 * Copyright (c) 2018 Charlie Waters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"

#include "vortex.h"

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

extern ioline_t row_list[MATRIX_ROWS];
extern ioline_t col_list[MATRIX_COLS];

static void sleep_cyc(uint32_t n) {
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    uint32_t cnt = DWT->CYCCNT + n;
    while(DWT->CYCCNT < cnt);
}

#define US2CYC(usec) (((((uint32_t)(usec)) * HT32_CK_AHB_FREQUENCY) + 999999UL) / 1000000UL)

void matrix_init(void) {
    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    for (int row = 0; row < MATRIX_ROWS; row++) {
        palSetLine(row_list[row]);
    }
    matrix_init_quantum();
}

static inline matrix_row_t read_columns(void) {
    matrix_row_t row = 0;
    // read each column
    for (int col = 0; col < MATRIX_COLS; ++col) {
        row |= ((palReadLine(col_list[col]) & 1) << col);
    }
    return row;
}

uint8_t matrix_scan(void) {
    // scan each row
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data;

        palClearLine(row_list[row]);
//        wait_us(20);
        sleep_cyc(US2CYC(1));
        data = ~read_columns();
        palSetLine(row_list[row]);

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }

//    matrix_print();

    matrix_scan_quantum();
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1 << col));
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    printf("\nr/c 123456789\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("  %u ", row+1);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col)) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }
}

