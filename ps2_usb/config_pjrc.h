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

#ifndef CONFIG_H
#define CONFIG_H

/* controller configuration */
#include "controller_teensy.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6512
#define MANUFACTURER    t.m.k.
#define PRODUCT         PS/2 keyboard converter
#define DESCRIPTION     convert PS/2 keyboard to USB


/* matrix size */
#define MATRIX_ROWS 32  // keycode bit: 3-0
#define MATRIX_COLS 8   // keycode bit: 6-4


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KB_LSHIFT) | MOD_BIT(KB_RSHIFT)) || \
    keyboard_report->mods == (MOD_BIT(KB_LCTRL) | MOD_BIT(KB_RSHIFT)) \
)


/* mouse keys */
#ifdef MOUSEKEY_ENABLE
#   define MOUSEKEY_DELAY_TIME 255
#endif


/* PS/2 lines */
#define PS2_CLOCK_PORT  PORTF
#define PS2_CLOCK_PIN   PINF
#define PS2_CLOCK_DDR   DDRF
#define PS2_CLOCK_BIT   0
#define PS2_DATA_PORT   PORTF
#define PS2_DATA_PIN    PINF
#define PS2_DATA_DDR    DDRF
#define PS2_DATA_BIT    1

#endif
