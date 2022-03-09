/* Copyright 2021 Matt Gauf
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// clang-format off
#include <inttypes.h>
#include "rgb_matrix_types.h"

/* Color Codes */
#define LEDWHIT 0xff, 0xff, 0xff
#define LED_RED 0xff, 0x00, 0x00
#define LEDORAN 0xff, 0x29, 0x00
#define LEDGOLD 0xff, 0x80, 0x00
#define LEDYELL 0xff, 0xff, 0x00
#define LEDCHAR 0x80, 0xff, 0x00
#define LEDGREE 0x00, 0xff, 0x00
#define LEDFOAM 0x00, 0xff, 0x40
#define LEDTEAL 0x00, 0x80, 0xff
#define LEDBLUE 0x00, 0x00, 0xff
#define LEDPURP 0x80, 0x00, 0xff
#define LEDMAGE 0xff, 0x00, 0xff
#define LEDPINK 0xff, 0x00, 0x80
#define LEDBLAC 0x00, 0x00, 0x00
#define LED_OFF 0x00, 0x00, 0x00

/* Color Functions */
void rgb_matrix_set_color_flags(uint8_t red, uint8_t green, uint8_t blue, uint8_t flags);

/* Function Row */
#define PIN_ESC      0
#define PIN_F1       6
#define PIN_F2       12
#define PIN_F3       18
#define PIN_F4       23
#define PIN_F5       28
#define PIN_F6       34
#define PIN_F7       39
#define PIN_F8       44
#define PIN_F9       50
#define PIN_F10      56
#define PIN_F11      61
#define PIN_F12      66
#define PIN_PRINT    69

/* Number Row */
#define PIN_0        57
#define PIN_1        7
#define PIN_2        13
#define PIN_3        19
#define PIN_4        24
#define PIN_5        29
#define PIN_6        35
#define PIN_7        40
#define PIN_8        45
#define PIN_9        51

/* QWERTY */
#define PIN_A        9
#define PIN_B        32
#define PIN_C        22
#define PIN_D        21
#define PIN_E        20
#define PIN_F        26
#define PIN_G        31
#define PIN_H        37
#define PIN_I        46
#define PIN_J        42
#define PIN_K        47
#define PIN_L        53
#define PIN_M        43
#define PIN_N        38
#define PIN_O        52
#define PIN_P        58
#define PIN_Q        8
#define PIN_R        25
#define PIN_S        15
#define PIN_T        30
#define PIN_U        41
#define PIN_V        27
#define PIN_W        14
#define PIN_X        16
#define PIN_Y        36
#define PIN_Z        10

/* Symbols */
#define PIN_MINUS    62
#define PIN_EQUAL    78
#define PIN_RBRACKET 89
#define PIN_LBRACKET 63
#define PIN_BSLASH   93
#define PIN_SLASH    60
#define PIN_SCOLON   59
#define PIN_QUOTE    64
#define PIN_COMMA    48
#define PIN_DOT      54
#define PIN_GRAVE    1

/* Indentation */
#define PIN_TAB      2
#define PIN_SPACE    33

/* Line Control */
#define PIN_BSPACE   85
#define PIN_ENTER    96

/* Indicator */
#define PIN_CAPS     3

/* Left Modifiers */
#define PIN_LSHIFT   4
#define PIN_LCTRL    5
#define PIN_LALT     17
#define PIN_LGUI     11

/* Right Modifiers */
#define PIN_RSHIFT   90
#define PIN_RCTRL    65
#define PIN_RALT     49
#define PIN_FN       55

/* Arrow Keys */
#define PIN_UP       94
#define PIN_DOWN     97
#define PIN_LEFT     95
#define PIN_RIGHT    79

/* Fn Column */
#define PIN_DEL      72 // ┳ TOP
#define PIN_PGUP     75 // ┃
#define PIN_PGDN     86 // ┃
#define PIN_END      82 // ┻ BOTTOM

/* Left Side Underglow */
#define PIN_LED_L01  67 // ┳ TOP
#define PIN_LED_L02  70 // ┃
#define PIN_LED_L03  73 // ┃
#define PIN_LED_L04  76 // ┃
#define PIN_LED_L05  80 // ┃
#define PIN_LED_L06  83 // ┃
#define PIN_LED_L07  87 // ┃
#define PIN_LED_L08  91 // ┻ BOTTOM

/* Right Side Underglow */
#define PIN_LED_L11  68 // ┳ TOP
#define PIN_LED_L12  71 // ┃
#define PIN_LED_L13  74 // ┃
#define PIN_LED_L14  77 // ┃
#define PIN_LED_L15  81 // ┃
#define PIN_LED_L16  84 // ┃
#define PIN_LED_L17  88 // ┃
#define PIN_LED_L18  92 // ┻ BOTTOM

// clang-format on
