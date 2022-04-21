#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "timer.h"
#include "matrix.h"
#include "switch_board.h"

#define DEBOUNCE_DN_MASK (uint8_t)(~(0x80 >> 5))
#define DEBOUNCE_UP_MASK (uint8_t)(0x80 >> 5)

static matrix_row_t matrix[MATRIX_ROWS] = {0};

static uint16_t matrix_scan_timestamp = 0;
static uint8_t matrix_debouncing[MATRIX_ROWS][MATRIX_COLS] = {0};
static void select_next_key(uint8_t mode);
static uint8_t get_key(uint8_t col);

static void init_cols(void);
__attribute__ ((weak))
void matrix_scan_user(void) {}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

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

static void get_key_ready(void) {
    DDRB  &= ~(1<<3);
    PORTB |=  (1<<3);
    _delay_us(5);
}

inline void select_key_ready(void) {
    DDRB |= (1<<3);
}


void matrix_init(void)
{
    init_cols();
}

uint8_t matrix_scan(void)
{
    uint16_t time_check = timer_read();
    if (matrix_scan_timestamp == time_check) return 1;
    matrix_scan_timestamp = time_check;

    select_next_key(0);
    uint8_t *debounce = &matrix_debouncing[0][0];
    for (uint8_t row=0; row<matrix_rows(); row++) {
        for (uint8_t col=0; col<matrix_cols(); col++, *debounce++) {
            uint8_t real_col = col/2;
            if (col & 1) real_col += 8;

            uint8_t key = get_key(real_col);
            if (real_col >= 8) select_next_key(1);
            *debounce = (*debounce >> 1) | key;
            if ((*debounce > 0) && (*debounce < 255)) {
                matrix_row_t *p_row = &matrix[row];
                matrix_row_t col_mask = ((matrix_row_t)1 << real_col);
                if        (*debounce >= DEBOUNCE_DN_MASK) {
                    *p_row |=  col_mask;
                } else if (*debounce <= DEBOUNCE_UP_MASK) {
                    *p_row &= ~col_mask;
                }
            }

        }
    }

    matrix_scan_quantum();
    return 1;
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

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

void init_cols(void)
{
    //595 pin
    DDRB  |=  (1<<3 | 1<<1);
    DDRB  &= ~(1<<2);
    PORTB |=  (1<<3 | 1<<2 | 1<<1);
}


static uint8_t get_key(uint8_t col) {
    if (col<8) return PINB&(1<<3) ? 0 : 0x80;
    else return PINB&(1<<2) ? 0 : 0x80;
}


void unselect_rows(void)
{
}

static void select_next_key(uint8_t mode)
{
    select_key_ready();
    if (mode == 0) {
        DS_PL_HI();
        for (uint8_t i = 0; i < 40; i++) {
            CLOCK_PULSE();
        }
        DS_PL_LO();
        CLOCK_PULSE();
    } else {
        DS_PL_HI();
        CLOCK_PULSE();
    }
    get_key_ready();
}

