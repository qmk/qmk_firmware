/* Copyright 2021 JasonRen(biu)
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

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

//                        0    1    2    3     4    5    6   7    8    9    10   11   12  13   14  15   16   17
#define MATRIX_COL_PINS { A6,  A3,  A7,  B0,   B1,  B10, A2, B13, C13, C15, A15, B3,  B4, B6,  B9}
#define MATRIX_ROW_PINS { A9,  A8,  B15, B14,  A1,  C14}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL


/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN B5
#    define RGBLED_NUM 81
#    define DRIVER_LED_TOTAL RGBLED_NUM


#define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.


#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    define RGBLIGHT_VAL_STEP 15
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGB_MATRIX_CENTER { 32, 96 }
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGBLIGHT_ANIMATIONS

// #    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif


#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B5
#    define RGBLED_NUM 81
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 150
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_SLEEP

#define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.



// #    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif



#ifdef ENCODER_ENABLE

#define ENCODERS_PAD_A { B7, A4 }
#define ENCODERS_PAD_B { B8, A5 }

#define ENCODER_RESOLUTIONS { 4, 4 }

#endif
