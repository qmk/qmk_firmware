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
#include <string.h>
#include "pointing_device_gestures.h"
#include "timer.h"

#ifdef POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#    ifdef POINTING_DEVICE_MOTION_PIN
#        error POINTING_DEVICE_MOTION_PIN not supported when using inertial cursor. Need repeated calls to get_report() to generate glide events.
#    endif

static void cursor_glide_stop(cursor_glide_context_t* glide) {
    memset(&glide->status, 0, sizeof(glide->status));
}

static cursor_glide_t cursor_glide(cursor_glide_context_t* glide) {
    cursor_glide_status_t* status = &glide->status;
    cursor_glide_t         report;
    int32_t                p;
    int32_t                x, y;

    if (status->v0 == 0) {
        report.dx    = 0;
        report.dy    = 0;
        report.valid = false;
        cursor_glide_stop(glide);
        goto exit;
    }

    status->counter++;
    /* Calculate current 1D position */
    p = status->v0 * status->counter - (int32_t)glide->config.coef * status->counter * status->counter / 2;
    /*
     * Translate to x & y axes
     * Done this way instead of applying friction to each axis separately, so we don't end up with the shorter axis stuck at 0 towards the end of diagonal movements.
     */
    x            = (int32_t)(p * status->dx0 / status->v0);
    y            = (int32_t)(p * status->dy0 / status->v0);
    report.dx    = (mouse_xy_report_t)(x - status->x);
    report.dy    = (mouse_xy_report_t)(y - status->y);
    report.valid = true;
    if (report.dx <= 1 && report.dx >= -1 && report.dy <= 1 && report.dy >= -1) {
        /* Stop gliding once speed is low enough */
        cursor_glide_stop(glide);
        goto exit;
    }
    status->x     = x;
    status->y     = y;
    status->timer = timer_read();

exit:
    return report;
}

cursor_glide_t cursor_glide_check(cursor_glide_context_t* glide) {
    cursor_glide_t         invalid_report = {0, 0, false};
    cursor_glide_status_t* status         = &glide->status;

    if (status->z || (status->dx0 == 0 && status->dy0 == 0) || timer_elapsed(status->timer) < glide->config.interval) {
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
        /* Safe upper bound to avoid integer overflow with m * m */
        h = UINT16_MAX;
    } else {
        /* Upper bound based on closest log2 */
        h = (1 << (((__builtin_clzl(1) - __builtin_clzl(x) + 1) + 1) >> 1));
    }
    /* Lower bound based on closest log2 */
    l = (1 << ((__builtin_clzl(1) - __builtin_clzl(x)) >> 1));

    /* Binary search to find integer square root */
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
    cursor_glide_t         invalid_report = {0, 0, false};
    cursor_glide_status_t* status         = &glide->status;

    status->timer   = timer_read();
    status->counter = 0;
    status->v0      = (status->dx0 == 0 && status->dy0 == 0) ? 0.0 : sqrt32(((int32_t)status->dx0 * 256 * status->dx0 * 256) + ((int32_t)status->dy0 * 256 * status->dy0 * 256)); // skip trigonometry if not needed, calculate distance in Q8
    status->x       = 0;
    status->y       = 0;
    status->z       = 0;

    if (status->v0 < ((uint32_t)glide->config.trigger_px * 256)) { /* Q8 comparison */
        /* Not enough velocity to be worth gliding, abort */
        cursor_glide_stop(glide);
        return invalid_report;
    }

    return cursor_glide(glide);
}

void cursor_glide_update(cursor_glide_context_t* glide, mouse_xy_report_t dx, mouse_xy_report_t dy, uint16_t z) {
    cursor_glide_status_t* status = &glide->status;

    status->dx0 = dx;
    status->dy0 = dy;
    status->z   = z;
}
#endif
