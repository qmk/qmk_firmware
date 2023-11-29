/* Copyright 2023 SHVD3x
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

#define GPIO_INPUT_PIN_DELAY 12

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

#define RGB_MATRIX_LED_FLUSH_LIMIT 10

#define RGB_DISABLE_WHEN_USB_SUSPENDED

/* External spi flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B14
#define WEAR_LEVELING_BACKING_SIZE (8 * 1024)

/* SPI Config for LED Driver */
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

#define AW20216S_CS_PIN_1 A15
#define AW20216S_CS_PIN_2 B15
#define AW20216S_EN_PIN_1 C13
#define AW20216S_EN_PIN_2 C13

#define DRIVER_1_LED_TOTAL 66
#define DRIVER_2_LED_TOTAL 19
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
//(Optional) LED current scaling value (0-255, higher values mean LED is brighter at full PWM). Default 150.
#define AW20216S_SCALING_MAX 255
// (Optional) Driver global current limit (0-255, higher values means the driver may consume more power). Default 150.
#define AW20216S_GLOBAL_CURRENT_MAX 255

#define ENCODER_DEFAULT_POS 0x3 // Fixes encoder skipping when changing directions
