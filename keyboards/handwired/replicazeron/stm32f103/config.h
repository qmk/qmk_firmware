/* Copyright 2023 9R
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

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 5

/* joystick configuration */
#define JOYSTICK_BUTTON_COUNT 0
#define JOYSTICK_AXIS_COUNT 2
#define JOYSTICK_AXIS_RESOLUTION 10


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Use I2C2 */
#define I2C_DRIVER I2CD2

#define I2C1_SDA_PIN B11
#define I2C1_SCL_PIN B10

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//////////////////////////////

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#define STATUS_LED_A_PIN B13
#define STATUS_LED_B_PIN B12

#define RGB_DI_PIN B14
#define RGBLED_NUM 6
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_TWINKLE

#define THUMBSTICK_DEBUG
