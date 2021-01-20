/* Copyright 2020 Paul James
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

#define USE_2U_SPACE 1

#include QMK_KEYBOARD_H
#include "peej.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_PEEJ(
    BASE_ROW_2,
    BASE_ROW_3,
    BASE_ROW_4,
    BASE_ROW_5
),

[_SYMBOL] = LAYOUT_PEEJ(
    SYMBOL_ROW_2,
    SYMBOL_ROW_3,
    SYMBOL_ROW_4,
    SYMBOL_ROW_5
),

[_FUNCTION] = LAYOUT_PEEJ(
    FUNCTION_ROW_2,
    FUNCTION_ROW_3,
    FUNCTION_ROW_4,
    FUNCTION_ROW_5
),

[_ADJUST] = LAYOUT_PEEJ(
    ADJUST_ROW_2,
    ADJUST_ROW_3,
    ADJUST_ROW_4,
    ADJUST_ROW_5
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(LED_RED) && defined(LED_GREEN)
    writePinLow(LED_RED);
    writePinLow(LED_GREEN);

    switch (biton32(state)) {
    case _FUNCTION:
        writePinHigh(LED_RED);
        break;
    case _SYMBOL:
        writePinHigh(LED_GREEN);
        break;
    case _ADJUST:
        writePinHigh(LED_RED);
        writePinHigh(LED_GREEN);
        break;
    }
#endif
    return state;
}
