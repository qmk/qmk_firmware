/*
Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>
Modified by Ryan Skidmore <rskeys@ryanskidmore.co.uk> (@ryanskidmore)
to support the rskeys100.

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

#include "matrix.h"
#include <util/delay.h>

static const uint32_t col_values[24] = SHR_COLS;

static uint8_t read_rows(void);
static void    select_col(uint8_t col);

static void    shift_pulse(void);
static void    shift_out_single(uint8_t value);
static void    shift_out(uint32_t value);

void matrix_init_custom(void) {
  gpio_set_pin_input(ROW_A);
  gpio_set_pin_input(ROW_B);
  gpio_set_pin_input(ROW_C);
  gpio_set_pin_input(ROW_D);
  gpio_set_pin_input(ROW_E);
  gpio_set_pin_input(ROW_F);

  gpio_set_pin_output(SHR_DATA);
  gpio_set_pin_output(SHR_LATCH);
  gpio_set_pin_output(SHR_CLOCK);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        _delay_us(1);
        uint8_t rows = read_rows();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = ((uint32_t)(current_matrix[row]) & (matrix_row_t)(1UL << col)) ? 1 : 0;
            bool curr_bit = ((uint32_t)rows & (uint32_t)(1UL << row)) ? 1 : 0;
            if (prev_bit != curr_bit) {
                current_matrix[row] = (uint32_t)(current_matrix[row]) ^ (uint32_t)(1UL << col);
                changed = true;
            }
        }
    }

    return changed;
}

static uint8_t read_rows(void) {
  return (gpio_read_pin(ROW_F) << 5)
         | (gpio_read_pin(ROW_E) << 4)
         | (gpio_read_pin(ROW_D) << 3)
         | (gpio_read_pin(ROW_C) << 2)
         | (gpio_read_pin(ROW_B) << 1)
         | (gpio_read_pin(ROW_A) );
}

static void select_col(uint8_t col) {
    shift_out(col_values[col]);
}

static void shift_out(uint32_t value) {
  gpio_write_pin_low(SHR_LATCH);
  uint8_t first_byte  = (value >> 16) & 0xFF;
  uint8_t second_byte  = (value >> 8) & 0xFF;
  uint8_t third_byte = (uint8_t)(value & 0xFF);

  shift_out_single(first_byte);
  shift_out_single(second_byte);
  shift_out_single(third_byte);
  gpio_write_pin_high(SHR_LATCH);
  /* We delay here to prevent multiple consecutive keys being triggered with a single switch press */
  _delay_us(10);
}

static void shift_out_single(uint8_t value) {
    for (uint8_t i = 0; i < 8; i++) {
        if (value & 0b10000000) {
            gpio_write_pin_high(SHR_DATA);
        } else {
            gpio_write_pin_low(SHR_DATA);
        }

        shift_pulse();
        value = value << 1;
    }
}

static inline void shift_pulse(void) {
    gpio_write_pin_high(SHR_CLOCK);
    gpio_write_pin_low(SHR_CLOCK);
}