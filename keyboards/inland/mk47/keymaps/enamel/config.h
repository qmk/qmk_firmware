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
#define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_GND

/* WB32 MCU has no default definition */
#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 400000

#define TAPPING_TERM_PER_KEY
#define OS_DETECTION_DEBOUNCE 200

/* Backlighting */
#define RGBLIGHT_ANIMATIONS

/* Typing heatmap animation settings */
// In order to change the delay of temperature decrease define `RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS`:
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50

// As heatmap uses the physical position of the leds set in the g_led_config, you may need to tweak the following
// options to get the best effect for your keyboard. Note the size of this grid is `224x64`.
// Limit the distance the effect spreads to surrounding keys.
#define RGB_MATRIX_TYPING_HEATMAP_SPREAD 40

// Limit how hot surrounding keys get from each press.
// #define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16

// Remove the spread effect entirely.
// #define RGB_MATRIX_TYPING_HEATMAP_SLIM

// It's also possible to adjust the tempo of *heating up*. It's defined as the number of shades that are
// increased on the [HSV scale](https://en.wikipedia.org/wiki/HSL_and_HSV). Decreasing this value increases
// the number of keystrokes needed to fully heat up the key.
#define RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP 25
