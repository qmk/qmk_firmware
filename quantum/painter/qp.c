// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <quantum.h>
#include <utf8.h>

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_draw.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal driver validation

static bool validate_driver_vtable(painter_driver_t *driver) {
    return (driver->driver_vtable && driver->driver_vtable->init && driver->driver_vtable->power && driver->driver_vtable->clear && driver->driver_vtable->viewport && driver->driver_vtable->pixdata && driver->driver_vtable->palette_convert && driver->driver_vtable->append_pixels && driver->driver_vtable->append_pixdata) ? true : false;
}

static bool validate_comms_vtable(painter_driver_t *driver) {
    return (driver->comms_vtable && driver->comms_vtable->comms_init && driver->comms_vtable->comms_start && driver->comms_vtable->comms_stop && driver->comms_vtable->comms_send) ? true : false;
}

static bool validate_driver_integrity(painter_driver_t *driver) {
    return validate_driver_vtable(driver) && validate_comms_vtable(driver);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_init

bool qp_init(painter_device_t device, painter_rotation_t rotation) {
    qp_dprintf("qp_init: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;

    if (!driver) {
        qp_dprintf("qp_init: fail (pointer to NULL)\n");
        return false;
    }

    driver->validate_ok = false;
    if (!validate_driver_integrity(driver)) {
        qp_dprintf("Failed to validate driver integrity in qp_init\n");
        return false;
    }

    driver->validate_ok = true;

    if (!qp_comms_init(device)) {
        driver->validate_ok = false;
        qp_dprintf("qp_init: fail (could not init comms)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_init: fail (could not start comms)\n");
        return false;
    }

    // Set the rotation before init
    driver->rotation = rotation;

    // Invoke init
    bool ret = driver->driver_vtable->init(device, rotation);
    qp_comms_stop(device);
    qp_dprintf("qp_init: %s\n", ret ? "ok" : "fail");
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_power

bool qp_power(painter_device_t device, bool power_on) {
    qp_dprintf("qp_power: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;
    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_power: fail (validation_ok == false)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_power: fail (could not start comms)\n");
        return false;
    }

    bool ret = driver->driver_vtable->power(device, power_on);
    qp_comms_stop(device);
    qp_dprintf("qp_power: %s\n", ret ? "ok" : "fail");
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_clear

bool qp_clear(painter_device_t device) {
    qp_dprintf("qp_clear: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;
    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_clear: fail (validation_ok == false)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_clear: fail (could not start comms)\n");
        return false;
    }

    bool ret = driver->driver_vtable->clear(device);
    qp_comms_stop(device);
    qp_dprintf("qp_clear: %s\n", ret ? "ok" : "fail");
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_flush

bool qp_flush(painter_device_t device) {
    qp_dprintf("qp_flush: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;
    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_flush: fail (validation_ok == false)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_flush: fail (could not start comms)\n");
        return false;
    }

    bool ret = driver->driver_vtable->flush(device);
    qp_comms_stop(device);
    qp_dprintf("qp_flush: %s\n", ret ? "ok" : "fail");
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_get_*

uint16_t qp_get_width(painter_device_t device) {
    qp_dprintf("qp_get_width: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;

    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_get_width: fail (invalid driver)\n");
        return 0;
    }

    uint16_t width;
    switch (driver->rotation) {
        default:
        case QP_ROTATION_0:
        case QP_ROTATION_180:
            width = driver->panel_width;

        case QP_ROTATION_90:
        case QP_ROTATION_270:
            width = driver->panel_height;
    }

    qp_dprintf("qp_get_width: ok\n");
    return width;
}

uint16_t qp_get_height(painter_device_t device) {
    qp_dprintf("qp_get_height: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;

    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_get_height: fail (invalid driver)\n");
        return 0;
    }

    uint16_t height;
    switch (driver->rotation) {
        default:
        case QP_ROTATION_0:
        case QP_ROTATION_180:
            height = driver->panel_height;

        case QP_ROTATION_90:
        case QP_ROTATION_270:
            height = driver->panel_width;
    }

    qp_dprintf("qp_get_height: ok\n");
    return height;
}

painter_rotation_t qp_get_rotation(painter_device_t device) {
    qp_dprintf("qp_get_rotation: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;

    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_get_rotation: fail (invalid driver)\n");
        return QP_ROTATION_0;
    }

    qp_dprintf("qp_get_rotation: ok\n");
    return driver->rotation;
}

uint16_t qp_get_offset_x(painter_device_t device) {
    qp_dprintf("qp_get_offset_x: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;

    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_get_offset_x: fail (invalid driver)\n");
        return 0;
    }

    qp_dprintf("qp_get_offset_x: ok\n");
    return driver->offset_x;
}

uint16_t qp_get_offset_y(painter_device_t device) {
    qp_dprintf("qp_get_offset_y: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;

    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_get_offset_y: fail (invalid driver)\n");
        return 0;
    }

    qp_dprintf("qp_get_offset_y: ok\n");
    return driver->offset_y;
}

void qp_get_geometry(painter_device_t device, uint16_t *width, uint16_t *height, painter_rotation_t *rotation, uint16_t *offset_x, uint16_t *offset_y) {
    qp_dprintf("qp_geometry: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;

    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_geometry: fail (invalid driver)\n");
        return;
    }

    if (width) {
        *width = qp_get_width(device);
    }

    if (height) {
        *height = qp_get_height(device);
    }

    if (rotation) {
        *rotation = qp_get_rotation(device);
    }

    if (offset_x) {
        *offset_x = qp_get_offset_x(device);
    }

    if (offset_y) {
        *offset_y = qp_get_offset_y(device);
    }

    qp_dprintf("qp_get_geometry: ok\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_set_viewport_offsets

void qp_set_viewport_offsets(painter_device_t device, uint16_t offset_x, uint16_t offset_y) {
    qp_dprintf("qp_set_viewport_offsets: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;

    if (!driver) {
        qp_dprintf("qp_set_viewport_offsets: fail (pointer to NULL)\n");
        return;
    }

    driver->offset_x = offset_x;
    driver->offset_y = offset_y;

    qp_dprintf("qp_set_viewport_offsets: ok\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_viewport

bool qp_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    qp_dprintf("qp_viewport: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;
    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_viewport: fail (validation_ok == false)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_viewport: fail (could not start comms)\n");
        return false;
    }

    // Set the viewport
    bool ret = driver->driver_vtable->viewport(device, left, top, right, bottom);
    qp_dprintf("qp_viewport: %s\n", ret ? "ok" : "fail");
    qp_comms_stop(device);
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_pixdata

bool qp_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    qp_dprintf("qp_pixdata: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;
    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_pixdata: fail (validation_ok == false)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_pixdata: fail (could not start comms)\n");
        return false;
    }

    bool ret = driver->driver_vtable->pixdata(device, pixel_data, native_pixel_count);
    qp_dprintf("qp_pixdata: %s\n", ret ? "ok" : "fail");
    qp_comms_stop(device);
    return ret;
}
