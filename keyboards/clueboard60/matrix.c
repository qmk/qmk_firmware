#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "printf.h"
#include "backlight.h"
#include "matrix.h"


/* Clueboard 60%
 *
 * Column pins are input with internal pull-down. 
 * Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { PA2, PA3, PA6, PB14, PB15, PA8, PA9, PA7, PB3, PB4, PC14, PC15, PC13, PB5, PB6 }
 *     row: { PB0, PB1, PB2, PA15, PA10 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;


void matrix_init(void) {
    printf("matrix init\n");
    //debug_matrix = true;

    /* Column(sense) */
    palSetPadMode(GPIOA, 2,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 6,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 14, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 15, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 8,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 9,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 7,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 4,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 14, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 15, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 13, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 5,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 6,  PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
    palSetPadMode(GPIOB, 0,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 1,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 15,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 10,  PAL_MODE_OUTPUT_PUSHPULL);

    memset(matrix, 0, MATRIX_ROWS);
    memset(matrix_debouncing, 0, MATRIX_ROWS);

    /* Setup capslock */
    palSetPadMode(GPIOB, 7,  PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOB, 7);
}

uint8_t matrix_scan(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;

        // strobe row { PB0, PB1, PB2, PA15, PA10 }
        switch (row) {
            case 0: palSetPad(GPIOB, 0);    break;
            case 1: palSetPad(GPIOB, 1);    break;
            case 2: palSetPad(GPIOB, 2);    break;
            case 3: palSetPad(GPIOA, 15);   break;
            case 4: palSetPad(GPIOA, 10);   break;
        }

        // need wait to settle pin state
        wait_us(20);

        // read col data { PA2, PA3, PA6, PB14, PB15, PA8, PA9, PA7, PB3, PB4, PC14, PC15, PC13, PB5, PB6 }
        data = (
            palReadPad(GPIOA, 2) << 0 |
            palReadPad(GPIOA, 3) << 1 |
            palReadPad(GPIOA, 6) << 2 |
            palReadPad(GPIOA, 14) << 3 |
            palReadPad(GPIOA, 15) << 4 |
            palReadPad(GPIOA, 8) << 5 |
            palReadPad(GPIOA, 9) << 6 |
            palReadPad(GPIOA, 7) << 7 |
            palReadPad(GPIOA, 3) << 8 |
            palReadPad(GPIOA, 4) << 9 |
            palReadPad(GPIOA, 14) << 10 |
            palReadPad(GPIOA, 15) << 11 |
            palReadPad(GPIOA, 13) << 12 |
            palReadPad(GPIOA, 5) << 13 |
            palReadPad(GPIOA, 6) << 14
        );

        // unstrobe row { PB0, PB1, PB2, PA15, PA10 }
        switch (row) {
            case 0: palClearPad(GPIOB, 0);    break;
            case 1: palClearPad(GPIOB, 1);    break;
            case 2: palClearPad(GPIOB, 2);    break;
            case 3: palClearPad(GPIOA, 15);   break;
            case 4: palClearPad(GPIOA, 10);   break;
        }

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
