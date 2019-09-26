/* Copyright 2020 zvecr<git@zvecr.com>
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
#include "mcp23018.h"
#include "i2c_master.h"
#include "wait.h"
#include "debug.h"

#define SLAVE_TO_ADDR(n) (n << 1)
#define TIMEOUT 100

enum {
    CMD_IODIRA = 0x00,  // i/o direction register
    CMD_IODIRB = 0x01,
    CMD_GPPUA  = 0x0C,  // GPIO pull-up resistor register
    CMD_GPPUB  = 0x0D,
    CMD_GPIOA  = 0x12,  // general purpose i/o port register (write modifies OLAT)
    CMD_GPIOB  = 0x13,
};

void mcp23018_init(uint8_t addr) {
    static uint8_t s_init = 0;
    if (!s_init) {
        i2c_init();
        wait_ms(1000);

        s_init = 1;
    }
}

bool mcp23018_set_config(uint8_t slave_addr, uint8_t port, uint8_t conf) {
    uint8_t addr         = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmdDirection = port ? CMD_IODIRB : CMD_IODIRA;
    uint8_t cmdPullup    = port ? CMD_GPPUB : CMD_GPPUA;

    i2c_status_t ret = i2c_writeReg(addr, cmdDirection, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("mcp23018_set_config::directionFAILED::%u\n", ret);
        return false;
    }

    ret = i2c_writeReg(addr, cmdPullup, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("mcp23018_set_config::pullupFAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool mcp23018_set_output(uint8_t slave_addr, uint8_t port, uint8_t conf) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = port ? CMD_GPIOB : CMD_GPIOA;

    i2c_status_t ret = i2c_writeReg(addr, cmd, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("mcp23018_set_output::FAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool mcp23018_set_output_all(uint8_t slave_addr, uint8_t confA, uint8_t confB) {
    uint8_t addr    = SLAVE_TO_ADDR(slave_addr);
    uint8_t conf[2] = {confA, confB};

    i2c_status_t ret = i2c_writeReg(addr, CMD_GPIOA, &conf[0], sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("mcp23018_set_output::FAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool mcp23018_readPins(uint8_t slave_addr, uint8_t port, uint8_t* out) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = port ? CMD_GPIOB : CMD_GPIOA;

    i2c_status_t ret = i2c_readReg(addr, cmd, out, sizeof(uint8_t), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("mcp23018_readPins::FAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool mcp23018_readPins_all(uint8_t slave_addr, uint16_t* out) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);

    typedef union {
        uint8_t  u8[2];
        uint16_t u16;
    } data16;

    data16 data = {.u16 = 0};

    i2c_status_t ret = i2c_readReg(addr, CMD_GPIOA, &data.u8[0], sizeof(data), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("mcp23018_readPins::FAILED::%u\n", ret);
        return false;
    }

    *out = data.u16;
    return true;
}
