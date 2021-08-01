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
#include "mcp2301x.h"

#define MCP2301X_ADDR 0b0100000

#define MCP2301X_TIMEOUT 100

#define PINS2REG(pins) \
    { pins & 0xFF, pins >> 8 }

#define REG2PINS(reg) \
    ( reg[0] | (reg[1] << 8) )

static i2c_status_t mcp2301x_status = I2C_STATUS_ERROR;

void mcp2301x_init(mcp2301x_pin_t input, mcp2301x_pin_t pullup, mcp2301x_pin_t enabled) {
    const uint8_t gpio[] = PINS2REG(enabled);
    const uint8_t iodir[] = PINS2REG(input);
    const uint8_t gppu[] = PINS2REG(pullup);

    mcp2301x_status = I2C_STATUS_SUCCESS;
    mcp2301x_writeReg(GPIOA, gpio, 2);
    mcp2301x_writeReg(IODIRA, iodir, 2);
    mcp2301x_writeReg(GPPUA, gppu, 2);
}

bool mcp2301x_reset_required(void) { return mcp2301x_status != I2C_STATUS_SUCCESS; }

mcp2301x_status_t mcp2301x_writePins(mcp2301x_pin_t gpio) {
    const uint8_t reg[2] = PINS2REG(gpio);
    return mcp2301x_writeReg(GPIOA, reg, 2);
}

mcp2301x_status_t mcp2301x_readPins(mcp2301x_pin_t* gpio) {
    uint8_t           reg[2];
    mcp2301x_status_t status = mcp2301x_readReg(GPIOA, reg, 2);
    if (!status) {
        *gpio = REG2PINS(reg);
    }

    return status;
}

i2c_status_t mcp2301x_writeReg(uint8_t regaddr, const uint8_t* data, uint16_t length) {
    if (mcp2301x_status) {
        return mcp2301x_status;
    }

    mcp2301x_status = i2c_writeReg((MCP2301X_ADDR << 1), regaddr, data, length, MCP2301X_TIMEOUT);
    return mcp2301x_status;
}

i2c_status_t mcp2301x_readReg(uint8_t regaddr, uint8_t* data, uint16_t length) {
    if (mcp2301x_status) {
        return mcp2301x_status;
    }

    mcp2301x_status = i2c_readReg((MCP2301X_ADDR << 1), regaddr, data, length, MCP2301X_TIMEOUT);
    return mcp2301x_status;
}
