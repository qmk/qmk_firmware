/* Copyright 2017 Jason Williams (Wilba)
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

// IS31FL3731 driver
#define DRIVER_COUNT 2
#define RGB_MATRIX_LED_COUNT 72

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

// disable debug print
//#define NO_DEBUG

// disable print
//#define NO_PRINT

// disable action features
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define RGB_BACKLIGHT_ENABLED 1

// This conditionally compiles the backlight code for Zeal60 specifics
#define RGB_BACKLIGHT_ZEAL60

// enable/disable LEDs based on layout
#define RGB_BACKLIGHT_USE_SPLIT_BACKSPACE 0
#define RGB_BACKLIGHT_USE_SPLIT_LEFT_SHIFT 0
#define RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT 0
#define RGB_BACKLIGHT_USE_7U_SPACEBAR 0
#define RGB_BACKLIGHT_USE_ISO_ENTER 0
#define RGB_BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS 0

// disable backlight when USB suspended (PC sleep/hibernate/shutdown)
#define RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED 0

// disable backlight after timeout in minutes, 0 = no timeout
#define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 0

// the default brightness
#define RGB_BACKLIGHT_BRIGHTNESS 255

// the default effect (RGB test)
#define RGB_BACKLIGHT_EFFECT 255

// the default effect speed (0-3)
#define RGB_BACKLIGHT_EFFECT_SPEED 0

// the default color1 and color2
#define RGB_BACKLIGHT_COLOR_1 { .h = 0, .s = 255 }
#define RGB_BACKLIGHT_COLOR_2 { .h = 127, .s = 255 }

// These define which keys in the matrix are alphas/mods
// Used for backlight effects so colors are different for
// alphas vs. mods
// Each value is for a row, bit 0 is column 0
// Alpha=0 Mod=1
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_0 0b0010000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_1 0b0000000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_2 0b0001000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_3 0b0011000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_4 0b0011110000000111

#define RGB_BACKLIGHT_CAPS_LOCK_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
#define RGB_BACKLIGHT_LAYER_1_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
#define RGB_BACKLIGHT_LAYER_2_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
#define RGB_BACKLIGHT_LAYER_3_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }

// Backlight config starts after VIA's EEPROM usage,
// dynamic keymaps start after this.
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 31
