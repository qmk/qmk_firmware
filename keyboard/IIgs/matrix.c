/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "led.h"


#if (MATRIX_COLS > 16)
#   error "MATRIX_COLS must not exceed 16"
#endif
#if (MATRIX_ROWS > 255)
#   error "MATRIX_ROWS must not exceed 255"
#endif


#ifndef DEBOUNCE
#   define DEBOUNCE	0
#endif
static uint8_t debouncing = DEBOUNCE;

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
static uint8_t read_col(uint8_t row);
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
    // initialize row and col
    unselect_rows();
    // Input with pull-up(DDR:0, PORT:1)
	// Column C1 ~ C7 (PortC0-6)
	// Column C0(Port E1)
    DDRC &= ~0b01111111;
    PORTC |= 0b01111111;
    DDRE &= ~0b00000010;
    PORTE |= 0b00000010;
	//DDRB &= ~0b00000100;
	//PORTB |= 0b00000100;
	// modifier	B3/4,F4/5,E4	always input
	// 			A0
    //DDRA |=  0b00000001;
    //PORTA &= 0b00000001;
    //DDRB |=  0b00011000;
    //PORTB &= 0b00011000;
    //DDRF |= ~0b00110000;
    //PORTF &= 0b00110000;
    //DDRB &= ~0b00011000;
    //PORTB |= 0b00011000;
    //DDRF &= ~0b00110000;
    //PORTF |= 0b00110000;
    //DDRE &= ~0b00010000;
    //PORTE |= 0b00010000;

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix1[i] = 0x00;
    matrix = _matrix0;
    matrix_prev = _matrix1;
}

uint8_t matrix_scan(void)
{
    if (!debouncing) {
        uint8_t *tmp = matrix_prev;
        matrix_prev = matrix;
        matrix = tmp;
    }

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        unselect_rows();
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
		if ( i == ( MATRIX_ROWS - 1 ) ) {							// CHECK CAPS LOCK
       		if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {		// CAPS LOCK is ON on HOST
				if ( ~read_col(i) & (1<< 4) ) { 							// CAPS LOCK is still DOWN ( 0bXXX1_XXXX)	
					matrix[i]        = ~read_col(i) & 0b11101111;				// change CAPS LOCK as released
				} else {													// CAPS LOCK in UP
					matrix[i] = ~read_col(i) | 0b00010000;						// send fake caps lock down
				}
			} else {													// CAPS LOCK is OFF on HOST
        		if (matrix[i] != (uint8_t)~read_col(i)) {
           			matrix[i] = (uint8_t)~read_col(i);
        			if (debouncing) {
        				debug("bounce!: "); debug_hex(debouncing); print("\n");
					}
       				debouncing = DEBOUNCE;
				}
			}
		} else {
        	if (matrix[i] != (uint8_t)~read_col(i)) {
           		matrix[i] = (uint8_t)~read_col(i);
        		if (debouncing) {
        			debug("bounce!: "); debug_hex(debouncing); print("\n");
				}
       			debouncing = DEBOUNCE;
			}
		}
	}
    unselect_rows();

    if (debouncing) {
        debouncing--;
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] != matrix_prev[i]) {
            return true;
        }
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
//	if ( row == ( MATRIX_ROWS - 1 ) && col == 4) {							// CHECK CAPS LOCK
//    	if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {		// CAPS LOCK is ON on HOST
//			if ((matrix_prev[row] & 0b00010000) && (~matrix[row] & 0b00010000)) {
//				debug("CapsLock Reverse:");debug_hex(matrix[row]);
//				matrix[row] |= 0b00010000;
//				matrix_prev[row] &= ~0b00010000;
//				debug("->");debug_hex(matrix[row]);debug("\n");
//			}
//		} 
//	}
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
    print("\nr/c 01234567\n");
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

inline
static uint8_t read_col(uint8_t row)
{
	// For normal 	: Column C1 ~ C7 (PortC0-6), C0(Port E1)
	// For modifier	: B3(CNTRL)/4(SHIFT),F4(CMD/GUI)/5(OPTION,ALT)
	// Modifier would be copied to report->mods except E4(CAPSLOCK)
	uint8_t tmp;
	if ( row == 10 ) {
		tmp = 0xC0;
		tmp |= (PINB >> 3 ) & 0b00000011;	// LEFT CTRL  is 0bit in modifier (HID Spec)
											// LEFT SHIFT is 1bit in modifier (HID Spec)
		tmp |= (PINF >> 3 ) & 0b00000100;	// LEFT ALT   is 2bit in modifier (HID Spec)
		tmp |= (PINF >> 1 ) & 0b00001000;	// LEFT GUI   is 3bit in modifier (HID Spec)
		tmp |= (PINA << 4 ) & 0b00010000;	// CAPSLOCK
		tmp |= (PINB << 3 ) & 0b00100000;	// POWER 	 
	} else {
		tmp = 0x00;
		tmp = (PINE >> 1)&0b00000001; 
		tmp |= PINC << 1 ;
	}
	return tmp;
}

inline
static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
	// DDR : 1, output	0, input
    DDRB  &= ~0b00000011; // PB: 1,0  
    PORTB &= ~0b00000011;
    DDRD  &= ~0b00010000; // PD: 4
    PORTD &= ~0b00010000;
    DDRE  &= ~0b11000000; // PE: 7,6
    PORTE &= ~0b11000000;
    DDRF  &= ~0b11000111; // PF: 7,6,2,1,0 
    PORTF &= ~0b11000111;
	// to unselect virtual row(modifier), set port to output with low
    DDRA  |=  0b00000001; // PA: 0 for CAPSLOCK
    PORTA &= ~0b00000001;
    DDRB  |=  0b00011100; // PB: 3,4 for modifier(row10)
    PORTB &= ~0b00011100; // PB: 2 for power
    DDRF  |=  0b00110000; // PF: 4,5 for modifier
    PORTF &= ~0b00110000;
}

inline
static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
	// with row enable, column could send low to AVR when pressed
    // row: 0    1    2    3    4    5    6    7    8    9
    // pin: PB1, PB0, PE7, PE6, PD4, PF2, PF0, PF1, PF6  PF7
    switch (row) {
        case 0:
            DDRB  |= (1<<1);
            PORTB &= ~(1<<1);
            break;
        case 1:
            DDRB  |= (1<<0);
            PORTB &= ~(1<<0);
            break;
        case 2:
            DDRE  |= (1<<7);
            PORTE &= ~(1<<7);
            break;
        case 3:
            DDRE  |= (1<<6);
            PORTE &= ~(1<<6);
            break;
        case 4:
            DDRD  |= (1<<4);
            PORTD &= ~(1<<4);
            break;
        case 5:
            DDRF  |= (1<<2);
            PORTF &= ~(1<<2);
            break;
        case 6:
            DDRF  |= (1<<0);
            PORTF &= ~(1<<0);
            break;
        case 7:
            DDRF  |= (1<<1);
            PORTF &= ~(1<<1);
            break;
        case 8:
            DDRF  |= (1<<6);
            PORTF &= ~(1<<6);
            break;
        case 9:
            DDRF  |= (1<<7);
            PORTF &= ~(1<<7);
            break;
		case 10:
			// modifier has no row enable
			// to select virtual row, set port as input
		    DDRA &= ~0b00000001;
		    PORTA |= 0b00000001;
		    DDRB &= ~0b00011100;
		    PORTB |= 0b00011100;
		    DDRF &= ~0b00110000;
		    PORTF |= 0b00110000;
            break;

    }
}
