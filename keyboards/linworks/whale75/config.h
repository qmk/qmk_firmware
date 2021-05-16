/*
Copyright 2020 Moritz Plattner
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4C58      //"LX"
#define PRODUCT_ID      0x0001      
#define DEVICE_VER      0x0001
#define MANUFACTURER    Lx3
#define PRODUCT         Whale-75

/* Set 1 kHz polling rate and force USB NKRO */
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { B3, B4, B5, B6, B7, A0 }
#define MATRIX_COL_PINS { A1, A2, A3, A4, A5, A6, A7, B0, B1, B2, B10, B11, B12, B13, B14, B15 }
#define UNUSED_PINS { C13, C14, C15 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define LED_NUM_LOCK_PIN A8
#define LED_CAPS_LOCK_PIN A9
#define LED_SCROLL_LOCK_PIN A13
#define LED_PIN_ON_STATE 0

/* Backlight */
#define BACKLIGHT_PIN A10
#define BACKLIGHT_BREATHING
#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PWM_CHANNEL 3
#define BACKLIGHT_PAL_MODE 6
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_ON_STATE 1
#define BACKLIGHT_PWM_OUTPUT_FREQUENCY 1000 // Increases backlight PWM freq if compiled with an unmerged PR. Does no harm without it.

/* Underglow */
#define RGB_DI_PIN B9
#define WS2812_EXTERNAL_PULLUP // This board uses a pull-up + 5 V tolerant GPIO in open drain config ro generate a 5 V signal
#define RGBLED_NUM 18
/* section for PWM WS2812 driver */
#define WS2812_PWM_DRIVER PWMD4
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM7
#define WS2812_DMA_CHANNEL 7
#define RGBLIGHT_SLEEP
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL


/* Rotary encoder - set the resolution fitting your encoder.
Most will need a value of 4. If 1 encoder click results in 2 keycodes sent
double the value. If you need 2 clicks for 1 keycode, half it */
#define ENCODER_RESOLUTION 2
#define ENCODERS_PAD_A { A15 }
#define ENCODERS_PAD_B { A14 }
#define TAP_CODE_DELAY 10
