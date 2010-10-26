/*
 * scan matrix
 */
#include <avr/io.h>
#include <util/delay.h>
#include "matrix.h"
#include "print.h"

// matrix is active low. (key on: 0/key off: 1)
//
// HHKB has no ghost and no bounce.
// row: HC4051 select input channel(0-8)
//      PB0, PB1, PB2(A, B, C)
// col: LS145 select low output line(0-8)
//      PB3, PB4, PB5, PB6(A, B, C, D)
//      use D as ENABLE: (enable: 0/unenable: 1)
// key: KEY: (on: 0/ off:1)
//      UNKNOWN: unknown whether input or output
//      PE6,PE7(KEY, UNKNOWN)
#define COL_ENABLE              (1<<6)
#define KEY_SELELCT(ROW, COL)   (PORTB = COL_ENABLE|(((COL)&0x07)<<3)|((ROW)&0x07))
#define KEY_ENABLE              (PORTB &= ~COL_ENABLE)
#define KEY_UNABLE              (PORTB |=  COL_ENABLE)
#define KEY_ON                  ((PINE&(1<<6)) ? false : true)

// matrix state buffer
uint8_t *matrix;
uint8_t *matrix_prev;
static uint8_t _matrix0[MATRIX_ROWS];
static uint8_t _matrix1[MATRIX_ROWS];


static bool matrix_has_ghost_in_row(int row);
static int bit_pop(uint8_t bits);


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
    // row & col output(PB0-6)
    DDRB = 0xFF;
    PORTB = KEY_SELELCT(0, 0);
    // KEY & VALID input with pullup(PE6,7)
    DDRE = 0x3F;
    PORTE = 0xC0;

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

    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            KEY_SELELCT(row, col);
            _delay_us(50);  // from logic analyzer chart
            KEY_ENABLE;
            _delay_us(10);  // from logic analyzer chart
            if (KEY_ON) {
                matrix[row] |= (1<<col);
            } else {
                matrix[row] &= ~(1<<col);
            }
            KEY_UNABLE;
            _delay_us(150);  // from logic analyzer chart
        }
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

inline
bool matrix_has_ghost(void)
{
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
        count += bit_pop(matrix[i]);
    }
    return count;
}

inline
static bool matrix_has_ghost_in_row(int row)
{
    return false;
}

inline
static int bit_pop(uint8_t bits)
{
    int c;
    for (c = 0; bits; c++)
        bits &= bits -1;
    return c;
}
