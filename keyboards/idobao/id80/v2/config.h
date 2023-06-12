/*
Copyright 2020 Sergey Vlasov <sigprof@gmail.com>

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


/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 * The matrix description in the vendor-supplied JSON file for kbfirmware.com
 * had 9 columns:
 *     { D0, D1, D2, D3, D5, D4, D6, D7, B4 }
 * and 12 rows:
 *     { B7, B3, B2, B1, B0, E6, F0, F1, F4, F5, F6, F7 }
 * However, the row 6 was completely empty, and the pin F0 was not actually
 * routed anywhere on the PCB, therefore this row was removed to save some
 * resources (the EEPROM space for dynamic keymaps is especially scarce).
 *
 * After doing the above change, the matrix was transposed (rows and columns
 * were swapped), because a matrix with the COL2ROW layout can be scanned much
 * more efficiently than a matrix with the ROW2COL layout (depending on various
 * optimizations, the difference in scan rate can be over 2 times).  Because of
 * this, the "columns" in the matrix layout now mostly correspond to physical
 * rows, and the "rows" have mostly vertical physical orientation.
 */
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4 }
#define MATRIX_COL_PINS { B7, B3, B2, B1, B0, E6, F1, F4, F5, F6, F7 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 20       /* 16 underglow LEDs, 4 top LEDs */
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 180 /* The maximum brightness level */
    #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */

    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_TWINKLE
#endif
