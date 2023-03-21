/*
Copyright 2017 MechMerlin <mechmerlin@gmail.com>
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

static uint8_t read_rows(uint8_t col);
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

void backlight_init_ports(void)
{
    DDRB |= 0b00011111;  // PB0 (caps), PB1 (alpha), PB2 (extra), PB3 (modnum), PB4 (caps)
    DDRD |= 0b11010000;  // PD4, (rgb blue), PD6 (rgb red), PD7 (rgb green)
    DDRE |= 0b01000000;  // PE6 (frow)
}

void matrix_init(void) {
  backlight_init_ports();
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

    uint8_t rows = read_rows(col);

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
    DDRD  &= ~0b00101111; // PD0, PD1, PD2, PD3, PD5 input
    PORTD &= ~0b00101111; // PD0, PD1, PD2, PD3, PD5 low

    DDRB  &= ~0b10000000; // PB7 input
    PORTB &= ~0b10000000; // PB7 low

    DDRE  &= ~0b00000100; // PE2 input
    PORTE |=  0b00000100; // PE2 high
}

static uint8_t read_rows(uint8_t col) {
  if (col == 14) {
    return PINE&(1<<2) ? 0 : (1<<0);        // PE2 (Row 0)
  } else {
      return (PIND&(1<<0) ? (1<<0) : 0) |   // PD0 (Row 0)
             (PIND&(1<<1) ? (1<<1) : 0) |   // PD1 (Row 1)
             (PIND&(1<<2) ? (1<<2) : 0) |   // PD2 (Row 2)
             (PIND&(1<<3) ? (1<<3) : 0) |   // PD3 (Row 3)
             (PIND&(1<<5) ? (1<<4) : 0) |   // PD5 (Row 4)
             (PINB&(1<<7) ? (1<<5) : 0);    // PB7 (Row 5)
    }
}

uint8_t read_fwkey(void)
{
  return PINE&(1<<2) ? 0 : (1<<0);
}

static void unselect_cols(void) {
    DDRB  |=  0b01000000; // PB6 (U2) output
    PORTB &= ~0b01000000; // PB6 (U2) low

    DDRC  |=  0b11000000; // PC6 (U1), PC7 (A2) output
    PORTC &= ~0b11000000; // PC6 (U1), PC7 (A2) low

    DDRF  |=  0b00000011; // PF0 (A0), PF1 (A1) output
    PORTF &= ~0b00000011; // PF0 (A0), PF1 (A1) low
}

static void select_col(uint8_t col) {
 
   switch (col) {
        case 0:
            PORTC |= 0b01000000; // PC6 high
            break;
        case 1:
            PORTC |= 0b01000000; // PC6 high
            PORTF |= 0b00000001; // PF0 high
            break;
        case 2:
            PORTC |= 0b01000000; // PC6 high
            PORTF |= 0b00000010; // PF1 high
            break;
        case 3:
            PORTC |= 0b01000000; // PC6 high
            PORTF |= 0b00000011; // PF0, PF1 high
            break;
        case 4:
            PORTC |= 0b11000000; // PC6, PC7 high
            break;
        case 5:
            PORTC |= 0b11000000; // PC6, PC7 high
            PORTF |= 0b00000001; // PF0 high
            break;
        case 6:
            PORTC |= 0b11000000; // PC6, PC7 high
            PORTF |= 0b00000010; // PF1 high
            break;
        case 7:
            PORTC |= 0b11000000; // PC6, PC7 high
            PORTF |= 0b00000011; // PF0, PF1 high
            break;
        case 8:
            PORTB |= 0b01000000; // PB6 high
            break;
        case 9:
            PORTB |= 0b01000000; // PB6 high
            PORTF |= 0b00000001; // PF0 high
            break;
        case 10:
            PORTB |= 0b01000000; // PB6 high
            PORTF |= 0b00000010; // PF1 high
            break;
        case 11:
            PORTB |= 0b01000000; // PB6 high
            PORTF |= 0b00000011; // PF0, PF1 high
            break;
        case 12:
            PORTB |= 0b01000000; // PB6 high
            PORTC |= 0b10000000; // PC7 high
            break;
        case 13:
            PORTB |= 0b01000000; // PB6 high
            PORTF |= 0b00000001; // PF0 high
            PORTC |= 0b10000000; // PC7 high
            break;
        case 15:
            PORTB |= 0b01000000; // PB6 high
            PORTF |= 0b00000010; // PF1 high
            PORTC |= 0b10000000; // PC7 high
            break;
    }
}
