// Copyright 2021 Paul Cotter (@gr1mr3aver)
// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_draw.h"

// Utilize 4-way symmetry to draw an ellipse
static bool qp_ellipse_helper_impl(painter_device_t device, uint16_t centerx, uint16_t centery, uint16_t offsetx, uint16_t offsety, bool filled) {
    /*
    Ellipses have the property of 4-way symmetry, so four pixels can be drawn
    for each computed [offsetx,offsety] given the center coordinates
    represented by [centerx,centery].

    For filled ellipses, we can draw horizontal lines between each pair of
    pixels with the same final value of y.

    When offsetx == 0 only two pixels can be drawn for filled or unfilled ellipses
    */

    int16_t xpx = ((int16_t)centerx) + ((int16_t)offsetx);
    int16_t xmx = ((int16_t)centerx) - ((int16_t)offsetx);
    int16_t ypy = ((int16_t)centery) + ((int16_t)offsety);
    int16_t ymy = ((int16_t)centery) - ((int16_t)offsety);

    if (offsetx == 0) {
        if (!qp_internal_setpixel_impl(device, xpx, ypy)) {
            return false;
        }
        if (!qp_internal_setpixel_impl(device, xpx, ymy)) {
            return false;
        }
    } else if (filled) {
        if (!qp_internal_fillrect_helper_impl(device, xpx, ypy, xmx, ypy)) {
            return false;
        }
        if (offsety > 0 && !qp_internal_fillrect_helper_impl(device, xpx, ymy, xmx, ymy)) {
            return false;
        }
    } else {
        if (!qp_internal_setpixel_impl(device, xpx, ypy)) {
            return false;
        }
        if (!qp_internal_setpixel_impl(device, xpx, ymy)) {
            return false;
        }
        if (!qp_internal_setpixel_impl(device, xmx, ypy)) {
            return false;
        }
        if (!qp_internal_setpixel_impl(device, xmx, ymy)) {
            return false;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_ellipse

bool qp_ellipse(painter_device_t device, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint8_t hue, uint8_t sat, uint8_t val, bool filled) {
    qp_dprintf("qp_ellipse: entry\n");
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_ellipse: fail (validation_ok == false)\n");
        return false;
    }

    int16_t aa = ((int16_t)sizex) * ((int16_t)sizex);
    int16_t bb = ((int16_t)sizey) * ((int16_t)sizey);
    int16_t fa = 4 * ((int16_t)aa);
    int16_t fb = 4 * ((int16_t)bb);

    int16_t dx = 0;
    int16_t dy = ((int16_t)sizey);

    qp_internal_fill_pixdata(device, QP_MAX(sizex, sizey), hue, sat, val);

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_ellipse: fail (could not start comms)\n");
        return false;
    }

    bool ret = true;
    for (int16_t delta = (2 * bb) + (aa * (1 - (2 * sizey))); bb * dx <= aa * dy; dx++) {
        if (!qp_ellipse_helper_impl(device, x, y, dx, dy, filled)) {
            ret = false;
            break;
        }
        if (delta >= 0) {
            delta += fa * (1 - dy);
            dy--;
        }
        delta += bb * (4 * dx + 6);
    }

    dx = sizex;
    dy = 0;

    for (int16_t delta = (2 * aa) + (bb * (1 - (2 * sizex))); aa * dy <= bb * dx; dy++) {
        if (!qp_ellipse_helper_impl(device, x, y, dx, dy, filled)) {
            ret = false;
            break;
        }
        if (delta >= 0) {
            delta += fb * (1 - dx);
            dx--;
        }
        delta += aa * (4 * dy + 6);
    }

    qp_dprintf("qp_ellipse: %s\n", ret ? "ok" : "fail");
    qp_comms_stop(device);
    return ret;
}
