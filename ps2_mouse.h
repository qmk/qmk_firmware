#ifndef PS2_MOUSE_H
#define  PS2_MOUSE_H

#include <stdbool.h>

#define PS2_MOUSE_BTN_MASK      0x07
#define PS2_MOUSE_BTN_LEFT      0
#define PS2_MOUSE_BTN_RIGHT     1
#define PS2_MOUSE_BTN_MIDDLE    2
#define PS2_MOUSE_X_SIGN        4
#define PS2_MOUSE_Y_SIGN        5
#define PS2_MOUSE_X_OVFLW       6
#define PS2_MOUSE_Y_OVFLW       7

extern uint8_t ps2_mouse_x;
extern uint8_t ps2_mouse_y;
extern uint8_t ps2_mouse_btn;
extern uint8_t ps2_mouse_error_count;

void ps2_mouse_init(void);
void ps2_mouse_read(void);
bool ps2_mouse_changed(void);
void ps2_mouse_usb_send(void);
void ps2_mouse_print(void);

#endif
