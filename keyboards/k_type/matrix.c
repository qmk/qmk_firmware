//#include <stdint.h>
//#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"
#include "debug.h"

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

void matrix_init(void)
{
    debug_matrix = true;

    /* Column(sense) */
    palSetPadMode(GPIOD, 5,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 6,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 7,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 1,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 2,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 4,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 5,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 6,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 7,  PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
    palSetPadMode(GPIOB, 2,   PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 3,   PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 18,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 19,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 0,   PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 8,   PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 9,   PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 0,   PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 1,   PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 4,   PAL_MODE_OUTPUT_PUSHPULL);

    memset(matrix, 0, MATRIX_ROWS);
    memset(matrix_debouncing, 0, MATRIX_ROWS);

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;
        // strobe row
        switch (row) {
            case 0: palSetPad(GPIOB, 2);    break;
            case 1: palSetPad(GPIOB, 3);    break;
            case 2: palSetPad(GPIOB, 18);   break;
            case 3: palSetPad(GPIOB, 19);   break;
            case 4: palSetPad(GPIOC, 0);    break;
            case 5: palSetPad(GPIOC, 8);    break;
            case 6: palSetPad(GPIOC, 9);    break;
            case 7: palSetPad(GPIOD, 0);    break;
            case 8: palSetPad(GPIOD, 1);    break;
            case 9: palSetPad(GPIOD, 4);    break;
        }

        // need wait to settle pin state
        // if you wait too short, or have a too high update rate
        // the keyboard might freeze, or there might not be enough
        // processing power to update the LCD screen properly.
        // 20us, or two ticks at 100000Hz seems to be OK
        wait_us(20);

        // read col data: { PTD5, PTD6, PTD7, PTC1, PTC2, PTC3, PTC4, PTC5, PTC6, PTC7 }
        data = ((palReadPort(GPIOC) & 0xFEUL) << 2) |
               ((palReadPort(GPIOD) & 0xE0UL) >> 5);

        // un-strobe row
        switch (row) {
            case 0: palClearPad(GPIOB, 2);  break;
            case 1: palClearPad(GPIOB, 3);  break;
            case 2: palClearPad(GPIOB, 18); break;
            case 3: palClearPad(GPIOB, 19); break;
            case 4: palClearPad(GPIOC, 0);  break;
            case 5: palClearPad(GPIOC, 8);  break;
            case 6: palClearPad(GPIOC, 9);  break;
            case 7: palClearPad(GPIOD, 0);  break;
            case 8: palClearPad(GPIOD, 1);  break;
            case 9: palClearPad(GPIOD, 4);  break;
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

    matrix_scan_quantum();
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1 << col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    xprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                xprintf("1");
            else
                xprintf("0");
        }
        xprintf("\n");
    }

    wait_ms(50);
}
