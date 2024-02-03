/*
Copyright 2014 Warren Janssens <warren.janssens@gmail.com>

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
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "led.h"
#include "config.h"

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static uint8_t matrix[MATRIX_ROWS];
static uint8_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_row(uint8_t row);
static void unselect_rows(void);
static void select_rows(uint8_t row);


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
    //debug_enable = true;
    
    //dprint("matrix_init"); dprintln();
    // output high (leds)
    DDRD    = 0xFF;
    PORTD   = 0xFF;
    
    // output low (multiplexers)
    DDRF    = 0xFF;
    PORTF   = 0x00;
    
    // input with pullup (matrix)
    DDRB    = 0x00;
    PORTB   = 0xFF;
    
    // input with pullup (program and keypad buttons)
    DDRC    = 0x00;
    PORTC   = 0xFF;
    
    // initialize row and col
    unselect_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
	
}

uint8_t matrix_scan(void)
{

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_rows(i);
        uint8_t row = read_row(i);
        if (matrix_debouncing[i] != row) {
            matrix_debouncing[i] = row;
            if (debouncing) {
                dprintf("bounce!: %02X\n", debouncing);
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }
    matrix_scan_kb();
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
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

static matrix_row_t read_row(uint8_t row)
{
	_delay_us(30);  // without this wait read unstable value.

	//keypad and program buttons
	if (row == 12)
	{
		return ~(PINC | 0b00111111);
	}
	return ~PINB;
}

static void unselect_rows(void)
{
    // set A,B,C,G to 0 (F4 - F7)
    PORTF &= 0x0F;
}

static void select_rows(uint8_t row)
{
    // set A,B,C,G to row value
    PORTF |= row << 4;
}


/* Row pin configuration
PF0		A
PF1		B
PF2		C
PF3		G	0 = U4, 1 = U5

				4y0	4y1	4y2	4y3	4y4	4y5	4y6	4y7	5y0	5y1	5y2	5y3	5y4	5y5	5y6	5y7	
				r1	r2	 r3 r4	r5	r6	r7	r8	r9	r10	r11	r12	r13	r14	r15	r16	
PB0		21	c1	f6	f8	f7	5	4	3	2	1	=+								
PB1		22	c2	f3	f5	f4	t	r	e	w	q	TAB								
PB2		23	c3	ESC	f2	f1	g	f	d	s	a	CL								
PB3		24	c4	f9	f11	f10	b	v	c	x	z	LS	UP		DN		[{	]}		
PB4		25	c5  f12	SL	PS	RT		LT	§±	`~		6	7	8		9	0	-_ 	
PB5		26	c6	PB	PGM	KPD							y	u	i		o	p	\	
PB6		27	c7  			LC	DL	BS	RC	EN	SP	h	j	k		l	;:	'"	
PB7		28	c8					RA		PU		PD	n	m	,<		.>	/?	RS	
 */


