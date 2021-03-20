/**
 * matrix.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <hal.h>
#include "quantum.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"

/**
 *
 * Row pins are input with internal pull-down.
 * Column pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_COLS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

void matrix_init(void)
{
    //debug_enable = true;
    palSetLineMode(LINE_COL_1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_3, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_4, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_5, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_6, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_7, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_8, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_9, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_11, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_12, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_13, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_14, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_COL_15, PAL_MODE_OUTPUT_PUSHPULL);

    palSetLineMode(LINE_ROW_1, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(LINE_ROW_2, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(LINE_ROW_3, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(LINE_ROW_4, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(LINE_ROW_5, PAL_MODE_INPUT_PULLDOWN);

    palClearLine(LINE_COL_1);
    palClearLine(LINE_COL_2);
    palClearLine(LINE_COL_3);
    palClearLine(LINE_COL_4);
    palClearLine(LINE_COL_5);
    palClearLine(LINE_COL_6);
    palClearLine(LINE_COL_7);
    palClearLine(LINE_COL_8);
    palClearLine(LINE_COL_9);
    palClearLine(LINE_COL_10);
    palClearLine(LINE_COL_11);
    palClearLine(LINE_COL_12);
    palClearLine(LINE_COL_13);
    palClearLine(LINE_COL_14);
    palClearLine(LINE_COL_15);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;
        switch (col) {
            case 0: palSetLine(LINE_COL_1); break;
            case 1: palSetLine(LINE_COL_2); break;
            case 2: palSetLine(LINE_COL_3); break;
            case 3: palSetLine(LINE_COL_4); break;
            case 4: palSetLine(LINE_COL_5); break;
            case 5: palSetLine(LINE_COL_6); break;
            case 6: palSetLine(LINE_COL_7); break;
            case 7: palSetLine(LINE_COL_8); break;
            case 8: palSetLine(LINE_COL_9); break;
            case 9: palSetLine(LINE_COL_10); break;
            case 10: palSetLine(LINE_COL_11); break;
            case 11: palSetLine(LINE_COL_12); break;
            case 12: palSetLine(LINE_COL_13); break;
            case 13: palSetLine(LINE_COL_14); break;
            case 14: palSetLine(LINE_COL_15); break;
        }

        // need wait to settle pin state
        wait_us(20);

        data = (
            (palReadLine(LINE_ROW_1) << 0 ) |
            (palReadLine(LINE_ROW_2) << 1 ) |
            (palReadLine(LINE_ROW_3) << 2 ) |
            (palReadLine(LINE_ROW_4) << 3 ) |
            (palReadLine(LINE_ROW_5) << 4 )
        );

        switch (col) {
            case 0: palClearLine(LINE_COL_1); break;
            case 1: palClearLine(LINE_COL_2); break;
            case 2: palClearLine(LINE_COL_3); break;
            case 3: palClearLine(LINE_COL_4); break;
            case 4: palClearLine(LINE_COL_5); break;
            case 5: palClearLine(LINE_COL_6); break;
            case 6: palClearLine(LINE_COL_7); break;
            case 7: palClearLine(LINE_COL_8); break;
            case 8: palClearLine(LINE_COL_9); break;
            case 9: palClearLine(LINE_COL_10); break;
            case 10: palClearLine(LINE_COL_11); break;
            case 11: palClearLine(LINE_COL_12); break;
            case 12: palClearLine(LINE_COL_13); break;
            case 13: palClearLine(LINE_COL_14); break;
            case 14: palClearLine(LINE_COL_15); break;
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

bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & (1<<col)); }

matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void)
{
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
