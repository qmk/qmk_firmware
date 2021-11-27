/* Copyright 2021 Christoph Rehmann (crehmann)
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

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED 
#define PRODUCT_ID   0xB077
#define DEVICE_VER   0x0001
#define MANUFACTURER crehmann
#define PRODUCT      Buzzard

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS  8
#define MATRIX_COLS  6

// wiring
#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7 }
#define MATRIX_COL_PINS \
    { B1, B3, B2, B6, B5, B4}
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE        5

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D2

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X32
#    define SPLIT_OLED_ENABLE
#endif

#ifdef PS2_USE_INT
#define PS2_CLOCK_PORT  PORTE
#define PS2_CLOCK_PIN   PINE
#define PS2_CLOCK_DDR   DDRE
#define PS2_CLOCK_BIT   6
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    7
#define PS2_INT_INIT()  do { EICRB |= ((1<<ISC61) | (0<<ISC60)); } while (0)
#define PS2_INT_ON()  do { EIMSK |= (1<<INT6); } while (0)
#define PS2_INT_OFF() do { EIMSK &= ~(1<<INT6);} while (0)
#define PS2_INT_VECT   INT6_vect
#define PS2_MOUSE_ROTATE 270 /* Compensate for East-facing device orientation. */
#endif