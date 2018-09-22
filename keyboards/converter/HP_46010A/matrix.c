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


#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif

#if ( DEBOUNCING_DELAY > 0 )
static uint16_t debouncing_time         ;
static bool     debouncing      = false ;
#endif

static uint8_t matrix [MATRIX_ROWS] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#if ( DEBOUNCING_DELAY > 0 )
static uint8_t matrix_debounce_old [MATRIX_ROWS] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static uint8_t matrix_debounce_new [MATRIX_ROWS] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
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

// the keyboard's internal wiring is such that the inputs to the logic are
// a clock signal, and a reset line.
// the output is a single output pin. im bitbanging here, but the SPI controller
// would work normally
//
// the device functions, by using the clock signal to count 128 bits, the lower
// 3 bits of this 7 bit counter are tied to a 1-of-8 multiplexer, this forms 
// the columns.
// the upper 4 bits form the rows, and are decoded using bcd to decimal 
// decoders, so that 14 out of 16 of the outputs are wired to the rows of the 
// matrix. each switch has a diode, such that the row signal feeds into the
// switch, and then into the diode, then into one of the columns into the 
// matrix. the reset pin can be used to reset the entire counter.

uint8_t matrix_ReceiveByte (void) ;

void matrix_init () {
    //debug_enable=true ;     
    // PB0 (SS) and PB1 (SCLK) set to outputs
    DDRB  |= ((1 << 0) | (1 << 1)) ;
    // PB2, is unused, and PB3 is our serial input
    DDRB &= ~(1 << 3) ;
  
    // SS is reset for this board, and is active High
    // SCLK is the serial clock and is active High
    PORTB &= ~((1 << 0) | (1 << 1)) ;

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
#if ( DEBOUNCING_DELAY > 0 )

    //toggle reset, to put the keyboard logic into a known state
    PORTB ^= 1 ;
    _delay_us( 30 ) ; // make sure the line is stable
    PORTB ^= 1 ;
    
    for ( uint8_t current_row = 0 ; current_row < MATRIX_ROWS ; ++current_row ) {
        // the first byte of the keyboard's output data can be ignored
        if ( current_row == 0 ) {
            // we dont really care about this first byte, but we need to do something to shut up gcc
            matrix_debounce_old[0] = matrix_ReceiveByte() ;
            // so we just overwrite them later on...
        } else {
            //transfer old debouncing values
            matrix_debounce_old[current_row - 8] = matrix_debounce_new[current_row - 8] ;
            // read new key-states in
            matrix_debounce_new[current_row - 8] = matrix_ReceiveByte() ;
        }
    }
    
    // detect matrix changes (exit on first change)
    for ( uint8_t i = 0 ; i < MATRIX_ROWS ; ++i ) {
        if ( !( matrix_debounce_new[i] ^ matrix_debounce_old[i] ) ) {
            debouncing      = true         ;
            debouncing_time = timer_read() ;
            break ;
        }
    }
    
#else
    // without debouncing we simply just read in the raw matrix
    for ( uint8_t current_row = 0 ; current_row < MATRIX_ROWS ; ++current_row ) {
        matrix[current_row] = matrix_ReceiveByte() ;
    }
#endif 

    
#if ( DEBOUNCING_DELAY > 0 )
    if ( debouncing && ( timer_elapsed( debouncing_time ) > DEBOUNCING_DELAY ) ) {
        
        for ( uint8_t i = 0 ; i < MATRIX_ROWS ; ++i ) {
            matrix[i] = matrix_debounce_new[i] ;
        }
        debouncing = false ;
    }
#endif

    matrix_scan_quantum() ;
    return 1;
}

inline
uint8_t matrix_get_row( uint8_t row ) {
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_ReceiveByte (void) {
    uint8_t received = 0;
    for ( uint8_t bit = 0; bit < MATRIX_COLS; ++bit ) {
        // toggle the clock
        PORTB ^= (1 << 1) ;
        _delay_us( 30 ) ; // make sure the line is stable
        PORTB ^= (1 << 1) ;
        
        // read bit using PB3, and cram it into a byte
        received |= (PINB & (1 << 3) << bit) ;
    }
    
    return received ;
}

inline
uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

// as an aside, I used the M0110 converter:
// tmk_core/common/keyboard.c, quantum/matrix.c, and the project layout of the planck
// the online ducmentation starting from : 
// https://docs.qmk.fm/#/config_options
// https://docs.qmk.fm/#/understanding_qmk
// and probably a few i forgot....