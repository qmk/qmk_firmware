// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>

#include "azoteq_iqs5xx.h"

static azoteq_iqs5xx_base_data_t mock_base_data;
static i2c_status_t              mock_read_status = I2C_STATUS_SUCCESS;

void azoteq_iqs5xx_mock_reset(void) {
    memset(&mock_base_data, 0, sizeof(mock_base_data));
    mock_read_status = I2C_STATUS_SUCCESS;
}

void azoteq_iqs5xx_mock_set_base_data(azoteq_iqs5xx_base_data_t base_data) {
    mock_base_data   = base_data;
    mock_read_status = I2C_STATUS_SUCCESS;
}

void i2c_init(void) {}

i2c_status_t i2c_ping_address(uint8_t address, uint16_t timeout) {
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_read_register16(uint8_t devaddr, uint16_t regaddr, uint8_t *data, uint16_t length, uint16_t timeout) {
    if (mock_read_status == I2C_STATUS_SUCCESS && data != NULL) {
        memcpy(data, &mock_base_data, MIN(length, sizeof(mock_base_data)));
    }
    return mock_read_status;
}

i2c_status_t i2c_write_register16(uint8_t devaddr, uint16_t regaddr, const uint8_t *data, uint16_t length, uint16_t timeout) {
    return I2C_STATUS_SUCCESS;
}

uint8_t pointing_device_handle_buttons(uint8_t buttons, bool pressed, pointing_device_buttons_t button) {
    if (pressed) {
        buttons |= 1 << button;
    } else {
        buttons &= ~(1 << button);
    }
    return buttons;
}
