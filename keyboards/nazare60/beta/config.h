/*
 Copyright 2022 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x7865 // NA for Nazare
#define PRODUCT_ID      0x0061 // 60 + 1 for revision beta, alpha was 60
#define DEVICE_VER      0x0001
#define MANUFACTURER    Nazaré Engineering
#define PRODUCT         Nazaré1-60

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { B12, A8 , B14, A2 , A1 , A0 , C15, C14, C13, B9 , B8 , B5 , A15, B4 , B3 }
#define MATRIX_ROW_PINS { A10 , B10, A3 , A4 , A5 }
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define BACKLIGHT_PIN           A6
#define BACKLIGHT_PWM_DRIVER    PWMD3
#define BACKLIGHT_PWM_CHANNEL   1
#define BACKLIGHT_PAL_MODE      2
#define BACKLIGHT_LEVELS 20
#define BACKLIGHT_ON_STATE 0

#define STM32_HSECLK 8000000

#define RGB_DI_PIN B15
#define RGBLED_NUM 10
#define RGBLIGHT_SLEEP
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
#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL + 5)

#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6

// Defining the backlight as caps lock backlight (there is only one LED present on the PCB)
#define BACKLIGHT_CAPS_LOCK
#define LED_PIN_ON_STATE 1

// Defining the EEPROM
#define EEPROM_I2C_24LC256
