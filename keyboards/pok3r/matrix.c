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

#include "pok3r.h"

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

static inline void init_row(ioportid_t portid, ioportmask_t portmask, size_t portoffset) {
    palWriteGroup(portid, portmask, portoffset, portmask);
    palSetGroupMode(portid, portmask, portoffset, PAL_MODE_OUTPUT_PUSHPULL|PAL_MODE_HT32_AF(AFIO_GPIO));
}

static inline void init_col(ioportid_t portid, ioportmask_t portmask, size_t portoffset) {
    palSetGroupMode(portid, portmask, portoffset, PAL_MODE_INPUT_PULLUP|PAL_MODE_HT32_AF(AFIO_GPIO));
}

void matrix_init(void) {

    /* rows, tmk "columns" */
    init_col(GPIO_A, 0x00f0, 0);	// A7-A4:	TEX Ro3,Ro2,Ro1,Ro4
    init_col(GPIO_C, 0xf000, 0);	// C15-C12	TEX Ro7,Ro6,Ro5,Ro0
    /* columns, tmk "rows" */
    init_row(GPIO_A, 0x080f, 0);	// A11,A3-A0	TEX Co4,Co8-Co5
    init_row(GPIO_B, 0x0840, 0);	// B11,B6	TEX Co3,Co1
    init_row(GPIO_C, 0x0018, 0);	// C4,C3	TEX Co0,Co9
    init_row(GPIO_D, 0x0001, 0);	// D0		TEX Co2
    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    /* Caps Lock LED */
    palSetLine(LINE_LED65);
    palSetLineMode(LINE_LED65, PAL_MODE_OUTPUT_PUSHPULL);

    /* not sure what this is, but the TEX firmware sets it as an output */
    palSetLine(LINE_PB0);
    palSetLineMode(LINE_PB0, PAL_MODE_OUTPUT_PUSHPULL);

    /* DIP switches */
    palSetGroupMode(GPIO_B, 0x003c, 0, PAL_MODE_INPUT_PULLUP);
    palSetGroupMode(GPIO_C, 0x0180, 0, PAL_MODE_INPUT_PULLUP);

    /* NOR Flash */
    palSetGroupMode(GPIO_B, 0x7, 7, PAL_MODE_HT32_AF(AFIO_SPI)); /* SPI1 */
    palSetLine(LINE_NORCE);
    palSetLineMode(LINE_NORCE, PAL_MODE_OUTPUT_PUSHPULL); /* CE/CS */

    matrix_init_quantum();
}

static matrix_row_t read_columns(void) {
    return (palReadGroup(GPIO_A, 0xf, 4) | (palReadGroup(GPIO_C, 0xf, 12) << 4));
}

static const ioline_t row_list[MATRIX_ROWS] = {
    LINE_COL1,
    LINE_COL2,
    LINE_COL3,
    LINE_COL4,
    LINE_COL5,
    LINE_COL6,
    LINE_COL7,
    LINE_COL8,
};

uint8_t matrix_scan(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data;

        palClearLine(row_list[row]);
        wait_us(20);
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

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    printf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("% 3u ", row);
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

