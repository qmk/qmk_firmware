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
#define I2C_ADDR 0x20  // 0b0100000
#define I2C_ADDR_WRITE ((I2C_ADDR << 1) | I2C_WRITE)
#define I2C_ADDR_READ ((I2C_ADDR << 1) | I2C_READ)
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA 0x0C  // GPIO pull-up resistor register
#define GPIOA 0x12  // general purpose i/o port register (write modifies OLAT)
#define OLATA 0x14  // output latch register

uint8_t init_mcp23018(void);

#define LAYOUT_split_3x5_3( \
    L00, L01, L02, L03, L04,        R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14,        R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24,        R20, R21, R22, R23, R24, \
                L30, L31, L32,    R30, R31, R32 \
) { \
    { L04, L14, L24, XXX }, \
    { L03, L13, L23, L32 }, \
    { L02, L12, L22, L31 }, \
    { L01, L11, L21, L30 }, \
    { L00, L10, L20, XXX }, \
    { R00, R10, R20, XXX }, \
    { R01, R11, R21, R30 }, \
    { R02, R12, R22, R31 }, \
    { R03, R13, R23, R32 }, \
    { R04, R14, R24, XXX } \
}
