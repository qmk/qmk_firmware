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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xBEEA
// TODO: share these strings with usbconfig.h
// Edit usbconfig.h to change these.
#define MANUFACTURER    t.m.k.
#define PRODUCT         HHKB mod
#define DESCRIPTION     t.m.k. keyboard firmware for HHKB mod


/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) 

/* pins for Software UART */
#define SUART_IN_PIN    PINC
#define SUART_IN_BIT    5
#define SUART_OUT_PORT  PORTC
#define SUART_OUT_BIT   4


#define DEBUG_LED 1
#define DEBUG_LED_CONFIG    (DDRD |= (1<<4))
#define DEBUG_LED_OFF       (PORTD |= (1<<4))
#define DEBUG_LED_ON        (PORTD &= ~(1<<4))

/* period of tapping(ms) */
#define TAPPING_TERM    300
/* tap count needed for toggling a feature */
#define TAPPING_TOGGLE  5

#endif
