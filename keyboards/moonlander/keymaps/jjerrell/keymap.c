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

// enum layers {
//     WRK,  // default layer
//     SYM,
//     _RAISE,
//     MOD,
//     FN,
//     ADJ
// };

#define MO_SEL (MOD_LSFT | MOD_LALT)

// enum moonlander_keycodes {
//     // kc_example = NEW_SAFE_RANGE
// };

// clang-format off
#define OVERLAY_moonlander(...) LAYOUT_moonlander_overlay(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WORKMAN] = OVERLAY_moonlander(
        XXXXXXX, __________________NUMS__LHS__________________, XXXXXXX,    XXXXXXX, __________________NUMS__RHS__________________, XXXXXXX,
        XXXXXXX, __________________WORKMN_L1__________________, XXXXXXX,    XXXXXXX, __________________WORKMN_L1__________________, XXXXXXX,
        XXXXXXX, __________________WORKMN_L2__________________, XXXXXXX,    XXXXXXX, __________________WORKMN_L2__________________, KC_QUOT,
        KC_LSFT, __________________WORKMN_L3__________________,                      __________________WORKMN_L3__________________, XXXXXXX,
        XXXXXXX, XXXXXXX , XXXXXXX , XXXXXXX , MO(_RAISE),          MO(_ADJUST) ,    MO(_ADJUST),            MO(_RAISE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                               KC_SPC , KC_BSPC, MO(_LOWER),    MO(_LOWER), KC_TAB , KC_ENT
    ),

    [_QWERTY] = OVERLAY_moonlander(
        XXXXXXX, __________________NUMS__LHS__________________, XXXXXXX,    XXXXXXX, __________________NUMS__RHS__________________, XXXXXXX,
        XXXXXXX, __________________QWERTY_L1__________________, XXXXXXX,    XXXXXXX, __________________QWERTY_L1__________________, XXXXXXX,
        XXXXXXX, __________________QWERTY_L2__________________, XXXXXXX,    XXXXXXX, __________________QWERTY_L2__________________, KC_QUOT,
        KC_LSFT, __________________QWERTY_L3__________________,                      __________________QWERTY_L3__________________, XXXXXXX,
        XXXXXXX, XXXXXXX , XXXXXXX , XXXXXXX , MO(_RAISE),          MO(_ADJUST) ,    MO(_ADJUST),            MO(_RAISE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                               KC_SPC , KC_BSPC, MO(_LOWER),    MO(_LOWER), KC_TAB , KC_ENT
    ),

    [_LOWER] = LAYOUT_moonlander_wrapper(
        XXXXXXX, __________________SYMB__LHS__________________, XXXXXXX,    XXXXXXX, __________________SYMB__RHS__________________, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, XXXXXXX,    XXXXXXX, KC_EXLM, KC_LABK, KC_RABK, KC_EQL , KC_AMPR, XXXXXXX,
        XXXXXXX, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR, XXXXXXX,    XXXXXXX, KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_AT  ,
        XXXXXXX, KC_HASH, KC_DLR , KC_PIPE, KC_TILD, KC_GRV ,                      KC_PLUS, KC_PERC, KC_DQUO, KC_QUOT, KC_SCLN, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______,    _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX
    ),

    [_RAISE] = OVERLAY_moonlander(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_PGUP, KC_BSPC, KC_UP  , KC_DEL , KC_PGDN, XXXXXXX,    XXXXXXX, XXXXXXX, KC_7   , KC_8   , KC_9   , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END , XXXXXXX,    XXXXXXX, XXXXXXX, KC_4   , KC_5   , KC_6   , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_ESC , KC_TAB , XXXXXXX, KC_ENT , XXXXXXX,                      XXXXXXX, KC_1   , KC_2   , KC_3   , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______,    _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, KC_0
    ),

    [_ADJUST] = LAYOUT_moonlander_wrapper(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_F22 , KC_F23 , KC_F24 , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_F19 , KC_F20 , KC_F21 , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_LSFT, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_F16 , KC_F17 , KC_F18 , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_F13 , KC_F14 , KC_F15 , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
    )


};

layer_state_t layer_state_set_user(layer_state_t state) {
    ML_LED_1(0);
    ML_LED_2(0);
    ML_LED_3(0);
    ML_LED_4(0);
    ML_LED_5(0);
    ML_LED_6(0);

    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

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
