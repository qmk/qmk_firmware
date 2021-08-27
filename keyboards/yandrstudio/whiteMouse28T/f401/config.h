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


/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN B5
#    define RGBLED_NUM 1
#    define DRIVER_LED_TOTAL RGBLED_NUM

#define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
#    define RGBLIGHT_VAL_STEP 18
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGB_MATRIX_CENTER { 32, 96 }
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif


#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B5
#    define RGBLED_NUM 1
#    define RGBLIGHT_ANIMATIONS
#    define DRIVER_LED_TOTAL RGBLED_NUM


#define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.


#    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif

#ifdef EEPROM_SPI

#    define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4
#    define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 3
#    define EXTERNAL_EEPROM_BYTE_COUNT 32768
#    define EXTERNAL_EEPROM_PAGE_SIZE  64
#    define EXTERNAL_EEPROM_ADDRESS_SIZE 2


#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN A5
#    define SPI_MOSI_PIN A7
#    define SPI_MISO_PIN A6

#    ifdef VIA_ENABLE
#       define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
#       define DYNAMIC_KEYMAP_LAYER_COUNT 24
#       define DYNAMIC_KEYMAP_MACRO_COUNT 30
#       define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 10240
#    endif
#endif


// #define SERIAL_DRIVER SD1
// #define SD1_TX_PIN A9
// #define SD1_TX_PAL_MODE 7
// #define SD1_RX_PIN A10
// #define SD1_RX_PAL_MODE 7


// #define ADC_RESOLUTION ADC_CFGR1_RES_12BIT


