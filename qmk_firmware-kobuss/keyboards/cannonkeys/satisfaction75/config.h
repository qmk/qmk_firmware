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

#pragma once

/* Ensure we jump to bootloader if the RESET keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

/* LSE clock */
#define STM32_LSECLK 32768

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCA04
#define PRODUCT_ID      0x57F5
#define DEVICE_VER      0x0001
#define MANUFACTURER CannonKeys
#define PRODUCT Satisfaction75
#define DESCRIPTION Satisfaction 75 Keyboard

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define MATRIX_COL_PINS { B1, B2, B10, B11, B12, B13, B14, A8, A9, A10, B0, A7, A5, B5, A15, A1 }
#define MATRIX_ROW_PINS { B3, B4, A0, A2, A4, A3 }
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { B9 }
#define ENCODERS_PAD_B { B8 }

#define ENCODER_RESOLUTION 2

//LEDS A6, RGB B15
#define BACKLIGHT_LEVELS 24
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef QWIIC_MICRO_OLED_ENABLE

#undef I2C_ADDRESS_SA0_1
#define I2C_ADDRESS_SA0_1 0b0111100
#define LCDWIDTH      128
#define LCDHEIGHT     32

#endif

// Custom config starts after VIA's EEPROM usage,
// dynamic keymaps start after this.
// Custom config Usage:
// 1 for enabled encoder modes (1 byte)
// 1 for custom backlighting controls (1 byte)
// 1 for OLED default mode (1 byte)
// 6 for 3x custom encoder settings, left, right, and press (18 bytes)
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 21

// VIA lighting is handled by the keyboard-level code
#define VIA_CUSTOM_LIGHTING_ENABLE

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
