#include <stdint.h>
#include <util/delay.h>
#include "usb_keycodes.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "mousekey.h"


static report_mouse_t report;
static report_mouse_t report_prev;

static uint8_t mousekey_repeat =  0;

static void mousekey_debug(void);


/*
 * TODO: fix acceleration algorithm
 * see wikipedia http://en.wikipedia.org/wiki/Mouse_keys
 */
#ifndef MOUSEKEY_DELAY_TIME
#   define MOUSEKEY_DELAY_TIME 255
#endif

// acceleration parameters
uint8_t mousekey_move_unit = 2;
uint8_t mousekey_resolution = 5;


static inline uint8_t move_unit(void)
{
    uint16_t unit = 5 + mousekey_repeat*2;
    return (unit > 63 ? 63 : unit);
}

void mousekey_decode(uint8_t code)
{
    if      (code == KB_MS_UP)      report.y = -move_unit();
    else if (code == KB_MS_DOWN)    report.y = move_unit();
    else if (code == KB_MS_LEFT)    report.x = -move_unit();
    else if (code == KB_MS_RIGHT)   report.x = move_unit();
    else if (code == KB_MS_BTN1)    report.buttons |= MOUSE_BTN1;
    else if (code == KB_MS_BTN2)    report.buttons |= MOUSE_BTN2;
    else if (code == KB_MS_BTN3)    report.buttons |= MOUSE_BTN3;
    else if (code == KB_MS_BTN4)    report.buttons |= MOUSE_BTN4;
    else if (code == KB_MS_BTN5)    report.buttons |= MOUSE_BTN5;
    else if (code == KB_MS_WH_UP)   report.v += 1;
    else if (code == KB_MS_WH_DOWN) report.v -= 1;
    else if (code == KB_MS_WH_LEFT) report.h -= 1;
    else if (code == KB_MS_WH_RIGHT)report.h += 1;
}

bool mousekey_changed(void)
{
    return (report.buttons != report_prev.buttons ||
            report.x || report.y || report.v || report.h);
}

void mousekey_send(void)
{
    static uint16_t last_timer = 0;

    if (!mousekey_changed()) {
        mousekey_repeat = 0;
        mousekey_clear_report();
        return;
    }

    // send immediately when buttun state is changed
    if (report.buttons == report_prev.buttons) {
        if (timer_elapsed(last_timer) < 5) {
            mousekey_clear_report();
            return;
        }
    }

    if (mousekey_repeat != 0xFF) {
        mousekey_repeat++;
    }

    if (report.x && report.y) {
        report.x *= 0.7;
        report.y *= 0.7;
    }

    mousekey_debug();
    host_mouse_send(&report);
    report_prev = report;
    last_timer = timer_read();
    mousekey_clear_report();
}

void mousekey_clear_report(void)
{
    report.buttons = 0;
    report.x = 0;
    report.y = 0;
    report.v = 0;
    report.h = 0;
}

static void mousekey_debug(void)
{
    if (!debug_mouse) return;
    print("mousekey[btn|x y v h]: ");
    phex(report.buttons); print("|");
    phex(report.x); print(" ");
    phex(report.y); print(" ");
    phex(report.v); print(" ");
    phex(report.h);
    phex(mousekey_repeat);
    print("\n");
}
