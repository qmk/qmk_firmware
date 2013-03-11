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

/* matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if need no debouncing */
#define DEBOUNCE    5

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

/* 
 * Boot magic keys
 * call some function by pressing key when pluging cable or powering on.
 */
/* key position on matrix(ROW:COL) */
#define KEY_FN          0x4A
#define KEY_D           0x23
#define KEY_ESC         0x00
#define KEY_IS_ON(key)  matrix_is_on((key)>>4, (key)&0xF)
/* kick up bootloader */
#define IS_BOOTMAGIC_BOOTLOADER()       KEY_IS_ON(KEY_FN)
/* debug on */
#define IS_BOOTMAGIC_DEBUG()            KEY_IS_ON(KEY_D)
/* eeprom clear */
#define IS_BOOTMAGIC_EEPROM_CLEAR()     KEY_IS_ON(KEY_ESC)

#endif
