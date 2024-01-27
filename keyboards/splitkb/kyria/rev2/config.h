/*
Copyright 2022 Thomas Baart <thomas@splitkb.com>

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

// Side detection
// col 4 row 3 on right-hand-side
#define SPLIT_HAND_MATRIX_GRID E6, B3 // row first because the board is col2row
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
#define MATRIX_MASKED // actual mask is defined by `matrix_mask` in `rev2.c`

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */

#if defined(CONVERT_TO_PROTON_C)
#    define SERIAL_USART_FULL_DUPLEX      // Enable full duplex operation mode.
#    define SERIAL_USART_PIN_SWAP         // Swap TX and RX pins if keyboard is master halve.
#    define SERIAL_USART_DRIVER      SD1  // USART driver of TX pin. default: SD1
#    define SERIAL_USART_TX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#    define SERIAL_USART_TX_PIN      D3
#    define SERIAL_USART_RX_PIN      D2

#    define WS2812_DI_PIN            PAL_LINE(GPIOA, 3)
#    define WS2812_PWM_DRIVER        PWMD2                  // default: PWMD2
#    define WS2812_PWM_CHANNEL       4                      // default: 2
#    define WS2812_PWM_PAL_MODE      1                      // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM        STM32_DMA1_STREAM2     // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL       2                      // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMAMUX_ID         STM32_DMAMUX1_TIM2_UP  // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.
#else
#    define WS2812_DI_PIN D3
#    define SOFT_SERIAL_PIN D2
#endif

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define SPLIT_OLED_ENABLE
#endif

/* RGB matrix support */
#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define RGB_MATRIX_LED_COUNT 20 // Number of LEDs
#    define RGB_MATRIX_SPLIT { 10, 10 }
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 170
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif
