#pragma once
/* Copyright 2021 James Badger
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

/* matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3
#define MATRIX_ROW_PINS { F5, F4, F1 }
#define MATRIX_COL_PINS { D6, D2, D1 }
#define DIODE_DIRECTION ROW2COL
#define DEVICE_VER      0x0001

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
 #define RGBLED_NUM 9
 #define RGBLIGHT_HUE_STEP 8
 #define RGBLIGHT_SAT_STEP 8
 #define RGBLIGHT_VAL_STEP 8
 #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
 #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
 /*== all animations enable ==*/
 #define RGBLIGHT_ANIMATIONS
#endif
