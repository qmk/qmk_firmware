/*

Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>

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

#ifdef KEYBOARD_bastardkb_charybdis_3x5_blackpill

#    undef MATRIX_ROW_PINS
#    define MATRIX_ROW_PINS \
        { B12, B13, B14, B15 }
#    undef MATRIX_COL_PINS
#    define MATRIX_COL_PINS \
        { A15, B3, B4, B5, B6 }

#    undef MATRIX_ROW_PINS_RIGHT
#    define MATRIX_ROW_PINS_RIGHT \
        { B12, B13, B14, B15 }
#    undef MATRIX_COL_PINS_RIGHT
#    define MATRIX_COL_PINS_RIGHT \
        { A15, B3, B4, B5, B6 }

#    define USB_VBUS_PIN B10
#    undef SPLIT_HAND_PIN
#    define SPLIT_HAND_PIN C14 // high = left, low = right

// WS2812 RGB LED strip input and number of LEDs
#    undef WS2812_DI_PIN
#    define WS2812_DI_PIN A1
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    define WS2812_PWM_DRIVER PWMD2 // default: PWMD2
#    define WS2812_PWM_CHANNEL 2    // default: 2
#    define WS2812_PWM_PAL_MODE 1   // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_EXTERNAL_PULLUP
//#define WS2812_PWM_COMPLEMENTARY_OUTPUT // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
#    undef WS2812_DMA_STREAM
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM7 // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 3                 // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_PWM_TARGET_PERIOD 800000

#    define DEBUG_LED_PIN C13

/* Audio config */
#    define AUDIO_PIN B1
#    define AUDIO_PWM_DRIVER PWMD3
#    define AUDIO_PWM_CHANNEL 4
#    define AUDIO_PWM_PAL_MODE 2

/* serial.c configuration for split keyboard */
#    undef SOFT_SERIAL_PIN
#    define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#    undef SERIAL_USART_TX_PIN
#    define SERIAL_USART_TX_PIN A2
#    undef SERIAL_USART_RX_PIN
#    define SERIAL_USART_RX_PIN A3
#    define SERIAL_USART_DRIVER SD2
#    define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#    define SERIAL_USART_RX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#    define SERIAL_USART_TIMEOUT 100   // USART driver timeout. default 100
#    define SERIAL_USART_SPEED 921600
// #define SERIAL_USART_PIN_SWAP // swap RX and TX pins on master
// To use the highest possible baudrate (3.75Mbit/s) uncomment the following
// line, this can result in dropped communications so lower the speed if there
// are many timeouts.
// #define SERIAL_USART_SPEED (STM32_PCLK2 >> 4)

#    define CRC8_USE_TABLE
#    define CRC8_OPTIMIZE_SPEED

/* spi config for eeprom and pmw3360 sensor */
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN A5
#    define SPI_SCK_PAL_MODE 5
#    define SPI_MOSI_PIN A7
#    define SPI_MOSI_PAL_MODE 5
#    define SPI_MISO_PIN A6
#    define SPI_MISO_PAL_MODE 5

/* eeprom config */
#    define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4
#    define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 64
// #define EXTERNAL_EEPROM_BYTE_COUNT           8196
// #define EXTERNAL_EEPROM_PAGE_SIZE            32
// #define EXTERNAL_EEPROM_ADDRESS_SIZE         2

/* pmw3360 config  */
#    undef PMW33XX_CS_PIN
#    define PMW33XX_CS_PIN B0
#endif

#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1200
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 400
#define CHARYBDIS_MINIMUM_SNIPING_DPI 200
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 100
