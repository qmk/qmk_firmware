#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"


/*
 * Infinity Pinusage:
 * Column pins are input with internal pull-down. Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *  INFINITY PRODUCTION (NO LED)
 *     col: { PTD1, PTD2, PTD3, PTD4, PTD5, PTD6, PTD7 }
 *     row: { PTB0, PTB1, PTB2, PTB3, PTB16, PTB17, PTC4, PTC5, PTD0 }
 *  INFINITY PRODUCTION (WITH LED)
 *     col: { PTD1, PTD2, PTD3, PTD4, PTD5, PTD6, PTD7 }
 *     row: { PTC0, PTC1, PTC2, PTC3, PTC4, PTC5, PTC6, PTC7, PTD0 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;


void matrix_init(void)
{
    /* Column(sense) */
    palSetPadMode(GPIOD, 1,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 2,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 4,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 5,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 6,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 7,  PAL_MODE_INPUT_PULLDOWN);

#ifdef INFINITY_LED
    /* Row(strobe) */
    palSetPadMode(GPIOC, 0,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 1,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 2,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 3,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 4,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 5,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 6,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 7,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 0,  PAL_MODE_OUTPUT_PUSHPULL);
#else
    /* Row(strobe) */
    palSetPadMode(GPIOB, 0,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 1,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 3,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 16, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 17, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 4,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 5,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 0,  PAL_MODE_OUTPUT_PUSHPULL);
#endif
    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;
    #ifdef INFINITY_LED
        // strobe row
        switch (row) {
            case 0: palSetPad(GPIOC, 0);    break;
            case 1: palSetPad(GPIOC, 1);    break;
            case 2: palSetPad(GPIOC, 2);    break;
            case 3: palSetPad(GPIOC, 3);    break;
            case 4: palSetPad(GPIOC, 4);    break;
            case 5: palSetPad(GPIOC, 5);    break;
            case 6: palSetPad(GPIOC, 6);    break;
            case 7: palSetPad(GPIOC, 7);    break;
            case 8: palSetPad(GPIOD, 0);    break;
        }
    #else
        // strobe row
        switch (row) {
            case 0: palSetPad(GPIOB, 0);    break;
            case 1: palSetPad(GPIOB, 1);    break;
            case 2: palSetPad(GPIOB, 2);    break;
            case 3: palSetPad(GPIOB, 3);    break;
            case 4: palSetPad(GPIOB, 16);   break;
            case 5: palSetPad(GPIOB, 17);   break;
            case 6: palSetPad(GPIOC, 4);    break;
            case 7: palSetPad(GPIOC, 5);    break;
            case 8: palSetPad(GPIOD, 0);    break;
        }
    #endif

        // need wait to settle pin state
        // if you wait too short, or have a too high update rate
        // the keyboard might freeze, or there might not be enough
        // processing power to update the LCD screen properly.
        // 20us, or two ticks at 100000Hz seems to be OK
        wait_us(20);

        // read col data
        data = (palReadPort(GPIOD)>>1);
    #ifdef INFINITY_LED
        // un-strobe row
        switch (row) {
            case 0: palClearPad(GPIOC, 0);    break;
            case 1: palClearPad(GPIOC, 1);    break;
            case 2: palClearPad(GPIOC, 2);    break;
            case 3: palClearPad(GPIOC, 3);    break;
            case 4: palClearPad(GPIOC, 4);    break;
            case 5: palClearPad(GPIOC, 5);    break;
            case 6: palClearPad(GPIOC, 6);    break;
            case 7: palClearPad(GPIOC, 7);    break;
            case 8: palClearPad(GPIOD, 0);    break;
        }
    #else
        // un-strobe row
        switch (row) {
            case 0: palClearPad(GPIOB, 0);    break;
            case 1: palClearPad(GPIOB, 1);    break;
            case 2: palClearPad(GPIOB, 2);    break;
            case 3: palClearPad(GPIOB, 3);    break;
            case 4: palClearPad(GPIOB, 16);   break;
            case 5: palClearPad(GPIOB, 17);   break;
            case 6: palClearPad(GPIOC, 4);    break;
            case 7: palClearPad(GPIOC, 5);    break;
            case 8: palClearPad(GPIOD, 0);    break;
        }
    #endif

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
        xprintf("%02X: ");
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

__attribute__ ((weak))
void matrix_init_kb(void) {
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

