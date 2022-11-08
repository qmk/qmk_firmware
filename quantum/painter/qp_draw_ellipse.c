// Copyright 2021 Paul Cotter (@gr1mr3aver)
// Copyright 2021 Nick Brassel (@tzarc)
// Copyright 2022 Pablo Martinez (@elpekenin)
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

    // Algorithm adapted from https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/

    // Works a lot worse if sizey<sizex, so flip them if needed and  keep trap of the change in order to flip offsets too
    bool flipped = false;
    if (sizey > sizex) {
        flipped = true;
        uint16_t temp = sizex;
        sizex = sizey;
        sizey = temp;
    }

    // Compute x^2 and y^2 as they are used all over the place
    int32_t xx = ((int16_t)sizex) * ((int16_t)sizex);
    int32_t yy = ((int16_t)sizey) * ((int16_t)sizey);

    int16_t offsetx = 0;
    int16_t offsety = (int16_t) sizey;

    int32_t dx = 0;
    int32_t dy = 2 * xx * offsety;

    bool temp_ret = true;
    bool ret = true;

    qp_internal_fill_pixdata(device, QP_MAX(sizex, sizey), hue, sat, val);

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_ellipse: fail (could not start comms)\n");
        return false;
    }

    // Simplified (and aproximated) form of the formula for region 1
    //      in original code `sizey` would've been `(sizey-0.25)`
    int32_t d1 = yy - xx * sizey;
    while(dx < dy) {
        // Draw current point
        if (!flipped) {
            temp_ret = qp_ellipse_helper_impl(device, x, y, offsetx, offsety, filled);
        } else {
            temp_ret = qp_ellipse_helper_impl(device, x, y, offsety, offsetx, filled);
        }
        // Check returned value
        if (!temp_ret) {
            ret = false;
            break;
        }

        // Compute next point, simplified version of the if/else in original code
        offsetx += 1;
        dx += 2 * yy;
        if (d1 >= 0) {
            offsety -= 1;
            dy -= 2 * xx;
            d1 -= dy;
        }
        d1 += dx + yy;
    }

    // Simplified (and aproximated) form of the formula for region 2
    //      in original code 1st parenthesis would have and extra `+0.25`
    //                       2nd one would have and extra `+1`
    // Note: xx could be factored out from some terms
    int32_t d2 = yy * (xx + sizex) + xx * (yy - 2*sizey) - xx * yy;
    while(offsety >= 0) {
        if (!flipped) {
            temp_ret = qp_ellipse_helper_impl(device, x, y, offsetx, offsety, filled);
        } else {
            temp_ret = qp_ellipse_helper_impl(device, x, y, offsety, offsetx, filled);
        }

        if (!temp_ret) {
            ret = false;
            break;
        }

        offsety -= 1;
        dy -= 2 * xx;
        if (d2 <= 0) {
            offsetx += 1;
            dx += 2 * yy;
            d2 += dx;
        }
        d2 += xx - dy;
    }

    qp_dprintf("qp_ellipse: %s\n", ret ? "ok" : "fail");
    qp_comms_stop(device);
    return ret;
}
