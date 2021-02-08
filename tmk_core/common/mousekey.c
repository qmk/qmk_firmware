/*
 * Copyright 2011 Jun Wako <wakojun@gmail.com>
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

#include <stdint.h>
#include "keycode.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "mousekey.h"

inline int8_t times_inv_sqrt2(int8_t x) {
    // 181/256 is pretty close to 1/sqrt(2)
    // 0.70703125                 0.707106781
    // 1 too small for x=99 and x=198
    // This ends up being a mult and discard lower 8 bits
    return (x * 181) >> 8;
}

typedef struct {
    int8_t x, y;
} move_t;

static move_t bishop(const move_t sm, const int8_t unit) {
    move_t m = {};
    int8_t sig_x = 0;
    int8_t sig_y = 0;

    if (sm.x > 0) { m.x =  unit; sig_x =  1; }
    if (sm.x < 0) { m.x = -unit; sig_x = -1; }
    if (sm.y > 0) { m.y =  unit; sig_y =  1; }
    if (sm.y < 0) { m.y = -unit; sig_y = -1; }

    if (m.x && m.y) {
        /* diagonal move [1/sqrt(2)] */
        /* valid only when |x| ≡ |y| */
        /* which is true for us here */
        /* ensure we move at least 1 */
        m.x = times_inv_sqrt2(m.x);
        if (m.x == 0) m.x = sig_x;
        m.y = times_inv_sqrt2(m.y);
        if (m.y == 0) m.y = sig_y;
    }

    return m;
}

typedef struct {
    uint16_t last_timer;
    // move is {,re}set by mousekey_o{n,ff}(),
    // but never updated by mousekey_task().
    move_t move;
#ifndef MK_3_SPEED
    uint8_t repeat;
#endif
} state_t;

static state_t mouse_state = {};
static state_t wheel_state = {};
static uint8_t buttons_state = 0;

#ifndef MK_3_SPEED

static uint8_t mousekey_accel = 0;
mousekey_t mouse = MOUSEKEY_MOUSE_DEFAULT;
mousekey_t wheel = MOUSEKEY_WHEEL_DEFAULT;

#else // #ifndef MK_3_SPEED

enum { mkspd_unmod, mkspd_0, mkspd_1, mkspd_2, mkspd_COUNT };
#    ifndef MK_MOMENTARY_ACCEL
static uint8_t mk_speed = mkspd_1;
#    else
static uint8_t mk_speed = mkspd_unmod;
#    endif

const int8_t c_offsets[mkspd_COUNT] = {MK_C_OFFSET_UNMOD, MK_C_OFFSET_0, MK_C_OFFSET_1, MK_C_OFFSET_2};
const int8_t w_offsets[mkspd_COUNT] = {MK_W_OFFSET_UNMOD, MK_W_OFFSET_0, MK_W_OFFSET_1, MK_W_OFFSET_2};

const uint16_t c_intervals[mkspd_COUNT] = {MK_C_INTERVAL_UNMOD, MK_C_INTERVAL_0, MK_C_INTERVAL_1, MK_C_INTERVAL_2};
const uint16_t w_intervals[mkspd_COUNT] = {MK_W_INTERVAL_UNMOD, MK_W_INTERVAL_0, MK_W_INTERVAL_1, MK_W_INTERVAL_2};

#endif // #ifndef MK_3_SPEED

static void send_move(uint8_t btn, move_t m, move_t w) {
    if (debug_mouse) {
        xprintf("mousekey btn: %08b"
                ", mouse x:%+3d y:%+3d"
                ", wheel h:%+3d v:%+3d"
#               ifndef MK_3_SPEED
                ", repeat m:%2u w:%2u"
                ", accel: %03b"
#               else
                ", speed: %u"
#               endif
            , btn
            , m.x, m.y
            , w.x, w.y

#           ifndef MK_3_SPEED
            , mouse_state.repeat
            , wheel_state.repeat
            , mousekey_accel
#           else
            , mk_speed
#           endif
            );
    }

    uint16_t time = timer_read();
    if (m.x || m.y) mouse_state.last_timer = time;
    if (w.x || w.y) wheel_state.last_timer = time;

    report_mouse_t report = {
        .buttons = buttons_state,
        .x = mouse_state.move.x,
        .y = mouse_state.move.y,
        .h = wheel_state.move.x,
        .v = wheel_state.move.y
    };
    host_mouse_send(&report);
}

void mousekey_send(void) {
    send_move(buttons_state, mouse_state.move, wheel_state.move);
}

#ifndef MK_3_SPEED

/*
 * Mouse keys  acceleration algorithm
 *  http://en.wikipedia.org/wiki/Mouse_keys
 *
 *  speed = delta * max_speed * (repeat / time_to_max)**((1000+curve)/1000)
 */

// G G G G-Unit!
static uint16_t g_unit(const mousekey_t *what, uint8_t repeat, uint8_t delta) {
    if (mousekey_accel & (1 << 0)) {
#       ifndef MK_COMBINED
        return (delta * what->max_speed) / 4;
#       else
        return 1;
#       endif
    } else if (mousekey_accel & (1 << 1)) {
        return (delta * what->max_speed) / 2;
    } else if (mousekey_accel & (1 << 2)) {
#       ifndef MK_COMBINED
        return (delta * what->max_speed);
#       else
        return UINT16_MAX; // will be clamp()'d
#       endif
    } else if (repeat == 0) {
        return delta;
    } else if (repeat >= what->time_to_max) {
        return delta * what->max_speed;
    } else {
        return (delta * what->max_speed * repeat) / what->time_to_max;
    }
}

static inline uint8_t clamp(uint8_t n, uint8_t min, uint8_t max) {
    if (n < min) return min;
    if (n > max) return max;
    return n;
}

static move_t mousekey_step(const mousekey_t * what, state_t * state, uint8_t delta, uint8_t max) {
    if (!state->move.x && !state->move.y) return (move_t){};

    uint16_t dur = state->repeat ? what->interval : what->delay * 10;
    if (timer_elapsed(state->last_timer) < dur) return (move_t){};

    if (state->repeat < UINT8_MAX)
        state->repeat++;

    int8_t unit = clamp(g_unit(what, state->repeat, delta), 1, max);
    return bishop(state->move, unit);
}

#else // #ifndef MK_3_SPEED

static move_t mousekey_step(state_t * state, uint16_t interval) {
    if (state->move.x || state->move.y)
    {
        if (timer_elapsed(state->last_timer) > interval)
            return state->move;
    }
    return (move_t){};
}

static void adjust_speed(void) {
    mouse_state.move = bishop(mouse_state.move, c_offsets[mk_speed]);
    wheel_state.move = bishop(wheel_state.move, w_offsets[mk_speed]);
}

#endif // #ifndef MK_3_SPEED


void mousekey_task(void) {
#ifndef MK_3_SPEED
    move_t m = mousekey_step(&mouse, &mouse_state, MOUSEKEY_MOVE_DELTA,  MOUSEKEY_MOVE_MAX);
    move_t w = mousekey_step(&wheel, &wheel_state, MOUSEKEY_WHEEL_DELTA, MOUSEKEY_WHEEL_MAX);
#else
    move_t m = mousekey_step(&mouse_state, c_intervals[mk_speed]);
    move_t w = mousekey_step(&wheel_state, w_intervals[mk_speed]);
#endif
    if (m.x || m.y || w.x || w.y) send_move(0, m, w);
}

#define MOUSE_M mouse_state.move
#define WHEEL_M wheel_state.move

void mousekey_on(uint8_t code) {
#   ifdef MK_3_SPEED
    uint8_t const  old_speed = mk_speed;
#   endif

    switch (code)
    {

#   ifndef MK_3_SPEED
#       define MOUSE_UNIT clamp(g_unit(&mouse, mouse_state.repeat, MOUSEKEY_MOVE_DELTA),  1, MOUSEKEY_MOVE_MAX)
#       define WHEEL_UNIT clamp(g_unit(&wheel, wheel_state.repeat, MOUSEKEY_WHEEL_DELTA), 1, MOUSEKEY_WHEEL_MAX)
#   else
#       define MOUSE_UNIT c_offsets[mk_speed]
#       define WHEEL_UNIT w_offsets[mk_speed]
#   endif

        case KC_MS_UP:       MOUSE_M.y = -MOUSE_UNIT; break;
        case KC_MS_DOWN:     MOUSE_M.y =  MOUSE_UNIT; break;
        case KC_MS_LEFT:     MOUSE_M.x = -MOUSE_UNIT; break;
        case KC_MS_RIGHT:    MOUSE_M.x =  MOUSE_UNIT; break;

        case KC_MS_WH_UP:    WHEEL_M.y =  WHEEL_UNIT; break;
        case KC_MS_WH_DOWN:  WHEEL_M.y = -WHEEL_UNIT; break;
        case KC_MS_WH_LEFT:  WHEEL_M.x = -WHEEL_UNIT; break;
        case KC_MS_WH_RIGHT: WHEEL_M.x =  WHEEL_UNIT; break;

#undef MOUSE_UNIT
#undef WHEEL_UNIT

        case KC_MS_BTN1: buttons_state |=  MOUSE_BTN1; break;
        case KC_MS_BTN2: buttons_state |=  MOUSE_BTN2; break;
        case KC_MS_BTN3: buttons_state |=  MOUSE_BTN3; break;
        case KC_MS_BTN4: buttons_state |=  MOUSE_BTN4; break;
        case KC_MS_BTN5: buttons_state |=  MOUSE_BTN5; break;

#       ifndef MK_3_SPEED
        case KC_MS_ACCEL0: mousekey_accel |=  (1 << 0); break;
        case KC_MS_ACCEL1: mousekey_accel |=  (1 << 1); break;
        case KC_MS_ACCEL2: mousekey_accel |=  (1 << 2); break;
#       else
        case KC_MS_ACCEL0: mk_speed = mkspd_0;
        case KC_MS_ACCEL1: mk_speed = mkspd_1;
        case KC_MS_ACCEL2: mk_speed = mkspd_2;
#       endif

    }

#   ifdef MK_3_SPEED
    if (mk_speed != old_speed) adjust_speed();
#   endif

}

void mousekey_off(uint8_t code) {
#   if defined(MK_3_SPEED) && defined(MK_MOMENTARY_ACCEL)
    uint8_t const old_speed = mk_speed;
#   endif

    switch (code)
    {

        case KC_MS_UP:       if (MOUSE_M.y < 0) MOUSE_M.y = 0; break;
        case KC_MS_DOWN:     if (MOUSE_M.y > 0) MOUSE_M.y = 0; break;
        case KC_MS_LEFT:     if (MOUSE_M.x < 0) MOUSE_M.x = 0; break;
        case KC_MS_RIGHT:    if (MOUSE_M.x > 0) MOUSE_M.x = 0; break;

        case KC_MS_WH_UP:    if (WHEEL_M.y > 0) WHEEL_M.y = 0; break;
        case KC_MS_WH_DOWN:  if (WHEEL_M.y < 0) WHEEL_M.y = 0; break;
        case KC_MS_WH_LEFT:  if (WHEEL_M.x < 0) WHEEL_M.x = 0; break;
        case KC_MS_WH_RIGHT: if (WHEEL_M.x > 0) WHEEL_M.x = 0; break;

        case KC_MS_BTN1: buttons_state &= ~MOUSE_BTN1; break;
        case KC_MS_BTN2: buttons_state &= ~MOUSE_BTN2; break;
        case KC_MS_BTN3: buttons_state &= ~MOUSE_BTN3; break;
        case KC_MS_BTN4: buttons_state &= ~MOUSE_BTN4; break;
        case KC_MS_BTN5: buttons_state &= ~MOUSE_BTN5; break;

#       ifndef MK_3_SPEED
        case KC_MS_ACCEL0: mousekey_accel &= ~(1 << 0); break;
        case KC_MS_ACCEL1: mousekey_accel &= ~(1 << 1); break;
        case KC_MS_ACCEL2: mousekey_accel &= ~(1 << 2); break;
#       elif defined(MK_MOMENTARY_ACCEL)
        case KC_MS_ACCEL0 ... KC_MS_ACCEL2: mk_speed = mkspd_unmod; break;
#       endif
    }

#   ifndef MK_3_SPEED
    if (MOUSE_M.x == 0 && MOUSE_M.y == 0) mouse_state.repeat = 0;
    if (WHEEL_M.x == 0 && WHEEL_M.y == 0) wheel_state.repeat = 0;
#   elif defined(MK_MOMENTARY_ACCEL)
    if (mk_speed != old_speed) adjust_speed();
#   endif
}

#undef MOUSE_M
#undef WHEEL_M

void mousekey_clear(void) {
    // old behaviour was to preserve .last_timer
    mouse_state.move   = (move_t){};
    wheel_state.move   = (move_t){};
#   ifndef MK_3_SPEED
    mouse_state.repeat = 0;
    wheel_state.repeat = 0;
    mousekey_accel     = 0;
#   endif
}

