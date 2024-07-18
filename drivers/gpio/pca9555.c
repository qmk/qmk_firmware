// Copyright 2020 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "i2c_master.h"
#include "pca9555.h"

#include "debug.h"

#define SLAVE_TO_ADDR(n) (n << 1)
#define TIMEOUT 100

enum {
    CMD_INPUT_0 = 0,
    CMD_INPUT_1,
    CMD_OUTPUT_0,
    CMD_OUTPUT_1,
    CMD_INVERSION_0,
    CMD_INVERSION_1,
    CMD_CONFIG_0,
    CMD_CONFIG_1,
};

void pca9555_init(uint8_t slave_addr) {
    static uint8_t s_init = 0;
    if (!s_init) {
        i2c_init();

        s_init = 1;
    }

    // TODO: could check device connected
}

bool pca9555_set_config(uint8_t slave_addr, pca9555_port_t port, uint8_t conf) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = port ? CMD_CONFIG_1 : CMD_CONFIG_0;

    i2c_status_t ret = i2c_write_register(addr, cmd, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9555_set_config::FAILED\n");
        return false;
    }

    return true;
}

bool pca9555_set_output(uint8_t slave_addr, pca9555_port_t port, uint8_t conf) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = port ? CMD_OUTPUT_1 : CMD_OUTPUT_0;

    i2c_status_t ret = i2c_write_register(addr, cmd, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9555_set_output::FAILED\n");
        return false;
    }

    return true;
}

bool pca9555_set_output_all(uint8_t slave_addr, uint8_t confA, uint8_t confB) {
    uint8_t addr    = SLAVE_TO_ADDR(slave_addr);
    uint8_t conf[2] = {confA, confB};

    i2c_status_t ret = i2c_write_register(addr, CMD_OUTPUT_0, &conf[0], sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("pca9555_set_output::FAILED::%u\n", ret);
        return false;
    }

    return true;
}

bool pca9555_read_pins(uint8_t slave_addr, pca9555_port_t port, uint8_t* out) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = port ? CMD_INPUT_1 : CMD_INPUT_0;

    i2c_status_t ret = i2c_read_register(addr, cmd, out, sizeof(uint8_t), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9555_read_pins::FAILED\n");
        return false;
    }

    return true;
}

bool pca9555_read_pins_all(uint8_t slave_addr, uint16_t* out) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);

    typedef union {
        uint8_t  u8[2];
        uint16_t u16;
    } data16;

    data16 data = {.u16 = 0};

    i2c_status_t ret = i2c_read_register(addr, CMD_INPUT_0, &data.u8[0], sizeof(data), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9555_read_pins_all::FAILED\n");
        return false;
    }

    *out = data.u16;
    return true;
}
