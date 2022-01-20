/* Copyright 2015-2017 Jack Humbert
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

enum layers {
    _BASE,
    _GAME,
    _FN1,
    _FN2,
    _FN3,
    _ADJUST
};

#define BASE DF(_BASE)
#define GAME DF(_GAME)
#define FN1 LT(_FN1, KC_BSPC)
#define FN2 LT(_FN2, KC_ENT)
#define FN3SPC LT(_FN3, KC_SPC)

#define CTRLESC MT(MOD_LCTL, KC_ESC)
#define CTRLMIN MT(MOD_RCTL, KC_MINS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    XXXXXXX,
        CTRLESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    CTRLMIN,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                               KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                                            KC_LGUI, FN1,     FN3SPC,           FN3SPC,  FN2,     KC_RALT
    ),
    [_GAME] = LAYOUT_split_3x6_3(
        KC_3,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,                               KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_BSPC,
        KC_2,    CTRLESC, KC_A,    KC_S,    KC_D,    KC_F,                               KC_G,    KC_H,    KC_J,    KC_K,    KC_UP,   KC_ENT,
        KC_1,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,                               KC_B,    KC_N,    KC_M,    KC_LEFT, KC_DOWN, KC_RGHT,
                                            KC_LALT, _______, KC_SPC,           _______, _______, _______
    ),
    [_FN1] = LAYOUT_split_3x6_3(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PIPE,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,          _______, _______, _______
    ),
    [_FN2] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                             KC_F12,  KC_LCBR, KC_RCBR, KC_QUES, KC_PLUS, _______,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_LBRC, KC_RBRC, KC_SLSH, KC_EQL,  KC_BSLS,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,          _______, _______, _______
    ),
    [_FN3] = LAYOUT_split_3x6_3(
        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,                            KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_BSPC, _______,
        _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______,                            KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, KC_APP,  _______, _______, _______, _______,                            KC_PGDN, KC_DEL,  _______, _______, _______, _______,
                                            _______, _______, _______,          _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_split_3x6_3(
        XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, GAME,    BASE,    XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _FN1, _FN2, _ADJUST);
};
