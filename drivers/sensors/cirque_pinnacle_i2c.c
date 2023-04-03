// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
#include "pointing_device.h"
#include "cirque_pinnacle.h"
#include "i2c_master.h"
#include "stdio.h"

// Masks for Cirque Register Access Protocol (RAP)
#define WRITE_MASK 0x80
#define READ_MASK 0xA0

const cirque_rap_t                 cirque_rap_i2c            = {.read = &cirque_read_i2c, .write = &cirque_write_i2c};
const pointing_device_driver_t     cirque_driver_i2c_default = {.init = cirque_pinnacle_init_i2c, .get_report = cirque_pinnacle_get_report_i2c, .set_cpi = cirque_pinnacle_set_scale, .get_cpi = cirque_pinnacle_get_scale};
const pointing_device_i2c_config_t cirque_config_i2c_default = {.address = CIRQUE_PINNACLE_ADDR, .timeout = CIRQUE_PINNACLE_TIMEOUT};

/*  RAP Functions */
// Reads <count> Pinnacle registers starting at <address>
void cirque_read_i2c(const void *config, uint8_t regaddr, uint8_t *data, uint8_t count) {
    uint8_t                       cmdByte    = READ_MASK | regaddr; // Form the READ command byte
    pointing_device_i2c_config_t *i2c_config = (pointing_device_i2c_config_t *)config;

    i2c_write_register(i2c_config->address << 1, cmdByte, NULL, 0, i2c_config->timeout);
    if (i2c_read_register(i2c_config->address << 1, cmdByte, data, count, CIRQUE_PINNACLE_TIMEOUT) != I2C_STATUS_SUCCESS) {
        pd_dprintf("error cirque_pinnacle i2c_readReg\n");
        touchpad_init = false;
    }

}

// Writes single-byte <data> to <address>
void cirque_write_i2c(const void *config, uint8_t regaddr, uint8_t data) {
    uint8_t                       cmdByte    = WRITE_MASK | regaddr; // Form the WRITE command byte
    pointing_device_i2c_config_t *i2c_config = (pointing_device_i2c_config_t *)config;
    if (i2c_write_register(i2c_config->address << 1, cmdByte, &data, sizeof(data), i2c_config->timeout) != I2C_STATUS_SUCCESS) {
        pd_dprintf("error cirque_pinnacle i2c_writeReg\n");
        touchpad_init = false;
    }
}

void cirque_pinnacle_init_i2c(const void *config) {
    i2c_init();
    cirque_pinnacle_init(&cirque_rap_i2c, config);
}
report_mouse_t cirque_pinnacle_get_report_i2c(const void *config) {
    return cirque_pinnacle_get_report(&cirque_rap_i2c, config);
}
