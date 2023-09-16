/* Copyright 2019 Neil Kettle
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

#ifdef RIGHT_HALF
# include <stdint.h>
# include "i2c_master.h"

// I2C aliases and register addresses (see "mcp23018.md")
# define I2C_ADDR        0b0100000
# define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
# define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
# define IODIRA          0x00            // i/o direction register
# define IODIRB          0x01
# define GPPUA           0x0C            // GPIO pull-up resistor register
# define GPPUB           0x0D
# define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
# define GPIOB           0x13
# define OLATA           0x14            // output latch register
# define OLATB           0x15

extern i2c_status_t mcp23018_status;
# define MCP23018_I2C_TIMEOUT 100

uint8_t init_mcp23018(void);
#endif
