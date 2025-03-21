/*
Copyright 2019 MechMerlin <mechmerlin@gmail.com>
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
  // DDRD  |=  0b11010000;
  // PORTD &= ~0b01010000;
  // PORTD |=  0b10000000;
  // DDRB  |=  0b00011111;
  // PORTB &= ~0b00001110;
  // PORTB |=  0b00010001;
  // DDRE  |=  0b01000000;
  // PORTE &= ~0b01000000;
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
 * Reset Key uses its own pin PE2
 */
static void init_rows(void) {
    DDRD  &= ~0b00101111;
    PORTD &= ~0b00101111;

    DDRB  &= ~0b10000000;
    PORTB &= ~0b10000000;

    DDRE  &= ~0b00000100;
    PORTE |=  0b00000100;
}

static uint8_t read_rows(uint8_t col) {
  if (col == 19) {
    return PINE&(1<<2) ? 0 : (1<<0);
  } else {
      return (PIND&(1<<0) ? (1<<1) : 0) |
             (PIND&(1<<1) ? (1<<2) : 0) |
             (PIND&(1<<2) ? (1<<3) : 0) |
             (PIND&(1<<3) ? (1<<4) : 0) |
             (PIND&(1<<5) ? (1<<5) : 0) |
             (PINB&(1<<7) ? (1<<0) : 0);
    }
}


/* Columns 0 - G
 * These columns uses two 74HC237D 3 to 8 bit demultiplexers.
 *
 * atmega32u4    decoder    pin
 *    C6           U1       E2
 *    B6           U2       E2
 *    F0          U1, U2    A0
 *    F1          U1, U2    A1
 *    C7          U1, U2    A2
 *
 * col 0: B4
 * col 1: D7
 * col I: B5
 *
 * col / pin:    PC6  PB6  PF0  PF1  PC7  Decoder Pin
 * 2:             1    0    0    0    0     U1    Y0
 * 3:             1    0    1    0    0     U1    Y1
 * 4:             1    0    0    1    0     U1    Y2
 * 5:             1    0    1    1    0     U1    Y3
 * 6:             1    0    0    0    1     U1    Y4
 * 7:             1    0    1    0    1     U1    Y5
 * 8:             1    0    0    1    1     U1    Y6
 * 9:             1    0    1    1    1     U1    Y7
 * A:             0    1    0    0    0     U2    Y0
 * B:             0    1    1    0    0     U2    Y1
 * C:             0    1    0    1    0     U2    Y2
 * D:             0    1    1    1    0     U2    Y3
 * E:             0    1    0    0    1     U2    Y4
 * F:             0    1    1    0    1     U2    Y5
 * G:             0    1    0    1    1     U2    Y6
 * H:             0    1    1    1    1     U2    Y7
 *
 */
static void unselect_cols(void) {
  DDRB  |=  0b01110000;
  PORTB &= ~0b01110000;

  DDRC  |=  0b11000000;
  PORTC &= ~0b11000000;

  DDRD  |=  0b10000000;
  PORTD &= ~0b10000000;

  DDRF  |=  0b00000011;
  PORTF &= ~0b00000011;
}

static void select_col(uint8_t col) {
 
   switch (col) {
        case 0:
            PORTB |= 0b00010000;
            break;
        case 1:
            PORTD |= 0b10000000;
            break;
        case 2: // U1 Y0
            PORTC |= 0b01000000;
            break;
        case 3: // U1 Y1
            PORTC |= 0b01000000;
            PORTF |= 0b00000001;
            break;
        case 4: // U1 Y2
            PORTC |= 0b01000000;
            PORTF |= 0b00000010;
            break;
        case 5: // U1 Y3
            PORTC |= 0b01000000;
            PORTF |= 0b00000011;
            break;
        case 6: // U1 Y4
            PORTC |= 0b11000000;
            break;
        case 7: // U1 Y5
            PORTC |= 0b11000000;
            PORTF |= 0b00000001;
            break;
        case 8: // U1 Y6
            PORTC |= 0b11000000;
            PORTF |= 0b00000010;
            break;
        case 9: // U1 Y7
            PORTC |= 0b11000000;
            PORTF |= 0b00000011;
            break;
        case 10: // U2 Y0
            PORTB |= 0b01000000;
            break;
        case 11: // U2 Y1
            PORTB |= 0b01000000;
            PORTF |= 0b00000001;
            break;
        case 12: // U2 Y2
            PORTB |= 0b01000000;
            PORTF |= 0b00000010;
            break;
        case 13: // U2 Y3
            PORTB |= 0b01000000;
            PORTF |= 0b00000011;
            break;
        case 14: // U2 Y4
            PORTB |= 0b01000000;
            PORTC |= 0b10000000;
            break;
        case 15: // U2 Y5
            PORTB |= 0b01000000;
            PORTC |= 0b10000000;
            PORTF |= 0b00000001;
            break;
        case 16: // U2 Y6
            PORTB |= 0b01000000;
            PORTC |= 0b10000000;
            PORTF |= 0b00000010;
            break;
        case 17: // U2 Y7
            PORTB |= 0b01000000;
            PORTC |= 0b10000000;
            PORTF |= 0b00000011;
            break;
        case 18:
            PORTB |= 0b00100000;
            break;
    }
}
