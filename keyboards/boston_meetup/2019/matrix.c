#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "printf.h"
#include "backlight.h"
#include "matrix.h"
#include "action.h"
#include "keycode.h"

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_COLS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

static uint8_t encoder_state = 0;
static int8_t encoder_value = 0;
static int8_t encoder_LUT[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };

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

    // encoder setup
    palSetPadMode(GPIOB, 13, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOB, 14, PAL_MODE_INPUT_PULLUP);

    encoder_state = (palReadPad(GPIOB, 13) << 0) | (palReadPad(GPIOB, 14) << 1);

    // actual matrix setup
    palSetPadMode(GPIOA, 7,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 8,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 10, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(GPIOA, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 8,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 9,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 1,  PAL_MODE_INPUT_PULLDOWN);


    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));


    matrix_init_quantum();
}

__attribute__ ((weak))
void encoder_update(bool clockwise) { }

#ifndef ENCODER_RESOLUTION
  #define ENCODER_RESOLUTION 4
#endif

uint8_t matrix_scan(void) {
    // encoder on B13 and B14
    encoder_state <<= 2;
    encoder_state |= (palReadPad(GPIOB, 13) << 0) | (palReadPad(GPIOB, 14) << 1);
    encoder_value += encoder_LUT[encoder_state & 0xF];
    if (encoder_value >= ENCODER_RESOLUTION) {
        encoder_update(0);
    }
    if (encoder_value <= -ENCODER_RESOLUTION) { // direction is arbitrary here, but this clockwise
        encoder_update(1);
    }
    encoder_value %= ENCODER_RESOLUTION;

    // actual matrix
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;

        // strobe col { A7, A8, B2, B10 }
        switch (col) {
            case 0:  palSetPad(GPIOA, 7); break;
            case 1:  palSetPad(GPIOA, 8); break;
            case 2:  palSetPad(GPIOB, 2); break;
            case 3:  palSetPad(GPIOB, 10); break;
        }

        // need wait to settle pin state
        wait_us(20);

        // read row data { A3, B8, B9, B1 }
        data = (
            (palReadPad(GPIOA, 3)  << 0 ) |
            (palReadPad(GPIOB, 8)  << 1 ) |
            (palReadPad(GPIOB, 9)  << 2 ) |
            (palReadPad(GPIOB, 1)  << 3 )
        );

        // unstrobe  col { A7, A8, B2, B10 }
        switch (col) {
            case 0:  palClearPad(GPIOA, 7); break;
            case 1:  palClearPad(GPIOA, 8); break;
            case 2:  palClearPad(GPIOB, 2); break;
            case 3:  palClearPad(GPIOB, 10); break;
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
