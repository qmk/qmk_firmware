/*
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { F7, C6, D4, B5 }
#define MATRIX_COL_PINS \
    { F6, F5, B6, D7, E6, B4 }

/* Handedness. */
#define MASTER_RIGHT

// To use the handedness pin, resistors need to be installed on the adapter PCB.
// If so, uncomment the following code, and undefine MASTER_RIGHT above.
// #define A0 PAL_LINE(GPIOA, 0)
// #define SPLIT_HAND_PIN A0
// #define SPLIT_HAND_PIN_LOW_IS_LEFT  // High -> right, Low -> left.

/* RGB settings. */
#define RGB_DI_PIN D3
#define WS2812_PWM_DRIVER PWMD2
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA1_STREAM7
#define WS2812_DMA_CHANNEL 3

/* CRC. */
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* SPI config for pmw3360 sensor. */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B1
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN B2
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN B3
#define SPI_MISO_PAL_MODE 5

/* PMW3360 settings. */
#define A1 PAL_LINE(GPIOA, 1)
#define POINTING_DEVICE_CS_PIN A1
#define PMW3360_CS_MODE 3
#define PMW3360_CS_DIVISOR 64
