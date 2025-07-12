/* Copyright 2025 @mawaeg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#define STM32_FLASH_SECTORS_PER_BANK 128

#define I2C1_SCL_PIN A9
#define I2C1_SDA_PIN A10

#define WS2812_PWM_DRIVER PWMD2
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 1
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_PWM_DMA_CHANNEL 4

#define RGB_MATRIX_MODE_NAME_ENABLE
