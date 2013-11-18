/*
Copyright 2011,2013 Jun Wako <wakojun@gmail.com>

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
#include<avr/io.h>
#include<util/delay.h>
#include "ps2.h"
#include "ps2_mouse.h"
#include "usb_mouse.h"

#define PS2_MOUSE_DEBUG
#ifdef PS2_MOUSE_DEBUG
#   include "print.h"
#   include "debug.h"
#else
#   define print(s)
#   define phex(h)
#   define phex16(h)
#endif


bool ps2_mouse_enable = true;
uint8_t ps2_mouse_x = 0;
uint8_t ps2_mouse_y = 0;
uint8_t ps2_mouse_btn = 0;
uint8_t ps2_mouse_error_count = 0;

static uint8_t ps2_mouse_btn_prev = 0;


uint8_t ps2_mouse_init(void) {
    uint8_t rcv;

    if (!ps2_mouse_enable) return 1;

    ps2_host_init();

    _delay_ms(1000);    // wait for powering up

    // send Reset
    rcv = ps2_host_send(0xFF);
    print("ps2_mouse_init: send Reset: ");
    phex(rcv); phex(ps2_error); print("\n");

    // read completion code of BAT
    rcv = ps2_host_recv();
    print("ps2_mouse_init: read BAT: ");
    phex(rcv); phex(ps2_error); print("\n");

    // read Device ID
    rcv = ps2_host_recv();
    print("ps2_mouse_init: read DevID: ");
    phex(rcv); phex(ps2_error); print("\n");

    // send Enable Data Reporting
    rcv = ps2_host_send(0xF4);
    print("ps2_mouse_init: send 0xF4: ");
    phex(rcv); phex(ps2_error); print("\n");

    // send Set Remote mode
    rcv = ps2_host_send(0xF0);
    print("ps2_mouse_init: send 0xF0: ");
    phex(rcv); phex(ps2_error); print("\n");

    return 0;
}

uint8_t ps2_mouse_read(void)
{
    uint8_t rcv;

    if (!ps2_mouse_enable) return 1;

    rcv = ps2_host_send(0xEB);

    if(rcv==0xFA) {
        ps2_mouse_btn = ps2_host_recv_response();
        ps2_mouse_x = ps2_host_recv_response();
        ps2_mouse_y = ps2_host_recv_response();
    }
    return 0;
}

bool ps2_mouse_changed(void)
{
    return (ps2_mouse_x || ps2_mouse_y || (ps2_mouse_btn & PS2_MOUSE_BTN_MASK) != ps2_mouse_btn_prev);
}

#define PS2_MOUSE_SCROLL_BUTTON 0x04
void ps2_mouse_usb_send(void)
{
    static bool scrolled = false;

    if (!ps2_mouse_enable) return;

    if (ps2_mouse_changed()) {
        int8_t x, y, v, h;
        x = y = v = h = 0;

        // convert scale of X, Y: PS/2(-256/255) -> USB(-127/127)
        if (ps2_mouse_btn & (1<<PS2_MOUSE_X_SIGN))
            x = ps2_mouse_x > 128 ? (int8_t)ps2_mouse_x : -127;
        else
            x = ps2_mouse_x < 128 ? (int8_t)ps2_mouse_x : 127;

        if (ps2_mouse_btn & (1<<PS2_MOUSE_Y_SIGN))
            y = ps2_mouse_y > 128 ? (int8_t)ps2_mouse_y : -127;
        else
            y = ps2_mouse_y < 128 ? (int8_t)ps2_mouse_y : 127;

        // Y is needed to reverse
        y = -y;

        if (ps2_mouse_btn & PS2_MOUSE_SCROLL_BUTTON) {
            // scroll
            if (x > 0 || x < 0) h = (x > 64 ? 64 : (x < -64 ? -64 :x));
            if (y > 0 || y < 0) v = (y > 64 ? 64 : (y < -64 ? -64 :y));
            if (h || v) {
                scrolled = true;
                usb_mouse_send(0,0, -v/16, h/16, 0);
                _delay_ms(100);
            }
        } else if (!scrolled && (ps2_mouse_btn_prev & PS2_MOUSE_SCROLL_BUTTON)) {
            usb_mouse_send(0,0,0,0, PS2_MOUSE_SCROLL_BUTTON);
            _delay_ms(100);
            usb_mouse_send(0,0,0,0, 0);
        } else { 
            scrolled = false;
            usb_mouse_send(x, y, 0, 0, ps2_mouse_btn & PS2_MOUSE_BTN_MASK);
        }

        ps2_mouse_btn_prev = (ps2_mouse_btn & PS2_MOUSE_BTN_MASK);
        ps2_mouse_print();
    }
    ps2_mouse_x = 0;
    ps2_mouse_y = 0;
    ps2_mouse_btn = 0;
}

void ps2_mouse_print(void)
{
    if (!debug_mouse) return;
    print("ps2_mouse[btn|x y]: ");
    phex(ps2_mouse_btn); print("|");
    phex(ps2_mouse_x); print(" ");
    phex(ps2_mouse_y); print("\n");
}


/* PS/2 Mouse Synopsis
 * http://www.computer-engineering.org/ps2mouse/
 *
 * Command:
 * 0xFF: Reset
 * 0xF6: Set Defaults Sampling; rate=100, resolution=4cnt/mm, scaling=1:1, reporting=disabled
 * 0xF5: Disable Data Reporting
 * 0xF4: Enable Data Reporting
 * 0xF3: Set Sample Rate
 * 0xF2: Get Device ID
 * 0xF0: Set Remote Mode
 * 0xEB: Read Data
 * 0xEA: Set Stream Mode
 * 0xE9: Status Request
 * 0xE8: Set Resolution
 * 0xE7: Set Scaling 2:1
 * 0xE6: Set Scaling 1:1
 *
 * Mode:
 * Stream Mode: devices sends the data when it changs its state
 * Remote Mode: host polls the data periodically
 *
 * This code uses Remote Mode and polls the data with Read Data(0xEB).
 *
 * Data format:
 * byte|7       6       5       4       3       2       1       0
 * ----+--------------------------------------------------------------
 *    0|Yovflw  Xovflw  Ysign   Xsign   1       Middle  Right   Left
 *    1|                    X movement(0-255)
 *    2|                    Y movement(0-255)
 */
