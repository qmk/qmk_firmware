/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Drashna Jael're  <drashna@live.com>
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
    LAYER_3,
    LAYER_4,
    SYMB,  // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        XXXXXXX,    XXXXXXX, KC_6,        KC_7,        KC_8,    KC_9,    KC_0,    XXXXXXX,
        XXXXXXX, KC_X,    KC_V,    KC_L,    KC_C,    KC_W,        XXXXXXX,    XXXXXXX, KC_K,        KC_H,        KC_G,    KC_F,    KC_Q,    XXXXXXX,
        XXXXXXX, KC_U,    KC_I,    KC_A,    KC_E,    KC_O,        XXXXXXX,    XXXXXXX, KC_S,        KC_N,        KC_R,    KC_T,    KC_D,    KC_Y,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P,    KC_Z,                             KC_B,        KC_M,        KC_COMM, KC_DOT,  XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX,    XXXXXXX,              MO(LAYER_4), KC_RGUI, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_LSFT, MO(LAYER_3), KC_SPC,     KC_SPC,  MO(LAYER_3), KC_RSFT
    ),

    // copied from my planck layout
    // XXXXXXX, XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, KC_EXLM, KC_LABK, KC_RABK, KC_EQL , KC_AMPR, XXXXXXX,
    // XXXXXXX, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR, KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_AT  ,
    // XXXXXXX, KC_HASH, KC_DLR , KC_PIPE, KC_TILD, KC_GRV , KC_PLUS, KC_PERC, KC_DQUO, KC_QUOT, KC_SCLN, XXXXXXX,
    // XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC , KC_SPC , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    [LAYER_3] = LAYOUT_moonlander(
        VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,           KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS, KC_EXLM, KC_BSPC, KC_UP,   KC_DEL,  KC_PIPE, KC_TRNS,           KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        KC_TRNS, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR, KC_TRNS,           KC_TRNS, KC_DOWN, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_TRNS,
        KC_TRNS, KC_ESC,  KC_CIRC, KC_LBRC, KC_ENT,  KC_TILD,                             KC_AMPR, KC_PERC, KC_2,    KC_3,    KC_BSLS, KC_TRNS,
        EEP_RST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_VAI,           RGB_TOG,          KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
                                            RGB_HUD, KC_TRNS, RGB_HUI, TOGGLE_LAYER_COLOR,KC_TRNS, KC_TRNS
    ),

    [LAYER_4] = LAYOUT_moonlander(
        VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,           KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS, KC_EXLM, KC_BSPC, KC_UP,   KC_DEL,  KC_PIPE, KC_TRNS,           KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_TRNS,           KC_TRNS, KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
        KC_TRNS, KC_ESC,  KC_CIRC, KC_LBRC, KC_ENT,  KC_TILD,                             KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
        EEP_RST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_VAI,           RGB_TOG,          KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
                                            RGB_HUD, RGB_VAD, RGB_HUI, TOGGLE_LAYER_COLOR,KC_TRNS, KC_TRNS
    ),

    [SYMB] = LAYOUT_moonlander(
        VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,           KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,           KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  KC_TRNS,           KC_TRNS, KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
        KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                             KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
        EEP_RST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_VAI,           RGB_TOG,          KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
                                            RGB_HUD, RGB_VAD, RGB_HUI, TOGGLE_LAYER_COLOR,KC_TRNS, KC_TRNS
    ),

    [MDIA] = LAYOUT_moonlander(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,         KC_TRNS,            KC_TRNS,               KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        }
    }
    return true;
}
