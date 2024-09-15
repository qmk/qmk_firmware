/*
Copyright 2011,2013 Jun Wako <wakojun@gmail.com>
Copyright 2023 Johannes H. Jensen <joh@pseudoberries.com>

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

#include <stdbool.h>
#include "ps2_mouse.h"
#include "wait.h"
#include "gpio.h"
#include "host.h"
#include "timer.h"
#include "report.h"
#include "ps2.h"
#include "pointing_device.h"
#include "pointing_device_internal.h"

/* ============================= HELPERS ============================ */

static inline void ps2_mouse_convert_report_to_hid(ps2_mouse_report_t *ps2_report, report_mouse_t *mouse_report);
static inline void ps2_mouse_enable_scrolling(void);

/* ============================= IMPLEMENTATION ============================ */

/* supports only 3 button mouse at this time */
void ps2_mouse_init(void) {
    ps2_host_init();

    wait_ms(PS2_MOUSE_INIT_DELAY); // wait for powering up

    PS2_MOUSE_SEND(PS2_MOUSE_RESET, "ps2_mouse_init: sending reset");

    PS2_MOUSE_RECEIVE("ps2_mouse_init: read BAT");
    PS2_MOUSE_RECEIVE("ps2_mouse_init: read DevID");

#ifdef PS2_MOUSE_USE_REMOTE_MODE
    ps2_mouse_set_remote_mode();
#else
    ps2_mouse_enable_data_reporting();
    ps2_mouse_set_stream_mode();
#endif

#ifdef PS2_MOUSE_ENABLE_SCROLLING
    ps2_mouse_enable_scrolling();
#endif

#ifdef PS2_MOUSE_USE_2_1_SCALING
    ps2_mouse_set_scaling_2_1();
#endif
}

report_mouse_t ps2_mouse_get_report(report_mouse_t mouse_report) {
    report_mouse_t     new_report = {};
    ps2_mouse_report_t ps2_report = {};

    /* receives packet from mouse */
#ifdef PS2_MOUSE_USE_REMOTE_MODE
    uint8_t rcv;
    rcv = ps2_host_send(PS2_MOUSE_READ_DATA);
    if (rcv == PS2_ACK) {
        ps2_report.head.w = ps2_host_recv_response();
        ps2_report.x      = ps2_host_recv_response();
        ps2_report.y      = ps2_host_recv_response();
#    ifdef PS2_MOUSE_ENABLE_SCROLLING
        ps2_report.z = ps2_host_recv_response();
#    endif
    } else {
        pd_dprintf("ps2_mouse: fail to get mouse packet\n");
    }
#else
    /* Streaming mode */
    if (pbuf_has_data()) {
        ps2_report.head.w = ps2_host_recv_response();
        ps2_report.x      = ps2_host_recv_response();
        ps2_report.y      = ps2_host_recv_response();
#    ifdef PS2_MOUSE_ENABLE_SCROLLING
        ps2_report.z      = ps2_host_recv_response();
#    endif
    }
#endif

    ps2_mouse_convert_report_to_hid(&ps2_report, &new_report);

#ifdef POINTING_DEVICE_DEBUG
    if (has_mouse_report_changed(&new_report, &mouse_report)) {
        pd_dprintf("ps2_mouse: raw x=%02x y=%02x head=0x%02x [left=%u right=%u middle=%u one=%u x_sign=%u y_sign=%u x_ovf=%u y_ovf=%u]\n", ps2_report.x, ps2_report.y, ps2_report.head.w, ps2_report.head.b.left_button, ps2_report.head.b.right_button, ps2_report.head.b.middle_button, ps2_report.head.b.always_one, ps2_report.head.b.x_sign, ps2_report.head.b.y_sign, ps2_report.head.b.x_overflow, ps2_report.head.b.y_overflow);

        pd_dprintf("ps2_mouse: hid x=%d y=%d v=%d h=%d buttons=%x\n", new_report.x, new_report.y, new_report.v, new_report.h, new_report.buttons);
    }
#endif

    return new_report;
}

void ps2_mouse_disable_data_reporting(void) {
    PS2_MOUSE_SEND(PS2_MOUSE_DISABLE_DATA_REPORTING, "ps2 mouse disable data reporting");
}

void ps2_mouse_enable_data_reporting(void) {
    PS2_MOUSE_SEND(PS2_MOUSE_ENABLE_DATA_REPORTING, "ps2 mouse enable data reporting");
}

void ps2_mouse_set_remote_mode(void) {
    PS2_MOUSE_SEND_SAFE(PS2_MOUSE_SET_REMOTE_MODE, "ps2 mouse set remote mode");
    ps2_mouse_mode = PS2_MOUSE_REMOTE_MODE;
}

void ps2_mouse_set_stream_mode(void) {
    PS2_MOUSE_SEND_SAFE(PS2_MOUSE_SET_STREAM_MODE, "ps2 mouse set stream mode");
    ps2_mouse_mode = PS2_MOUSE_STREAM_MODE;
}

void ps2_mouse_set_scaling_2_1(void) {
    PS2_MOUSE_SEND_SAFE(PS2_MOUSE_SET_SCALING_2_1, "ps2 mouse set scaling 2:1");
}

void ps2_mouse_set_scaling_1_1(void) {
    PS2_MOUSE_SEND_SAFE(PS2_MOUSE_SET_SCALING_1_1, "ps2 mouse set scaling 1:1");
}

void ps2_mouse_set_resolution(ps2_mouse_resolution_t resolution) {
    PS2_MOUSE_SET_SAFE(PS2_MOUSE_SET_RESOLUTION, resolution, "ps2 mouse set resolution");
}

void ps2_mouse_set_sample_rate(ps2_mouse_sample_rate_t sample_rate) {
    PS2_MOUSE_SET_SAFE(PS2_MOUSE_SET_SAMPLE_RATE, sample_rate, "ps2 mouse set sample rate");
}

/* Note: PS/2 mouse uses counts/mm */
uint16_t ps2_mouse_get_cpi(void) {
    uint8_t rcv, cpm;
    rcv = ps2_host_send(PS2_MOUSE_STATUS_REQUEST);
    if (rcv == PS2_ACK) {
        rcv = ps2_host_recv_response();
        cpm = ps2_host_recv_response();
        rcv = ps2_host_recv_response();

        return (1 << cpm);
    }

    return 0;
}

/* Note: PS/2 mouse uses counts/mm */
void ps2_mouse_set_cpi(uint16_t cpi) {
    switch (cpi) {
        case 1:
            ps2_mouse_set_resolution(PS2_MOUSE_1_COUNT_MM);
            break;
        case 2:
            ps2_mouse_set_resolution(PS2_MOUSE_2_COUNT_MM);
            break;
        case 4:
            ps2_mouse_set_resolution(PS2_MOUSE_4_COUNT_MM);
            break;
        case 8:
            ps2_mouse_set_resolution(PS2_MOUSE_8_COUNT_MM);
            break;
        default:
            pd_dprintf("ps2_mouse: invalid cpi: %u\n", cpi);
            break;
    }
}

/* ============================= HELPERS ============================ */

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

static inline void ps2_mouse_convert_report_to_hid(ps2_mouse_report_t *ps2_report, report_mouse_t *mouse_report) {
    bool x_sign        = ps2_report->head.b.x_sign;
    bool y_sign        = ps2_report->head.b.y_sign;
    bool left_button   = ps2_report->head.b.left_button;
    bool right_button  = ps2_report->head.b.right_button;
    bool middle_button = ps2_report->head.b.middle_button;

    // PS/2 mouse data is '9-bit integer'(-256 to 255), comprised of sign-bit and 8-bit value.
    // Sign extend if negative, otherwise leave positive 8-bits as-is
    int16_t x = x_sign ? (ps2_report->x | ~0xFF) : ps2_report->x;
    int16_t y = y_sign ? (ps2_report->y | ~0xFF) : ps2_report->y;

    x *= PS2_MOUSE_X_MULTIPLIER;
    y *= PS2_MOUSE_Y_MULTIPLIER;

    // Constrain xy values to valid range
    mouse_report->x = min(max(XY_REPORT_MIN, x), XY_REPORT_MAX);
    mouse_report->y = min(max(XY_REPORT_MIN, y), XY_REPORT_MAX);

    // invert coordinate of y to conform to USB HID mouse
    mouse_report->y = -mouse_report->y;

#ifdef PS2_MOUSE_ENABLE_SCROLLING
    // Valid z values are in the range -8 to +7
    mouse_report->v = -(ps2_report->z & PS2_MOUSE_SCROLL_MASK);
    mouse_report->v *= PS2_MOUSE_V_MULTIPLIER;
#endif

#ifdef PS2_MOUSE_INVERT_BUTTONS
    // swap left & right buttons
    if (left_button) mouse_report->buttons |= MOUSE_BTN2;
    if (right_button) mouse_report->buttons |= MOUSE_BTN1;
#else
    if (left_button) mouse_report->buttons |= MOUSE_BTN1;
    if (right_button) mouse_report->buttons |= MOUSE_BTN2;
#endif

    if (middle_button) mouse_report->buttons |= MOUSE_BTN3;
}

static inline void ps2_mouse_enable_scrolling(void) {
    PS2_MOUSE_SEND(PS2_MOUSE_SET_SAMPLE_RATE, "Initiaing scroll wheel enable: Set sample rate");
    PS2_MOUSE_SEND(200, "200");
    PS2_MOUSE_SEND(PS2_MOUSE_SET_SAMPLE_RATE, "Set sample rate");
    PS2_MOUSE_SEND(100, "100");
    PS2_MOUSE_SEND(PS2_MOUSE_SET_SAMPLE_RATE, "Set sample rate");
    PS2_MOUSE_SEND(80, "80");
    PS2_MOUSE_SEND(PS2_MOUSE_GET_DEVICE_ID, "Finished enabling scroll wheel");
    wait_ms(20);
}
