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


#define MATRIX_ROW_PINS { A15, B4, B5, B6, B7, B8}
#define MATRIX_COL_PINS { B12, B13, B14, B15, A8, A10, A13, A14, B9, C13, F0, F1, A0, B2, B10, B11 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Backlight */
#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PWM_CHANNEL 2
#define BACKLIGHT_PAL_MODE 2
#define BACKLIGHT_PWM_OUTPUT_FREQUENCY 1000 // Increases backlight PWM freq if compiled with an unmerged PR. Does no harm without it.

/* Underglow */
#define RGB_DI_PIN B3
#define RGBLED_NUM 17
#define WS2812_PWM_DRIVER PWMD2
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_DMA_CHANNEL 2
#define RGBLIGHT_SLEEP
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL

#define TAP_CODE_DELAY 10

/* ADC - will be used for battery monitoring once BT support is added */
/* #define ADC_PIN B0 */
