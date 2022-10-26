// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "ads1100.h"
#include "i2c_master.h"

int16_t ads1100_read(void) {
    uint8_t data[2];
    if (i2c_receive(ADS1100_ADDRESS, data, sizeof(data), ADS1100_TIMEOUT) != I2C_STATUS_SUCCESS) {
        dprintf("error ads1100 read\n");
    }
    uint16_t data_combined = (data[0] << 8) | data[1];
    if (data_combined > ADS1100_MAX_VAL) {
        data_combined = 0;
    }
    return (int16_t)data_combined;
}

void ads1100_write_config(void) {
    uint8_t data = ADS1100_CONFIG;
    if (i2c_transmit(ADS1100_ADDRESS, &data, sizeof(data), ADS1100_TIMEOUT) != I2C_STATUS_SUCCESS) {
        dprintf("error ads1100 write config\n");
    }
}

void ads1100_init(void) {
    i2c_init();
    ads1100_write_config();
}