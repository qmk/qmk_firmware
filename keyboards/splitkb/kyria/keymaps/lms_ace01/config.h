/* Copyright 2021 Luis Moreno <acevice69@gmail.com>
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

// Set handedness by EEPROM
#define EE_HANDS

// Tapping / One Shot settings
#define TAPPING_TOGGLE               2
#define TAPPING_TERM               175

#define ONESHOT_TAP_TOGGLE           2
#define ONESHOT_TIMEOUT           2250

// OLED settings -if applicable-
#ifdef OLED_DRIVER_ENABLE
    #define OLED_DISPLAY_128X64
#endif

// Encoder settings -if applicable-
#ifdef ENCODER_ENABLE
    #define ENCODER_RESOLUTION       4
#endif

// RGB settings -if applicable-
#ifdef RGBLIGHT_ENABLE
    #undef  RGBLIGHT_ANIMATIONS

    #define RGBLIGHT_EFFECT_BREATHING

    #define RGBLIGHT_HUE_STEP        2
    #define RGBLIGHT_SAT_STEP        2
    #define RGBLIGHT_VAL_STEP        2
    #define RGBLIGHT_LIMIT_VAL     230

    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_SPLIT

    #define RGBLIGHT_DEFAULT_MODE  RGBLIGHT_MODE_BREATHING + 2
    #define RGBLIGHT_DEFAULT_HUE   201
    #define RGBLIGHT_DEFAULT_SAT   255
#endif
