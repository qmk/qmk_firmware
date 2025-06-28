/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

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

/*
 * Keycodes based on HID Keyboard/Keypad Usage Page (0x07) plus media keys from Generic Desktop Page (0x01) and Consumer Page (0x0C)
 *
 * See https://web.archive.org/web/20060218214400/http://www.usb.org/developers/devclass_docs/Hut1_12.pdf
 * or http://www.usb.org/developers/hidpage/Hut1_12v2.pdf (older)
 */

#pragma once

/* FIXME: Add doxygen comments here */

#define IS_ANY(code) (KC_A <= (code) && (code) <= 0xFF)

#define IS_MOUSEKEY(code) IS_MOUSE_KEYCODE(code)
#define IS_MOUSEKEY_MOVE(code) (QK_MOUSE_CURSOR_UP <= (code) && (code) <= QK_MOUSE_CURSOR_RIGHT)
#define IS_MOUSEKEY_BUTTON(code) (QK_MOUSE_BUTTON_1 <= (code) && (code) <= QK_MOUSE_BUTTON_8)
#define IS_MOUSEKEY_WHEEL(code) (QK_MOUSE_WHEEL_UP <= (code) && (code) <= QK_MOUSE_WHEEL_RIGHT)
#define IS_MOUSEKEY_ACCEL(code) (QK_MOUSE_ACCELERATION_0 <= (code) && (code) <= QK_MOUSE_ACCELERATION_2)

#define MOD_BIT(code) (1 << ((code)&0x07))

// clang-format off

// TODO: dd keycodes
#include "keycodes.h"
#include "modifiers.h"
