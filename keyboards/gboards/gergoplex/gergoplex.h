/* Copyright 2021 Jane Bernhardt
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#pragma once

#include "quantum.h"
#include "i2c_master.h"

extern i2c_status_t mcp23018_status;
#define I2C_TIMEOUT 1000

#define XXX KC_NO

// I2C aliases and register addresses (see "mcp23018.md")
#define I2C_ADDR (0x20 << 1)  // 0b0100000
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA 0x0C  // GPIO pull-up resistor register
#define GPIOA 0x12  // general purpose i/o port register (write modifies OLAT)
#define OLATA 0x14  // output latch register

uint8_t init_mcp23018(void);
