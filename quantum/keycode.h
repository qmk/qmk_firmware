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
#define IS_KEY(code) IS_BASIC_KEYCODE(code)
#define IS_MOD(code) IS_MODIFIERS_KEYCODE(code)

#define IS_SYSTEM(code) IS_SYSTEM_KEYCODE(code)
#define IS_CONSUMER(code) IS_MEDIA_KEYCODE(code)

#define IS_MOUSEKEY(code) IS_MOUSE_KEYCODE(code)
#define IS_MOUSEKEY_MOVE(code) (KC_MS_UP <= (code) && (code) <= KC_MS_RIGHT)
#define IS_MOUSEKEY_BUTTON(code) (KC_MS_BTN1 <= (code) && (code) <= KC_MS_BTN8)
#define IS_MOUSEKEY_WHEEL(code) (KC_MS_WH_UP <= (code) && (code) <= KC_MS_WH_RIGHT)
#define IS_MOUSEKEY_ACCEL(code) (KC_MS_ACCEL0 <= (code) && (code) <= KC_MS_ACCEL2)

#define MOD_BIT(code) (1 << MOD_INDEX(code))
#define MOD_INDEX(code) ((code)&0x07)

#define MOD_MASK_CTRL (MOD_BIT(KC_LEFT_CTRL) | MOD_BIT(KC_RIGHT_CTRL))
#define MOD_MASK_SHIFT (MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_RIGHT_SHIFT))
#define MOD_MASK_ALT (MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_RIGHT_ALT))
#define MOD_MASK_GUI (MOD_BIT(KC_LEFT_GUI) | MOD_BIT(KC_RIGHT_GUI))
#define MOD_MASK_CS (MOD_MASK_CTRL | MOD_MASK_SHIFT)
#define MOD_MASK_CA (MOD_MASK_CTRL | MOD_MASK_ALT)
#define MOD_MASK_CG (MOD_MASK_CTRL | MOD_MASK_GUI)
#define MOD_MASK_SA (MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_SG (MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_AG (MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSA (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_CSG (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_CAG (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_SAG (MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSAG (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)

// clang-format off

// TODO: dd keycodes
#include "keycodes.h"
