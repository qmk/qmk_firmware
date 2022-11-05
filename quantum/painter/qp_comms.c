// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_comms.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base comms APIs

bool qp_comms_init(painter_device_t device) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_comms_init: fail (validation_ok == false)\n");
        return false;
    }

    return driver->comms_vtable->comms_init(device);
}

bool qp_comms_start(painter_device_t device) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_comms_start: fail (validation_ok == false)\n");
        return false;
    }

    return driver->comms_vtable->comms_start(device);
}

void qp_comms_stop(painter_device_t device) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_comms_stop: fail (validation_ok == false)\n");
        return;
    }

    driver->comms_vtable->comms_stop(device);
}

uint32_t qp_comms_send(painter_device_t device, const void *data, uint32_t byte_count) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_comms_send: fail (validation_ok == false)\n");
        return false;
    }

    return driver->comms_vtable->comms_send(device, data, byte_count);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Comms APIs that use a D/C pin

void qp_comms_command(painter_device_t device, uint8_t cmd) {
    struct painter_driver_t *                   driver       = (struct painter_driver_t *)device;
    struct painter_comms_with_command_vtable_t *comms_vtable = (struct painter_comms_with_command_vtable_t *)driver->comms_vtable;
    comms_vtable->send_command(device, cmd);
}

void qp_comms_command_databyte(painter_device_t device, uint8_t cmd, uint8_t data) {
    qp_comms_command(device, cmd);
    qp_comms_send(device, &data, sizeof(data));
}

uint32_t qp_comms_command_databuf(painter_device_t device, uint8_t cmd, const void *data, uint32_t byte_count) {
    qp_comms_command(device, cmd);
    return qp_comms_send(device, data, byte_count);
}

void qp_comms_bulk_command_sequence(painter_device_t device, const uint8_t *sequence, size_t sequence_len) {
    struct painter_driver_t *                   driver       = (struct painter_driver_t *)device;
    struct painter_comms_with_command_vtable_t *comms_vtable = (struct painter_comms_with_command_vtable_t *)driver->comms_vtable;
    comms_vtable->bulk_command_sequence(device, sequence, sequence_len);
}
