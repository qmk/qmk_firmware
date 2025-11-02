// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef QUANTUM_PAINTER_I2C_ENABLE

#    include "i2c_master.h"
#    include "qp_comms_i2c.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

static uint32_t qp_comms_i2c_send_raw(painter_device_t device, const void *data, uint32_t byte_count) {
    painter_driver_t *     driver       = (painter_driver_t *)device;
    qp_comms_i2c_config_t *comms_config = (qp_comms_i2c_config_t *)driver->comms_config;
    i2c_status_t           res          = i2c_transmit(comms_config->chip_address << 1, data, byte_count, I2C_TIMEOUT);
    if (res < 0) {
        return 0;
    }
    return byte_count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base I2C support

bool qp_comms_i2c_init(painter_device_t device) {
    i2c_init();
    return true;
}

bool qp_comms_i2c_start(painter_device_t device) {
    return true;
}

uint32_t qp_comms_i2c_send_data(painter_device_t device, const void *data, uint32_t byte_count) {
    return qp_comms_i2c_send_raw(device, data, byte_count);
}

bool qp_comms_i2c_stop(painter_device_t device) {
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Command+Data I2C support

static const uint8_t cmd_byte  = 0x00;
static const uint8_t data_byte = 0x40;

bool qp_comms_i2c_cmddata_send_command(painter_device_t device, uint8_t cmd) {
    uint8_t buf[2] = {cmd_byte, cmd};
    return qp_comms_i2c_send_raw(device, &buf, 2);
}

uint32_t qp_comms_i2c_cmddata_send_data(painter_device_t device, const void *data, uint32_t byte_count) {
    uint8_t buf[1 + byte_count];
    buf[0] = data_byte;
    memcpy(&buf[1], data, byte_count);
    if (qp_comms_i2c_send_raw(device, buf, sizeof(buf)) != sizeof(buf)) {
        return 0;
    }
    return byte_count;
}

bool qp_comms_i2c_bulk_command_sequence(painter_device_t device, const uint8_t *sequence, size_t sequence_len) {
    uint8_t buf[32];
    for (size_t i = 0; i < sequence_len;) {
        uint8_t command   = sequence[i];
        uint8_t delay     = sequence[i + 1];
        uint8_t num_bytes = sequence[i + 2];
        buf[0]            = cmd_byte;
        buf[1]            = command;
        memcpy(&buf[2], &sequence[i + 3], num_bytes);
        if (!qp_comms_i2c_send_raw(device, buf, num_bytes + 2)) {
            return false;
        }

        if (delay > 0) {
            wait_ms(delay);
        }
        i += (3 + num_bytes);
    }

    return true;
}

const painter_comms_with_command_vtable_t i2c_comms_cmddata_vtable = {
    .base =
        {
            .comms_init  = qp_comms_i2c_init,
            .comms_start = qp_comms_i2c_start,
            .comms_send  = qp_comms_i2c_cmddata_send_data,
            .comms_stop  = qp_comms_i2c_stop,
        },
    .send_command          = qp_comms_i2c_cmddata_send_command,
    .bulk_command_sequence = qp_comms_i2c_bulk_command_sequence,
};

#endif // QUANTUM_PAINTER_I2C_ENABLE
