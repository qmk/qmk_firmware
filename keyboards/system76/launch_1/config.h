/*
 *  Copyright (C) 2021-2022  System76
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"
#ifndef __ASSEMBLER__
#include "eeconfig.h"
#include "eeprom.h"
#endif

// Key matrix size
#define MATRIX_ROWS 6
#define MATRIX_COLS 14

// Key matrix pins
// ROWS: AVR pins used for rows, top to bottom
// COLS: AVR pins used for columns, left to right
#define MATRIX_ROW_PINS { F0, F1, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { D7, C7, C6, B6, B5, B4, D6, D4, E6, D5, D3, D2, B7, B0 }

// Matrix diode direction
// COL2ROW: COL => Anode (+), ROW => Cathode (-)
// ROW2COL: ROW => Anode (+), COL => Cathode (-)
#define DIODE_DIRECTION COL2ROW

// Delay when reading the value of the pin; set to `0' if debouncing is not needed
#define DEBOUNCE 5

// Disable mechanical locking support (`KC_LCAP', `KC_LNUM', or `KC_LSCR')
#undef LOCKING_SUPPORT_ENABLE

// Disable switch state consistency with keyboard LED state
#undef LOCKING_RESYNC_ENABLE

// RGB matrix
#ifdef RGB_MATRIX_ENABLE
#    define RGB_DI_PIN E2
#    define RGB_MATRIX_LED_COUNT 84
#    define RGB_MATRIX_KEYPRESSES                                      // Reacts to keypresses
// #    define RGB_MATRIX_KEYRELEASES                                     // Reacts to keyreleases (instead of keypresses)
// #    define RGB_MATRIX_FRAMEBUFFER_EFFECTS                             // Enables framebuffer effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED                             // Turns off effects when suspended
// Limit brightness to support USB-A at 0.5 A
// TODO: Do this dynamically based on power source
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 176                          // Limits maximum brightness of LEDs to 176 out of 255. If not defined, maximum brightness is set to 255
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Sets the default mode, if none has been set
#    define RGB_MATRIX_DEFAULT_HUE 142                                 // Sets the default hue value, if none has been set
#    define RGB_MATRIX_DEFAULT_SAT 255                                 // Sets the default saturation value, if none has been set
#    define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS       // Sets the default brightness value, if none has been set
#    define RGB_MATRIX_DEFAULT_SPD 127                                 // Sets the default animation speed, if none has been set
#    define RGB_MATRIX_DISABLE_KEYCODES                                // Disables control of rgb matrix by keycodes (must use code functions to control the feature)

#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#endif // RGB_MATRIX_ENABLE

// I2C
#define F_SCL 100000UL // Run I2C bus at 100 kHz
#define I2C_START_RETRY_COUNT 20
#define I2C_TIMEOUT 100 // milliseconds

#ifndef __ASSEMBLER__
// EEPROM
#define EEPROM_SIZE (TOTAL_EEPROM_BYTE_COUNT)
#define EEPROM_MAGIC 0x76EC
#define EEPROM_MAGIC_ADDR (EECONFIG_SIZE)
// Bump `EEPROM_VERSION' every time what is stored changes
// to automatically reset the EEPROM with defaults and
// avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x02
#define EEPROM_VERSION_ADDR (EEPROM_MAGIC_ADDR + 2)

// Dynamic keymap
#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#define DYNAMIC_KEYMAP_MACRO_COUNT 0
// Dynamic keymap starts after EEPROM version
#define DYNAMIC_KEYMAP_EEPROM_ADDR (EEPROM_VERSION_ADDR + 1)
// Dynamic macro starts after dynamic keymaps, it is disabled
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 0

// System76 EC
#define SYSTEM76_EC_EEPROM_ADDR (DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE)
#define SYSTEM76_EC_EEPROM_SIZE (EEPROM_SIZE - SYSTEM76_EC_EEPROM_ADDR)
#endif // __ASSEMBLER__
