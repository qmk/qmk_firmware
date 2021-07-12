/*
 * Copyright 2020 Richard Titmuss (richard.titmuss@gmail.com)
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

#define IODIRA 0x00
#define IODIRB 0x01
#define GPPUA 0x0C
#define GPPUB 0x0D
#define GPIOA 0x12
#define GPIOB 0x13

#define GPA0 (1 << 0)
#define GPA1 (1 << 1)
#define GPA2 (1 << 2)
#define GPA3 (1 << 3)
#define GPA4 (1 << 4)
#define GPA5 (1 << 5)
#define GPA6 (1 << 6)
#define GPA7 (1 << 7)
#define GPB0 (1 << 8)
#define GPB1 (1 << 9)
#define GPB2 (1 << 10)
#define GPB3 (1 << 11)
#define GPB4 (1 << 12)
#define GPB5 (1 << 13)
#define GPB6 (1 << 14)
#define GPB7 (1 << 15)

typedef uint16_t mcp2301x_pin_t;

typedef int16_t mcp2301x_status_t;

void              mcp2301x_init(mcp2301x_pin_t input, mcp2301x_pin_t pullup, mcp2301x_pin_t enabled);
bool              mcp2301x_reset_required(void);
mcp2301x_status_t mcp2301x_writePins(mcp2301x_pin_t gpio);
mcp2301x_status_t mcp2301x_readPins(mcp2301x_pin_t* gpio);

mcp2301x_status_t mcp2301x_writeReg(uint8_t regaddr, const uint8_t* data, uint16_t length);
mcp2301x_status_t mcp2301x_readReg(uint8_t regaddr, uint8_t* data, uint16_t length);
