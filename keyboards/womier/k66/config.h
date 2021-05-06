/* Copyright 2018 Jack Humbert
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID              0xFEED
#define PRODUCT_ID             0x4B42
#define DEVICE_VER             0x0001
#define MANUFACTURER           Womier
#define PRODUCT                K66
#define DESCRIPTION            K66 Keyboard

/* key matrix size */
#define MATRIX_ROWS            5
#define MATRIX_COLS            14

#define DIODE_DIRECTION        ROW2COL

#define MATRIX_ROW_PINS        {B1, B2, B3, B4, B5}
#define MATRIX_COL_PINS        {D1, D2, D3, D4, D5, D6, D7, D8, C3, C4, C5, C6, C7, C8}

// #define HAL_USE_I2C            TRUE

#define DRIVER_ADDR_1          0b1110100
#define DRIVER_ADDR_2          0b1110110

// #define DRIVER_COUNT           1
// #define DRIVER_1_LED_TOTAL     5
// #define DRIVER_2_LED_TOTAL     0
#define DRIVER_LED_TOTAL       (66)


// #define LED_MATRIX_ROWS 14
// #define LED_MATRIX_ROW_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5 }

#define LED_MATRIX_ROWS        14
#define LED_MATRIX_ROW_PINS    {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13}

// #define LED_MATRIX_ROW_PINS    {C14, C13, C12, C11, C10, C9, C8, C7, C6, C5, C4, C3, C1, C0, C15}

// #define LED_MATRIX_ROWS 1
// G B R
// #define LED_MATRIX_ROW_PINS { C15 } //{ C15, C14, C13, C12, C11, C10, C9, C8, C7, C6, C5, C4, C3, C1, C0 }

// #define LED_MATRIX_ROW_PINS { {14, 13, 12}, {11, 10, 9}, {8, 7, 6}, {5, 4, 3}, {1, 0, 15 } }

// #define LED_MATRIX_ROWS 3
// #define LED_MATRIX_ROW_PINS { C15, C14, C13 }
// #define LED_MATRIX_ROW_PINS { C15, C12, C9, C6, C3} // B
// #define LED_MATRIX_ROW_PINS { C14, C11, C8, C5, C1} // R?
// #define LED_MATRIX_ROW_PINS { C13, C10, C7, C4, C0} // G

#define LED_MATRIX_COLS        14
#define LED_MATRIX_COL_PINS    {A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5}

// #define LED_MATRIX_COLS 15
// #define LED_MATRIX_COL_PINS { C15, C14, C13, C12, C11, C10, C9, C8, C7, C6, C5, C4, C3, C1, C0 }

// #define LED_MATRIX_COLS 1
// #define LED_MATRIX_COL_PINS { B5 }

#define LED_DRIVER_LED_COUNT       63  // * 3(rgb)

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_OUT_IN_DUAL

// #define SW_I2C_USE_I2C1            1

#define GFX_EMULATE_MALLOC         TRUE

#define MS2ST(x)    (x / 10)

#define USB_POLLING_INTERVAL_MS    1
#define QMK_KEYS_PER_SCAN          4

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE                   5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */

// #define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */

// #define LOCKING_RESYNC_ENABLE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */

// #define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */

// #define NO_DEBUG

/* disable print */

// #define NO_PRINT

/* disable action features */

// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */

// #define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
 * - MIDI notes can be sent when in Music mode is on
 */

// #define MIDI_BASIC

/* enable advanced MIDI features:
 * - MIDI notes can be added to the keymap
 * - Octave shift and transpose
 * - Virtual sustain, portamento, and modulation wheel
 * - etc.
 */

// #define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */

// #define MIDI_TONE_KEYCODE_OCTAVES 1

// #define WS2812_LED_N 2
// #define RGBLED_NUM WS2812_LED_N
// #define WS2812_TIM_N 2
// #define WS2812_TIM_CH 2
// #define PORT_WS2812     GPIOA
// #define PIN_WS2812      1
// #define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA stream for TIMx_UP (look up in reference manual under DMA Channel selection)
// #define WS2812_DMA_CHANNEL 7                  // DMA channel for TIMx_UP
// #define WS2812_EXTERNAL_PULLUP

// #define DISABLE_RGB_MATRIX_BAND_SAT
// #define DISABLE_RGB_MATRIX_BAND_VAL
// #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
// #define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
// #define DISABLE_RGB_MATRIX_CYCLE_ALL
// #define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
// #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
// #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #define DISABLE_RGB_MATRIX_DUAL_BEACON
// #define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
// #define DISABLE_RGB_MATRIX_RAINBOW_BEACON
// #define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define DISABLE_RGB_MATRIX_TYPING_HEATMAP
// #define DISABLE_RGB_MATRIX_DIGITAL_RAIN
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #define DISABLE_RGB_MATRIX_SPLASH
