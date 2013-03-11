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
#define PRODUCT_ID      0xCAFE
#define DEVICE_VER      0x0103
#define MANUFACTURER    t.m.k.
#define PRODUCT         HHKB mod
#define DESCRIPTION     t.m.k. keyboard firmware for HHKB mod


/* Boot Section Size in *BYTEs*
 *   Teensy   halfKay    512
 *   Teensy++ halfKay    1024
 *   Atmel DFU loader    4096
 *   LUFA bootloader     4096
 *   USBaspLoader        2048
 */
#define BOOTLOADER_SIZE 1024


/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* 
 * Boot magic keys
 * call some function by pressing key when pluging cable or powering on.
 */
/* key position on matrix(ROW:COL) */
#define KEY_FN          0x54
#define KEY_D           0x14
#define KEY_IS_ON(key)  matrix_is_on((key)>>4, (key)&0xF)
/* kick up bootloader */
#define IS_BOOTMAGIC_BOOTLOADER()       KEY_IS_ON(KEY_FN)
/* debug on */
#define IS_BOOTMAGIC_DEBUG()            KEY_IS_ON(KEY_D)


/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) 

/* mouse keys */
#ifdef MOUSEKEY_ENABLE
#   define MOUSEKEY_DELAY_TIME 100
#endif

/* period of tapping(ms) */
#define TAPPING_TERM    200
/* tap count needed for toggling a feature */
#define TAPPING_TOGGLE  5

/* PS/2 mouse */
#ifdef PS2_MOUSE_ENABLE
/*
#   define PS2_CLOCK_PORT  PORTF
#   define PS2_CLOCK_PIN   PINF
#   define PS2_CLOCK_DDR   DDRF
#   define PS2_CLOCK_BIT   0
#   define PS2_DATA_PORT   PORTF
#   define PS2_DATA_PIN    PINF
#   define PS2_DATA_DDR    DDRF
#   define PS2_DATA_BIT    1
*/
#endif

#endif
