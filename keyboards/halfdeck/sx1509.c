/*
Copyright 2016-2018 Wez Furlong

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
#include "config.h"
#include <stdbool.h>
#include "debug.h"

#include "i2c.h"

// Controls the SX1509 16 pin I/O expander
static bool initialized;
static uint8_t reinit_counter;

#define i2cAddress 0x3e // Configurable with jumpers
enum sx1509_registers {
  RegReset = 0x7d,
  RegDirA = 0x0f,
  RegDirB = 0x0e,
  RegPullUpA = 0x07,
  RegPullUpB = 0x06,
  DataA = 0x11,
  DataB = 0x10,
};

#define set_reg(reg, val) if (!twi_write_register(i2cAddress, reg, val)) { goto done; }

bool sx1509_init(void) {
  initialized = false;

  // Software reset
  set_reg(RegReset, 0x12);
  set_reg(RegReset, 0x34);

  _delay_ms(25);

  // set pin directions: 1 is input, 0 is output
  set_reg(RegDirA, 0b11000000);
  set_reg(RegDirB, 0b01111111);

  // 1 is high
  set_reg(DataA, 0b00111111);

  // internal pull-ups; 1 is pull up enabled
  set_reg(RegPullUpA, 0);
  set_reg(RegPullUpB, 0b01111111);

  initialized = true;
done:
  if (!initialized) {
    xprintf("failed to init sx1509\n");
  } else {
    xprintf("sx1509 initialized!\n");
  }
  return initialized;
}

bool sx1509_make_ready(void) {
  if (initialized) {
    return true;
  }
  // This will roll over 1 every 255 matrix scans
  if (reinit_counter++ != 0) {
    return false;
  }
  return sx1509_init();
}

bool sx1509_unselect_rows(void) {
  // 1 is high
  set_reg(DataA, 0b00111111);
  return true;
done:
  return false;
}

bool sx1509_select_row(uint8_t row) {
  // Set just this row to to LOW in the expander, the rest are HIGH
  set_reg(DataA, ~(1 << row) & 0b00111111);
  return true;
done:
  return false;
}

bool sx1509_unselect_row(uint8_t row) {
  return sx1509_unselect_rows();
}

bool read_one(uint8_t reg, uint8_t *val) {
  return twi_read_register(i2cAddress, reg, val);
}

// Read all 16 inputs and return them
uint8_t sx1509_read_b(uint8_t current_row) {
  uint8_t pins = 0;

  if (!initialized) {
    // xprintf("sx1509: read pins for row %d failed: need init\n", current_row);
    return 0;
  }

  if (read_one(DataB, &pins)) {
    return ~pins;
  }

  return 0;
}
