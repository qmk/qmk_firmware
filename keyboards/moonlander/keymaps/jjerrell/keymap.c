/**
 * Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
 * 
 * This file is part of qmk_firmware.
 * 
 * qmk_firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qmk_firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jjerrell.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WORKMAN] = LAYOUT_moonlander_mods(
        __________________WORKMN_L1__________________, __________________WORKMN_R1__________________,
        __________________WORKMN_L2__________________, __________________WORKMN_R2__________________,
        __________________WORKMN_L3__________________, __________________WORKMN_R3__________________,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT,                       KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_LOWER] = LAYOUT_moonlander_mods(
        __________________LOWER_L1___________________, __________________LOWER_R1___________________,
        __________________LOWER_L2___________________, __________________LOWER_R2___________________,
        __________________LOWER_L3___________________, __________________LOWER_R3___________________,
          XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT,                         KC_0, KC_DOT, KC_COMM, KC_PLUS
    ),

    [_RAISE] = LAYOUT_moonlander_common(
        __________________RAISE_L1___________________, __________________RAISE_R1___________________,
        __________________RAISE_L2___________________, __________________RAISE_R2___________________,
        __________________RAISE_L3___________________, __________________RAISE_R3___________________,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT,                       KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_ADJUST] = LAYOUT_moonlander_common(
        __________________ADJUST_L1__________________, __________________ADJUST_R1__________________,
        __________________ADJUST_L2__________________, __________________ADJUST_R2__________________,
        __________________ADJUST_L3__________________, __________________ADJUST_R3__________________,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT,                       KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_SPECIAL] = LAYOUT_moonlander_common(
        XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_WH_L, KC_WH_U, KC_WH_R, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,                       KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
// clang-format on

layer_state_t layer_state_set_keymap(layer_state_t state) {
    ML_LED_1(0);
    ML_LED_2(0);
    ML_LED_3(0);
    ML_LED_4(0);
    ML_LED_5(0);
    ML_LED_6(0);

    switch (get_highest_layer(state)) {
        case 1:
            ML_LED_1(1);
            ML_LED_4(1);
            break;
        case 2:
            ML_LED_2(1);
            ML_LED_5(1);
            break;
        case 3:
            ML_LED_3(1);
            break;
        case 4:
            ML_LED_4(1);
            break;
        case 5:
            ML_LED_5(1);
            break;
        case 6:
            ML_LED_6(1);
            break;
        default:
            break;
    }

    return state;
}
