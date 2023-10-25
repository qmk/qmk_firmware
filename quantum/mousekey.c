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
#include <string.h>
#include "keycode.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "mousekey.h"

static inline int8_t times_inv_sqrt2(int8_t x) {
    // 181/256 (0.70703125) is used as an approximation for 1/sqrt(2)
    // because it is close to the exact value which is 0.707106781
    const int16_t  n = x * 181;
    const uint16_t d = 256;

    // To ensure that the integer result is rounded accurately after
    // division, check the sign of the numerator:
    // If negative, subtract half of the denominator before dividing
    // Otherwise, add half of the denominator before dividing
    return n < 0 ? (n - d / 2) / d : (n + d / 2) / d;
}

static report_mouse_t mouse_report = {0};
static void           mousekey_debug(void);
static uint8_t        mousekey_accel        = 0;
static uint8_t        mousekey_repeat       = 0;
static uint8_t        mousekey_wheel_repeat = 0;
#ifdef MOUSEKEY_INERTIA
static uint8_t mousekey_frame     = 0; // track whether gesture is inactive, first frame, or repeating
static int8_t  mousekey_x_dir     = 0; // -1 / 0 / 1 = left / neutral / right
static int8_t  mousekey_y_dir     = 0; // -1 / 0 / 0 = up / neutral / down
static int8_t  mousekey_x_inertia = 0; // current velocity, limit +/- MOUSEKEY_TIME_TO_MAX
static int8_t  mousekey_y_inertia = 0; // ...
#endif
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
#    ifdef MK_KINETIC_SPEED
uint16_t mk_wheel_interval = 1000U / MOUSEKEY_WHEEL_INITIAL_MOVEMENTS;
#    else
uint8_t mk_wheel_interval = MOUSEKEY_WHEEL_INTERVAL;
#    endif
uint8_t mk_wheel_max_speed   = MOUSEKEY_WHEEL_MAX_SPEED;
uint8_t mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;

#    ifndef MK_COMBINED
#        ifndef MK_KINETIC_SPEED
#            ifndef MOUSEKEY_INERTIA

/* Default accelerated mode */

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

#            else // MOUSEKEY_INERTIA mode

static int8_t move_unit(uint8_t axis) {
    int16_t unit;

    // handle X or Y axis
    int8_t inertia, dir;
    if (axis) {
        inertia = mousekey_y_inertia;
        dir     = mousekey_y_dir;
    } else {
        inertia = mousekey_x_inertia;
        dir     = mousekey_x_dir;
    }

    if (mousekey_frame < 2) { // first frame(s): initial keypress moves one pixel
        mousekey_frame = 1;
        unit           = dir * MOUSEKEY_MOVE_DELTA;
    } else { // acceleration
        // linear acceleration (is here for reference, but doesn't feel as good during use)
        // unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed * inertia) / mk_time_to_max;

        // x**2 acceleration (quadratic, more precise for short movements)
        int16_t percent = (inertia << 8) / mk_time_to_max;
        percent         = ((int32_t)percent * percent) >> 8;
        if (inertia < 0) percent = -percent;

        // unit = sign(inertia) + (percent of max speed)
        if (inertia > 0)
            unit = 1;
        else if (inertia < 0)
            unit = -1;
        else
            unit = 0;

        unit = unit + ((mk_max_speed * percent) >> 8);
    }

    if (unit > MOUSEKEY_MOVE_MAX)
        unit = MOUSEKEY_MOVE_MAX;
    else if (unit < -MOUSEKEY_MOVE_MAX)
        unit = -MOUSEKEY_MOVE_MAX;
    return unit;
}

#            endif // end MOUSEKEY_INERTIA mode

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

#        else /* #ifndef MK_KINETIC_SPEED */

/*
 * Kinetic movement  acceleration algorithm
 *
 *  current speed = I + A * T/50 + A * (T/50)^2 * 1/2 | maximum B
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
    uint16_t speed = mk_initial_speed;

    if (mousekey_accel & (1 << 0)) {
        speed = mk_decelerated_speed;
    } else if (mousekey_accel & (1 << 2)) {
        speed = mk_accelerated_speed;
    } else if (mousekey_repeat && mouse_timer) {
        const uint16_t time_elapsed = timer_elapsed(mouse_timer) / 50;
        speed                       = mk_initial_speed + MOUSEKEY_MOVE_DELTA * time_elapsed + (MOUSEKEY_MOVE_DELTA * time_elapsed * time_elapsed) / 2;
        if (speed > mk_base_speed) {
            speed = mk_base_speed;
        }
    }
    /* convert speed to USB mouse speed 1 to 127 */
    speed = (uint8_t)(speed / (1000U / mk_interval));

    if (speed > MOUSEKEY_MOVE_MAX) {
        speed = MOUSEKEY_MOVE_MAX;
    } else if (speed < 1) {
        speed = 1;
    }
    return speed;
}

static uint8_t wheel_unit(void) {
    uint16_t speed = MOUSEKEY_WHEEL_INITIAL_MOVEMENTS;

    if (mousekey_accel & (1 << 0)) {
        speed = MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS;
    } else if (mousekey_accel & (1 << 2)) {
        speed = MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS;
    } else if (mousekey_wheel_repeat && mouse_timer) {
        if (mk_wheel_interval != MOUSEKEY_WHEEL_BASE_MOVEMENTS) {
            const uint16_t time_elapsed = timer_elapsed(mouse_timer) / 50;
            speed                       = MOUSEKEY_WHEEL_INITIAL_MOVEMENTS + 1 * time_elapsed + (1 * time_elapsed * time_elapsed) / 2;
        }
        if (speed > MOUSEKEY_WHEEL_BASE_MOVEMENTS) {
            speed = MOUSEKEY_WHEEL_BASE_MOVEMENTS;
        }
    }
    mk_wheel_interval = 1000U / speed;
    return 1;
}

#        endif /* #ifndef MK_KINETIC_SPEED */
#    else      /* #ifndef MK_COMBINED */

/* Combined mode */

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

#    endif /* #ifndef MK_COMBINED */

#    ifdef MOUSEKEY_INERTIA

static int8_t calc_inertia(int8_t direction, int8_t velocity) {
    // simulate acceleration and deceleration

    // deceleration
    if ((direction > -1) && (velocity < 0))
        velocity = (velocity + 1) * (256 - MOUSEKEY_FRICTION) / 256;
    else if ((direction < 1) && (velocity > 0))
        velocity = velocity * (256 - MOUSEKEY_FRICTION) / 256;

    // acceleration
    if ((direction > 0) && (velocity < mk_time_to_max))
        velocity++;
    else if ((direction < 0) && (velocity > -mk_time_to_max))
        velocity--;

    return velocity;
}

#    endif

void mousekey_task(void) {
    // report cursor and scroll movement independently
    report_mouse_t tmpmr = mouse_report;

    mouse_report.x = 0;
    mouse_report.y = 0;
    mouse_report.v = 0;
    mouse_report.h = 0;

#    ifdef MOUSEKEY_INERTIA

    // if an animation is in progress and it's time for the next frame
    if ((mousekey_frame) && timer_elapsed(last_timer_c) > ((mousekey_frame > 1) ? mk_interval : mk_delay * 10)) {
        mousekey_x_inertia = calc_inertia(mousekey_x_dir, mousekey_x_inertia);
        mousekey_y_inertia = calc_inertia(mousekey_y_dir, mousekey_y_inertia);

        mouse_report.x = move_unit(0);
        mouse_report.y = move_unit(1);

        // prevent sticky "drift"
        if ((!mousekey_x_dir) && (!mousekey_x_inertia)) tmpmr.x = 0;
        if ((!mousekey_y_dir) && (!mousekey_y_inertia)) tmpmr.y = 0;

        if (mousekey_frame < 2) mousekey_frame++;
    }

    // reset if not moving and no movement keys are held
    if ((!mousekey_x_dir) && (!mousekey_y_dir) && (!mousekey_x_inertia) && (!mousekey_y_inertia)) {
        mousekey_frame = 0;
        tmpmr.x        = 0;
        tmpmr.y        = 0;
    }

#    else // default acceleration

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

#    endif // MOUSEKEY_INERTIA or not

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

    if (has_mouse_report_changed(&mouse_report, &tmpmr) || should_mousekey_report_send(&mouse_report)) {
        mousekey_send();
    }
    // save the state for later
    memcpy(&mouse_report, &tmpmr, sizeof(tmpmr));
}

void mousekey_on(uint8_t code) {
#    ifdef MK_KINETIC_SPEED
    if (mouse_timer == 0) {
        mouse_timer = timer_read();
    }
#    endif /* #ifdef MK_KINETIC_SPEED */

#    ifdef MOUSEKEY_INERTIA

    // initial keypress sets impulse and activates first frame of movement
    if ((code == KC_MS_UP) || (code == KC_MS_DOWN)) {
        mousekey_y_dir = (code == KC_MS_DOWN) ? 1 : -1;
        if (mousekey_frame < 2) mouse_report.y = move_unit(1);
    } else if ((code == KC_MS_LEFT) || (code == KC_MS_RIGHT)) {
        mousekey_x_dir = (code == KC_MS_RIGHT) ? 1 : -1;
        if (mousekey_frame < 2) mouse_report.x = move_unit(0);
    }

#    else // no inertia

    if (code == KC_MS_UP)
        mouse_report.y = move_unit() * -1;
    else if (code == KC_MS_DOWN)
        mouse_report.y = move_unit();
    else if (code == KC_MS_LEFT)
        mouse_report.x = move_unit() * -1;
    else if (code == KC_MS_RIGHT)
        mouse_report.x = move_unit();

#    endif // inertia or not

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
#    ifdef MOUSEKEY_INERTIA

    // key release clears impulse unless opposite direction is held
    if ((code == KC_MS_UP) && (mousekey_y_dir < 1))
        mousekey_y_dir = 0;
    else if ((code == KC_MS_DOWN) && (mousekey_y_dir > -1))
        mousekey_y_dir = 0;
    else if ((code == KC_MS_LEFT) && (mousekey_x_dir < 1))
        mousekey_x_dir = 0;
    else if ((code == KC_MS_RIGHT) && (mousekey_x_dir > -1))
        mousekey_x_dir = 0;

#    else // no inertia

    if (code == KC_MS_UP && mouse_report.y < 0)
        mouse_report.y = 0;
    else if (code == KC_MS_DOWN && mouse_report.y > 0)
        mouse_report.y = 0;
    else if (code == KC_MS_LEFT && mouse_report.x < 0)
        mouse_report.x = 0;
    else if (code == KC_MS_RIGHT && mouse_report.x > 0)
        mouse_report.x = 0;

#    endif // inertia or not

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

    if (has_mouse_report_changed(&mouse_report, &tmpmr) || should_mousekey_report_send(&mouse_report)) {
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
#ifdef MOUSEKEY_INERTIA
    mousekey_frame     = 0;
    mousekey_x_inertia = 0;
    mousekey_y_inertia = 0;
    mousekey_x_dir     = 0;
    mousekey_y_dir     = 0;
#endif
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

bool should_mousekey_report_send(report_mouse_t *mouse_report) {
    return mouse_report->x || mouse_report->y || mouse_report->v || mouse_report->h;
}
