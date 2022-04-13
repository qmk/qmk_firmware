/* Copyright 2022 DZTECH <moyi4681@Live.cn>
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
 #define VENDOR_ID       0x4B42
 #define PRODUCT_ID      0x0106
 #define DEVICE_VER      0x0001
 #define MANUFACTURER    KBDFANS
 #define PRODUCT         BAGUETTE66RGB

 /* key matrix size */
 #define MATRIX_ROWS 5
 #define MATRIX_COLS 15
 #define MATRIX_ROW_PINS { F0, F1, F4, F5, B6 }
 #define MATRIX_COL_PINS { C6, C7, F7, F6, B0, B1, B2, B3, D0, D1, D2, D3, D5, D4, D6}
 #define UNUSED_PINS

 /* COL2ROW, ROW2COL*/
 #define DIODE_DIRECTION COL2ROW
 /* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
 #define DEBOUNCE 5
 /* disable these deprecated features by default */
 #define NO_ACTION_MACRO
 #define NO_ACTION_FUNCTION
 #define USB_SUSPEND_WAKEUP_DELAY 5000
 #define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

 #define RGB_DI_PIN E6
 #define RGBLED_NUM 66
 #define DRIVER_LED_TOTAL RGBLED_NUM
 #define RGBLIGHT_EFFECT_BREATHING
 #define RGBLIGHT_EFFECT_RAINBOW_MOOD
 #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
 #define RGBLIGHT_EFFECT_SNAKE
 #define RGBLIGHT_EFFECT_KNIGHT
 #define RGBLIGHT_EFFECT_CHRISTMAS
 #define RGBLIGHT_EFFECT_STATIC_GRADIENT
 #define RGBLIGHT_EFFECT_RGB_TEST
 #define RGBLIGHT_EFFECT_ALTERNATING
 #define RGBLIGHT_EFFECT_TWINKLE
 #define RGB_MATRIX_KEYPRESSES
 #define ENABLE_RGB_MATRIX_ALPHAS_MODS
 #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
 #define ENABLE_RGB_MATRIX_BREATHING
 #define ENABLE_RGB_MATRIX_BAND_VAL
 #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
 #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
 #define ENABLE_RGB_MATRIX_CYCLE_ALL
 #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
 #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
 #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
 #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
 #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
 #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
 #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
 #define ENABLE_RGB_MATRIX_DUAL_BEACON
 #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
 #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
 #define ENABLE_RGB_MATRIX_RAINDROPS
 #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
 #define ENABLE_RGB_MATRIX_HUE_BREATHING
 #define ENABLE_RGB_MATRIX_HUE_PENDULUM
 #define ENABLE_RGB_MATRIX_HUE_WAVE
 #define ENABLE_RGB_MATRIX_PIXEL_RAIN
 #define ENABLE_RGB_MATRIX_PIXEL_FLOW
 #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
 #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
 #define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspendedz
 #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
 #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
 #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
 #define RGB_MATRIX_HUE_STEP 8
 #define RGB_MATRIX_SAT_STEP 8
 #define RGB_MATRIX_VAL_STEP 8
 #define RGB_MATRIX_SPD_STEP 10

