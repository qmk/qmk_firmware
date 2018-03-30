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
#undef MAX
#endif
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

//#define SERIAL_MOUSE_CENTER_SCROLL

static void print_usb_data(const report_mouse_t *report);

void serial_mouse_task(void)
{
    /* 5 byte ring buffer */
    static uint8_t buffer[5];
    static int buffer_cur = 0;

    int16_t rcv;

    report_mouse_t report = {0, 0, 0, 0, 0};

    rcv = serial_recv2();
    if (rcv < 0)
        /* no new data */
        return;

    if (debug_mouse)
        xprintf("serial_mouse: byte: %04X\n", rcv);

    /*
     * Synchronization: mouse(4) says that all
     * bytes but the first one in the packet have
     * bit 7 == 0, but this is untrue.
     * Therefore we discard all bytes up to the
     * first one with the characteristic bit pattern.
     */
    if (buffer_cur == 0 && (rcv >> 3) != 0x10)
        return;

    buffer[buffer_cur++] = (uint8_t)rcv;

    if (buffer_cur < 5)
        return;
    buffer_cur = 0;

#ifdef SERIAL_MOUSE_CENTER_SCROLL
    if ((buffer[0] & 0x7) == 0x5 && (buffer[1] || buffer[2])) {
        /* USB HID uses only values from -127 to 127 */
        report.h = MAX((int8_t)buffer[1], -127);
        report.v = MAX((int8_t)buffer[2], -127);

        print_usb_data(&report);
        host_mouse_send(&report);

        if (buffer[3] || buffer[4]) {
            report.h = MAX((int8_t)buffer[3], -127);
            report.v = MAX((int8_t)buffer[4], -127);

            print_usb_data(&report);
            host_mouse_send(&report);
        }

        return;
    }
#endif

    /*
     * parse 5 byte packet.
     * NOTE: We only get a complete packet
     * if the mouse moved or the button states
     * change.
     */
    if (!(buffer[0] & (1 << 2)))
        report.buttons |= MOUSE_BTN1;
    if (!(buffer[0] & (1 << 1)))
        report.buttons |= MOUSE_BTN3;
    if (!(buffer[0] & (1 << 0)))
        report.buttons |= MOUSE_BTN2;

    /* USB HID uses only values from -127 to 127 */
    report.x = MAX((int8_t)buffer[1], -127);
    report.y = MAX(-(int8_t)buffer[2], -127);

    print_usb_data(&report);
    host_mouse_send(&report);

    if (buffer[3] || buffer[4]) {
        report.x = MAX((int8_t)buffer[3], -127);
        report.y = MAX(-(int8_t)buffer[4], -127);

        print_usb_data(&report);
        host_mouse_send(&report);
    }
}

static void print_usb_data(const report_mouse_t *report)
{
    if (!debug_mouse)
        return;

    xprintf("serial_mouse usb: [%02X|%d %d %d %d]\n",
            report->buttons, report->x, report->y,
            report->v, report->h);
}
