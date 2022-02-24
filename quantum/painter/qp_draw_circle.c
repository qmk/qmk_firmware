// Copyright 2021 Paul Cotter (@gr1mr3aver)
// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp.h"
#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_draw.h"

// Utilize 8-way symmetry to draw circles
static bool qp_circle_helper_impl(painter_device_t device, uint16_t centerx, uint16_t centery, uint16_t offsetx, uint16_t offsety, bool filled) {
    /*
    Circles have the property of 8-way symmetry, so eight pixels can be drawn
    for each computed [offsetx,offsety] given the center coordinates
    represented by [centerx,centery].

    For filled circles, we can draw horizontal lines between each pair of
    pixels with the same final value of y.

    Two special cases exist and have been optimized:
    1) offsetx == offsety (the final point), makes half the coordinates
    equivalent, so we can omit them (and the corresponding fill lines)
    2) offsetx == 0 (the starting point) means that some horizontal lines
    would be a single pixel in length, so we write individual pixels instead.
    This also makes half the symmetrical points identical to their twins,
    so we only need four points or two points and one line
    */

    int16_t xpx = ((int16_t)centerx) + ((int16_t)offsetx);
    int16_t xmx = ((int16_t)centerx) - ((int16_t)offsetx);
    int16_t xpy = ((int16_t)centerx) + ((int16_t)offsety);
    int16_t xmy = ((int16_t)centerx) - ((int16_t)offsety);
    int16_t ypx = ((int16_t)centery) + ((int16_t)offsetx);
    int16_t ymx = ((int16_t)centery) - ((int16_t)offsetx);
    int16_t ypy = ((int16_t)centery) + ((int16_t)offsety);
    int16_t ymy = ((int16_t)centery) - ((int16_t)offsety);

    if (offsetx == 0) {
        if (!qp_internal_setpixel_impl(device, centerx, ypy)) {
            return false;
        }
        if (!qp_internal_setpixel_impl(device, centerx, ymy)) {
            return false;
        }
        if (filled) {
            if (!qp_internal_fillrect_helper_impl(device, xpy, centery, xmy, centery)) {
                return false;
            }
        } else {
            if (!qp_internal_setpixel_impl(device, xpy, centery)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xmy, centery)) {
                return false;
            }
        }
    } else if (offsetx == offsety) {
        if (filled) {
            if (!qp_internal_fillrect_helper_impl(device, xpy, ypy, xmy, ypy)) {
                return false;
            }
            if (!qp_internal_fillrect_helper_impl(device, xpy, ymy, xmy, ymy)) {
                return false;
            }
        } else {
            if (!qp_internal_setpixel_impl(device, xpy, ypy)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xmy, ypy)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xpy, ymy)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xmy, ymy)) {
                return false;
            }
        }

    } else {
        if (filled) {
            if (!qp_internal_fillrect_helper_impl(device, xpx, ypy, xmx, ypy)) {
                return false;
            }
            if (!qp_internal_fillrect_helper_impl(device, xpx, ymy, xmx, ymy)) {
                return false;
            }
            if (!qp_internal_fillrect_helper_impl(device, xpy, ypx, xmy, ypx)) {
                return false;
            }
            if (!qp_internal_fillrect_helper_impl(device, xpy, ymx, xmy, ymx)) {
                return false;
            }
        } else {
            if (!qp_internal_setpixel_impl(device, xpx, ypy)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xmx, ypy)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xpx, ymy)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xmx, ymy)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xpy, ypx)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xmy, ypx)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xpy, ymx)) {
                return false;
            }
            if (!qp_internal_setpixel_impl(device, xmy, ymx)) {
                return false;
            }
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_circle

bool qp_circle(painter_device_t device, uint16_t x, uint16_t y, uint16_t radius, uint8_t hue, uint8_t sat, uint8_t val, bool filled) {
    qp_dprintf("qp_circle: entry\n");
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_circle: fail (validation_ok == false)\n");
        return false;
    }

    // plot the initial set of points for x, y and r
    int16_t xcalc = 0;
    int16_t ycalc = (int16_t)radius;
    int16_t err   = ((5 - (radius >> 2)) >> 2);

    qp_internal_fill_pixdata(device, (radius * 2) + 1, hue, sat, val);

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_circle: fail (could not start comms)\n");
        return false;
    }

    bool ret = true;
    if (!qp_circle_helper_impl(device, x, y, xcalc, ycalc, filled)) {
        ret = false;
    }

    if (ret) {
        while (xcalc < ycalc) {
            xcalc++;
            if (err < 0) {
                err += (xcalc << 1) + 1;
            } else {
                ycalc--;
                err += ((xcalc - ycalc) << 1) + 1;
            }
            if (!qp_circle_helper_impl(device, x, y, xcalc, ycalc, filled)) {
                ret = false;
                break;
            }
        }
    }

    qp_dprintf("qp_circle: %s\n", ret ? "ok" : "fail");
    qp_comms_stop(device);
    return ret;
}
