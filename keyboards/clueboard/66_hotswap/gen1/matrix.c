#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "printf.h"
#include "matrix.h"
#include "action.h"
#include "keycode.h"
#include <string.h>

/*
 * #define MATRIX_ROW_PINS { PB11, PA6, PA3, PA2, PA1, PB5, PB6, PC15, PC14, PC13 }
 * #define MATRIX_COL_PINS { PB10, PB2, PB1, PB0, PA7, PB4, PB3, PB7 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_COLS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

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

void matrix_init(void) {
    printf("matrix init\n");
    //debug_matrix = true;

    // actual matrix setup
    palSetPadMode(GPIOB, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 1,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 0,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 7,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 4,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 3,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 7,  PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(GPIOB, 11, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 6,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 2, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 6, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 15,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 14,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 13,  PAL_MODE_INPUT_PULLDOWN);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // actual matrix
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;

        // strobe col { PB10, PB2, PB1, PB0, PA7, PB4, PB3, PB7 }
        switch (col) {
            case 0: palSetPad(GPIOB, 10); break;
            case 1: palSetPad(GPIOB, 2); break;
            case 2: palSetPad(GPIOB, 1); break;
            case 3: palSetPad(GPIOB, 0); break;
            case 4: palSetPad(GPIOA, 7); break;
            case 5: palSetPad(GPIOB, 4); break;
            case 6: palSetPad(GPIOB, 3); break;
            case 7: palSetPad(GPIOB, 7); break;
        }

        // need wait to settle pin state
        wait_us(20);

        // read row data { PB11, PA6, PA3, PA2, PA1, PB5, PB6, PC15, PC14, PC13 }
        data = (
            (palReadPad(GPIOB, 11) << 0 ) |
            (palReadPad(GPIOA, 6)  << 1 ) |
            (palReadPad(GPIOA, 3)  << 2 ) |
            (palReadPad(GPIOA, 2) << 3 ) |
            (palReadPad(GPIOA, 1) << 4 ) |
            (palReadPad(GPIOB, 5) << 5 ) |
            (palReadPad(GPIOB, 6) << 6 ) |
            (palReadPad(GPIOC, 15)  << 7 ) |
            (palReadPad(GPIOC, 14)  << 8 ) |
            (palReadPad(GPIOC, 13)  << 9 )
        );

        // unstrobe  col { B11, B10, B2, B1, A7, B0 }
        switch (col) {
            case 0: palClearPad(GPIOB, 10); break;
            case 1: palClearPad(GPIOB, 2); break;
            case 2: palClearPad(GPIOB, 1); break;
            case 3: palClearPad(GPIOB, 0); break;
            case 4: palClearPad(GPIOA, 7); break;
            case 5: palClearPad(GPIOB, 4); break;
            case 6: palClearPad(GPIOB, 3); break;
            case 7: palClearPad(GPIOB, 7); break;
        }

        if (matrix_debouncing[col] != data) {
            matrix_debouncing[col] = data;
            debouncing = true;
            debouncing_time = timer_read();
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

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint16_t row) {
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
