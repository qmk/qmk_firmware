/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

// #define USE_I2C
// #define SELECT_SOFT_SERIAL_SPEED 1
// #define SERIAL_USE_MULTI_TRANSACTION
#define SPLIT_MODS_ENABLE
#define EE_HANDS

#define TRACKBALL_DPI_OPTIONS { 1200, 1800, 2600, 3400 }

#define RGBLIGHT_MAX_BRIGHTNESS 60

#undef DEBOUNCE
#define DEBOUNCE 10

#define SOLENOID_PIN F1
#define SOLENOID_DEFAULT_DWELL 8

#define OLED_DISPLAY_128X64
#define OLED_BRIGHTNESS 50
