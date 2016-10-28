/*
Copyright 2012 Jun Wako
Copyright 2014 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#if defined(__AVR__)
#include <avr/io.h>
#endif
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"

#if (MATRIX_COLS <= 8)
#    define print_matrix_header()  print("\nr/c 01234567\n")
#    define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop(matrix[i])
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop16(matrix[i])
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop32(matrix[i])
#    define ROW_SHIFTER  ((uint32_t)1)
#endif

#ifdef MATRIX_MASKED
extern const matrix_row_t matrix_mask[];
#endif

/* Set 0 if debouncing isn't needed */

#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif
static uint8_t debouncing = DEBOUNCING_DELAY;

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

static matrix_row_t matrix_raw[MATRIX_ROWS];


#if DIODE_DIRECTION == COL2ROW
    static matrix_row_t matrix_debouncing[MATRIX_ROWS];
#else // ROW2COL
    static matrix_col_t matrix_transposed[MATRIX_COLS];
    static matrix_col_t matrix_transposed_debouncing[MATRIX_COLS];
#endif

#if (DIODE_DIRECTION == COL2ROW)
    static void init_cols(void);
    static void read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
    static void unselect_rows(void);
    static void select_row(uint8_t row);
    static void unselect_row(uint8_t row);
#else // ROW2COL
    static void init_rows(void);
    static void read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
    static void unselect_cols(void);
    static void unselect_col(uint8_t col);
    static void select_col(uint8_t col);
#endif

__attribute__ ((weak))
void matrix_init_quantum(void) {
    matrix_init_kb();
}

__attribute__ ((weak))
void matrix_scan_quantum(void) {
    matrix_scan_kb();
}

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

inline
uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

// void matrix_power_up(void) {
// #if (DIODE_DIRECTION == COL2ROW)
//     for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
//         /* DDRxn */
//         _SFR_IO8((row_pins[r] >> 4) + 1) |= _BV(row_pins[r] & 0xF);
//         toggle_row(r);
//     }
//     for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
//         /* PORTxn */
//         _SFR_IO8((col_pins[c] >> 4) + 2) |= _BV(col_pins[c] & 0xF);
//     }
// #else
//     for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
//         /* DDRxn */
//         _SFR_IO8((col_pins[c] >> 4) + 1) |= _BV(col_pins[c] & 0xF);
//         toggle_col(c);
//     }
//     for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
//         /* PORTxn */
//         _SFR_IO8((row_pins[r] >> 4) + 2) |= _BV(row_pins[r] & 0xF);
//     }
// #endif
// }

void matrix_init(void) {

    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
    #if  (defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega32U4__))
        MCUCR |= _BV(JTD);
        MCUCR |= _BV(JTD);
    #endif

    // initialize row and col
#if (DIODE_DIRECTION == COL2ROW)
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_raw[i] = 0;
        matrix_debouncing[i] = 0;
    }

#else // ROW2COL
    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix_raw[i] = 0;
        matrix[i] = 0;
    }

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_COLS; i++) {
        matrix_transposed_debouncing[i] = 0;
    }
#endif

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{

#if (DIODE_DIRECTION == COL2ROW)

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        read_cols_on_row(matrix, current_row);
    }

    //     select_row(i);
    //     wait_us(30);  // without this wait read unstable value.
    //     matrix_row_t current_row = read_cols();
    //     if (matrix_debouncing[i] != current_row) {
    //         matrix_debouncing[i] = current_row;
    //         if (debouncing) {
    //             debug("bounce!: "); debug_hex(debouncing); debug("\n");
    //         }
    //         debouncing = DEBOUNCING_DELAY;
    //     }
    //     unselect_row(i);
    // }

    // if (debouncing) {
    //     if (--debouncing) {
    //         wait_ms(1);
    //     } else {
    //         for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    //             matrix[i] = matrix_debouncing[i];
    //         }
    //     }
    // }

#else // ROW2COL

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        read_rows_on_col(matrix, current_col);
    }


    // for (uint8_t i = 0; i < MATRIX_COLS; i++) {
    //     select_col(i);
    //     wait_us(30);  // without this wait read unstable value.
    //     matrix_col_t current_col = read_rows();
    //     if (matrix_transposed_debouncing[i] != current_col) {
    //         matrix_transposed_debouncing[i] = current_col;
    //         if (debouncing) {
    //             debug("bounce!: "); debug_hex(debouncing); debug("\n");
    //         }
    //         debouncing = DEBOUNCING_DELAY;
    //     }
    //     unselect_col(i);
    // }

    // if (debouncing) {
    //     if (--debouncing) {
    //         wait_ms(1);
    //     } else {
    //         for (uint8_t i = 0; i < MATRIX_COLS; i++) {
    //             matrix_transposed[i] = matrix_transposed_debouncing[i];
    //         }
    //     }
    // }

    // // Untranspose matrix
    // for (uint8_t y = 0; y < MATRIX_ROWS; y++) {
    //     matrix_row_t row = 0;
    //     for (uint8_t x = 0; x < MATRIX_COLS; x++) {
    //         row |= ((matrix_transposed[x] & (1<<y)) >> y) << x;
    //     }
    //     matrix[y] = row;
    // }

#endif

    matrix_scan_quantum();

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
    return (matrix[row] & ((matrix_row_t)1<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
    // switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}

void matrix_print(void)
{
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += matrix_bitpop(i);
    }
    return count;
}



#if (DIODE_DIRECTION == COL2ROW)

static void init_cols(void)
{
    for(uint8_t x = 0; x < MATRIX_COLS; x++) {
        uint8_t pin = col_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
    }
}

static void read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
{
    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    wait_us(30);

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

        // Select the col pin to read (active low)
        uint8_t pin = col_pins[col_index];
        uint8_t pin_state = (_SFR_IO8(pin >> 4) & _BV(pin & 0xF));

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << col_index);
    }
}

static void select_row(uint8_t row)
{
    uint8_t pin = row_pins[row];
    _SFR_IO8((pin >> 4) + 1) |=  _BV(pin & 0xF); // OUT
    _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
}

static void unselect_row(uint8_t row)
{
    uint8_t pin = row_pins[row];
    _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
    _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
}

static void unselect_rows(void)
{
    for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
        uint8_t pin = row_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
    }
}

#else // ROW2COL

static void init_rows(void)
{
    for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
        uint8_t pin = row_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
    }
}

static void read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(30);

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {

        // Select the row pin to read (active low)
        uint8_t pin = row_pins[row_index];
        uint8_t pin_state = (_SFR_IO8(pin >> 4) & _BV(pin & 0xF));

        // Populate the matrix row with the state of the col pin
        current_matrix[row_index] &= pin_state ? ~(ROW_SHIFTER << current_col) : 0;
    }
}

static void select_col(uint8_t col)
{
    uint8_t pin = col_pins[col];
    _SFR_IO8((pin >> 4) + 1) |=  _BV(pin & 0xF); // OUT
    _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
}

static void unselect_col(uint8_t col)
{
    uint8_t pin = col_pins[col];
    _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
    _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
}

static void unselect_cols(void)
{
    for(uint8_t x = 0; x < MATRIX_COLS; x++) {
        uint8_t pin = col_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
    }
}

#endif
