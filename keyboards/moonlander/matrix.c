/*
Copyright 2018 Jack Humbert <jack.humb@gmail.com>

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
#include "printf.h"
#include "backlight.h"
#include "matrix.h"
#include "action.h"
#include "keycode.h"
#include <string.h>
#include "moonlander.h"
#include "i2c_master.h"

/*
#define MATRIX_ROW_PINS { B10, B11, B12, B13, B14, B15 } outputs
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6 }   inputs
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;
static bool debouncing_right = false;
static uint16_t debouncing_time_right = 0;

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

bool mcp23018_initd = false;
uint8_t mcp23018_tx[3];
uint8_t mcp23018_rx[1];

void mcp23018_init(void) {

    i2c_init();
    i2c_start(MCP23018_DEFAULT_ADDRESS << 1);

// #define MCP23_ROW_PINS { GPB5, GBP4, GBP3, GBP2, GBP1, GBP0 }       outputs
// #define MCP23_COL_PINS { GPA0, GBA1, GBA2, GBA3, GBA4, GBA5, GBA6 } inputs

    mcp23018_tx[0] = 0x00; // IODIRA
    mcp23018_tx[1] = 0x00; // ?
    mcp23018_tx[2] = 0b00111111; // A is inputs

    if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1,
        mcp23018_tx, 3, 100
    )) {
        printf("error hori\n");
    } else {
        mcp23018_tx[0] = 0x0C; // GPPUA
        mcp23018_tx[1] = 0x00; // ?
        mcp23018_tx[2] = 0b00111111; // pull-up As

        if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1,
            mcp23018_tx, 3, 100
        )) {
            printf("error hori\n");
        } else {
            mcp23018_initd = true;
        }
    }
}

void matrix_init(void) {
    printf("matrix init\n");
    //debug_matrix = true;

    // outputs
    palSetPadMode(GPIOB, 10,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 11,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 12,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 13,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 14,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 15,  PAL_MODE_OUTPUT_PUSHPULL);

    // inputs
    palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 2, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 3, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 6, PAL_MODE_INPUT_PULLDOWN);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    mcp23018_init();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {

    // actual matrix
    for (int row = 0; row < 6; row++) {
        matrix_row_t data = 0;

        // strobe row
        switch (row) {
            case 0: palSetPad(GPIOB, 10); break;
            case 1: palSetPad(GPIOB, 11); break;
            case 2: palSetPad(GPIOB, 12); break;
            case 3: palSetPad(GPIOB, 13); break;
            case 4: palSetPad(GPIOB, 14); break;
            case 5: palSetPad(GPIOB, 15); break;
        }

        // need wait to settle pin state
        wait_us(20);

        // read col data
        data = (
            (palReadPad(GPIOA, 0) << 0 ) |
            (palReadPad(GPIOA, 1) << 1 ) |
            (palReadPad(GPIOA, 2) << 2 ) |
            (palReadPad(GPIOA, 3) << 3 ) |
            (palReadPad(GPIOA, 4) << 4 ) |
            (palReadPad(GPIOA, 5) << 5 ) |
            (palReadPad(GPIOA, 6) << 6 )
        );

        // unstrobe  row
        switch (row) {
            case 0: palClearPad(GPIOB, 10); break;
            case 1: palClearPad(GPIOB, 11); break;
            case 2: palClearPad(GPIOB, 12); break;
            case 3: palClearPad(GPIOB, 13); break;
            case 4: palClearPad(GPIOB, 14); break;
            case 5: palClearPad(GPIOB, 15); break;
        }

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }



        // right side

        if (!mcp23018_initd) {
            printf("trying to init right\n");
            mcp23018_init();
        }

        // #define MCP23_ROW_PINS { GPB5, GBP4, GBP3, GBP2, GBP1, GBP0 }       outputs
        // #define MCP23_COL_PINS { GPA0, GBA1, GBA2, GBA3, GBA4, GBA5, GBA6 } inputs

        // select row

        mcp23018_tx[0] = 0x12; // GPIOA
        mcp23018_tx[1] = 0xFF & ~(1<<(row)); // activate row

        if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1,
            mcp23018_tx, 2, 100
        )) {
            printf("error hori\n");
        }

        // read col

        mcp23018_tx[0] = 0x13; // GPIOB

        if (MSG_OK != i2c_transmit_receive(MCP23018_DEFAULT_ADDRESS << 1,
            mcp23018_tx, 1,
            mcp23018_rx, 1
        )) {
            printf("error vert\n");
        }

        data = mcp23018_rx[0];

        if (matrix_debouncing[row + 6] != data) {
            matrix_debouncing[row + 6] = data;
            debouncing_right = true;
            debouncing_time_right = timer_read();
        }

    }


    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCING_DELAY) {
        for (int row = 0; row < 6; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }

    if (debouncing_right && timer_elapsed(debouncing_time_right) > DEBOUNCING_DELAY) {
        for (int row = 6; row < 12; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing_right = false;
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
        printf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}
