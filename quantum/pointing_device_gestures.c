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

cursor_glide_t cursor_glide(cursor_glide_context_t* glide) {
    cursor_glide_t report;
    float          p;
    int16_t        x, y;

    glide->counter++;
    // calculate current position
    p            = glide->v0 * glide->counter - glide->coef * glide->counter * glide->counter / 2;
    x            = (int16_t)(p * glide->dx0 / glide->v0);
    y            = (int16_t)(p * glide->dy0 / glide->v0);
    report.dx    = (mouse_xy_report_t)(x - glide->x);
    report.dy    = (mouse_xy_report_t)(y - glide->y);
    report.valid = true;
    if (report.dx <= 1 && report.dx >= -1 && report.dy <= 1 && report.dy >= -1) {
        glide->dx0 = 0;
        glide->dy0 = 0;
    }
    glide->x     = x;
    glide->y     = y;
    glide->timer = timer_read();

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

cursor_glide_t cursor_glide_start(cursor_glide_context_t* glide) {
    cursor_glide_t invalid_report = {0, 0, false};

    glide->timer   = timer_read();
    glide->counter = 0;
    glide->v0      = (glide->dx0 == 0 && glide->dy0 == 0) ? 0.0 : hypotf(glide->dx0, glide->dy0); // skip trigonometry if not needed
    glide->x       = 0;
    glide->y       = 0;
    glide->z       = 0;

    if (glide->v0 < glide->trigger_px) {
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
