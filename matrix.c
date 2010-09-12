/*
 * scan matrix
 */
#include <avr/io.h>
#include <util/delay.h>
#include "keymap.h"
#include "matrix.h"
#include "print.h"

// matrix is active low. (key on: 0/key off: 1)
// row: Hi-Z(unselected)/low output(selected)
//      PD:0,1,2,3,6,7/PC:6,7/PF:7
// col: input w/pullup
//      PB:0-8

// matrix state buffer
uint8_t *matrix;
uint8_t *matrix_prev;
static uint8_t _matrix0[MATRIX_ROWS];
static uint8_t _matrix1[MATRIX_ROWS];

static uint8_t read_col(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


// this must be called once before matrix_scan.
void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    DDRB = 0x00;
    PORTB = 0xFF;

    // initialize matrix state: all keys off
    for (int i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0xFF;
    for (int i=0; i < MATRIX_ROWS; i++) _matrix1[i] = 0xFF;
    matrix = _matrix0;
    matrix_prev = _matrix1;
}

uint8_t matrix_scan(void)
{
    uint8_t row, state;
    uint8_t *tmp;

    tmp = matrix_prev;
    matrix_prev = matrix;
    matrix = tmp;

    for (row = 0; row < MATRIX_ROWS; row++) {
        select_row(row);
        _delay_us(30);  // without this wait read unstable value.
        state = read_col();
        unselect_rows();

        matrix[row] = state;
    }
    return 1;
}

bool matrix_is_modified(void) {
    for (int i=0; i <MATRIX_ROWS; i++) {
        if (matrix[i] != matrix_prev[i])
            return true;
    }
    return false;
}

bool matrix_has_ghost(void) {
    for (int i=0; i <MATRIX_ROWS; i++) {
        if (matrix_has_ghost_in_row(i))
            return true;
    }
    return false;
}

bool matrix_has_ghost_in_row(uint8_t row) {
    uint8_t state = ~matrix[row];
    // no ghost exists in case less than 2 keys on
    if (((state - 1) & state) == 0)
        return false;

    // ghost exists in case same state as other row
    for (int i=0; i < MATRIX_ROWS; i++) {
        if (i == row) continue;
        if ((~matrix[i] & state) == state) return true;
    }
    return false;
}

static uint8_t read_col(void)
{
    return PINB;
}

static void unselect_rows(void) {
    DDRD  = 0x00;
    PORTD = 0x00;
    DDRC  = 0x00;
    PORTC = 0x00;
    DDRF  = 0x00;
    PORTF = 0x00;
}

static void select_row(uint8_t row)
{
    switch (row) {
        case 0:
            DDRD  = (1<<0);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 1:
            DDRD  = (1<<1);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 2:
            DDRD  = (1<<2);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 3:
            DDRD  = (1<<3);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 4:
            DDRD  = (1<<6);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 5:
            DDRD  = (1<<7);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 6:
            DDRD  = 0x00;
            PORTD = 0x00;
            DDRC  = (1<<6);
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 7:
            DDRD  = 0x00;
            PORTD = 0x00;
            DDRC  = (1<<7);
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 8:
            DDRD  = 0x00;
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = (1<<7);
            PORTF = 0x00;
            break;
    }
}
