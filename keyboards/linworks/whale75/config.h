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


/* Force USB NKRO */
#define FORCE_NKRO

#define MATRIX_ROW_PINS { B3, B4, B5, B6, B7, A0 }
#define MATRIX_COL_PINS { A1, A2, A3, A4, A5, A6, A7, B0, B1, B2, B10, B11, B12, B13, B14, B15 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PWM_CHANNEL 3
#define BACKLIGHT_PAL_MODE 6
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

#define TAP_CODE_DELAY 10
