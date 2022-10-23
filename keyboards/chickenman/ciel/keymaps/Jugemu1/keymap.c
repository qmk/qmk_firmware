/* Copyright 2020 Koichi Katano
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

#include "jugemu.h"

enum layer_names {
    _BASE = 0,
    _FN = 1,
    _FN1 = ARROW_LAYER,
};

#define F_MM LT(CK_MM,KC_F)
#define J_MM LT(CK_MM,KC_J)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_ansi_split_bs_rshift(
        KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,     KC_EQL,     KC_GRV,    KC_BSPC,
        KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,    KC_RBRC,                KC_BSLS,
        KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, ARROW_SCLN,    KC_QUOT,                             KC_ENT,
        KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH,               KC_UP,   MO(_FN),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                           _______,   KC_LEFT,  KC_DOWN,   KC_RIGHT
    ),
    [_FN] = LAYOUT_60_ansi_split_bs_rshift(
        QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,KC_VOLD, KC_VOLU,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         TD_AUDIO,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       CK_TD_MODE, _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______, _______
    ),
    [_FN1] = LAYOUT_60_ansi_split_bs_rshift(
        KC_GRAVE,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,     KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,  KC_DEL,
        _______, _______, _______, _______, _______,  CK_SWL, _______,    KC_HOME,    KC_END, _______,  _______, _______, _______,           _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT,    KC_DOWN,     KC_UP,KC_RIGHT,  _______, _______,                    _______,
        _______,          _______, _______, _______, KC_BSPC, _______,    _______,   KC_PGUP, KC_PGDN,   _______, _______,        CK_TD_MODE, _______,
        _______, _______, _______,                            KC_PENT,                                             _______, _______, _______, _______
    ),
};

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record){
    return true;
}
