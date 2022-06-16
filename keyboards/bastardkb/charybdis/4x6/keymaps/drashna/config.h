/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS \
    { B0, B1, B10, B3, B4, B5 }
#undef MATRIX_COL_PINS_RIGHT
#define MATRIX_COL_PINS_RIGHT \
    { B0, B1, B10, B3, B4, B5 }

#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS \
    { B15, A2, B8, A8, B9 }
#undef MATRIX_ROW_PINS_RIGHT
#define MATRIX_ROW_PINS_RIGHT \
    { B15, A2, B8, A8, B9 }

#define DIODE_DIRECTION ROW2COL
#define SPLIT_HAND_PIN A3

#undef RGB_DI_PIN
#define RGB_DI_PIN A1
#define WS2812_EXTERNAL_PULLUP
#define WS2812_PWM_DRIVER PWMD2
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 1
#define WS2812_EXTERNAL_PULLUP
#define WS2812_DMA_STREAM STM32_DMA1_STREAM1
#define WS2812_DMA_CHANNEL 3
#define WS2812_PWM_TARGET_PERIOD 800000

#define DEBUG_LED_PIN     C13

#undef SOFT_SERIAL_PIN
// #define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN      A9
// #define SERIAL_USART_RX_PIN      A3
// #define SERIAL_USART_DRIVER      SD2
// #define SERIAL_USART_TX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
// #define SERIAL_USART_RX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
// #define SERIAL_USART_TIMEOUT     100  // USART driver timeout. default 100
// // #define SERIAL_USART_PIN_SWAP // swap RX and TX pins on master
// // To use the highest possible baudrate (3.75Mbit/s) uncomment the following
// // line, this can result in dropped communications so lower the speed if there
// // are many timeouts.
// // #define SERIAL_USART_SPEED (STM32_PCLK2 >> 4)
#define SERIAL_USART_SPEED       921600

#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* spi config for eeprom and pmw3360 sensor */
#define SPI_DRIVER                           SPID1
#define SPI_SCK_PIN                          A5
#define SPI_SCK_PAL_MODE                     5
#define SPI_MOSI_PIN                         A7
#define SPI_MOSI_PAL_MODE                    5
#define SPI_MISO_PIN                         A6
#define SPI_MISO_PAL_MODE                    5

#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR    64

#undef PMW3360_CS_PIN
#define PMW3360_CS_PIN                       B14
#define PMW3360_CS_MODE 3
#define PMW3360_CS_DIVISOR 64

#define CHARYBDIS_MINIMUM_DEFAULT_DPI     1200
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 400
#define CHARYBDIS_MINIMUM_SNIPING_DPI     200
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 100

/* RGB Matrix. */

#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
