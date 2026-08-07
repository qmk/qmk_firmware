/*
 * Copyright 2020 Richard Titmuss (richard.titmuss@gmail.com)
 * Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar
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

#include "i2c_master.h"
#include "mcp23018.h"

#define MCP23018_ADDR 0b0100000

#define MCP23018_TIMEOUT 100

static i2c_status_t mcp23018_status = I2C_STATUS_ERROR;

void msp23018_init(void) {
    mcp23018_status = I2C_STATUS_SUCCESS;

    // Set pin direction
    uint8_t iodir[] = {0b00001111, 0b11111111};
    mcp23018_writeReg(IODIRA, iodir, 2);

    // Set pull-up
    uint8_t gppu[] = {0b00001111, 0b11111000};
    mcp23018_writeReg(GPPUA, gppu, 2);

    // LEDs output high
    uint8_t gpio[] = {0b00000000, 0b00000111};
    mcp23018_writeReg(GPIOA, gpio, 2);
}

bool mcp23018_reset_required(void) { return mcp23018_status != I2C_STATUS_SUCCESS; }

i2c_status_t mcp23018_writeReg(uint8_t regaddr, const uint8_t* data, uint16_t length) {
    if (mcp23018_status) {
        return mcp23018_status;
    }

    mcp23018_status = i2c_write_register((MCP23018_ADDR << 1), regaddr, data, length, MCP23018_TIMEOUT);
    return mcp23018_status;
}

i2c_status_t mcp23018_readReg(uint8_t regaddr, uint8_t* data, uint16_t length) {
    if (mcp23018_status) {
        return mcp23018_status;
    }

    mcp23018_status = i2c_read_register((MCP23018_ADDR << 1), regaddr, data, length, MCP23018_TIMEOUT);
    return mcp23018_status;
}
