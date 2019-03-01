/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include "keycode.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "mousekey.h"



static report_mouse_t mouse_report = {};
static uint8_t mousekey_repeat =  0;
static uint8_t mousekey_accel = 0;

static void mousekey_debug(void);


/*
 * Mouse keys  acceleration algorithm
 *  http://en.wikipedia.org/wiki/Mouse_keys
 *
 *  speed = delta * max_speed * (repeat / time_to_max)**((1000+curve)/1000)
 */
/* milliseconds between the initial key press and first repeated motion event (0-2550) */
uint8_t mk_delay = MOUSEKEY_DELAY/10;
/* milliseconds between repeated motion events (0-255) */
uint8_t mk_interval = MOUSEKEY_INTERVAL;
/* steady speed (in action_delta units) applied each event (0-255) */
uint8_t mk_max_speed = MOUSEKEY_MAX_SPEED;
/* number of events (count) accelerating to steady speed (0-255) */
uint8_t mk_time_to_max = MOUSEKEY_TIME_TO_MAX;
/* ramp used to reach maximum pointer speed (NOT SUPPORTED) */
//int8_t mk_curve = 0;
/* wheel params */
uint8_t mk_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
uint8_t mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;


static uint16_t last_timer = 0;

inline int8_t times_inv_sqrt2(int8_t x)
{
    // 181/256 is pretty close to 1/sqrt(2)
    // 0.70703125                 0.707106781
    // 1 too small for x=99 and x=198
    // This ends up being a mult and discard lower 8 bits
    return (x * 181) >> 8;
}

static uint8_t move_unit(void)
{
    uint16_t unit;
    if (mousekey_accel & (1<<0)) {
        unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed)/4;
    } else if (mousekey_accel & (1<<1)) {
        unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed)/2;
    } else if (mousekey_accel & (1<<2)) {
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

static uint8_t wheel_unit(void)
{
    uint16_t unit;
    if (mousekey_accel & (1<<0)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed)/4;
    } else if (mousekey_accel & (1<<1)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed)/2;
    } else if (mousekey_accel & (1<<2)) {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed);
    } else if (mousekey_repeat == 0) {
        unit = MOUSEKEY_WHEEL_DELTA;
    } else if (mousekey_repeat >= mk_wheel_time_to_max) {
        unit = MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed;
    } else {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed * mousekey_repeat) / mk_wheel_time_to_max;
    }
    return (unit > MOUSEKEY_WHEEL_MAX ? MOUSEKEY_WHEEL_MAX : (unit == 0 ? 1 : unit));
}

void mousekey_task(void)
{
    if (timer_elapsed(last_timer) < (mousekey_repeat ? mk_interval : mk_delay*10))
        return;

    if (mouse_report.x == 0 && mouse_report.y == 0 && mouse_report.v == 0 && mouse_report.h == 0)
        return;

    if (mousekey_repeat != UINT8_MAX)
        mousekey_repeat++;


    if (mouse_report.x > 0) mouse_report.x = move_unit();
    if (mouse_report.x < 0) mouse_report.x = move_unit() * -1;
    if (mouse_report.y > 0) mouse_report.y = move_unit();
    if (mouse_report.y < 0) mouse_report.y = move_unit() * -1;

    /* diagonal move [1/sqrt(2)] */
    if (mouse_report.x && mouse_report.y) {
        mouse_report.x = times_inv_sqrt2(mouse_report.x);
        mouse_report.x = mouse_report.x == 0 ? 1 : mouse_report.x;
        mouse_report.y = times_inv_sqrt2(mouse_report.y);
        mouse_report.y = mouse_report.y == 0 ? 1 : mouse_report.y;
    }

    if (mouse_report.v > 0) mouse_report.v = wheel_unit();
    if (mouse_report.v < 0) mouse_report.v = wheel_unit() * -1;
    if (mouse_report.h > 0) mouse_report.h = wheel_unit();
    if (mouse_report.h < 0) mouse_report.h = wheel_unit() * -1;

    mousekey_send();
}

void mousekey_on(uint8_t code)
{
    if      (code == KC_MS_UP)       mouse_report.y = move_unit() * -1;
    else if (code == KC_MS_DOWN)     mouse_report.y = move_unit();
    else if (code == KC_MS_LEFT)     mouse_report.x = move_unit() * -1;
    else if (code == KC_MS_RIGHT)    mouse_report.x = move_unit();
    else if (code == KC_MS_WH_UP)    mouse_report.v = wheel_unit();
    else if (code == KC_MS_WH_DOWN)  mouse_report.v = wheel_unit() * -1;
    else if (code == KC_MS_WH_LEFT)  mouse_report.h = wheel_unit() * -1;
    else if (code == KC_MS_WH_RIGHT) mouse_report.h = wheel_unit();
    else if (code == KC_MS_BTN1)     mouse_report.buttons |= MOUSE_BTN1;
    else if (code == KC_MS_BTN2)     mouse_report.buttons |= MOUSE_BTN2;
    else if (code == KC_MS_BTN3)     mouse_report.buttons |= MOUSE_BTN3;
    else if (code == KC_MS_BTN4)     mouse_report.buttons |= MOUSE_BTN4;
    else if (code == KC_MS_BTN5)     mouse_report.buttons |= MOUSE_BTN5;
    else if (code == KC_MS_ACCEL0)   mousekey_accel |= (1<<0);
    else if (code == KC_MS_ACCEL1)   mousekey_accel |= (1<<1);
    else if (code == KC_MS_ACCEL2)   mousekey_accel |= (1<<2);
}

void mousekey_off(uint8_t code)
{
    if      (code == KC_MS_UP       && mouse_report.y < 0) mouse_report.y = 0;
    else if (code == KC_MS_DOWN     && mouse_report.y > 0) mouse_report.y = 0;
    else if (code == KC_MS_LEFT     && mouse_report.x < 0) mouse_report.x = 0;
    else if (code == KC_MS_RIGHT    && mouse_report.x > 0) mouse_report.x = 0;
    else if (code == KC_MS_WH_UP    && mouse_report.v > 0) mouse_report.v = 0;
    else if (code == KC_MS_WH_DOWN  && mouse_report.v < 0) mouse_report.v = 0;
    else if (code == KC_MS_WH_LEFT  && mouse_report.h < 0) mouse_report.h = 0;
    else if (code == KC_MS_WH_RIGHT && mouse_report.h > 0) mouse_report.h = 0;
    else if (code == KC_MS_BTN1) mouse_report.buttons &= ~MOUSE_BTN1;
    else if (code == KC_MS_BTN2) mouse_report.buttons &= ~MOUSE_BTN2;
    else if (code == KC_MS_BTN3) mouse_report.buttons &= ~MOUSE_BTN3;
    else if (code == KC_MS_BTN4) mouse_report.buttons &= ~MOUSE_BTN4;
    else if (code == KC_MS_BTN5) mouse_report.buttons &= ~MOUSE_BTN5;
    else if (code == KC_MS_ACCEL0) mousekey_accel &= ~(1<<0);
    else if (code == KC_MS_ACCEL1) mousekey_accel &= ~(1<<1);
    else if (code == KC_MS_ACCEL2) mousekey_accel &= ~(1<<2);

    if (mouse_report.x == 0 && mouse_report.y == 0 && mouse_report.v == 0 && mouse_report.h == 0)
        mousekey_repeat = 0;
}

void mousekey_send(void)
{
    mousekey_debug();
    host_mouse_send(&mouse_report);
    last_timer = timer_read();
}

void mousekey_clear(void)
{
    mouse_report = (report_mouse_t){};
    mousekey_repeat = 0;
    mousekey_accel = 0;
}

static void mousekey_debug(void)
{
    if (!debug_mouse) return;
    print("mousekey [btn|x y v h](rep/acl): [");
    phex(mouse_report.buttons); print("|");
    print_decs(mouse_report.x); print(" ");
    print_decs(mouse_report.y); print(" ");
    print_decs(mouse_report.v); print(" ");
    print_decs(mouse_report.h); print("](");
    print_dec(mousekey_repeat); print("/");
    print_dec(mousekey_accel); print(")\n");
}
