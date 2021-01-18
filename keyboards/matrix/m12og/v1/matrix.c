/**
 * matrix.c
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
    setPinOutput(C0);
    setPinOutput(C1);
    setPinOutput(C2);
    setPinOutput(C3);
    setPinOutput(C4);
    setPinOutput(C5);
    setPinOutput(C6);
    setPinOutput(C7);
    setPinOutput(C8);
    setPinOutput(C9);
    setPinOutput(C10);
    setPinOutput(C11);
    setPinOutput(C12);
    setPinOutput(C13);
    setPinOutput(C14);
    setPinOutput(C15);

    setPinInputLow(A0);
    setPinInputLow(A1);
    setPinInputLow(A2);
    setPinInputLow(A3);
    setPinInputLow(A4);
    setPinInputLow(A5);

    writePinLow(C0);
    writePinLow(C1);
    writePinLow(C2);
    writePinLow(C3);
    writePinLow(C4);
    writePinLow(C5);
    writePinLow(C6);
    writePinLow(C7);
    writePinLow(C8);
    writePinLow(C9);
    writePinLow(C10);
    writePinLow(C11);
    writePinLow(C12);
    writePinLow(C13);
    writePinLow(C14);
    writePinLow(C15);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;
        switch (col) {
            case 0: writePinHigh(C0); break;
            case 1: writePinHigh(C1); break;
            case 2: writePinHigh(C2); break;
            case 3: writePinHigh(C3); break;
            case 4: writePinHigh(C4); break;
            case 5: writePinHigh(C5); break;
            case 6: writePinHigh(C6); break;
            case 7: writePinHigh(C7); break;
            case 8: writePinHigh(C8); break;
            case 9: writePinHigh(C9); break;
            case 10: writePinHigh(C10); break;
            case 11: writePinHigh(C11); break;
            case 12: writePinHigh(C12); break;
            case 13: writePinHigh(C13); break;
            case 14: writePinHigh(C14); break;
            case 15: writePinHigh(C15); break;
        }

        // need wait to settle pin state
        wait_us(20);

        data = (
            (readPin(A0) << 0 ) |
            (readPin(A1) << 1 ) |
            (readPin(A2) << 2 ) |
            (readPin(A3) << 3 ) |
            (readPin(A4) << 4 ) |
            (readPin(A5) << 5 )
        );

        switch (col) {
            case 0: writePinLow(C0); break;
            case 1: writePinLow(C1); break;
            case 2: writePinLow(C2); break;
            case 3: writePinLow(C3); break;
            case 4: writePinLow(C4); break;
            case 5: writePinLow(C5); break;
            case 6: writePinLow(C6); break;
            case 7: writePinLow(C7); break;
            case 8: writePinLow(C8); break;
            case 9: writePinLow(C9); break;
            case 10: writePinLow(C10); break;
            case 11: writePinLow(C11); break;
            case 12: writePinLow(C12); break;
            case 13: writePinLow(C13); break;
            case 14: writePinLow(C14); break;
            case 15: writePinLow(C15); break;
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
    // printf("\nr/c 01234567\n");
    // for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    //     printf("%X0: ", row);
    //     matrix_row_t data = matrix_get_row(row);
    //     for (int col = 0; col < MATRIX_COLS; col++) {
    //         if (data & (1<<col))
    //             printf("1");
    //         else
    //             printf("0");
    //     }
    //     printf("\n");
    // }
}
