/*
Copyright 2018 listofoptions <listofoptions@gmail.com>

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
#include <string.h>
#if defined(__AVR__)
#include <avr/io.h>
#endif
#include <util/delay.h>

#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "timer.h"

#include "config.h"


#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif

#define print_matrix_header()      print("\nr/c 01234567\n")
#define print_matrix_row(row)      print_bin_reverse8(matrix_get_row(row))
#define matrix_bitpop(i)           bitpop(matrix[i])
#define ROW_SHIFTER                ((uint8_t)1)
#define check_bit(var,pos)         ((var) & (1<<(pos)))

#define NUM_ROW_PINS 5
#define NUM_COL_PINS 2

static const uint8_t row_pins [NUM_ROW_PINS] = MATRIX_ROW_PINS ;
static const uint8_t col_pins [NUM_ROW_PINS] = MATRIX_COL_PINS ;

#if ( DEBOUNCE > 0 )
static uint16_t debouncing_time         ;
static bool     debouncing      = false ;
#endif

static uint8_t matrix          [MATRIX_ROWS] = {0};

#if ( DEBOUNCE > 0 )
static uint8_t matrix_debounce [MATRIX_ROWS] = {0};
#endif 

static
inline
void toggle_led(void) {
    uint8_t pin = LED_PIN ;
    _SFR_IO8((pin >> 4) + 2) ^= _BV(pin & 0xF);
}

static
inline
void init_led(void) {
    uint8_t pin = LED_PIN ;
    _SFR_IO8((pin >> 4) + 1) |= _BV(pin & 0xF);  // OUT
    _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
}

static
inline
void init_data(void) {
    uint8_t pin = MATRIX_DATA_PIN ;
    _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
    _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // LO
}

static
inline
void init_strobe(void) {
    uint8_t pin = MATRIX_STROBE_PIN ;
    _SFR_IO8((pin >> 4) + 1) |= _BV(pin & 0xF);  // OUT
    _SFR_IO8((pin >> 4) + 2) |= _BV(pin & 0xF);  // HI
}

static
inline
void init_rows(void) {
    for ( uint8_t i = 0 ; i < NUM_ROW_PINS; ++i ) {
        uint8_t pin = row_pins[i];
        _SFR_IO8((pin >> 4) + 1) |=  _BV(pin & 0xF); // OUT
        _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
    }
}

static
inline
void init_cols(void) {
    for ( uint8_t i = 0 ; i < NUM_COL_PINS; ++i ) {
        uint8_t pin = col_pins[i];
        _SFR_IO8((pin >> 4) + 1) |=  _BV(pin & 0xF); // OUT
        _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
    }
}

static
inline
void select_row(uint8_t current_row) {
    for ( uint8_t i = 0 ; i < NUM_ROW_PINS; ++i ) {
        uint8_t pin = row_pins[i] ;
        if ( check_bit( current_row, i ) ) {
            _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
        } else {
            _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
        }
    }
    wait_us(30) ;
}

static
inline
void select_col(uint8_t current_col) {
    for ( uint8_t i = 0 ; i < NUM_COL_PINS; ++i ) {
        uint8_t pin = col_pins[i] ;
        if ( check_bit( current_col, i ) ) {
            _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
        } else {
            _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
        }
    }
    wait_us(30) ;
}

static
inline
uint8_t matrix_strobe(uint8_t col_index) {
    uint8_t strobe_pin = MATRIX_STROBE_PIN ;
    uint8_t data_pin   = MATRIX_DATA_PIN   ;
    
    // set strobe pin low
    _SFR_IO8((strobe_pin >> 4) + 2) &=  ~_BV(strobe_pin & 0xF);
    
    wait_us(30) ;
    
    // read data 
    uint8_t data = (_SFR_IO8(data_pin >> 4) & _BV(data_pin & 0xF)) ;
    
    // set strobe pin hi
    _SFR_IO8((strobe_pin >> 4) + 2) |= _BV(strobe_pin & 0xF);
    
    uint8_t out = data ? (1 << col_index) : 0 ;
    return out ;
}

static
bool matrix_read(uint8_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    uint8_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    select_row(current_row);

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS; ++col_index) {

        select_col(col_index) ;
        
        // strobe the matrix
        // Populate the matrix row with the state of the data pin
        current_matrix[current_row] |= matrix_strobe(col_index) ;
    }

    bool test = last_row_value != current_matrix[current_row] ;
    return test ;
}

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

inline
uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

inline
uint8_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_init(void) {
    init_led()    ;   
    init_rows()   ;
    init_cols()   ;
    init_data()   ;
    init_strobe() ;
    
    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i]            = 0;
#       if (DEBOUNCE > 0)
        matrix_debounce  [i] = 0;
#       endif
    }

    matrix_init_quantum() ;
}

uint8_t matrix_scan(void) { 
    for ( uint8_t current_row = 0; current_row < MATRIX_ROWS; ++current_row ) {
#       if (DEBOUNCE > 0)
            bool matrix_changed = matrix_read(matrix_debounce, current_row);
            
            if (matrix_changed) {
                debouncing      = true        ;
                debouncing_time = timer_read();
            }
                        
#       else
            matrix_read(matrix, current_row);
#       endif
    }
    
#   if (DEBOUNCE > 0)
        if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCE)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debounce[i];
            }
            debouncing = false;
        }
#   endif

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}
