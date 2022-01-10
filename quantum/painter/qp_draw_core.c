// Copyright 2021-2022 Nick Brassel (@tzarc)
// Copyright 2021 Paul Cotter (@gr1mr3aver)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <qp_internal.h>
#include <qp_comms.h>
#include <qp_draw.h>
#include <qgf.h>

_Static_assert((QP_PIXDATA_BUFFER_SIZE > 0) && (QP_PIXDATA_BUFFER_SIZE % 16) == 0, "QP_PIXDATA_BUFFER_SIZE needs to be a non-zero multiple of 16");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global variables
//
// NOTE: The variables in this section are intentionally outside a stack frame. They are able to be defined with larger
//       sizes than the normal stack frames would allow, and as such need to be external.
//
//       **** DO NOT refactor this and decide to place the variables inside the function calling them -- you will ****
//       **** very likely get artifacts rendered to the screen as a result.                                       ****
//

// Buffer used for transmitting native pixel data to the downstream device.
uint8_t qp_internal_global_pixdata_buffer[QP_PIXDATA_BUFFER_SIZE];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

uint32_t qp_internal_num_pixels_in_buffer(painter_device_t device) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    return ((QP_PIXDATA_BUFFER_SIZE * 8) / driver->native_bits_per_pixel);
}

// qp_setpixel internal implementation, but accepts a buffer with pre-converted native pixel. Only the first pixel is used.
bool qp_internal_setpixel_impl(painter_device_t device, uint16_t x, uint16_t y) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    return driver->driver_vtable->viewport(device, x, y, x, y) && driver->driver_vtable->pixdata(device, qp_internal_global_pixdata_buffer, 1);
}

// Fills the global native pixel buffer with equivalent pixels matching the supplied HSV
void qp_internal_fill_pixdata(painter_device_t device, uint32_t num_pixels, uint8_t hue, uint8_t sat, uint8_t val) {
    struct painter_driver_t *driver            = (struct painter_driver_t *)device;
    uint32_t                 pixels_in_pixdata = qp_internal_num_pixels_in_buffer(device);
    num_pixels                                 = QP_MIN(pixels_in_pixdata, num_pixels);

    // Convert the color to native pixel format
    qp_pixel_t color = {.hsv888 = {.h = hue, .s = sat, .v = val}};
    driver->driver_vtable->palette_convert(device, 1, &color);

    // Append the required number of pixels
    uint8_t palette_idx = 0;
    for (uint32_t i = 0; i < num_pixels; ++i) {
        driver->driver_vtable->append_pixels(device, qp_internal_global_pixdata_buffer, &color, i, 1, &palette_idx);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_setpixel

bool qp_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_setpixel: fail (validation_ok == false)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("Failed to start comms in qp_setpixel\n");
        return false;
    }

    qp_internal_fill_pixdata(device, 1, hue, sat, val);
    bool ret = qp_internal_setpixel_impl(device, x, y);
    qp_comms_stop(device);
    qp_dprintf("qp_setpixel: %s\n", ret ? "ok" : "fail");
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_line

bool qp_line(painter_device_t device, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t hue, uint8_t sat, uint8_t val) {
    if (x0 == x1 || y0 == y1) {
        qp_dprintf("qp_line(%d, %d, %d, %d): entry (deferring to qp_rect)\n", (int)x0, (int)y0, (int)x1, (int)y1);
        bool ret = qp_rect(device, x0, y0, x1, y1, hue, sat, val, true);
        qp_dprintf("qp_line(%d, %d, %d, %d): %s (deferred to qp_rect)\n", (int)x0, (int)y0, (int)x1, (int)y1, ret ? "ok" : "fail");
        return ret;
    }

    qp_dprintf("qp_line(%d, %d, %d, %d): entry\n", (int)x0, (int)y0, (int)x1, (int)y1);
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_line: fail (validation_ok == false)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("Failed to start comms in qp_line\n");
        return false;
    }

    qp_internal_fill_pixdata(device, 1, hue, sat, val);

    // draw angled line using Bresenham's algo
    int16_t x      = ((int16_t)x0);
    int16_t y      = ((int16_t)y0);
    int16_t slopex = ((int16_t)x0) < ((int16_t)x1) ? 1 : -1;
    int16_t slopey = ((int16_t)y0) < ((int16_t)y1) ? 1 : -1;
    int16_t dx     = abs(((int16_t)x1) - ((int16_t)x0));
    int16_t dy     = -abs(((int16_t)y1) - ((int16_t)y0));

    int16_t e  = dx + dy;
    int16_t e2 = 2 * e;

    bool ret = true;
    while (x != x1 || y != y1) {
        if (!qp_internal_setpixel_impl(device, x, y)) {
            ret = false;
            break;
        }
        e2 = 2 * e;
        if (e2 >= dy) {
            e += dy;
            x += slopex;
        }
        if (e2 <= dx) {
            e += dx;
            y += slopey;
        }
    }
    // draw the last pixel
    if (!qp_internal_setpixel_impl(device, x, y)) {
        ret = false;
    }

    qp_comms_stop(device);
    qp_dprintf("qp_line(%d, %d, %d, %d): %s\n", (int)x0, (int)y0, (int)x1, (int)y1, ret ? "ok" : "fail");
    return ret;
}
