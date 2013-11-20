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
#include "report.h"
#include "host.h"

#define PS2_MOUSE_DEBUG
#ifdef PS2_MOUSE_DEBUG
#   include "print.h"
#   include "debug.h"
#else
#   define print(s)
#   define phex(h)
#   define phex16(h)
#endif


static report_mouse_t mouse_report = {};


static void ps2_mouse_print_raw_data(void);
static void ps2_mouse_print_usb_data(void);


/* supports only 3 button mouse at this time */
uint8_t ps2_mouse_init(void) {
    uint8_t rcv;

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

/* scroll support 
 * TODO: should be build option
 */
#define PS2_MOUSE_SCROLL_BUTTON 0x04
#define X_IS_NEG  (mouse_report.buttons & (1<<PS2_MOUSE_X_SIGN))
#define Y_IS_NEG  (mouse_report.buttons & (1<<PS2_MOUSE_Y_SIGN))
#define X_IS_OVF  (mouse_report.buttons & (1<<PS2_MOUSE_X_OVFLW))
#define Y_IS_OVF  (mouse_report.buttons & (1<<PS2_MOUSE_Y_OVFLW))
void ps2_mouse_task(void)
{
    enum { SCROLL_NONE, SCROLL_BTN, SCROLL_SENT };
    static uint8_t scroll_state = SCROLL_NONE;
    static uint8_t buttons_prev = 0;

    /* receives packet from mouse */
    uint8_t rcv;
    rcv = ps2_host_send(PS2_MOUSE_READ_DATA);
    if (rcv == PS2_ACK) {
        mouse_report.buttons = ps2_host_recv_response();
        mouse_report.x = ps2_host_recv_response();
        mouse_report.y = ps2_host_recv_response();
    } else {
        if (!debug_mouse) print("ps2_mouse: fail to get mouse packet\n");
        return;
    }

    /* if mouse moves or buttons state changes */
    if (mouse_report.x || mouse_report.y ||
            ((mouse_report.buttons ^ buttons_prev) & PS2_MOUSE_BTN_MASK)) {

        ps2_mouse_print_raw_data();

        buttons_prev = mouse_report.buttons;

        // PS/2 mouse data is '9-bit integer'(-256 to 255) which is comprised of sign-bit and 8-bit value.
        // bit: 8    7 ... 0
        //      sign \8-bit/
        //
        // Meanwhile USB HID mouse indicates 8bit data(-127 to 127), note that -128 is not used.
        //
        // This converts PS/2 data into HID value. Use only -127-127 out of PS/2 9-bit.
        mouse_report.x = X_IS_NEG ?
                          ((!X_IS_OVF && -127 <= mouse_report.x && mouse_report.x <= -1) ?  mouse_report.x : -127) :
                          ((!X_IS_OVF && 0 <= mouse_report.x && mouse_report.x <= 127) ? mouse_report.x : 127);
        mouse_report.y = Y_IS_NEG ?
                          ((!Y_IS_OVF && -127 <= mouse_report.y && mouse_report.y <= -1) ?  mouse_report.y : -127) :
                          ((!Y_IS_OVF && 0 <= mouse_report.y && mouse_report.y <= 127) ? mouse_report.y : 127);

        // remove sign and overflow flags
        mouse_report.buttons &= PS2_MOUSE_BTN_MASK;

        // invert coordinate of y to conform to USB HID mouse
        mouse_report.y = -mouse_report.y;


        if ((mouse_report.buttons & PS2_MOUSE_SCROLL_BUTTON) == PS2_MOUSE_SCROLL_BUTTON) {
            if (scroll_state == SCROLL_NONE) scroll_state = SCROLL_BTN;

            // doesn't send Scroll Button
            mouse_report.buttons &= ~PS2_MOUSE_SCROLL_BUTTON;

            if (mouse_report.x || mouse_report.y) {
                scroll_state = SCROLL_SENT;

                mouse_report.v = -mouse_report.y/2;
                mouse_report.h =  mouse_report.x/2;
                mouse_report.x = 0;
                mouse_report.y = 0;
                host_mouse_send(&mouse_report);
            }
        } else if (scroll_state == SCROLL_BTN &&
                (mouse_report.buttons & PS2_MOUSE_SCROLL_BUTTON) == 0) {
            scroll_state = SCROLL_NONE;

            // send Scroll Button(down and up at once) when not scrolled
            mouse_report.buttons |= PS2_MOUSE_SCROLL_BUTTON;
            host_mouse_send(&mouse_report);
            _delay_ms(100);
            mouse_report.buttons &= ~PS2_MOUSE_SCROLL_BUTTON;
            host_mouse_send(&mouse_report);
        } else { 
            scroll_state = SCROLL_NONE;

            host_mouse_send(&mouse_report);
        }
        ps2_mouse_print_usb_data();
    }
    // clear report
    mouse_report.x = 0;
    mouse_report.y = 0;
    mouse_report.v = 0;
    mouse_report.h = 0;
    mouse_report.buttons = 0;
}

static void ps2_mouse_print_raw_data(void)
{
    if (!debug_mouse) return;
    print("ps2_mouse raw [btn|x y]: [");
    phex(mouse_report.buttons); print("|");
    print_hex8((uint8_t)mouse_report.x); print(" ");
    print_hex8((uint8_t)mouse_report.y); print("]\n");
}

static void ps2_mouse_print_usb_data(void)
{
    if (!debug_mouse) return;
    print("ps2_mouse usb [btn|x y v h]: [");
    phex(mouse_report.buttons); print("|");
    print_hex8((uint8_t)mouse_report.x); print(" ");
    print_hex8((uint8_t)mouse_report.y); print(" ");
    print_hex8((uint8_t)mouse_report.v); print(" ");
    print_hex8((uint8_t)mouse_report.h); print("]\n");
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
 *    1|                    X movement
 *    2|                    Y movement
 */
