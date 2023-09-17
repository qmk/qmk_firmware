/* Copyright 2023 David Hoelscher (@customMK)
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

// No VBUS sense needed
#define BOARD_OTG_NOVBUSSENS 1

#define STM32_LSECLK 32768

#define MATRIX_ROWS 5
#define MATRIX_COLS 16
#define MATRIX_ROW_PINS { A8, A1, A2, B1, A7 }

// FRAM configuration
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A0
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 4 // 48MHz / 4 = 12MHz; max supported by MB85R64 is 20MHz

// External flash configuration
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B12
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 1  // 48MHz; max supported by W25Q128JV is 133MHz
#define EXTERNAL_FLASH_SIZE (16 * 1024 * 1024)  //128Mbit or 16MByte
#define EXTERNAL_FLASH_SPI_TIMEOUT 200000 //datasheet max is 200seconds for flash chip erase

// SPI Configuration
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B3
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN B5
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN B4
#define SPI_MISO_PAL_MODE 5


// SPI LCD Configuration
#define LCD_RST_PIN B2
#define LCD_CS_PIN A9
#define LCD_DC_PIN B0
#ifndef LCD_ACTIVITY_TIMEOUT
    #define LCD_ACTIVITY_TIMEOUT 30000
#endif

// I2C OLED Configuration
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B9

#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

#define OLED_DISABLE_TIMEOUT

#define COL_SHIFT_IN_PIN B14
#define COL_SHIFT_CLK_PIN B15

#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE

#define OLED_UPDATE_INTERVAL 66

#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_PAL_MODE 2

#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6

#define TAP_CODE_DELAY 10

#define AUDIO_PIN B8
#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL 3 
#define AUDIO_PWM_PAL_MODE 2
#define AUDIO_STATE_TIMER GPTD5
#define AUDIO_INIT_DELAY
