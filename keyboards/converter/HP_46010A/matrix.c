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
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "util.h"
#include "debug.h"
#include "host.h"
#include "matrix.h"
#include "report.h"
#include "timer.h"
#include "LUFA/Drivers/Peripheral/SPI.h"

#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif

#if ( DEBOUNCING_DELAY > 0 )
static uint16_t debouncing_time         ;
static bool     debouncing      = false ;
#endif

static uint8_t matrix [MATRIX_ROWS] ;

#if ( DEBOUNCING_DELAY > 0 )
static uint8_t matrix_debounce_old [MATRIX_ROWS] ;
static uint8_t matrix_debounce_new [MATRIX_ROWS] ;
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
// the outputs are a single output pin.
// I'm using the SPI controller of the 32u4 to do all the dirty work of reading
// the pins and toggling the data into memory a byte at a time.
//
// the device functions, by using the clock signal to count 128 bits, the lower
// 3 bits of this 7 bit counter are tied to a 1-of-8 multiplexer, this forms 
// the columns.
// the upper 4 bits form the rows, and are decoded using bcd to decimal 
// decoders, so that 14 out of 16 of the outputs are wired to the rows of the 
// matrix. each switch has a diode, such that the row signal feeds into the
// switch, and then into the diode, then into one of the columns into the 
// matrix. the reset pin can be used to reset the entire counter.

void matrix_init () {
    // SS pin set to output
    DDRB  |= (1 << 0) ;
            
    // SS is reset for this board, and is active High
    PORTB &= ( 0b11111110 ) ;
 
    //toggle reset, to put the keyboard logic into a known state
    PORTB ^= 1 ;
    wait_us( 30 ) ; // make sure the line is stable
    PORTB ^= 1 ;
 
    // establish matrices in memory
    memset( matrix, 0, MATRIX_ROWS ) ;
    
#if ( DEBOUNCING_DELAY > 0 )
    memset( matrix_debounce_old, 0, MATRIX_ROWS ) ;
    memset( matrix_debounce_new, 0, MATRIX_ROWS ) ;
#endif
 
    // the spi is configured to scan at a rate of 2 Mhz
    SPI_Init( SPI_MODE_MASTER
            | SPI_ORDER_LSB_FIRST
            | SPI_SCK_LEAD_RISING
            | SPI_SAMPLE_TRAILING
            | SPI_SPEED_FCPU_DIV_8 // largest divider that produces an SPI clock
                                   // slower than the slowest propagation delay
                                   // of the logic chips (350nS).
            );
             
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
#if ( DEBOUNCING_DELAY > 0 )
    
    // the first byte of the keyboard's output data can be ignored
    SPI_ReceiveByte() ;

    for ( uint8_t current_row = 0 ; current_row < MATRIX_ROW ; ++current_row ) {
        //transfer old debouncing values
        matrix_debounce_old[current_row] = matrix_debounce_new[current_row] ;
        // read new key-states in
        matrix_debounce_new[current_row] = SPI_ReceiveByte() ;
    }
    
    // the last 2 bytes of the keyboard can be ignored too, so we simply reset
    PORTB ^= 1 ;
    wait_us( 30 ) ; // make sure the line is stable
    PORTB ^= 1 ;
    
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
        matrix[current_row] = SPI_ReceiveByte() ;
    }
#endif 

    
#if ( DEBOUNCING_DELAY > 0 )
    if ( debouncing && ( timer_elapsed( debouncing_time ) > DEBOUNCING_DELAY ) ) {
        
        for ( uint8_t i = 0 ; i < MATRIX_ROWS ; ++i ) {
            matrix[i] = matrix_debouncing_new[i] ;
        }
        debouncing = false ;
    }
#endif
}

inline
uint8_t matrix_get_row( uint8_t row ) {
    return matrix[row];
}


// as an aside, I used the M0110 converter:
// tmk_core/common/keyboard.c, quantum/matrix.c, and the project layout of the planck
// the lufa documentation: 
// http://www.fourwalledcubicle.com/files/LUFA/Doc/170418/html/group___group___s_p_i___a_v_r8.html
// the online ducmentation starting from : 
// https://docs.qmk.fm/#/config_options
// https://docs.qmk.fm/#/understanding_qmk
// and probably a few i forgot....