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
#include "usb_keycodes.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "mousekey.h"


static report_mouse_t report;

static uint8_t mousekey_repeat =  0;

static void mousekey_debug(void);


/*
 * TODO: fix acceleration algorithm
 * see wikipedia http://en.wikipedia.org/wiki/Mouse_keys
 */
#ifndef MOUSEKEY_DELAY_TIME
#   define MOUSEKEY_DELAY_TIME 20
#endif

#define MOUSEKEY_MOVE_INIT      5
#define MOUSEKEY_WHEEL_INIT     1
#define MOUSEKEY_MOVE_ACCEL     5
#define MOUSEKEY_WHEEL_ACCEL    1

static uint16_t last_timer = 0;

// acceleration parameters
//uint8_t mousekey_move_unit = 2;
//uint8_t mousekey_resolution = 5;


static inline uint8_t move_unit(void)
{
    uint16_t unit = 5 + mousekey_repeat*4;
    return (unit > 63 ? 63 : unit);
}

void mousekey_task(void)
{
    if (timer_elapsed(last_timer) < MOUSEKEY_DELAY_TIME)
        return;

    if (report.x == 0 && report.y == 0 && report.v == 0 && report.h == 0)
        return;

    if (mousekey_repeat != UINT8_MAX)
        mousekey_repeat++;


    if (report.x > 0) report.x = move_unit();
    if (report.x < 0) report.x = move_unit() * -1;
    if (report.y > 0) report.y = move_unit();
    if (report.y < 0) report.y = move_unit() * -1;

    if (report.x && report.y) {
        report.x *= 0.7;
        report.y *= 0.7;
    }

    if (report.v > 0) report.v = move_unit();
    if (report.v < 0) report.v = move_unit() * -1;
    if (report.h > 0) report.h = move_unit();
    if (report.h < 0) report.h = move_unit() * -1;

    mousekey_send();
}

void mousekey_on(uint8_t code)
{
    if      (code == KB_MS_UP)       report.y = MOUSEKEY_MOVE_INIT * -1;
    else if (code == KB_MS_DOWN)     report.y = MOUSEKEY_MOVE_INIT;
    else if (code == KB_MS_LEFT)     report.x = MOUSEKEY_MOVE_INIT * -1;
    else if (code == KB_MS_RIGHT)    report.x = MOUSEKEY_MOVE_INIT;
    else if (code == KB_MS_WH_UP)    report.v = MOUSEKEY_WHEEL_INIT;
    else if (code == KB_MS_WH_DOWN)  report.v = MOUSEKEY_WHEEL_INIT * -1;
    else if (code == KB_MS_WH_LEFT)  report.h = MOUSEKEY_WHEEL_INIT * -1;
    else if (code == KB_MS_WH_RIGHT) report.h = MOUSEKEY_WHEEL_INIT;
    else if (code == KB_MS_BTN1)     report.buttons |= MOUSE_BTN1;
    else if (code == KB_MS_BTN2)     report.buttons |= MOUSE_BTN2;
    else if (code == KB_MS_BTN3)     report.buttons |= MOUSE_BTN3;
    else if (code == KB_MS_BTN4)     report.buttons |= MOUSE_BTN4;
    else if (code == KB_MS_BTN5)     report.buttons |= MOUSE_BTN5;
}

void mousekey_off(uint8_t code)
{
    if      (code == KB_MS_UP    && report.y < 0) report.y = 0;
    else if (code == KB_MS_DOWN  && report.y > 0) report.y = 0;
    else if (code == KB_MS_LEFT  && report.x < 0) report.x = 0;
    else if (code == KB_MS_RIGHT && report.x > 0) report.x = 0;
    else if (code == KB_MS_WH_UP    && report.v > 0) report.v = 0;
    else if (code == KB_MS_WH_DOWN  && report.v < 0) report.v = 0;
    else if (code == KB_MS_WH_LEFT  && report.h < 0) report.h = 0;
    else if (code == KB_MS_WH_RIGHT && report.h > 0) report.h = 0;
    else if (code == KB_MS_BTN1) report.buttons &= ~MOUSE_BTN1;
    else if (code == KB_MS_BTN2) report.buttons &= ~MOUSE_BTN2;
    else if (code == KB_MS_BTN3) report.buttons &= ~MOUSE_BTN3;
    else if (code == KB_MS_BTN4) report.buttons &= ~MOUSE_BTN4;
    else if (code == KB_MS_BTN5) report.buttons &= ~MOUSE_BTN5;

    if (report.x == 0 && report.y == 0 && report.v == 0 && report.h == 0)
        mousekey_repeat = 0;
}

void mousekey_send(void)
{
    mousekey_debug();
    host_mouse_send(&report);
    last_timer = timer_read();
}

void mousekey_clear(void)
{
    report = (report_mouse_t){};
/*
    report.buttons = 0;
    report.x = 0;
    report.y = 0;
    report.v = 0;
    report.h = 0;
*/
}

static void mousekey_debug(void)
{
    if (!debug_mouse) return;
    print("mousekey [btn|x y v h]rep: [");
    phex(report.buttons); print("|");
    phex(report.x); print(" ");
    phex(report.y); print(" ");
    phex(report.v); print(" ");
    phex(report.h); print("]");
    phex(mousekey_repeat);
    print("\n");
}
