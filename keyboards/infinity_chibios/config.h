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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6464
#define DEVICE_VER      0x0001
/* in python2: list(u"whatever".encode('utf-16-le')) */
/*   at most 32 characters or the ugly hack in usb_main.c borks */
#define MANUFACTURER "TMK"
#define USBSTR_MANUFACTURER    'T', '\x00', 'M', '\x00', 'K', '\x00', ' ', '\x00', '\xc6', '\x00'
#define PRODUCT "Infinity keyboard/TMK"
#define USBSTR_PRODUCT         'I', '\x00', 'n', '\x00', 'f', '\x00', 'i', '\x00', 'n', '\x00', 'i', '\x00', 't', '\x00', 'y', '\x00', ' ', '\x00', 'k', '\x00', 'e', '\x00', 'y', '\x00', 'b', '\x00', 'o', '\x00', 'a', '\x00', 'r', '\x00', 'd', '\x00', '/', '\x00', 'T', '\x00', 'M', '\x00', 'K', '\x00'

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 7

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* Keymap for Infiity prototype */
#define INFINITY_PROTOTYPE


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
