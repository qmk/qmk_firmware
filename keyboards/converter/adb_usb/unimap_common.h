/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

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
#ifndef UNIMAP_COMMON_H
#define UNIMAP_COMMON_H

#include <stdint.h>
#include <avr/pgmspace.h>
#include "unimap.h"


/* Apple Extended Keyboard Common layout: ANSI+ISO
 * ,---.   .---------------. ,---------------. ,---------------. ,-----------. ,---------------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau| |VDn|VUp|Mut|F24|
 * `---'   `---------------' `---------------' `---------------' `-----------' `---------------'
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |NmL|  =|  /|  *|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|  -|
 * |-----------------------------------------------------------| `-----------' |---------------|
 * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |  4|  5|  6|  +|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shif|\  |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
 * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
 * |Ctrl |Alt |Gui |         Space           |Gui  |Alt |Ctrl  | |Lef|Dow|Rig| |      0|  .|   |
 * `-----------------------------------------------------------' `-----------' `---------------'
 * Command      = Gui
 * Option       = Alt
 * Power key    = F24
 * Mic          = F13(Adjustable keyboard)
 */
// http://lxr.free-electrons.com/source/drivers/macintosh/adbhid.c
// http://opensource.apple.com//source/IOHIDFamily/IOHIDFamily-701.20.10/IOHIDFamily/Cosmo_USB2ADB.c
// http://m0115.web.fc2.com/m0115.jpg
const uint8_t PROGMEM unimap_trans[MATRIX_ROWS][MATRIX_COLS] = {
        //  Position(unimap)        ADB scan code(matrix)
        //  ---------------------------------------------
        {
            UNIMAP_A,               // 0x00
            UNIMAP_S,               // 0x01
            UNIMAP_D,               // 0x02
            UNIMAP_F,               // 0x03
            UNIMAP_H,               // 0x04
            UNIMAP_G,               // 0x05
            UNIMAP_Z,               // 0x06
            UNIMAP_X,               // 0x07
        },
        {
            UNIMAP_C,               // 0x08
            UNIMAP_V,               // 0x09
            UNIMAP_NONUS_BSLASH,    // 0x0A
            UNIMAP_B,               // 0x0B
            UNIMAP_Q,               // 0x0C
            UNIMAP_W,               // 0x0D
            UNIMAP_E,               // 0x0E
            UNIMAP_R,               // 0x0F
        },
        {
            UNIMAP_Y,               // 0x10
            UNIMAP_T,               // 0x11
            UNIMAP_1,               // 0x12
            UNIMAP_2,               // 0x13
            UNIMAP_3,               // 0x14
            UNIMAP_4,               // 0x15
            UNIMAP_6,               // 0x16
            UNIMAP_5,               // 0x17
        },
        {
            UNIMAP_EQUAL,           // 0x18
            UNIMAP_9,               // 0x19
            UNIMAP_7,               // 0x1A
            UNIMAP_MINUS,           // 0x1B
            UNIMAP_8,               // 0x1C
            UNIMAP_0,               // 0x1D
            UNIMAP_RBRACKET,        // 0x1E
            UNIMAP_O,               // 0x1F
        },
        {
            UNIMAP_U,               // 0x20
            UNIMAP_LBRACKET,        // 0x21
            UNIMAP_I,               // 0x22
            UNIMAP_P,               // 0x23
            UNIMAP_ENTER,           // 0x24
            UNIMAP_L,               // 0x25
            UNIMAP_J,               // 0x26
            UNIMAP_QUOTE,           // 0x27
        },
        {
            UNIMAP_K,               // 0x28
            UNIMAP_SCOLON,          // 0x29
            UNIMAP_BSLASH,          // 0x2A
            UNIMAP_COMMA,           // 0x2B
            UNIMAP_SLASH,           // 0x2C
            UNIMAP_N,               // 0x2D
            UNIMAP_M,               // 0x2E
            UNIMAP_DOT,             // 0x2F
        },
        {
            UNIMAP_TAB,             // 0x30
            UNIMAP_SPACE,           // 0x31
            UNIMAP_GRAVE,           // 0x32
            UNIMAP_BSPACE,          // 0x33
            UNIMAP_KP_ENTER,        // 0x34
            UNIMAP_ESCAPE,          // 0x35
            UNIMAP_LCTRL,           // 0x36
            UNIMAP_LGUI,            // 0x37
        },
        {
            UNIMAP_LSHIFT,          // 0x38
            UNIMAP_CAPSLOCK,        // 0x39
            UNIMAP_LALT,            // 0x3A
            UNIMAP_LEFT,            // 0x3B
            UNIMAP_RIGHT,           // 0x3C
            UNIMAP_DOWN,            // 0x3D
            UNIMAP_UP,              // 0x3E
            UNIMAP_F23,             // 0x3F     FN?
        },
        {
            UNIMAP_F17,             // 0x40
            UNIMAP_KP_DOT,          // 0x41
            UNIMAP_F13,             // 0x42     Mic(Adjustable keyboard)
            UNIMAP_KP_MINUS,        // 0x43     ADB keypad asterisk(top right)
            UNIMAP_NO,              // 0x44
            UNIMAP_KP_COMMA,        // 0x45     ADB keypad plus
            UNIMAP_NO,              // 0x46
            UNIMAP_NUMLOCK,         // 0x47
        },
        {
            UNIMAP_VOLUME_UP,       // 0x48     Vol Up(Adjustable keyboard)
            UNIMAP_VOLUME_DOWN,     // 0x49     Vol Down(Adjustable keyboard)
            UNIMAP_VOLUME_MUTE,     // 0x4A     Vol Mute(Adjustable keyboard)
            UNIMAP_KP_ASTERISK,     // 0x4B     ADB keypad slash(between equal and asterisk)
            UNIMAP_KP_ENTER,        // 0x4C
            UNIMAP_NO,              // 0x4D
            UNIMAP_KP_PLUS,         // 0x4E     ADB keypad minus
            UNIMAP_F18,             // 0x4F
        },
        {
            UNIMAP_F19,             // 0x50
            UNIMAP_KP_SLASH,        // 0x51     ADB keypad equal(next to clear/numlock)
            UNIMAP_KP_0,            // 0x52
            UNIMAP_KP_1,            // 0x53
            UNIMAP_KP_2,            // 0x54
            UNIMAP_KP_3,            // 0x55
            UNIMAP_KP_4,            // 0x56
            UNIMAP_KP_5,            // 0x57
        },
        {
            UNIMAP_KP_6,            // 0x58
            UNIMAP_KP_7,            // 0x59
            UNIMAP_F20,             // 0x5A
            UNIMAP_KP_8,            // 0x5B
            UNIMAP_KP_9,            // 0x5C
            UNIMAP_JYEN,            // 0x5D
            UNIMAP_RO,              // 0x5E
            UNIMAP_KP_COMMA,        // 0x5F
        },
        {
            UNIMAP_F5,              // 0x60
            UNIMAP_F6,              // 0x61
            UNIMAP_F7,              // 0x62
            UNIMAP_F3,              // 0x63
            UNIMAP_F8,              // 0x64
            UNIMAP_F9,              // 0x65
            UNIMAP_MHEN,            // 0x66
            UNIMAP_F11,             // 0x67
        },
        {
            UNIMAP_HENK,            // 0x68
            UNIMAP_PSCREEN,         // 0x69
            UNIMAP_F16,             // 0x6A
            UNIMAP_SCROLLLOCK,      // 0x6B
            UNIMAP_NO,              // 0x6C
            UNIMAP_F10,             // 0x6D
            UNIMAP_APPLICATION,     // 0x6E     compose
            UNIMAP_F12,             // 0x6F
        },
        {
            UNIMAP_NO,              // 0x70
            UNIMAP_PAUSE,           // 0x71
            UNIMAP_INSERT,          // 0x72
            UNIMAP_HOME,            // 0x73
            UNIMAP_PGUP,            // 0x74
            UNIMAP_DELETE,          // 0x75
            UNIMAP_F4,              // 0x76
            UNIMAP_END,             // 0x77
        },
        {
            UNIMAP_F2,              // 0x78
            UNIMAP_PGDOWN,          // 0x79
            UNIMAP_F1,              // 0x7A
            UNIMAP_RSHIFT,          // 0x7B
            UNIMAP_RALT,            // 0x7C
            UNIMAP_RCTRL,           // 0x7D
            UNIMAP_RGUI,            // 0x7E
            UNIMAP_F24,             // 0x7F     power key
        }
};

#endif
