// Copyright 2020 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later
//modification from pca9555 to pca9505/6 by nirim000
//https://github.com/nirim000


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
    CMD_OUTPUT_0 =8,
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
    uint8_t cmd = 0;
    switch (port) 
    {
        case 0:
            cmd  = CMD_CONFIG_0;
            break;
        case 1:
            cmd  = CMD_CONFIG_1;
            break;
        case 2:
            cmd  = CMD_CONFIG_2;
            break;
        case 3:
            cmd  = CMD_CONFIG_3;
            break;
        case 4:
            cmd  = CMD_CONFIG_4;
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
    uint8_t cmd = 0;
    switch (port) 
    {
        case 0:
            cmd  = CMD_INVERSION_0;
            break;
        case 1:
            cmd  = CMD_INVERSION_1;
            break;
        case 2:
            cmd  = CMD_INVERSION_2;
            break;
        case 3:
            cmd  = CMD_INVERSION_3;
            break;
        case 4:
            cmd  = CMD_INVERSION_4;
            break;
    }


    i2c_status_t ret = i2c_writeReg(addr, cmd, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9505_set_config::FAILED\n");
        return false;
    }

    return true;
}

bool pca9505_set_output(uint8_t slave_addr, pca9505_port_t port, uint8_t conf) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd = 0;
    switch (port) 
    {
        case 0:
            cmd  = CMD_OUTPUT_0;
            break;
        case 1:
            cmd  = CMD_OUTPUT_1;
            break;
        case 2:
            cmd  = CMD_OUTPUT_2;
            break;
        case 3:
            cmd  = CMD_OUTPUT_3;
            break;
        case 4:
            cmd  = CMD_OUTPUT_4;
            break;
    }
    

    i2c_status_t ret = i2c_writeReg(addr, cmd, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9505_set_output::FAILED\n");
        return false;
    }

    return true;
}
/**
bool pca9505_set_output_all(uint8_t slave_addr, uint8_t confA, uint8_t confB) {
    uint8_t addr    = SLAVE_TO_ADDR(slave_addr);
    uint8_t conf[2] = {confA, confB};

    i2c_status_t ret = i2c_writeReg(addr, CMD_OUTPUT_0, &conf[0], sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("pca9505_set_output::FAILED::%u\n", ret);
        return false;
    }

    return true;
}
*/
bool pca9505_readPins(uint8_t slave_addr, pca9505_port_t port, uint8_t* out) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd = 0;
    switch (port) 
    {
        case 0:
            cmd  = CMD_INPUT_0;
            break;
        case 1:
            cmd  = CMD_INPUT_1;
            break;
        case 2:
            cmd  = CMD_INPUT_2;
            break;
        case 3:
            cmd  = CMD_INPUT_3;
            break;
        case 4:
            cmd  = CMD_INPUT_4;
            break;
    }


    i2c_status_t ret = i2c_readReg(addr, cmd, out, sizeof(uint8_t), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9505_readPins::FAILED\n");
        return false;
    }

    return true;
}
/**
bool pca9505_readPins_all(uint8_t slave_addr, uint16_t* out) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);

    typedef union {
        uint8_t  u8[2];
        uint16_t u16;
    } data16;

    data16 data = {.u16 = 0};

    i2c_status_t ret = i2c_readReg(addr, CMD_INPUT_0, &data.u8[0], sizeof(data), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9505_readPins_all::FAILED\n");
        return false;
    }

    *out = data.u16;
    return true;
}
*/
