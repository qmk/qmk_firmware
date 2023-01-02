/* Copyright 2017-2019 Nikolaus Wittenstein <nikolaus.wittenstein@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include "datahand.h"

#include "matrix.h"
#include "action.h"

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

static matrix_row_t matrix[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void select_row(uint8_t row);

// user-defined overridable functions

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

// helper functions
void matrix_init(void) {
  /* See datahand.h for more detail on pins. */

  /* 7 - matrix scan; 6-3 - mode LEDs */
  DDRB = 0b11111000;

  /* 1-0 - matrix scan */
  DDRD = 0b00000011;

  /* 6 - matrix scan */
  DDRE = 0b01000000;

  /* 7-4 - lock LEDs */
  DDRF = 0b11110000;

  /* Turn off the non-Normal LEDs (they're active low). */
  PORTB |= LED_TENKEY | LED_FN | LED_NAS;

  /* Turn off the lock LEDs. */
  PORTF |= LED_CAPS_LOCK | LED_NUM_LOCK | LED_SCROLL_LOCK | LED_MOUSE_LOCK;

  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    select_row(row);
    /* The default hardware works down to at least 100us, but I have a replacement
     * photodiode that responds a little more slowly. Cranking it up to 1000us fixes
     * shadowing issues.
     */
    _delay_us(1000);
    matrix[row] = read_cols();
  }

  matrix_scan_quantum();

  return 1;
}

matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

void matrix_print(void) {
  print("\nr/c 01234567\n");

  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    print_hex8(row);
    print(": ");
    print_bin_reverse8(matrix_get_row(row));
    print("\n");
  }
}

static void select_row(uint8_t row) {
  /* Original 8051: P1 bits 0-3 (pins 1-4)
   * Teensy++: PE0, PB7, PD0, PD1
   */

  if (row & (1<<0)) {
    PORTE |= (1<<6);
  } else {
    PORTE &= ~(1<<6);
  }

  if (row & (1<<1)) {
    PORTB |= (1<<7);
  } else {
    PORTB &= ~(1<<7);
  }

  if (row & (1<<2)) {
    PORTD |= (1<<0);
  } else {
    PORTD &= ~(1<<0);
  }

  if (row & (1<<3)) {
    PORTD |= (1<<1);
  } else {
    PORTD &= ~(1<<1);
  }
}

static matrix_row_t read_cols(void) {
  /* Original 8051: P1 bits 4-7 (pins 5-8)
   * Teensy++: PD bits 2-5
   */

  return (PIND & 0b00111100) >> 2;
}
