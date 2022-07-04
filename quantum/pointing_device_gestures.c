/* Copyright 2022 Daniel Kao <daniel.m.kao@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "pointing_device_gestures.h"
#include "timer.h"
#include <math.h>

#ifdef POINTING_DEVICE_MOTION_PIN
#    error POINTING_DEVICE_MOTION_PIN not supported when using inertial cursor. Need repeated calls to get_report() to generate glide events.
#endif

static cursor_glide_t cursor_glide(cursor_glide_context_t* glide) {
    cursor_glide_t report;
    int32_t        p;
    int32_t        x, y;

    if (glide->v0 == 0) {
        report.dx    = 0;
        report.dy    = 0;
        report.valid = false;
        glide->dx0   = 0;
        glide->dy0   = 0;
        goto exit;
    }

    glide->counter++;
    // calculate current 1D position
    p = glide->v0 * glide->counter - (int32_t)glide->coef * glide->counter * glide->counter / 2;
    // translate to x & y axes
    x            = (int32_t)(p * glide->dx0 / glide->v0);
    y            = (int32_t)(p * glide->dy0 / glide->v0);
    report.dx    = (mouse_xy_report_t)(x - glide->x);
    report.dy    = (mouse_xy_report_t)(y - glide->y);
    report.valid = true;
    if (report.dx <= 1 && report.dx >= -1 && report.dy <= 1 && report.dy >= -1) {
        // stop gliding once speed is low enough
        glide->dx0 = 0;
        glide->dy0 = 0;
    }
    glide->x     = x;
    glide->y     = y;
    glide->timer = timer_read();

exit:
    return report;
}

cursor_glide_t cursor_glide_check(cursor_glide_context_t* glide) {
    cursor_glide_t invalid_report = {0, 0, false};
    if (glide->z || (glide->dx0 == 0 && glide->dy0 == 0) || timer_elapsed(glide->timer) < glide->interval) {
        return invalid_report;
    } else {
        return cursor_glide(glide);
    }
}

static inline uint16_t sqrt32(uint32_t x) {
    uint32_t l, m, h;

    if (x == 0) {
        return 0;
    } else if (x > (UINT16_MAX >> 2)) {
        // safe upper bound to avoid integer overflow with m * m
        h = UINT16_MAX;
    } else {
        // upper bound based on closest log2
        h = (1 << (((__builtin_clzl(1) - __builtin_clzl(x) + 1) + 1) >> 1));
    }
    // lower bound based on closest log2
    l = (1 << ((__builtin_clzl(1) - __builtin_clzl(x)) >> 1));

    // binary search to find integer square root
    while (l != h - 1) {
        m = (l + h) / 2;
        if (m * m <= x) {
            l = m;
        } else {
            h = m;
        }
    }
    return l;
}

cursor_glide_t cursor_glide_start(cursor_glide_context_t* glide) {
    cursor_glide_t invalid_report = {0, 0, false};

    glide->timer   = timer_read();
    glide->counter = 0;
    glide->v0      = (glide->dx0 == 0 && glide->dy0 == 0) ? 0.0 : sqrt32(((int32_t)glide->dx0 * 256 * glide->dx0 * 256) + ((int32_t)glide->dy0 * 256 * glide->dy0 * 256)); // skip trigonometry if not needed, calculate distance in Q8
    glide->x       = 0;
    glide->y       = 0;
    glide->z       = 0;

    if (glide->v0 < ((uint32_t)glide->trigger_px * 256)) { // Q8 comparison
        // not enough velocity to be worth gliding, abort
        glide->dx0 = 0;
        glide->dy0 = 0;
        return invalid_report;
    }

    return cursor_glide(glide);
}

void cursor_glide_update(cursor_glide_context_t* glide, mouse_xy_report_t dx, mouse_xy_report_t dy, uint16_t z) {
    glide->dx0 = dx;
    glide->dy0 = dy;
    glide->z   = z;
}
