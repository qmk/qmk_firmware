#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"
#include QMK_KEYBOARD_H

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

static matrix_row_t matrix[MATRIX_ROWS];

// static matrix_row_t raw_matrix[MATRIX_ROWS];

// static uint8_t debounce_matrix[MATRIX_ROWS * MATRIX_COLS];
static matrix_row_t read_cols(uint8_t row);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void)
{

}

void matrix_init(void)
{
    mcp23017_init();

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
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

static matrix_row_t read_cols(uint8_t row)
{
    
}
static void init_cols(void)
{
    
}
static void unselect_rows(void)
{
    GPIOA->regs->BSRR = 0b1111111 << 8;
}
static void select_row(uint8_t row)
{
    
}
