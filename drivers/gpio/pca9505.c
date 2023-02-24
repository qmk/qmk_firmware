// Copyright 2022 nirim000
// SPDX-License-Identifier: GPL-2.0-or-later

#include "i2c_master.h"
#include "pca9505.h"

#include "debug.h"

#define SLAVE_TO_ADDR(n) (n << 1)
#define TIMEOUT 100

enum {
    CMD_INPUT_0 = 0,
    CMD_INPUT_1,
    CMD_INPUT_2,
    CMD_INPUT_3,
    CMD_INPUT_4,
    CMD_OUTPUT_0 = 8,
    CMD_OUTPUT_1,
    CMD_OUTPUT_2,
    CMD_OUTPUT_3,
    CMD_OUTPUT_4,
    CMD_INVERSION_0 = 16,
    CMD_INVERSION_1,
    CMD_INVERSION_2,
    CMD_INVERSION_3,
    CMD_INVERSION_4,
    CMD_CONFIG_0 = 24,
    CMD_CONFIG_1,
    CMD_CONFIG_2,
    CMD_CONFIG_3,
    CMD_CONFIG_4,
};

void pca9505_init(uint8_t slave_addr) {
    static uint8_t s_init = 0;
    if (!s_init) {
        i2c_init();

        s_init = 1;
    }

    // TODO: could check device connected
    // i2c_start(SLAVE_TO_ADDR(slave) | I2C_WRITE);
    // i2c_stop();
}

bool pca9505_set_config(uint8_t slave_addr, pca9505_port_t port, uint8_t conf) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = 0;
    switch (port) {
        case 0:
            cmd = CMD_CONFIG_0;
            break;
        case 1:
            cmd = CMD_CONFIG_1;
            break;
        case 2:
            cmd = CMD_CONFIG_2;
            break;
        case 3:
            cmd = CMD_CONFIG_3;
            break;
        case 4:
            cmd = CMD_CONFIG_4;
            break;
    }

    i2c_status_t ret = i2c_writeReg(addr, cmd, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9505_set_config::FAILED\n");
        return false;
    }

    return true;
}

bool pca9505_set_polarity(uint8_t slave_addr, pca9505_port_t port, uint8_t conf) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = 0;
    switch (port) {
        case 0:
            cmd = CMD_INVERSION_0;
            break;
        case 1:
            cmd = CMD_INVERSION_1;
            break;
        case 2:
            cmd = CMD_INVERSION_2;
            break;
        case 3:
            cmd = CMD_INVERSION_3;
            break;
        case 4:
            cmd = CMD_INVERSION_4;
            break;
    }

    i2c_status_t ret = i2c_writeReg(addr, cmd, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9505_set_polarity::FAILED\n");
        return false;
    }

    return true;
}

bool pca9505_set_output(uint8_t slave_addr, pca9505_port_t port, uint8_t conf) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = 0;
    switch (port) {
        case 0:
            cmd = CMD_OUTPUT_0;
            break;
        case 1:
            cmd = CMD_OUTPUT_1;
            break;
        case 2:
            cmd = CMD_OUTPUT_2;
            break;
        case 3:
            cmd = CMD_OUTPUT_3;
            break;
        case 4:
            cmd = CMD_OUTPUT_4;
            break;
    }

    i2c_status_t ret = i2c_writeReg(addr, cmd, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9505_set_output::FAILED\n");
        return false;
    }

    return true;
}

bool pca9505_readPins(uint8_t slave_addr, pca9505_port_t port, uint8_t* out) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = 0;
    switch (port) {
        case 0:
            cmd = CMD_INPUT_0;
            break;
        case 1:
            cmd = CMD_INPUT_1;
            break;
        case 2:
            cmd = CMD_INPUT_2;
            break;
        case 3:
            cmd = CMD_INPUT_3;
            break;
        case 4:
            cmd = CMD_INPUT_4;
            break;
    }

    i2c_status_t ret = i2c_readReg(addr, cmd, out, sizeof(uint8_t), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9505_readPins::FAILED\n");
        return false;
    }

    return true;
}
