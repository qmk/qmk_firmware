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

#include QMK_KEYBOARD_H
#include "i2c_master.h"
#include "mcp23018.h"

#define MCP23018_ADDR 0b0100000

#define MCP23018_TIMEOUT 100

#define PIN2REG(pin) \
    { pin & 0xFF, pin >> 8 }

static i2c_status_t mcp23018_status = I2C_STATUS_ERROR;

void mcp23018_init(mcp23018_pin_t input, mcp23018_pin_t pullup, mcp23018_pin_t enabled) {
    const uint8_t gpio[] = PIN2REG(enabled);
    const uint8_t iodir[] = PIN2REG(input);
    const uint8_t gppu[] = PIN2REG(pullup);

    mcp23018_status = I2C_STATUS_SUCCESS;
    mcp23018_writeReg(GPIOA, gpio, 2);
    mcp23018_writeReg(IODIRA, iodir, 2);
    mcp23018_writeReg(GPPUA, gppu, 2);
}

bool mcp23018_reset_required(void) { return mcp23018_status != I2C_STATUS_SUCCESS; }

mcp23018_status_t mcp23018_writeGpio(mcp23018_pin_t gpio) {
    const uint8_t reg[2] = PIN2REG(gpio);
    return mcp23018_writeReg(GPIOA, reg, 2);
}

mcp23018_status_t mcp23018_readGpio(mcp23018_pin_t* gpio) {
    uint8_t           reg[2];
    mcp23018_status_t status = mcp23018_readReg(GPIOA, reg, 2);
    if (!status) {
        *gpio = reg[0] | (reg[1] << 8);
    }

    return status;
}

i2c_status_t mcp23018_writeReg(uint8_t regaddr, const uint8_t* data, uint16_t length) {
    if (mcp23018_status) {
        return mcp23018_status;
    }

    mcp23018_status = i2c_writeReg((MCP23018_ADDR << 1), regaddr, data, length, MCP23018_TIMEOUT);
    return mcp23018_status;
}

i2c_status_t mcp23018_readReg(uint8_t regaddr, uint8_t* data, uint16_t length) {
    if (mcp23018_status) {
        return mcp23018_status;
    }

    mcp23018_status = i2c_readReg((MCP23018_ADDR << 1), regaddr, data, length, MCP23018_TIMEOUT);
    return mcp23018_status;
}
