#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

#include "uno-matrix.h"

#define debug(X) NULL
#define debug_hex(X) NULL

#ifndef DEBOUNCE
#   define DEBOUNCE  5
#endif

static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    //debug_enable = true;
    //debug_matrix = true;
    //debug_mouse = true;
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        //Serial.println(cols, BIN);
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

// TODO update this comment
/* Column pin configuration
 * col: 0   1   2   3   4   5
 * pin: D3  D4  D5  D6  D7  B0
 */
static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
  DDRD  &= ~(1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7);
  PORTD |=  (1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7);

  DDRB  &= ~(1<<0);
  PORTB |=  (1<<0);
}

static matrix_row_t read_cols(void)
{
    return (PIND&(1<<3) ? 0 : (1<<0)) |
           (PIND&(1<<4) ? 0 : (1<<1)) |
           (PIND&(1<<5) ? 0 : (1<<2)) |
           (PIND&(1<<6) ? 0 : (1<<3)) |
           (PIND&(1<<7) ? 0 : (1<<4)) |
           (PINB&(1<<0) ? 0 : (1<<5));
}

/* Row pin configuration
 * row: 0  1  2  3
 * pin: C0 C1 C2 C3
 */
static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRC  &= ~0xF;
    PORTC &= ~0xF;
}

static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    switch (row) {
        case 0:
            DDRC  |= (1<<0);
            PORTC &= ~(1<<0);
            break;
        case 1:
            DDRC  |= (1<<1);
            PORTC &= ~(1<<1);
            break;
        case 2:
            DDRC  |= (1<<2);
            PORTC &= ~(1<<2);
            break;
        case 3:
            DDRC  |= (1<<3);
            PORTC &= ~(1<<3);
            break;
    }
}
