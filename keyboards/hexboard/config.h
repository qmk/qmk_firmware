/* Copyright 2019
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

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define TAPPING_TERM 500

//#define MIDI_ADVANCED

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

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

// TODO: including this causes "error: expected identifier before '(' token" errors
//#include "config_common.h"

// i2c_master defines
#define I2C1_SCL_PIN B0 // A2 on pinout = B0
#define I2C1_SDA_PIN B1 // A3 on pinout = B1
#define I2C1_SCL_PAL_MODE PAL_MODE_ALTERNATIVE_2
#define I2C1_SDA_PAL_MODE PAL_MODE_ALTERNATIVE_2

// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN B1 // aka pin 17
// The number of LEDs connected
#define DRIVER_LED_TOTAL 140
#define MATRIX_ROWS 14
#define MATRIX_COLS 10
#define NOP_FUDGE 1
//#undef RGB_MATRIX_SAT_STEP
//#undef RGB_MATRIX_SPD_STEP
//#undef RGB_MATRIX_VAL_STEP

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // Don't draw too much and damage USB
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define RGB_MATRIX_TYPING_HEATMAP_SLIM // Don't spread the heat to other keys.
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 10000 // persist a while


#define RGB_MATRIX_KEYPRESSES
#define RGB_TRIGGER_ON_KEYDOWN // Make it more responsive
//#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLED_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS

#define  ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
 #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

 
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
