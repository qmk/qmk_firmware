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

/*
TODO
----
- Error handling
- Stream mode
- Tracpoint command support: needed
- Middle button + move = Wheel traslation
*/
uint8_t ps2_mouse_x = 0;
uint8_t ps2_mouse_y = 0;
uint8_t ps2_mouse_btn = 0;
uint8_t ps2_mouse_error_count = 0;
static uint8_t ps2_mouse_btn_prev = 0;

void ps2_mouse_init(void) {
    uint8_t rcv;

    // Reset
    rcv = ps2_host_send(0xFF);
    print("ps2_mouse_init: send 0xFF: ");
    phex(ps2_error); print("\n");

    // ACK
    rcv = ps2_host_recv();
    print("ps2_mouse_init: read ACK: ");
    phex(rcv); phex(ps2_error); print("\n");

    // BAT takes some time
    _delay_ms(100);
    rcv = ps2_host_recv();
    print("ps2_mouse_init: read BAT: ");
    phex(rcv); phex(ps2_error); print("\n");

    // Device ID
    rcv = ps2_host_recv();
    print("ps2_mouse_init: read DevID: ");
    phex(rcv); phex(ps2_error); print("\n");

    // Enable data reporting
    ps2_host_send(0xF4);
    print("ps2_mouse_init: send 0xF4: ");
    phex(ps2_error); print("\n");

    // ACK
    rcv = ps2_host_recv();
    print("ps2_mouse_init: read ACK: ");
    phex(rcv); phex(ps2_error); print("\n");

    // Set Remote mode
    ps2_host_send(0xF0);
    print("ps2_mouse_init: send 0xF0: ");
    phex(ps2_error); print("\n");

    // ACK
    rcv = ps2_host_recv();
    print("ps2_mouse_init: read ACK: ");
    phex(rcv); phex(ps2_error); print("\n");

    if (ps2_error) ps2_mouse_error_count++;
}

/*
Data format:
    bit: 7       6       5       4       3       2       1       0
-----------------------------------------------------------------------
0   btn: Yovflw  Xovflw  Ysign   Xsign   1       Middle  Right   Left
1   x:   X movement(0-255)
2   y:   Y movement(0-255)
*/
void ps2_mouse_read(void)
{
    uint8_t rcv;

    ps2_host_send(0xEB);
    rcv=ps2_host_recv();
    if(rcv==0xFA) {
        ps2_mouse_btn = ps2_host_recv();
        ps2_mouse_x = ps2_host_recv();
        ps2_mouse_y = ps2_host_recv();
    }
    if (ps2_error) ps2_mouse_error_count++;
}

bool ps2_mouse_changed(void)
{
    return (ps2_mouse_x || ps2_mouse_y || (ps2_mouse_btn & PS2_MOUSE_BTN_MASK) != ps2_mouse_btn_prev);
}

#define PS2_MOUSE_SCROLL_BUTTON 0x04
void ps2_mouse_usb_send(void)
{
    static bool scrolled = false;
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
