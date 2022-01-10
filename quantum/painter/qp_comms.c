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

uint32_t qp_comms_send(painter_device_t device, const void QP_RESIDENT_FLASH_OR_RAM *data, uint32_t byte_count) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_comms_send: fail (validation_ok == false)\n");
        return false;
    }

    return driver->comms_vtable->comms_send(device, data, byte_count);
}
