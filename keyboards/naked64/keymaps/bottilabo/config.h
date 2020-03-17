/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// #define SSD1306OLED

#define USE_SERIAL_PD2


#define MK_3_SPEED

#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 0

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 150

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 3

#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA 5

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 1

#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 0

#undef RGBLED_NUM

//Please select the LED mode.
//The default is set to support transparent midplate.
//#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
//#define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
//#define RGBLIGHT_EFFECT_KNIGHT
//#define RGBLIGHT_EFFECT_CHRISTMAS
//#define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#define RGBLIGHT_EFFECT_RGB_TEST
//#define RGBLIGHT_EFFECT_ALTERNATING

//If you use LED tape, set RGB_NUM to 12.
#define RGBLED_NUM 6
//#define RGBLED_NUM 12
//#define RGBLIGHT_LIMIT_VAL 250
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17


