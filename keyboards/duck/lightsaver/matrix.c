/*
Copyright 2016-2017 Ralf Schmitt <ralf@bunkertor.net> Rasmus Schults <rasmusx@gmail.com>
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

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "matrix.h"
#include "util.h"
#include "print.h"
#include "debug.h"

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static uint8_t read_fwkey(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);


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

void matrix_init(void) {
  DDRD  |=  0b11010000;
  PORTD &= ~0b01010000;
  DDRB  |=  0b00011111;
  PORTB &= ~0b00001110;
  PORTB |=  0b00010001;
  DDRE  |=  0b01000000;
  PORTE &= ~0b01000000;

  unselect_cols();
  init_rows();

  for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_init_kb();
}

uint8_t matrix_scan(void) {
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_col(col);
    _delay_us(3);

    uint8_t rows = read_rows();
    if(col == 0) {
      rows |= read_fwkey();
    }
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
      bool curr_bit = rows & (1<<row);
      if (prev_bit != curr_bit) {
        matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
        if (debouncing) {
            dprint("bounce!: "); dprintf("%02X", debouncing); dprintln();
        }        
        debouncing = DEBOUNCE;
      }
    }
    unselect_cols();
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

inline matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
  }
}

/* Row pin configuration
 * row: 0    1    2    3    4    5
 * pin: PB7  PD0  PD1  PD2  PD3  PD5
 *
 * Esc uses its own pin PE2
 */
static void init_rows(void) {
  DDRB  &= ~0b10000000;
  PORTB &= ~0b10000000;

  DDRD  &= ~0b00101111;
  PORTD &= ~0b00101111;

  DDRE  &= ~0b00000100;
  PORTE |=  0b00000100;
}

static uint8_t read_rows(void) {
  return (PINB&(1<<7) ? (1<<0) : 0) |
    (PIND&(1<<0) ? (1<<1) : 0) |
    (PIND&(1<<1) ? (1<<2) : 0) |
    (PIND&(1<<2) ? (1<<3) : 0) |
    (PIND&(1<<3) ? (1<<4) : 0) |
    (PIND&(1<<5) ? (1<<5) : 0);
}

static uint8_t read_fwkey(void)
{
  return PINE&(1<<2) ? 0 : (1<<0);
}

/* Columns 0 - 15
 * These columns uses two 74HC237D 3 to 8 bit demultiplexers.
 * col / pin:    PC6  PB6  PF0  PF1  PC7
 * 0:             1    0    0    0    0
 * 1:             1    0    1    0    0
 * 2:             1    0    0    1    0
 * 3:             1    0    1    1    0
 * 4:             1    0    0    0    1
 * 5:             1    0    1    0    1
 * 6:             1    0    0    1    1
 * 7:             1    0    1    1    1
 * 8:             0    1    0    0    0
 * 9:             0    1    1    0    0
 * 10:            0    1    0    1    0
 * 11:            0    1    1    1    0
 * 12:            0    1    0    0    1
 * 13:            0    1    1    0    1
 * 14:            0    1    0    1    1
 * 15:            0    1    1    1    1
 *
 * col: 16
 * pin: PB5
 *
 * col: 17
 * pin: PB4
 *
 * col: 18
 * pin: PD7
 */
static void unselect_cols(void) {
  DDRB  |=  0b01110000;
  PORTB &= ~0b01110000;

  DDRC |= (1<<6) | (1<<7);
  PORTC &= ~((1<<6) | (1<<7));

  DDRF |= (1<<0) | (1<<1);
  PORTF &= ~((1<<0) | (1<<1));

  DDRD |= (1<<7);
  PORTD &= ~(1<<7);
}

static void select_col(uint8_t col) {
  switch (col) {
    case 0:
      PORTC |= (1<<6);
      break;
    case 1:
      PORTC |= (1<<6);
      PORTF |= (1<<0);
      break;
    case 2:
      PORTC |= (1<<6);
      PORTF |= (1<<1);
      break;
    case 3:
      PORTC |= (1<<6);
      PORTF |= (1<<0) | (1<<1);
      break;
    case 4:
      PORTC |= (1<<6);
      PORTC |= (1<<7);
      break;
    case 5:
      PORTC |= (1<<6);
      PORTF |= (1<<0);
      PORTC |= (1<<7);
      break;
    case 6:
      PORTC |= (1<<6);
      PORTF |= (1<<1);
      PORTC |= (1<<7);
      break;
    case 7:
      PORTC |= (1<<6);
      PORTF |= (1<<0) | (1<<1);
      PORTC |= (1<<7);
      break;
    case 8:
      PORTB |= (1<<6);
      break;
    case 9:
      PORTB |= (1<<6);
      PORTF |= (1<<0);
      break;
    case 10:
      PORTB |= (1<<6);
      PORTF |= (1<<1);
      break;
    case 11:
      PORTB |= (1<<6);
      PORTF |= (1<<0) | (1<<1);
      break;
    case 12:
      PORTB |= (1<<6);
      PORTC |= (1<<7);
      break;
    case 13:
      PORTB |= (1<<6);
      PORTF |= (1<<0);
      PORTC |= (1<<7);
      break;
    case 14:
      PORTB |= (1<<6);
      PORTF |= (1<<1);
      PORTC |= (1<<7);
      break;
    case 15:
      PORTB |= (1<<6);
      PORTF |= (1<<0) | (1<<1);
      PORTC |= (1<<7);
      break;
    case 16:
      PORTB |= (1<<5);
      break;
    case 17:
      PORTB |= (1<<4);
      break;
    case 18:
      PORTD |= (1<<7);
      break;
  }
}
