#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"


/*
 * JM60
 * Column pins are input with internal pull-down. Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { PTA15, PTC10, PTC11, PTC12, PTD2, PTB3, PTB4, PTB5, PTB6, PTB7, PTB8, PTB9, PTA2, PTA3 }
 *     row: { PTB11, PTB10, PTB2, PTB1, PTB0}
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;


void matrix_init(void)
{
//debug_matrix = true;
    /* Column(sense) */
    palSetPadMode(GPIOA, 15,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 10,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 11,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 12,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 2,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 4,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 5,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 6,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 7,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 8,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 9,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 2,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 3,  PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
    palSetPadMode(GPIOB, 11,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 10,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 0,  PAL_MODE_OUTPUT_PUSHPULL);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));
}

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;

        // strobe row
        switch (row) {
            case 0: palSetPad(GPIOB, 11);    break;
            case 1: palSetPad(GPIOB, 10);    break;
            case 2: palSetPad(GPIOB, 2);   	break;
            case 3: palSetPad(GPIOB, 1);   break;
            case 4: palSetPad(GPIOB, 0);    break;
        }

        wait_us(20); // need wait to settle pin state

        // read col data: { PTA15, PTC10, PTC11, PTC12, PTD2, PTB3, PTB4, PTB5, PTB6, PTB7, PTB8, PTB9, PTA2, PTA3 }
        data = ((palReadPort(GPIOA) & 0x8000UL) >> 15) |	// 0
        	   ((palReadPort(GPIOC) & 0x1C00UL) >> 9) |		// 1, 2, 3
			   ((palReadPort(GPIOD) & 0x0004UL) << 2) |		// 4
			   ((palReadPort(GPIOB) & 0x03F8UL) << 2) |		// 5, 6, 7, 8, 9, 10, 11
			   ((palReadPort(GPIOA) & 0x000CUL) << 10);    // 12, 13

        // un-strobe row
        switch (row) {
        	case 0: palClearPad(GPIOB, 11);    break;
        	case 1: palClearPad(GPIOB, 10);    break;
        	case 2: palClearPad(GPIOB, 2);	  break;
        	case 3: palClearPad(GPIOB, 1);   break;
        	case 4: palClearPad(GPIOB, 0);    break;
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

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    xprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                xprintf("1");
            else
                xprintf("0");
        }
        xprintf("\n");
    }
}
