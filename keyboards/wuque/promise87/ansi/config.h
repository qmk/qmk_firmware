/* Copyright 2022 wuque
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


#define MATRIX_ROW_PINS { B3, B7, B2, F0, D3, D0 }
#define MATRIX_COL_PINS { D6, D7, D1, D5, F7, D4, F5, F4, F1, C7, C6, B6, B5, B4, E6, B1, B0 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D2
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 1
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 200 /* The maximum brightness level */
    #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*======= RGB function=======*/
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#endif
