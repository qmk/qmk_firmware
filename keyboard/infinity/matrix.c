#include <stdint.h>
#include <stdbool.h>
#include "gpio_api.h"
#include "timer.h"
#include "wait.h"
#include "matrix.h"


#ifndef DEBOUNCE
#define DEBOUNCE    5
#endif

/*
 * Infinity Pinusage:
 * Column pins are input with internal pull-down. Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { PTD1, PTD2, PTD3, PTD4, PTD5, PTD6, PTD7 }
 *     row: { PTB0, PTB1, PTB2, PTB3, PTB16, PTB17, PTC4, PTC5, PTD0 }
 */
static gpio_t col[MATRIX_COLS];
static gpio_t row[MATRIX_ROWS];

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;


void matrix_init(void)
{
    /* Column(sense) */
    gpio_init_in_ex(&col[0], PTD1, PullDown);
    gpio_init_in_ex(&col[1], PTD2, PullDown);
    gpio_init_in_ex(&col[2], PTD3, PullDown);
    gpio_init_in_ex(&col[3], PTD4, PullDown);
    gpio_init_in_ex(&col[4], PTD5, PullDown);
    gpio_init_in_ex(&col[5], PTD6, PullDown);
    gpio_init_in_ex(&col[6], PTD7, PullDown);

    /* Row(strobe) */
    gpio_init_out_ex(&row[0], PTB0, 0);
    gpio_init_out_ex(&row[1], PTB1, 0);
    gpio_init_out_ex(&row[2], PTB2, 0);
    gpio_init_out_ex(&row[3], PTB3, 0);
    gpio_init_out_ex(&row[4], PTB16, 0);
    gpio_init_out_ex(&row[5], PTB17, 0);
    gpio_init_out_ex(&row[6], PTC4, 0);
    gpio_init_out_ex(&row[7], PTC5, 0);
    gpio_init_out_ex(&row[8], PTD0, 0);
}

uint8_t matrix_scan(void)
{
    for (int i = 0; i < MATRIX_ROWS; i++) {
        matrix_row_t r = 0;

        gpio_write(&row[i], 1);
        wait_us(1); // need wait to settle pin state
        for (int j = 0; j < MATRIX_COLS; j++) {
            if (gpio_read(&col[j])) {
                r |= (1<<j);
            }
        }
        gpio_write(&row[i], 0);

        if (matrix_debouncing[i] != r) {
            matrix_debouncing[i] = r;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int i = 0; i < MATRIX_ROWS; i++) {
            matrix[i] = matrix_debouncing[i];
        }
        debouncing = false;
    }
/*
    if (debouncing) {
        if (--debouncing) {
            return 0;
        } else {
            for (int i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }
*/
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
}
