/* Copyright 2023 HorrorTroll <https://github.com/HorrorTroll>
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

// SPI configuration
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

// Flash configuration
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN A2
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 16
#define EXTERNAL_FLASH_PAGE_SIZE 256
#define EXTERNAL_FLASH_SECTOR_SIZE 4096
#define EXTERNAL_FLASH_BLOCK_SIZE 4096
#define EXTERNAL_FLASH_SIZE (256 * 1024) // 2M-bit flash size

// Wear-leveling driver configuration
#define WEAR_LEVELING_LOGICAL_SIZE 1024
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)

// ADC configuration
#define ADC_PIN A0

#ifdef BACKLIGHT_ENABLE
    /* Backlight config */
    #define BACKLIGHT_PWM_DRIVER  PWMD2
    #define BACKLIGHT_PWM_CHANNEL 1
#endif
