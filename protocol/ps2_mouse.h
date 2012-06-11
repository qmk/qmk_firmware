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

bool ps2_mouse_enable;
extern uint8_t ps2_mouse_x;
extern uint8_t ps2_mouse_y;
extern uint8_t ps2_mouse_btn;
extern uint8_t ps2_mouse_error_count;

uint8_t ps2_mouse_init(void);
uint8_t ps2_mouse_read(void);
bool ps2_mouse_changed(void);
void ps2_mouse_usb_send(void);
void ps2_mouse_print(void);

#endif
