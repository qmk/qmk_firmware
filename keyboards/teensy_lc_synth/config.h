/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xC1ED
#define PRODUCT_ID      0x2370
#define DEVICE_VER      0x0001
/* in python2: list(u"whatever".encode('utf-16-le')) */
/*   at most 32 characters or the ugly hack in usb_main.c borks */
#define MANUFACTURER "Clueboard"
#define USBSTR_MANUFACTURER    'C', '\x00', 'l', '\x00', 'u', '\x00', 'e', '\x00', 'b', '\x00', 'o', '\x00', 'a', '\x00', 'r', '\x00', 'd', '\x00'
#define PRODUCT "Teensy LC Synth"
#define USBSTR_PRODUCT         'T', '\x00', 'e', '\x00', 'e', '\x00', 'n', '\x00', 's', '\x00', 'y', '\x00', ' ', '\x00', 'L', '\x00', 'C', '\x00', ' ', '\x00', 'S', '\x00', 'y', '\x00', 'n', '\x00', 't', '\x00', 'h', '\x00'
#define DESCRIPTION "Mini synth board by Clueboard."

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 4

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
