/*
Copyright 2014 Robin Haberkorn <robin.haberkorn@googlemail.com>

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
#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "serial_mouse.h"
#include "report.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"

#ifdef MAX
#    undef MAX
#endif
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

static void print_usb_data(const report_mouse_t *report);

void serial_mouse_task(void) {
    /* 3 byte ring buffer */
    static uint8_t buffer[3];
    static int     buffer_cur = 0;

    static report_mouse_t report = {};

    int16_t rcv;

    rcv = serial_recv2();
    if (rcv < 0) /* no new data */
        return;

    if (debug_mouse) xprintf("serial_mouse: byte: %04X\n", rcv);

    /*
     * If bit 6 is one, this signals the beginning
     * of a 3 byte sequence/packet.
     */
    if (rcv & (1 << 6)) buffer_cur = 0;

    buffer[buffer_cur] = (uint8_t)rcv;

    if (buffer_cur == 0 && buffer[buffer_cur] == 0x20) {
        /*
         * Logitech extension: This must be a follow-up on
         * the last 3-byte packet signaling a middle button click
         */
        report.buttons |= MOUSE_BTN3;
        report.x = report.y = 0;

        print_usb_data(&report);
        host_mouse_send(&report);
        return;
    }

    buffer_cur++;

    if (buffer_cur < 3) return;
    buffer_cur = 0;

    /*
     * parse 3 byte packet.
     * NOTE: We only get a complete packet
     * if the mouse moved or the button states
     * change.
     */
    report.buttons = 0;
    if (buffer[0] & (1 << 5)) report.buttons |= MOUSE_BTN1;
    if (buffer[0] & (1 << 4)) report.buttons |= MOUSE_BTN2;

    report.x = (buffer[0] << 6) | buffer[1];
    report.y = ((buffer[0] << 4) & 0xC0) | buffer[2];

    /* USB HID uses values from -127 to 127 only */
    report.x = MAX(report.x, -127);
    report.y = MAX(report.y, -127);

#if 0
    if (!report.buttons && !report.x && !report.y) {
        /*
         * Microsoft extension: Middle mouse button pressed
         * FIXME: I don't know how exactly this extension works.
         */
        report.buttons |= MOUSE_BTN3;
    }
#endif

    print_usb_data(&report);
    host_mouse_send(&report);
}

static void print_usb_data(const report_mouse_t *report) {
    if (!debug_mouse) return;

    xprintf("serial_mouse usb: [%02X|%d %d %d %d]\n", report->buttons, report->x, report->y, report->v, report->h);
}
