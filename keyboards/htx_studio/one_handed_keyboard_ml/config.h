/* Copyright 2025 htx-studio (@https://github.com/htx-studio)
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

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MISO_PIN A6
#define SPI_MOSI_PIN A7

#define POINTING_DEVICE_CS_PIN A4
#define POINTING_DEVICE_MOTION_PIN A3
#define POINTING_DEVICE_TASK_THROTTLE_MS 1
#define POINTING_DEVICE_INVERT_X 1

#define ENCODER_RESOLUTION 2

#ifdef RGB_MATRIX_ENABLE

#define WS2812_BITBANG_NOP_FUDGE 0
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 1
#define WS2812_DMA_STREAM STM32_DMA1_STREAM1
#define WS2812_DMA_CHANNEL 1
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM3_UP

#endif

