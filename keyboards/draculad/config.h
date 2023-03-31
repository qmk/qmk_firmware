/*
Copyright 2021 @mangoiv

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once


#define MATRIX_ROW_PINS {D4, C6, D7, E6}
#define MATRIX_COL_PINS {F4, F5,F6, F7, B1}

#define DIODE_DIRECTION COL2ROW

#ifdef OLED_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 30000
#endif

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLED_NUM 10
#define RGBLIGHT_SPLIT
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#endif

#define EE_HANDS

#define LAYER_STATE_8BIT
