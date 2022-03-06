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

static report_mouse_t mouse_report = {0};
static void           mousekey_debug(void);
static uint8_t        mousekey_accel        = 0;
static uint8_t        mousekey_repeat       = 0;
static uint8_t        mousekey_wheel_repeat = 0;
#ifdef MK_KINETIC_SPEED
static uint16_t mouse_timer = 0;
#endif

#ifndef MK_3_SPEED

static uint16_t last_timer_c = 0;
static uint16_t last_timer_w = 0;

/*
 * Mouse keys acceleration algorithm
 *  http://en.wikipedia.org/wiki/Mouse_keys
 *
 *  speed = delta * max_speed * (repeat / time_to_max)**((1000+curve)/1000)
 */
/* milliseconds between the initial key press and first repeated motion event (0-2550) */
uint8_t mk_delay = MOUSEKEY_DELAY / 10;
/* milliseconds between repeated motion events (0-255) */
uint8_t mk_interval = MOUSEKEY_INTERVAL;
/* steady speed (in action_delta units) applied each event (0-255) */
uint8_t mk_max_speed = MOUSEKEY_MAX_SPEED;
/* number of events (count) accelerating to steady speed (0-255) */
uint8_t mk_time_to_max = MOUSEKEY_TIME_TO_MAX;
/* ramp used to reach maximum pointer speed (NOT SUPPORTED) */
// int8_t mk_curve = 0;
/* wheel params */
/* milliseconds between the initial key press and first repeated motion event (0-2550) */
uint8_t mk_wheel_delay = MOUSEKEY_WHEEL_DELAY / 10;
/* milliseconds between repeated motion events (0-255) */
uint8_t mk_wheel_interval    = MOUSEKEY_WHEEL_INTERVAL;
uint8_t mk_wheel_max_speed   = MOUSEKEY_WHEEL_MAX_SPEED;
uint8_t mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;

#    ifndef MK_COMBINED

static uint8_t move_unit(void) {
    uint16_t unit;
    if (mousekey_accel & (1 << 0)) {
        unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed) / 4;
    } else if (mousekey_accel & (1 << 1)) {
        unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed) / 2;
    } else if (mousekey_accel & (1 << 2)) {
        unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed);
    } else if (mousekey_repeat == 0) {
        unit = MOUSEKEY_MOVE_DELTA;
    } else if (mousekey_repeat >= mk_time_to_max) {
        unit = MOUSEKEY_MOVE_DELTA * mk_max_speed;
    } else {
        unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed * mousekey_repeat) / mk_time_to_max;
    }
    return (unit > MOUSEKEY_MOVE_MAX ? MOUSEKEY_MOVE_MAX : (unit == 0 ? 1 : unit));
}

static uint8_t wheel_unit(void) {
    uint16_t unit;
    if (mousekey_accel & (1 << 0)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed) / 4;
    } else if (mousekey_accel & (1 << 1)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed) / 2;
    } else if (mousekey_accel & (1 << 2)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed);
    } else if (mousekey_wheel_repeat == 0) {
        unit = MOUSEKEY_WHEEL_DELTA;
    } else if (mousekey_wheel_repeat >= mk_wheel_time_to_max) {
        unit = MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed;
    } else {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed * mousekey_wheel_repeat) / mk_wheel_time_to_max;
    }
    return (unit > MOUSEKEY_WHEEL_MAX ? MOUSEKEY_WHEEL_MAX : (unit == 0 ? 1 : unit));
}

#    else /* #ifndef MK_COMBINED */
#        ifdef MK_KINETIC_SPEED

/*
 * Kinetic movement  acceleration algorithm
 *
 *  current speed = I + A * T/50 + A * 0.5 * T^2 | maximum B
 *
 * T: time since the mouse movement started
 * E: mouse events per second (set through MOUSEKEY_INTERVAL, UHK sends 250, the
 *    pro micro on my Signum 3.0 sends only 125!)
 * I: initial speed at time 0
 * A: acceleration
 * B: base mouse travel speed
 */
const uint16_t mk_accelerated_speed = MOUSEKEY_ACCELERATED_SPEED;
const uint16_t mk_base_speed        = MOUSEKEY_BASE_SPEED;
const uint16_t mk_decelerated_speed = MOUSEKEY_DECELERATED_SPEED;
const uint16_t mk_initial_speed     = MOUSEKEY_INITIAL_SPEED;

static uint8_t move_unit(void) {
    float speed = mk_initial_speed;

    if (mousekey_accel & ((1 << 0) | (1 << 2))) {
        speed = mousekey_accel & (1 << 2) ? mk_accelerated_speed : mk_decelerated_speed;
    } else if (mousekey_repeat && mouse_timer) {
        const float time_elapsed = timer_elapsed(mouse_timer) / 50;
        speed                    = mk_initial_speed + MOUSEKEY_MOVE_DELTA * time_elapsed + MOUSEKEY_MOVE_DELTA * 0.5 * time_elapsed * time_elapsed;

        speed = speed > mk_base_speed ? mk_base_speed : speed;
    }

    /* convert speed to USB mouse speed 1 to 127 */
    speed = (uint8_t)(speed / (1000.0f / mk_interval));
    speed = speed < 1 ? 1 : speed;

    return speed > MOUSEKEY_MOVE_MAX ? MOUSEKEY_MOVE_MAX : speed;
}

float mk_wheel_interval = 1000.0f / MOUSEKEY_WHEEL_INITIAL_MOVEMENTS;

static uint8_t wheel_unit(void) {
    float speed = MOUSEKEY_WHEEL_INITIAL_MOVEMENTS;

    if (mousekey_accel & ((1 << 0) | (1 << 2))) {
        speed = mousekey_accel & (1 << 2) ? MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS : MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS;
    } else if (mousekey_repeat && mouse_timer) {
        if (mk_wheel_interval != MOUSEKEY_WHEEL_BASE_MOVEMENTS) {
            const float time_elapsed = timer_elapsed(mouse_timer) / 50;
            speed                    = MOUSEKEY_WHEEL_INITIAL_MOVEMENTS + 1 * time_elapsed + 1 * 0.5 * time_elapsed * time_elapsed;
        }
        speed = speed > MOUSEKEY_WHEEL_BASE_MOVEMENTS ? MOUSEKEY_WHEEL_BASE_MOVEMENTS : speed;
    }

    mk_wheel_interval = 1000.0f / speed;

    return 1;
}

#        else /* #ifndef MK_KINETIC_SPEED */

static uint8_t move_unit(void) {
    uint16_t unit;
    if (mousekey_accel & (1 << 0)) {
        unit = 1;
    } else if (mousekey_accel & (1 << 1)) {
        unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed) / 2;
    } else if (mousekey_accel & (1 << 2)) {
        unit = MOUSEKEY_MOVE_MAX;
    } else if (mousekey_repeat == 0) {
        unit = MOUSEKEY_MOVE_DELTA;
    } else if (mousekey_repeat >= mk_time_to_max) {
        unit = MOUSEKEY_MOVE_DELTA * mk_max_speed;
    } else {
        unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed * mousekey_repeat) / mk_time_to_max;
    }
    return (unit > MOUSEKEY_MOVE_MAX ? MOUSEKEY_MOVE_MAX : (unit == 0 ? 1 : unit));
}

static uint8_t wheel_unit(void) {
    uint16_t unit;
    if (mousekey_accel & (1 << 0)) {
        unit = 1;
    } else if (mousekey_accel & (1 << 1)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed) / 2;
    } else if (mousekey_accel & (1 << 2)) {
        unit = MOUSEKEY_WHEEL_MAX;
    } else if (mousekey_repeat == 0) {
        unit = MOUSEKEY_WHEEL_DELTA;
    } else if (mousekey_repeat >= mk_wheel_time_to_max) {
        unit = MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed;
    } else {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed * mousekey_repeat) / mk_wheel_time_to_max;
    }
    return (unit > MOUSEKEY_WHEEL_MAX ? MOUSEKEY_WHEEL_MAX : (unit == 0 ? 1 : unit));
}

#        endif /* #ifndef MK_KINETIC_SPEED */
#    endif     /* #ifndef MK_COMBINED */

void mousekey_task(void) {
    // report cursor and scroll movement independently
    report_mouse_t tmpmr = mouse_report;

    mouse_report.x = 0;
    mouse_report.y = 0;
    mouse_report.v = 0;
    mouse_report.h = 0;

    if ((tmpmr.x || tmpmr.y) && timer_elapsed(last_timer_c) > (mousekey_repeat ? mk_interval : mk_delay * 10)) {
        if (mousekey_repeat != UINT8_MAX) mousekey_repeat++;
        if (tmpmr.x != 0) mouse_report.x = move_unit() * ((tmpmr.x > 0) ? 1 : -1);
        if (tmpmr.y != 0) mouse_report.y = move_unit() * ((tmpmr.y > 0) ? 1 : -1);

        /* diagonal move [1/sqrt(2)] */
        if (mouse_report.x && mouse_report.y) {
            mouse_report.x = times_inv_sqrt2(mouse_report.x);
            if (mouse_report.x == 0) {
                mouse_report.x = 1;
            }
            mouse_report.y = times_inv_sqrt2(mouse_report.y);
            if (mouse_report.y == 0) {
                mouse_report.y = 1;
            }
        }
    }
    if ((tmpmr.v || tmpmr.h) && timer_elapsed(last_timer_w) > (mousekey_wheel_repeat ? mk_wheel_interval : mk_wheel_delay * 10)) {
        if (mousekey_wheel_repeat != UINT8_MAX) mousekey_wheel_repeat++;
        if (tmpmr.v != 0) mouse_report.v = wheel_unit() * ((tmpmr.v > 0) ? 1 : -1);
        if (tmpmr.h != 0) mouse_report.h = wheel_unit() * ((tmpmr.h > 0) ? 1 : -1);

        /* diagonal move [1/sqrt(2)] */
        if (mouse_report.v && mouse_report.h) {
            mouse_report.v = times_inv_sqrt2(mouse_report.v);
            if (mouse_report.v == 0) {
                mouse_report.v = 1;
            }
            mouse_report.h = times_inv_sqrt2(mouse_report.h);
            if (mouse_report.h == 0) {
                mouse_report.h = 1;
            }
        }
    }

    if (has_mouse_report_changed(&mouse_report, &tmpmr)) {
        mousekey_send();
    }
    memcpy(&mouse_report, &tmpmr, sizeof(tmpmr));
}

void mousekey_on(uint8_t code) {
#    ifdef MK_KINETIC_SPEED
    if (mouse_timer == 0) {
        mouse_timer = timer_read();
    }
#    endif /* #ifdef MK_KINETIC_SPEED */

    if (code == KC_MS_UP)
        mouse_report.y = move_unit() * -1;
    else if (code == KC_MS_DOWN)
        mouse_report.y = move_unit();
    else if (code == KC_MS_LEFT)
        mouse_report.x = move_unit() * -1;
    else if (code == KC_MS_RIGHT)
        mouse_report.x = move_unit();
    else if (code == KC_MS_WH_UP)
        mouse_report.v = wheel_unit();
    else if (code == KC_MS_WH_DOWN)
        mouse_report.v = wheel_unit() * -1;
    else if (code == KC_MS_WH_LEFT)
        mouse_report.h = wheel_unit() * -1;
    else if (code == KC_MS_WH_RIGHT)
        mouse_report.h = wheel_unit();
    else if (IS_MOUSEKEY_BUTTON(code))
        mouse_report.buttons |= 1 << (code - KC_MS_BTN1);
    else if (code == KC_MS_ACCEL0)
        mousekey_accel |= (1 << 0);
    else if (code == KC_MS_ACCEL1)
        mousekey_accel |= (1 << 1);
    else if (code == KC_MS_ACCEL2)
        mousekey_accel |= (1 << 2);
}

void mousekey_off(uint8_t code) {
    if (code == KC_MS_UP && mouse_report.y < 0)
        mouse_report.y = 0;
    else if (code == KC_MS_DOWN && mouse_report.y > 0)
        mouse_report.y = 0;
    else if (code == KC_MS_LEFT && mouse_report.x < 0)
        mouse_report.x = 0;
    else if (code == KC_MS_RIGHT && mouse_report.x > 0)
        mouse_report.x = 0;
    else if (code == KC_MS_WH_UP && mouse_report.v > 0)
        mouse_report.v = 0;
    else if (code == KC_MS_WH_DOWN && mouse_report.v < 0)
        mouse_report.v = 0;
    else if (code == KC_MS_WH_LEFT && mouse_report.h < 0)
        mouse_report.h = 0;
    else if (code == KC_MS_WH_RIGHT && mouse_report.h > 0)
        mouse_report.h = 0;
    else if (IS_MOUSEKEY_BUTTON(code))
        mouse_report.buttons &= ~(1 << (code - KC_MS_BTN1));
    else if (code == KC_MS_ACCEL0)
        mousekey_accel &= ~(1 << 0);
    else if (code == KC_MS_ACCEL1)
        mousekey_accel &= ~(1 << 1);
    else if (code == KC_MS_ACCEL2)
        mousekey_accel &= ~(1 << 2);
    if (mouse_report.x == 0 && mouse_report.y == 0) {
        mousekey_repeat = 0;
#    ifdef MK_KINETIC_SPEED
        mouse_timer = 0;
#    endif /* #ifdef MK_KINETIC_SPEED */
    }
    if (mouse_report.v == 0 && mouse_report.h == 0) mousekey_wheel_repeat = 0;
}

#else /* #ifndef MK_3_SPEED */

enum { mkspd_unmod, mkspd_0, mkspd_1, mkspd_2, mkspd_COUNT };
#    ifndef MK_MOMENTARY_ACCEL
static uint8_t  mk_speed                 = mkspd_1;
#    else
static uint8_t mk_speed      = mkspd_unmod;
static uint8_t mkspd_DEFAULT = mkspd_unmod;
#    endif
static uint16_t last_timer_c             = 0;
static uint16_t last_timer_w             = 0;
uint16_t        c_offsets[mkspd_COUNT]   = {MK_C_OFFSET_UNMOD, MK_C_OFFSET_0, MK_C_OFFSET_1, MK_C_OFFSET_2};
uint16_t        c_intervals[mkspd_COUNT] = {MK_C_INTERVAL_UNMOD, MK_C_INTERVAL_0, MK_C_INTERVAL_1, MK_C_INTERVAL_2};
uint16_t        w_offsets[mkspd_COUNT]   = {MK_W_OFFSET_UNMOD, MK_W_OFFSET_0, MK_W_OFFSET_1, MK_W_OFFSET_2};
uint16_t        w_intervals[mkspd_COUNT] = {MK_W_INTERVAL_UNMOD, MK_W_INTERVAL_0, MK_W_INTERVAL_1, MK_W_INTERVAL_2};

void mousekey_task(void) {
    // report cursor and scroll movement independently
    report_mouse_t tmpmr = mouse_report;
    mouse_report.x       = 0;
    mouse_report.y       = 0;
    mouse_report.v       = 0;
    mouse_report.h       = 0;

    if ((tmpmr.x || tmpmr.y) && timer_elapsed(last_timer_c) > c_intervals[mk_speed]) {
        mouse_report.x = tmpmr.x;
        mouse_report.y = tmpmr.y;
    }
    if ((tmpmr.h || tmpmr.v) && timer_elapsed(last_timer_w) > w_intervals[mk_speed]) {
        mouse_report.v = tmpmr.v;
        mouse_report.h = tmpmr.h;
    }

    if (has_mouse_report_changed(&mouse_report, &tmpmr)) {
        mousekey_send();
    }
    memcpy(&mouse_report, &tmpmr, sizeof(tmpmr));
}

void adjust_speed(void) {
    uint16_t const c_offset = c_offsets[mk_speed];
    uint16_t const w_offset = w_offsets[mk_speed];
    if (mouse_report.x > 0) mouse_report.x = c_offset;
    if (mouse_report.x < 0) mouse_report.x = c_offset * -1;
    if (mouse_report.y > 0) mouse_report.y = c_offset;
    if (mouse_report.y < 0) mouse_report.y = c_offset * -1;
    if (mouse_report.h > 0) mouse_report.h = w_offset;
    if (mouse_report.h < 0) mouse_report.h = w_offset * -1;
    if (mouse_report.v > 0) mouse_report.v = w_offset;
    if (mouse_report.v < 0) mouse_report.v = w_offset * -1;
    // adjust for diagonals
    if (mouse_report.x && mouse_report.y) {
        mouse_report.x = times_inv_sqrt2(mouse_report.x);
        if (mouse_report.x == 0) {
            mouse_report.x = 1;
        }
        mouse_report.y = times_inv_sqrt2(mouse_report.y);
        if (mouse_report.y == 0) {
            mouse_report.y = 1;
        }
    }
    if (mouse_report.h && mouse_report.v) {
        mouse_report.h = times_inv_sqrt2(mouse_report.h);
        mouse_report.v = times_inv_sqrt2(mouse_report.v);
    }
}

void mousekey_on(uint8_t code) {
    uint16_t const c_offset  = c_offsets[mk_speed];
    uint16_t const w_offset  = w_offsets[mk_speed];
    uint8_t const  old_speed = mk_speed;
    if (code == KC_MS_UP)
        mouse_report.y = c_offset * -1;
    else if (code == KC_MS_DOWN)
        mouse_report.y = c_offset;
    else if (code == KC_MS_LEFT)
        mouse_report.x = c_offset * -1;
    else if (code == KC_MS_RIGHT)
        mouse_report.x = c_offset;
    else if (code == KC_MS_WH_UP)
        mouse_report.v = w_offset;
    else if (code == KC_MS_WH_DOWN)
        mouse_report.v = w_offset * -1;
    else if (code == KC_MS_WH_LEFT)
        mouse_report.h = w_offset * -1;
    else if (code == KC_MS_WH_RIGHT)
        mouse_report.h = w_offset;
    else if (IS_MOUSEKEY_BUTTON(code))
        mouse_report.buttons |= 1 << (code - KC_MS_BTN1);
    else if (code == KC_MS_ACCEL0)
        mk_speed = mkspd_0;
    else if (code == KC_MS_ACCEL1)
        mk_speed = mkspd_1;
    else if (code == KC_MS_ACCEL2)
        mk_speed = mkspd_2;
    if (mk_speed != old_speed) adjust_speed();
}

void mousekey_off(uint8_t code) {
#    ifdef MK_MOMENTARY_ACCEL
    uint8_t const old_speed = mk_speed;
#    endif
    if (code == KC_MS_UP && mouse_report.y < 0)
        mouse_report.y = 0;
    else if (code == KC_MS_DOWN && mouse_report.y > 0)
        mouse_report.y = 0;
    else if (code == KC_MS_LEFT && mouse_report.x < 0)
        mouse_report.x = 0;
    else if (code == KC_MS_RIGHT && mouse_report.x > 0)
        mouse_report.x = 0;
    else if (code == KC_MS_WH_UP && mouse_report.v > 0)
        mouse_report.v = 0;
    else if (code == KC_MS_WH_DOWN && mouse_report.v < 0)
        mouse_report.v = 0;
    else if (code == KC_MS_WH_LEFT && mouse_report.h < 0)
        mouse_report.h = 0;
    else if (code == KC_MS_WH_RIGHT && mouse_report.h > 0)
        mouse_report.h = 0;
    else if (IS_MOUSEKEY_BUTTON(code))
        mouse_report.buttons &= ~(1 << (code - KC_MS_BTN1));
#    ifdef MK_MOMENTARY_ACCEL
    else if (code == KC_MS_ACCEL0)
        mk_speed = mkspd_DEFAULT;
    else if (code == KC_MS_ACCEL1)
        mk_speed = mkspd_DEFAULT;
    else if (code == KC_MS_ACCEL2)
        mk_speed = mkspd_DEFAULT;
    if (mk_speed != old_speed) adjust_speed();
#    endif
}

#endif /* #ifndef MK_3_SPEED */

void mousekey_send(void) {
    mousekey_debug();
    uint16_t time = timer_read();
    if (mouse_report.x || mouse_report.y) last_timer_c = time;
    if (mouse_report.v || mouse_report.h) last_timer_w = time;
    host_mouse_send(&mouse_report);
}

void mousekey_clear(void) {
    mouse_report          = (report_mouse_t){};
    mousekey_repeat       = 0;
    mousekey_wheel_repeat = 0;
    mousekey_accel        = 0;
}

static void mousekey_debug(void) {
    if (!debug_mouse) return;
    print("mousekey [btn|x y v h](rep/acl): [");
    print_hex8(mouse_report.buttons);
    print("|");
    print_decs(mouse_report.x);
    print(" ");
    print_decs(mouse_report.y);
    print(" ");
    print_decs(mouse_report.v);
    print(" ");
    print_decs(mouse_report.h);
    print("](");
    print_dec(mousekey_repeat);
    print("/");
    print_dec(mousekey_accel);
    print(")\n");
}

report_mouse_t mousekey_get_report(void) {
    return mouse_report;
}
