/* Copyright 2023 Cipulot
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

#define MATRIX_ROWS 6
#define MATRIX_COLS 19

#define MATRIX_ROW_PINS \
    { B13, B12, B14, A9, B6, B7 }

#define AMUX_COUNT 3
#define AMUX_MAX_COLS_COUNT 8

#define AMUX_EN_PINS \
    { A0, A1, A8 }

#define AMUX_SEL_PINS \
    { A4, A3, A2 }

#define AMUX_COL_CHANNELS_SIZES \
    { 8, 7, 4 }

#define AMUX_0_COL_CHANNELS \
    { 0, 3, 1, 2, 4, 6, 7, 5 }

#define AMUX_1_COL_CHANNELS \
    { 1, 0, 3, 2, 4, 6, 7 }

#define AMUX_2_COL_CHANNELS \
    { 4, 6, 7, 5 }

#define AMUX_COL_CHANNELS AMUX_0_COL_CHANNELS, AMUX_1_COL_CHANNELS, AMUX_2_COL_CHANNELS

#define DISCHARGE_PIN A6
#define ANALOG_PORT A7

#define DEFAULT_ACTUATION_MODE 0
#define DEFAULT_MODE_0_ACTUATION_LEVEL 550
#define DEFAULT_MODE_0_RELEASE_LEVEL 500
#define DEFAULT_MODE_1_INITIAL_DEADZONE_OFFSET DEFAULT_MODE_0_ACTUATION_LEVEL
#define DEFAULT_MODE_1_ACTUATION_OFFSET 70
#define DEFAULT_MODE_1_RELEASE_OFFSET 70
#define DEFAULT_EXTREMUM 1023
#define EXPECTED_NOISE_FLOOR 0
#define NOISE_FLOOR_THRESHOLD 50
#define BOTTOMING_CALIBRATION_THRESHOLD 100
#define DEFAULT_NOISE_FLOOR_SAMPLING_COUNT 30
#define DEFAULT_BOTTOMING_READING 1023
#define DEFAULT_CALIBRATION_STARTER true

#define DISCHARGE_TIME 10

//#define DEBUG_MATRIX_SCAN_RATE

#define EECONFIG_KB_DATA_SIZE 249

// Indicators
// PWM driver with direct memory access (DMA) support
#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6

#define NUM_INDICATOR_INDEX 0
#define CAPS_INDICATOR_INDEX 1
#define SCROLL_INDICATOR_INDEX 2

#define RGB_MATRIX_DEFAULT_VAL 60
#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
