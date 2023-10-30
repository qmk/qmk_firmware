/* Copyright 2023 Moritz Plattner
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

/* Set up split communications */
#define SERIAL_USART_DRIVER SD3
#define SOFT_SERIAL_PIN B10             // The GPIO pin that is used split communication.
#define USART3_REMAP                    // Remap USART TX and RX pins for half duplex
#define SERIAL_USART_TX_PAL_MODE 7      // Pin alternate function 7 = USART3_TX for PB10

#if defined(SOFT_SERIAL_PIN)
#    define SERIAL_USART_TX_PIN SOFT_SERIAL_PIN
#endif

//#define SELECT_SOFT_SERIAL_SPEED {0}  // Experimental, will make connection faster but may need testing.

/* Set up various split configurations */
#define USB_VBUS_PIN C15                // The side that manages to establish a USB connection will be master. Disabled because default on ARM targets.

#define SPLIT_HAND_PIN B9               // The MCUs will probe a pin to determine if they are left or right side. high = left, low = right

// Not yet available in `info.json`
#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
#   define RGB_MATRIX_LED_COUNT 53
#   define RGB_MATRIX_SPLIT { 27, 26 }
#   define SPLIT_TRANSPORT_MIRROR
#   define NOP_FUDGE 0.4

#   define RGBLIGHT_SLEEP

#   define WS2812_EXTERNAL_PULLUP
#   define WS2812_PWM_DRIVER PWMD3
#   define WS2812_PWM_CHANNEL 4
#   define WS2812_PWM_PAL_MODE 10
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#   define WS2812_DMA_CHANNEL 2
#   define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM3_UP
#endif
