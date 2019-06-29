/* Copyright 2018
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
#undef DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL


/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#ifdef RGBLIGHT_ENABLE
#define RGBLED_NUM 4    // Number of LEDs
#endif

// #ifdef RGB_MATRIX_ENABLE
// #define RGBLED_NUM 2    // Number of LEDs
// #define DRIVER_LED_TOTAL RGBLED_NUM
// #endif



// #
// #define BACKLIGHT_BREATHING
// #define BACKLIGHT_LEVELS 3

// #define RGB_DI_PIN E2
 #ifdef RGB_DI_PIN
 #define RGBLIGHT_ANIMATIONS
// #define RGBLED_NUM 16
 #define RGBLIGHT_HUE_STEP 8
 #define RGBLIGHT_SAT_STEP 8
 #define RGBLIGHT_VAL_STEP 8
 #endif
