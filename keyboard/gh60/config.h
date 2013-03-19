/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    geekhack
#define PRODUCT         GH60
#define DESCRIPTION     t.m.k. keyboard firmware for GH60

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking CapsLock support. Use KC_LCAP instead of KC_CAPS in keymap */
#define CAPSLOCK_LOCKING_ENABLE
/* Locking CapsLock resynchronize hack */
#define CAPSLOCK_LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* Boot Section Size in *BYTEs*
 *   Teensy   halfKay    512
 *   Teensy++ halfKay    1024
 *   Atmel DFU loader    4096
 *   LUFA bootloader     4096
 *   USBaspLoader        2048
 */
#define BOOTLOADER_SIZE 4096

/* disable debug print */
//#define NO_DEBUG
/* disable print */
//#define NO_PRINT

#define NO_ACTION_OVERLAY
#define NO_ACTION_TAPPING
#define NO_ACTION_MACRO

#endif
