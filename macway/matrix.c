/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "matrix.h"
#include "print.h"
#include "util.h"

// matrix is active low. (key on: 0/key off: 1)
// row: Hi-Z(unselected)/low output(selected)
//      PD0, PC7, PD7, PF6, PD6, PD1, PD2, PC6, PF7
// col: input w/pullup
//      PB0-PB7

// matrix state buffer
uint8_t *matrix;
uint8_t *matrix_prev;
static uint8_t _matrix0[MATRIX_ROWS];
static uint8_t _matrix1[MATRIX_ROWS];

static bool matrix_has_ghost_in_row(uint8_t row);
static uint8_t read_col(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


inline
int matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
int matrix_cols(void)
{
    return MATRIX_COLS;
}

// this must be called once before matrix_scan.
void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    DDRB = 0x00;
    PORTB = 0xFF;

    // initialize matrix state: all keys off
    for (int i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    for (int i=0; i < MATRIX_ROWS; i++) _matrix1[i] = 0x00;
    matrix = _matrix0;
    matrix_prev = _matrix1;
}

int matrix_scan(void)
{
    uint8_t *tmp;

    tmp = matrix_prev;
    matrix_prev = matrix;
    matrix = tmp;

    for (int i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix[i] = ~read_col();
        unselect_rows();
    }
    return 1;
}

bool matrix_is_modified(void)
{
    for (int i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] != matrix_prev[i])
            return true;
    }
    return false;
}

bool matrix_has_ghost(void)
{
    for (int i = 0; i < MATRIX_ROWS; i++) {
        if (matrix_has_ghost_in_row(i))
            return true;
    }
    return false;
}

inline
bool matrix_is_on(int row, int col)
{
    return (matrix[row] & (1<<col));
}

inline
uint16_t matrix_get_row(int row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (int row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
        print("\n");
    }
}

int matrix_key_count(void)
{
    int count = 0;
    for (int i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop(matrix[i]);
    }
    return count;
}

static bool matrix_has_ghost_in_row(uint8_t row)
{
    // no ghost exists in case less than 2 keys on
    if (((matrix[row] - 1) & matrix[row]) == 0)
        return false;

    // ghost exists in case same state as other row
    for (int i=0; i < MATRIX_ROWS; i++) {
        if (i != row && (matrix[i] & matrix[row]) == matrix[row])
            return true;
    }
    return false;
}

static uint8_t read_col(void)
{
    return PINB;
}

static void unselect_rows(void)
{
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
            DDRD  = 0x00;
            PORTD = 0x00;
            DDRC  = (1<<7);
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 2:
            DDRD  = (1<<7);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 3:
            DDRD  = 0x00;
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = (1<<6);
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
            DDRD  = (1<<1);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 6:
            DDRD  = (1<<2);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 7:
            DDRD  = 0x00;
            PORTD = 0x00;
            DDRC  = (1<<6);
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
