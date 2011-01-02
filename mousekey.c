#include <stdint.h>
#include <util/delay.h>
#include "usb_keycodes.h"
#include "usb_mouse.h"
#include "mousekey.h"


static int8_t mousekey_x = 0;
static int8_t mousekey_y = 0;
static int8_t mousekey_v = 0;
static int8_t mousekey_h = 0;
static uint8_t mousekey_btn = 0;
static uint8_t mousekey_btn_prev = 0;
static uint8_t mousekey_repeat =  0;


/*
 * TODO: fix acceleration algorithm
 * see wikipedia http://en.wikipedia.org/wiki/Mouse_keys
 */
#ifndef MOUSEKEY_DELAY_TIME
#   define MOUSEKEY_DELAY_TIME 255
#endif


static inline uint8_t move_unit(void)
{
    return 10 + (mousekey_repeat < 50 ? mousekey_repeat/5 : 10);
}

void mousekey_decode(uint8_t code)
{
    if      (code == MS_UP)   mousekey_y -= move_unit();
    else if (code == MS_DOWN) mousekey_y += move_unit();
    else if (code == MS_LEFT) mousekey_x -= move_unit();
    else if (code == MS_RGHT) mousekey_x += move_unit();
    else if (code == MS_BTN1) mousekey_btn |= MOUSE_BTN1;
    else if (code == MS_BTN2) mousekey_btn |= MOUSE_BTN2;
    else if (code == MS_BTN3) mousekey_btn |= MOUSE_BTN3;
    else if (code == MS_BTN4) mousekey_btn |= MOUSE_BTN4;
    else if (code == MS_BTN5) mousekey_btn |= MOUSE_BTN5;
    else if (code == MS_WH_U) mousekey_v += 1;
    else if (code == MS_WH_D) mousekey_v -= 1;
    else if (code == MS_WH_L) mousekey_h -= 1;
    else if (code == MS_WH_R) mousekey_h += 1;
}

bool mousekey_changed(void)
{
    return (mousekey_x || mousekey_y || mousekey_v || mousekey_h || mousekey_btn != mousekey_btn_prev);
}

void mousekey_usb_send(void)
{
    if (mousekey_changed()) {
        mousekey_btn_prev = mousekey_btn;
        if (mousekey_x && mousekey_y)
            usb_mouse_send(mousekey_x*0.7, mousekey_y*0.7, mousekey_v, mousekey_h, mousekey_btn);
        else
            usb_mouse_send(mousekey_x, mousekey_y, mousekey_v, mousekey_h, mousekey_btn);

        usb_mouse_print(mousekey_x, mousekey_y, mousekey_v, mousekey_h, mousekey_btn);

        _delay_ms(MOUSEKEY_DELAY_TIME >> (mousekey_repeat < 5 ? mousekey_repeat : 4));
        mousekey_repeat++;
    } else {
        mousekey_repeat = 0;
    }
    mousekey_x = 0;
    mousekey_y = 0;
    mousekey_v = 0;
    mousekey_h = 0;
    mousekey_btn = 0;
}
