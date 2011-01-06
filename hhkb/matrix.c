/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "util.h"
#include "matrix_skel.h"


#if (MATRIX_COLS > 16)
#   error "MATRIX_COLS must not exceed 16"
#endif
#if (MATRIX_ROWS > 255)
#   error "MATRIX_ROWS must not exceed 255"
#endif


// matrix state buffer(1:on, 0:off)
#if (MATRIX_COLS <= 8)
static uint8_t *matrix;
static uint8_t *matrix_prev;
static uint8_t _matrix0[MATRIX_ROWS];
static uint8_t _matrix1[MATRIX_ROWS];
#else
static uint16_t *matrix;
static uint16_t *matrix_prev;
static uint16_t _matrix0[MATRIX_ROWS];
static uint16_t _matrix1[MATRIX_ROWS];
#endif

#ifdef MATRIX_HAS_GHOST
static bool matrix_has_ghost_in_row(uint8_t row);
#endif


// matrix is active low. (key on: 0/key off: 1)
//
// HHKB has no ghost and no bounce.
// row: HC4051 select input channel(0-8)
//      PB0, PB1, PB2(A, B, C)
// col: LS145 select low output line(0-8)
//      PB3, PB4, PB5, PB6(A, B, C, D)
//      use D as ENABLE: (enable: 0/unenable: 1)
// key: KEY: (on: 0/ off:1)
//      KEY_PREV: (on: 1/ off: 0)
//      PE6,PE7(KEY, KEY_PREV)
#define COL_ENABLE              (1<<6)
#define KEY_SELELCT(ROW, COL)   (PORTB = (PORTB&(1<<7))|COL_ENABLE|(((COL)&0x07)<<3)|((ROW)&0x07))
#define KEY_ENABLE              (PORTB &= ~COL_ENABLE)
#define KEY_UNABLE              (PORTB |=  COL_ENABLE)
#define KEY_STATE               (PINE&(1<<6))
#define KEY_PREV_ON             (PORTE |= (1<<7))
#define KEY_PREV_OFF            (PORTE &= ~(1<<7))


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
    // row & col output(PB0-6)
    DDRB = 0xFF;
    KEY_SELELCT(0, 0);
    // KEY: input with pullup(PE6)
    // KEY_PREV: output(PE7)
    DDRE = 0xBF;
    PORTE = 0x40;

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix1[i] = 0x00;
    matrix = _matrix0;
    matrix_prev = _matrix1;
}

uint8_t matrix_scan(void)
{
    uint8_t *tmp;

    tmp = matrix_prev;
    matrix_prev = matrix;
    matrix = tmp;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            KEY_SELELCT(row, col);
            _delay_us(40);  // from logic analyzer chart
            if (matrix_prev[row] & (1<<col)) {
                KEY_PREV_ON;
            }
            _delay_us(7);  // from logic analyzer chart
            KEY_ENABLE;
            _delay_us(10);  // from logic analyzer chart
            if (KEY_STATE) {
                matrix[row] &= ~(1<<col);
            } else {
                matrix[row] |= (1<<col);
            }
            KEY_PREV_OFF;
            KEY_UNABLE;
            _delay_us(150);  // from logic analyzer chart
        }
    }
    return 1;
}

bool matrix_is_modified(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] != matrix_prev[i])
            return true;
    }
    return false;
}

inline
bool matrix_has_ghost(void)
{
#ifdef MATRIX_HAS_GHOST
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix_has_ghost_in_row(i))
            return true;
    }
#endif
    return false;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
#if (MATRIX_COLS <= 8)
uint8_t matrix_get_row(uint8_t row)
#else
uint16_t matrix_get_row(uint8_t row)
#endif
{
    return matrix[row];
}

void matrix_print(void)
{
#if (MATRIX_COLS <= 8)
    print("\nr/c 01234567\n");
#else
    print("\nr/c 0123456789ABCDEF\n");
#endif
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
#if (MATRIX_COLS <= 8)
        pbin_reverse(matrix_get_row(row));
#else
        pbin_reverse16(matrix_get_row(row));
#endif
#ifdef MATRIX_HAS_GHOST
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
#endif
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
#if (MATRIX_COLS <= 8)
        count += bitpop(matrix[i]);
#else
        count += bitpop16(matrix[i]);
#endif
    }
    return count;
}

#ifdef MATRIX_HAS_GHOST
inline
static bool matrix_has_ghost_in_row(uint8_t row)
{
    // no ghost exists in case less than 2 keys on
    if (((matrix[row] - 1) & matrix[row]) == 0)
        return false;

    // ghost exists in case same state as other row
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && (matrix[i] & matrix[row]) == matrix[row])
            return true;
    }
    return false;
}
#endif
