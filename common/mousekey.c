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
#include <util/delay.h>
#include "keycode.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "mousekey.h"



static uint8_t mousekey_repeat =  0;

static void mousekey_debug(void);


/* max value on report descriptor */
#define MOUSEKEY_MOVE_MAX       127
#define MOUSEKEY_WHEEL_MAX      15

#ifndef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA     5
#endif
#ifndef MOUSEKEY_WHEEL_DELTA
#define MOUSEKEY_WHEEL_DELTA    1
#endif
#ifndef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 300
#endif
#ifndef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 50
#endif
#ifndef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 10
#endif
#ifndef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 20
#endif
#ifndef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#endif
#ifndef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40
#endif


/*
 * Mouse keys  acceleration algorithm
 *  http://en.wikipedia.org/wiki/Mouse_keys
 *
 *  speed = delta * max_speed * (repeat / time_to_max)**((1000+curve)/1000)
 */
/* milliseconds between the initial key press and first repeated motion event (0-2550) */
static uint8_t mk_delay = MOUSEKEY_DELAY/10;
/* milliseconds between repeated motion events (0-255) */
static uint8_t mk_interval = MOUSEKEY_INTERVAL;
/* steady speed (in action_delta units) applied each event (0-255) */
static uint8_t mk_max_speed = MOUSEKEY_MAX_SPEED;
/* number of events (count) accelerating to steady speed (0-255) */
static uint8_t mk_time_to_max = MOUSEKEY_TIME_TO_MAX;
/* ramp used to reach maximum pointer speed (NOT SUPPORTED) */
//static int8_t mk_curve = 0;

static uint8_t mk_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
static uint8_t mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;


static uint16_t last_timer = 0;


static uint8_t move_unit(void)
{
    uint16_t unit;
    if (mousekey_repeat > mk_time_to_max) {
        unit = MOUSEKEY_MOVE_DELTA * mk_max_speed;
    } else {
        unit = (MOUSEKEY_MOVE_DELTA * mk_max_speed * mousekey_repeat) / mk_time_to_max;
    }
    if (unit == 0) return 1;
    return (unit > MOUSEKEY_MOVE_MAX ? MOUSEKEY_MOVE_MAX : unit);
}

static uint8_t wheel_unit(void)
{
    uint16_t unit;
    if (mousekey_repeat > mk_time_to_max) {
        unit = MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed;
    } else {
        unit = (MOUSEKEY_WHEEL_DELTA * mk_wheel_max_speed * mousekey_repeat) / mk_wheel_time_to_max;
    }
    if (unit == 0) return 1;
    return (unit > MOUSEKEY_WHEEL_MAX ? MOUSEKEY_WHEEL_MAX : unit);
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

    if (mouse_report.x && mouse_report.y) {
        mouse_report.x *= 0.7;
        mouse_report.y *= 0.7;
    }

    if (mouse_report.v > 0) mouse_report.v = wheel_unit();
    if (mouse_report.v < 0) mouse_report.v = wheel_unit() * -1;
    if (mouse_report.h > 0) mouse_report.h = wheel_unit();
    if (mouse_report.h < 0) mouse_report.h = wheel_unit() * -1;

    mousekey_send();
}

void mousekey_on(uint8_t code)
{
    if      (code == KC_MS_UP)       mouse_report.y = MOUSEKEY_MOVE_DELTA * -1;
    else if (code == KC_MS_DOWN)     mouse_report.y = MOUSEKEY_MOVE_DELTA;
    else if (code == KC_MS_LEFT)     mouse_report.x = MOUSEKEY_MOVE_DELTA * -1;
    else if (code == KC_MS_RIGHT)    mouse_report.x = MOUSEKEY_MOVE_DELTA;
    else if (code == KC_MS_WH_UP)    mouse_report.v = MOUSEKEY_WHEEL_DELTA;
    else if (code == KC_MS_WH_DOWN)  mouse_report.v = MOUSEKEY_WHEEL_DELTA * -1;
    else if (code == KC_MS_WH_LEFT)  mouse_report.h = MOUSEKEY_WHEEL_DELTA * -1;
    else if (code == KC_MS_WH_RIGHT) mouse_report.h = MOUSEKEY_WHEEL_DELTA;
    else if (code == KC_MS_BTN1)     mouse_report.buttons |= MOUSE_BTN1;
    else if (code == KC_MS_BTN2)     mouse_report.buttons |= MOUSE_BTN2;
    else if (code == KC_MS_BTN3)     mouse_report.buttons |= MOUSE_BTN3;
    else if (code == KC_MS_BTN4)     mouse_report.buttons |= MOUSE_BTN4;
    else if (code == KC_MS_BTN5)     mouse_report.buttons |= MOUSE_BTN5;
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
}

static void mousekey_debug(void)
{
    if (!debug_mouse) return;
    print("mousekey [btn|x y v h]rep: [");
    phex(mouse_report.buttons); print("|");
    phex(mouse_report.x); print(" ");
    phex(mouse_report.y); print(" ");
    phex(mouse_report.v); print(" ");
    phex(mouse_report.h); print("]");
    phex(mousekey_repeat);
    print("\n");
}
