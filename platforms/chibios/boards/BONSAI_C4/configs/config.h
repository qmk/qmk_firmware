/* Copyright 2022 David Hoelscher, customMK
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

// Bonsai C4 includes Vbus sensing; derived designs that use PA9 for other purposes
// may disable Vbus sensing with #define BOARD_OTG_NOVBUSSENS 1

#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#endif

// FRAM configuration
#ifndef EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN
#    define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN PAL_LINE(GPIOA, 0)
#    define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 8 // 96MHz / 8 = 12MHz; max supported by MB85R64 is 20MHz
#    define EXTERNAL_EEPROM_BYTE_COUNT 8192
#    define EXTERNAL_EEPROM_PAGE_SIZE 64 // does not matter for FRAM, just sets the RAM buffer size in STM32F chip
#    define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191
#endif

// External flash configuration
#ifndef EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN
#    define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN PAL_LINE(GPIOB, 12)
#    define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 2  // 48MHz; max supported by W25Q128JV is 133MHz
#    define EXTERNAL_FLASH_BYTE_COUNT (16 * 1024 * 1024)  //128Mbit or 16MByte
#    define EXTERNAL_FLASH_PAGE_SIZE 256
#    define EXTERNAL_FLASH_SPI_TIMEOUT 200000 //datasheet max is 200 seconds for flash chip erase
#endif

// SPI Configuration (needed for FRAM and FLASH)
#ifndef SPI_DRIVER
#    define SPI_DRIVER SPID1
#endif
#ifndef SPI_SCK_PIN
#    define SPI_SCK_PIN PAL_LINE(GPIOB, 3)
#endif
#ifndef SPI_MOSI_PIN
#    define SPI_MOSI_PIN PAL_LINE(GPIOB, 5)
#endif
#ifndef SPI_MISO_PIN
#    define SPI_MISO_PIN PAL_LINE(GPIOB, 4)
#endif


// I2C Configuration
#ifdef CONVERT_TO_BONSAI_C4
#    ifndef I2C1_SCL_PIN
#        define I2C1_SCL_PIN PAL_LINE(GPIOB, 6)
#    endif
#    ifndef I2C1_SDA_PIN
#        define I2C1_SDA_PIN PAL_LINE(GPIOB, 9)
#    endif
#endif

// WS2812-style LED control on pin A10
#ifdef WS2812_DRIVER_PWM
#    ifndef RGB_DI_PIN
#        define RGB_DI_PIN PAL_LINE(GPIOA, 10)
#    endif
#    ifndef WS2812_PWM_DRIVER
#        define WS2812_PWM_DRIVER PWMD1
#    endif
#    ifndef WS2812_PWM_CHANNEL
#        define WS2812_PWM_CHANNEL 3
#    endif
#    ifndef WS2812_PWM_PAL_MODE
#        define WS2812_PWM_PAL_MODE 1
#    endif
#    ifndef WS2812_DMA_STREAM
#        define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#    endif
#    ifndef WS2812_DMA_CHANNEL
#        define WS2812_DMA_CHANNEL 6
#    endif
#endif

#ifndef USB_VBUS_PIN
#    define USB_VBUS_PIN PAL_LINE(GPIOA, 9)
#endif