/**
 * matrix.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "quantum.h"
#include "timer.h"
#include "wait.h"
#include "printf.h"
#include "matrix.h"
#include "pjf.h"
#include "color.h"


/**
 * pjf keybaord
 * #define MATRIX_ROW_PINS { PA0, PA1, PA3, PA2, PA4, PA5}
 * #define MATRIX_COL_PINS { PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15}
 *
 * Row pins are output high in default states and will be strobed with low.
 * Column pins are input with internal pullup.
 * Key is low or 0 when it turns on.
 *
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static bool debouncing = false;
static uint16_t debouncing_time = 0;

void matrix_init(void) {
    printf("matrix init\n");
    // column
    palSetPadMode(GPIOC,  0, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC,  1, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC,  2, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC,  3, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC,  4, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC,  5, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC,  6, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC,  7, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC,  8, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC,  9, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC, 10, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC, 11, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC, 12, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC, 13, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC, 14, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC, 15, PAL_MODE_INPUT_PULLUP);

    // row
    palSetPadMode(GPIOA,  0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  3, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  4, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  5, PAL_MODE_OUTPUT_PUSHPULL);

    wait_us(30);
    palSetPad(GPIOA, 0);
    palSetPad(GPIOA, 1);
    palSetPad(GPIOA, 3);
    palSetPad(GPIOA, 2);
    palSetPad(GPIOA, 4);
    palSetPad(GPIOA, 5);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS* sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;
        switch(row) {
            case 0:
              palClearPad(GPIOA, 0);
              break;
            case 1:
              palClearPad(GPIOA, 1);
              break;
            case 2:
              palClearPad(GPIOA, 3);
              break;
            case 3:
              palClearPad(GPIOA, 2);
              break;
            case 4:
              palClearPad(GPIOA, 4);
              break;
            case 5:
              palClearPad(GPIOA, 5);
              break;
        }

        // need wait to settle pin state
        wait_us(20);

        data = (
            ((palReadPad(GPIOC,  0) ? 0 : 1)  <<  0 ) |
            ((palReadPad(GPIOC,  1) ? 0 : 1)  <<  1 ) |
            ((palReadPad(GPIOC,  2) ? 0 : 1)  <<  2 ) |
            ((palReadPad(GPIOC,  3) ? 0 : 1)  <<  3 ) |
            ((palReadPad(GPIOC,  4) ? 0 : 1)  <<  4 ) |
            ((palReadPad(GPIOC,  5) ? 0 : 1)  <<  5 ) |
            ((palReadPad(GPIOC,  6) ? 0 : 1)  <<  6 ) |
            ((palReadPad(GPIOC,  7) ? 0 : 1)  <<  7 ) |
            ((palReadPad(GPIOC,  8) ? 0 : 1)  <<  8 ) |
            ((palReadPad(GPIOC,  9) ? 0 : 1)  <<  9 ) |
            ((palReadPad(GPIOC, 10) ? 0 : 1)  << 10 ) |
            ((palReadPad(GPIOC, 11) ? 0 : 1)  << 11 ) |
            ((palReadPad(GPIOC, 12) ? 0 : 1)  << 12 ) |
            ((palReadPad(GPIOC, 13) ? 0 : 1)  << 13 ) |
            ((palReadPad(GPIOC, 14) ? 0 : 1)  << 14 ) |
            ((palReadPad(GPIOC, 15) ? 0 : 1)  << 15 )
        );

        switch(row) {
            case 0:
              palSetPad(GPIOA, 0);
              break;
            case 1:
              palSetPad(GPIOA, 1);
              break;
            case 2:
              palSetPad(GPIOA, 3);
              break;
            case 3:
              palSetPad(GPIOA, 2);
              break;
            case 4:
              palSetPad(GPIOA, 4);
              break;
            case 5:
              palSetPad(GPIOA, 5);
              break;
        }

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = 0;
            for (int col = 0; col < MATRIX_COLS; col++) {
                matrix[row] |= ((matrix_debouncing[row] & (1 << col) ? 1 : 0) << col);
            }
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
