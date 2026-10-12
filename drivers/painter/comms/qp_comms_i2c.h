// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef QUANTUM_PAINTER_I2C_ENABLE

#    include <stdint.h>

#    include "gpio.h"
#    include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base I2C support

typedef struct qp_comms_i2c_config_t {
    uint8_t chip_address;
} qp_comms_i2c_config_t;

bool     qp_comms_i2c_init(painter_device_t device);
bool     qp_comms_i2c_start(painter_device_t device);
uint32_t qp_comms_i2c_send_data(painter_device_t device, const void* data, uint32_t byte_count);
bool     qp_comms_i2c_stop(painter_device_t device);

extern const painter_comms_with_command_vtable_t i2c_comms_cmddata_vtable;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // QUANTUM_PAINTER_I2C_ENABLE
