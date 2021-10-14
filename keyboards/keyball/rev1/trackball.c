/*
Copyright 2021 @Yowkees
Copyright 2021 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>

#include "quantum.h"
#include "pointing_device.h"

#include "optical_sensor/optical_sensor.h"
#include "trackball.h"

#ifndef TRACKBALL_MAX_NUMBER
#    define TRACKBALL_MAX_NUMBER 2
#endif
#if TRACKBALL_MAX_NUMBER <= 0
#    error "TRACKBALL_MAX_NUMBER should be larger then zero"
#endif

#ifndef TRACKBALL_SAMPLE_COUNT
#    define TRACKBALL_SAMPLE_COUNT 10
#endif
#if TRACKBALL_SAMPLE_COUNT <= 0
#    error "TRACKBALL_SAMPLE_COUNT should be larger than zero"
#endif

#ifndef TRACKBALL_SCROLL_DIVIDER
#    define TRACKBALL_SCROLL_DIVIDER 10
#endif
#if TRACKBALL_SCROLL_DIVIDER <= 0
#    error "TRACKBALL_SCROLL_DIVIDER should be larger than zero"
#endif

//////////////////////////////////////////////////////////////////////////////

void trackball_init(void) {
    if (trackball_has()) {
        optical_sensor_init();
    }
}

__attribute__((weak)) void trackball_secondary_availablity(bool available) {}

__attribute__((weak)) bool trackball_has(void) {
    // FIXME: support for secondary.
    return is_keyboard_master();
}

// add16 adds two int16_t with clipping.
static int16_t add16(int16_t a, int16_t b) {
    int16_t r = a + b;
    if (a >= 0 && b >= 0 && r < 0) {
        r = 32767;
    } else if (a < 0 && b < 0 && r >= 0) {
        r = -32768;
    }
    return r;
}

static void delta_add(trackball_delta_t *a, const trackball_delta_t *b) {
    a->x = add16(a->x, b->x);
    a->y = add16(a->y, b->y);
}

bool trackball_fetch_sensor(trackball_delta_t *p) {
    if (!trackball_has()) {
        return false;
    }
    report_optical_sensor_t r = optical_sensor_get_report();
    // The sensor returns negative values for downward rotation, but screen has
    // positive axis for downward, so we invert the sign of Y.
    p->x = r.x;
    p->y = -r.y;
    return true;
}

typedef struct {
    int16_t           count;
    trackball_delta_t accum;
} tb_state_t;

static tb_state_t state[TRACKBALL_MAX_NUMBER];

void trackball_apply_delta(int8_t num, const trackball_delta_t *delta) {
    if (num < 0 || num > TRACKBALL_MAX_NUMBER) {
        return;
    }
    if (delta == NULL) {
        state[num].count = -1;
        return;
    }
    delta_add(&state[num].accum, delta);
    state[num].count++;
}

void trackball_reset_delta(int8_t num) {
    if (num < 0 || num > TRACKBALL_MAX_NUMBER) {
        return;
    }
    memset(&state[num], 0, sizeof(state[num]));
}

bool trackball_consume_delta(int8_t num, int16_t div, trackball_delta_t *out) {
    if (num < 0 || num > TRACKBALL_MAX_NUMBER || state[num].count < TRACKBALL_SAMPLE_COUNT) {
        return false;
    }
    if (div <= 0) {
        div = 1;
    }
    div *= TRACKBALL_SAMPLE_COUNT;

    trackball_delta_t d;
    d.x = state[num].accum.x / div;
    state[num].accum.x %= div;
    d.y = state[num].accum.y / div;
    state[num].accum.y %= div;
    state[num].count = 0;
    if (out != NULL) {
        *out = d;
    }

    return true;
}
