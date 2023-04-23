/*
Copyright 2022 Yiancar-Designs

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published byß
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


#define MATRIX_ROW_PINS { A15, B3, A9, B5, A3 }
#define MATRIX_COL_PINS { A4, A5, A6, A7, B0, B1, B2, B10, B11, B12, B13, B14, B15, A8, A10, A14, B8, B9 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Ensure we jump to bootloader if the QK_BOOT keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

/* RGB Light */
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_DMA_CHANNEL 3
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#define RGB_DI_PIN B4
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
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
