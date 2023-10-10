/* Copyright (C) 2023 jonylee@hfd
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

/* SPI Config for spi flash*/
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12

/* I2C Config for LED Driver */
#define SNLED27351_DRIVER_COUNT 1
#define DRIVER_ADDR_1 SNLED27351_I2C_ADDRESS_GND

/* WB32 MCU has no default definition */
#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 400000

#define RGB_MATRIX_LED_COUNT 47
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

