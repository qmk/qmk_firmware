/* Copyright 2017 Jason Williams (Wilba)
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

//RGB Underglow defines
#define WS2812_LED_TOTAL 20

//RGB Matrix defines
#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define IS31FL3731_I2C_ADDRESS_2 IS31FL3731_I2C_ADDRESS_SDA
#define IS31FL3731_LED_COUNT 64

#define RGB_MATRIX_LED_COUNT (IS31FL3731_LED_COUNT + WS2812_LED_TOTAL)

// enable/disable LEDs based on layout
// switch between split backspace (1) or normal backspace(0)
#define RGB_BACKLIGHT_USE_SPLIT_BACKSPACE 1
// switch between Tsangan (1) or Arrows Bottom Row (0)
#define RGB_BACKLIGHT_USE_7U_SPACEBAR 0
// switch between standard split rshift (0) or arrows r shift (1)
// .------------------.           .-------------------.
// | ? |  Shift  | Fn |    vs     |  Shift  | Up | Fn |
// `------------------'           `-------------------'
#define RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT 1
