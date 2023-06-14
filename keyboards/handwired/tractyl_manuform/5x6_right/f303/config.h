/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

// #define USB_VBUS_PIN        B10
#define SPLIT_HAND_PIN      C14  // high = left, low = right

// WS2812 RGB LED strip input and number of LEDs
#define WS2812_PWM_DRIVER   PWMD3  // default: PWMD2
#define WS2812_PWM_CHANNEL  1      // default: 2
#define WS2812_PWM_PAL_MODE 2      // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
//#define WS2812_PWM_COMPLEMENTARY_OUTPUT // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
// #define WS2812_DMA_STREAM   STM32_DMA1_STREAM3  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL  3  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#define RGBLED_NUM          20
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT \
    { 10, 10 }

#define DEBUG_LED_PIN C13

/* Audio config */
#define AUDIO_PIN     A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE

/* serial.c configuration for split keyboard */
#define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN      A9
#define SERIAL_USART_RX_PIN      A10
#define SERIAL_USART_DRIVER      SD1
#define SERIAL_USART_TX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT     100  // USART driver timeout. default 100

/* i2c config for oleds */
#define I2C_DRIVER               I2CD1
#define I2C1_SCL_PIN             B6
#define I2C1_SDA_PIN             B7
#define I2C1_SCL_PAL_MODE        4
#define I2C1_SDA_PAL_MODE        4
#define I2C1_CLOCK_SPEED         400000

/* spi config for eeprom and pmw3360 sensor */
#define SPI_DRIVER                           SPID2
#define SPI_SCK_PIN                          B13
#define SPI_SCK_PAL_MODE                     5
#define SPI_MOSI_PIN                         B15
#define SPI_MOSI_PAL_MODE                    5
#define SPI_MISO_PIN                         B14
#define SPI_MISO_PAL_MODE                    5

/* eeprom config */
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN B8
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR    8
// #define EXTERNAL_EEPROM_BYTE_COUNT           8196
// #define EXTERNAL_EEPROM_PAGE_SIZE            32
// #define EXTERNAL_EEPROM_ADDRESS_SIZE         2
// #define DEBUG_EEPROM_OUTPUT

/* pmw3360 config  */
#define PMW33XX_CS_PIN                       B9
#define PMW33XX_SPI_DIVISOR                  8
