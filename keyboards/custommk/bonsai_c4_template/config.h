/* Copyright 2022 customMK
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

// This file includes example #defines to enable commonly-used functionality 
// (SPI, PWM backlight, etc.) on specific pins. Capabilities you want to include
// should be added to the config.h for your keyboard. Not all capabilities are
// shown; for example:
// I2C is not shown because the QMK defaults are sufficient for SCL on B6 and SDA on B7
// Serial communications (for split keyboards) is not shown because QMK defaults work
// for either pins A15 or B6

// If you need to change pins for PWM, SPI, I2C, or Serial communications, be aware that
// doing this may require changing the driver, channel, PAL (Pin ALternate function) mode, 
// DMA stream, and/or DMA channel.


// Bonsai C4 wires up pin A9 for Vbus sensing pin by default. For spilt keyboards, this
// can be used to determine which half of the keyboard is plugged into USB.
// For boards using Bonsai C4 merely as a reference design, the VBUS sense pin A9
// can be used for purposes other than Vbus sensing (e.g. the switch
// matrix).
//
// If A9 is needed for Vbus sensing, uncomment the line
// below. Most keyboards using Bonsai C4 can leave the line below
// commented out.
//
// #undef BOARD_OTG_NOVBUSSENS 

// FRAM configuration
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A0
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 8 // 96MHz / 8 = 12MHz; max supported by MB85R64 is 20MHz
#define EXTERNAL_EEPROM_PAGE_SIZE 64 // does not matter for FRAM, just sets the RAM buffer size in STM32F chip
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191

// External flash configuration
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B12
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 1  // 96MHz; max supported by W25Q128JV is 133MHz
#define EXTERNAL_FLASH_BYTE_COUNT (16 * 1024 * 1024)  //128Mbit or 16MByte
#define EXTERNAL_FLASH_PAGE_SIZE 256
#define EXTERNAL_FLASH_SPI_TIMEOUT 200000 //datasheet max is 200 seconds for flash chip erase

// SPI Configuration (needed for FRAM and FLASH)
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4

// Example code to set up PWM backlight on pin A6
// If a different pin is used, a different PWM driver/channel settings may be necessary
#define BACKLIGHT_PIN A6
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 1

// Example code for WS2812 underglow
// Only pin A10 is wired to send 5V signals to the WS2812
// This also usually requires adding special wiring during board assembly
#define RGB_DI_PIN A10
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6
