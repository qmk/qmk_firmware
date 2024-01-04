/* Copyright 2020 Sönke Hahn <SoenkeHahn@gmail.com>
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

#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE,  // default layer
    L_3,
    L_4,
};

enum custom_keycodes {
    a_umlaut = SAFE_RANGE,
    o_umlaut,
    u_umlaut,
    eszett,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        XXXXXXX, KC_1    , KC_2    , KC_3    , KC_4   , KC_5   , XXXXXXX,    XXXXXXX, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , XXXXXXX,
        KC_TAB , KC_X    , KC_V    , KC_L    , KC_C   , KC_W   , XXXXXXX,    XXXXXXX, KC_K   , KC_H   , KC_G   , KC_F   , KC_Q   , eszett ,
        XXXXXXX, KC_U    , KC_I    , KC_A    , KC_E   , KC_O   , XXXXXXX,    XXXXXXX, KC_S   , KC_N   , KC_R   , KC_T   , KC_D   , KC_Y   ,
        XXXXXXX, u_umlaut, o_umlaut, a_umlaut, KC_P   , KC_Z   ,                      KC_B   , KC_M   , KC_COMM, KC_DOT , KC_J   , XXXXXXX,
        XXXXXXX, XXXXXXX , XXXXXXX , KC_LGUI , MO(L_4),          XXXXXXX,    XXXXXXX,          MO(L_4), KC_RGUI, XXXXXXX, XXXXXXX, XXXXXXX,
                                               KC_LCTL, KC_LSFT, MO(L_3),    MO(L_3), KC_RSFT, KC_SPC
    ),

    [L_3] = LAYOUT_moonlander(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, XXXXXXX,    XXXXXXX, KC_EXLM, KC_LABK, KC_RABK, KC_EQL , KC_AMPR, XXXXXXX,
        XXXXXXX, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR, XXXXXXX,    XXXXXXX, KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_AT  ,
        XXXXXXX, KC_HASH, KC_DLR , KC_PIPE, KC_TILD, KC_GRV ,                      KC_PLUS, KC_PERC, KC_DQUO, KC_QUOT, KC_SCLN, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [L_4] = LAYOUT_moonlander(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_PGUP, KC_BSPC, KC_UP  , KC_DEL , KC_PGDN, XXXXXXX,    XXXXXXX, XXXXXXX, KC_7   , KC_8   , KC_9   , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END , XXXXXXX,    XXXXXXX, XXXXXXX, KC_4   , KC_5   , KC_6   , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_ESC , KC_TAB , XXXXXXX, KC_ENT , XXXXXXX,                      XXXXXXX, KC_1   , KC_2   , KC_3   , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_0
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    ML_LED_1(false);
    ML_LED_2(false);
    ML_LED_3(false);
    ML_LED_4(false);
    ML_LED_5(false);
    ML_LED_6(false);

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

// only works after executing
// $ xmodmap -e "keycode 138 = Multi_key"
#define compose_key SS_TAP(X_MENU)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case a_umlaut:
            SEND_STRING(compose_key "\"a");
            return false;
        case o_umlaut:
            SEND_STRING(compose_key "\"o");
            return false;
        case u_umlaut:
            SEND_STRING(compose_key "\"u");
            return false;
        case eszett:
            SEND_STRING(compose_key "ss");
            return false;
        }
    }
    return true;
}
