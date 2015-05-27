/*
Copyright 2014 Jun Wako <wakojun@gmail.com>

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

#if 0
// duplicated name against mbed USBDeivce
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3BED
#endif
#define DEVICE_VER      0x0001
#define MANUFACTURER    tmk.
#define PRODUCT         Infinitiy
#define DESCRIPTION     Massdrop Infinity keyboard firmware by tmk


/* matrix size */
#define MATRIX_ROWS 9   // Strobe
#define MATRIX_COLS 7   // Sense

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) 


/* for prototype */
//#define INFINITY_PROTOTYPE

#endif
