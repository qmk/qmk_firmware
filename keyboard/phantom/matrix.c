/* Copyright 2012 Jun Wako <wakojun@gmail.com>
 *
 * This is heavily based on phantom/board.{c|h}.
 * https://github.com/BathroomEpiphanies/AVR-Keyboard
 *
 * Copyright (c) 2012 Fredrik Atmer, Bathroom Epiphanies Inc
 * http://bathroomepiphanies.com
 *
 * As for liscensing consult with the original files or its author.
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	0
#endif
static uint8_t debouncing = DEBOUNCE;

// bit array of key state(1:on, 0:off)
static matrix_row_t *matrix;
static matrix_row_t *matrix_debounced;
static matrix_row_t matrix0[MATRIX_ROWS];
static matrix_row_t matrix1[MATRIX_ROWS];


#define _DDRA (uint8_t *const)&DDRA
#define _DDRB (uint8_t *const)&DDRB
#define _DDRC (uint8_t *const)&DDRC
#define _DDRD (uint8_t *const)&DDRD
#define _DDRE (uint8_t *const)&DDRE
#define _DDRF (uint8_t *const)&DDRF

#define _PINA (uint8_t *const)&PINA
#define _PINB (uint8_t *const)&PINB
#define _PINC (uint8_t *const)&PINC
#define _PIND (uint8_t *const)&PIND
#define _PINE (uint8_t *const)&PINE
#define _PINF (uint8_t *const)&PINF

#define _PORTA (uint8_t *const)&PORTA
#define _PORTB (uint8_t *const)&PORTB
#define _PORTC (uint8_t *const)&PORTC
#define _PORTD (uint8_t *const)&PORTD
#define _PORTE (uint8_t *const)&PORTE
#define _PORTF (uint8_t *const)&PORTF

#define _BIT0 0x01
#define _BIT1 0x02
#define _BIT2 0x04
#define _BIT3 0x08
#define _BIT4 0x10
#define _BIT5 0x20
#define _BIT6 0x40
#define _BIT7 0x80

/* Specifies the ports and pin numbers for the rows */
static
uint8_t *const row_ddr[MATRIX_ROWS] = {_DDRB,  _DDRB,  _DDRB,  _DDRB,  _DDRB,  _DDRB};

static
uint8_t *const row_port[MATRIX_ROWS] = {_PORTB, _PORTB, _PORTB, _PORTB, _PORTB, _PORTB};

static
uint8_t *const row_pin[MATRIX_ROWS] = {_PINB,  _PINB,  _PINB,  _PINB,  _PINB,  _PINB};

static
const uint8_t row_bit[MATRIX_ROWS] = { _BIT0,  _BIT1,  _BIT2,  _BIT3,  _BIT4,  _BIT5};

/* Specifies the ports and pin numbers for the columns */
static
uint8_t *const  col_ddr[MATRIX_COLS] = { _DDRD,  _DDRC,  _DDRC,  _DDRD,  _DDRD,  _DDRE,
				  _DDRF,  _DDRF,  _DDRF,  _DDRF,  _DDRF,  _DDRF,
				  _DDRD,  _DDRD,  _DDRD,  _DDRD,  _DDRD};

static
uint8_t *const col_port[MATRIX_COLS] = {_PORTD, _PORTC, _PORTC, _PORTD, _PORTD, _PORTE,
				 _PORTF, _PORTF, _PORTF, _PORTF, _PORTF, _PORTF,
				 _PORTD, _PORTD, _PORTD, _PORTD, _PORTD};

static
const uint8_t   col_bit[MATRIX_COLS] = {  _BIT5,  _BIT7,  _BIT6,  _BIT4,  _BIT0,  _BIT6,
				  _BIT0,  _BIT1,  _BIT4,  _BIT5,  _BIT6,  _BIT7,
				  _BIT7,  _BIT6,  _BIT1,  _BIT2,  _BIT3};

static
inline void pull_column(int col) {
  *col_port[col] &= ~col_bit[col];
}

static
inline void release_column(int col) {
  *col_port[col] |=  col_bit[col];
}

/* PORTB is set as input with pull-up resistors
   PORTC,D,E,F are set to high output */

static
void setup_io_pins(void) {
  uint8_t row, col;
  for(row = 0; row < MATRIX_ROWS; row++) {
    *row_ddr[row]  &= ~row_bit[row];
    *row_port[row] |=  row_bit[row];
  }
  for(col = 0; col < MATRIX_COLS; col++) {
    *col_ddr[col]  |= col_bit[col];
    *col_port[col] |= col_bit[col];
  }
}

/* LEDs are on output compare pins OC1B OC1C
   This activates fast PWM mode on them.
   Prescaler 256 and 8-bit counter results in
   16000000/256/256 = 244 Hz blink frequency.
   LED_A: Caps Lock
   LED_B: Scroll Lock  */
/* Output on PWM pins are turned off when the timer 
   reaches the value in the output compare register,
   and are turned on when it reaches TOP (=256). */
static
void setup_leds(void) {
  TCCR1A |=      // Timer control register 1A
    (1<<WGM10) | // Fast PWM 8-bit
    (1<<COM1B1)| // Clear OC1B on match, set at TOP
    (1<<COM1C1); // Clear OC1C on match, set at TOP
  TCCR1B |=      // Timer control register 1B
    (1<<WGM12) | // Fast PWM 8-bit
    (1<<CS12);   // Prescaler 256
  OCR1B = 250;    // Output compare register 1B
  OCR1C = 250;    // Output compare register 1C
  // LEDs: LED_A -> PORTB6, LED_B -> PORTB7
  DDRB  &= 0x3F;
  PORTB &= 0x3F;
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
    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
	
    // initialize row and col
    setup_io_pins();
    setup_leds();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
        matrix0[i] = 0;
        matrix1[i] = 0;
    }
    matrix = matrix0;
    matrix_debounced = matrix1;
}

uint8_t matrix_scan(void)
{
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {  // 0-16
        pull_column(col);   // output hi on theline
        _delay_us(3);       // without this wait it won't read stable value.
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {  // 0-5
            bool prev_bit = matrix[row] & ((matrix_row_t)1<<col);
            bool curr_bit = !(*row_pin[row] & row_bit[row]);
            if (prev_bit != curr_bit) {
                matrix[row] ^= ((matrix_row_t)1<<col);
                if (debouncing) {
                    debug("bounce!: "); debug_hex(debouncing); print("\n");
                }
                debouncing = DEBOUNCE;
            }
        }
        release_column(col);
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            matrix_row_t *tmp = matrix_debounced;
            matrix_debounced = matrix;
            matrix = tmp;
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    // NOTE: no longer used
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix_debounced[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix_debounced[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for (uint8_t j = 0; j < MATRIX_COLS; j++) {
            if (matrix_is_on(i, j))
                count++;
        }
    }
    return count;
}
