/* Copyright 2022 NaCly
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,                      KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,   
        KC_A,    KC_S,    LT(3,KC_D),    LT(1,KC_F), KC_G,                      KC_H,    LT(2,KC_J), KC_K,    KC_L,    KC_SCLN,
        MT(MOD_LSFT,KC_Z),    KC_X,    KC_C,    KC_V,       KC_B,                      KC_N,    KC_M,       KC_COMM, KC_DOT,  MT(MOD_RSFT,KC_SLSH),
        KC_LCTL, KC_LALT, KC_LGUI,  LT(2,KC_EQL),     KC_BSPC, KC_DEL,  KC_ENT,  KC_SPC,  KC_LBRC,    KC_RBRC, KC_MINS, KC_ESC
    ),
    //Holding F
    [1] = LAYOUT(
        KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, 
        KC_NO,   KC_NO,   KC_NO,   _______, KC_NO,                     KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        MT(MOD_LSFT,KC_Z),   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   MT(MOD_RSFT,KC_SLSH),  
        KC_LGUI, KC_LALT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_HOME, KC_END,  KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
    //Holding J
    [2] = LAYOUT(
        KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BSLS, 
        KC_MPRV, KC_MPLY, KC_MNXT, KC_TAB,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_QUOT, 
        MT(MOD_LSFT,KC_Z),   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   _______, KC_NO,   KC_NO,   MT(MOD_RSFT,KC_SLSH), 
        KC_LGUI, KC_LALT, KC_NO,   _______,   KC_F14,   KC_F15,   KC_ENT,  KC_SPC,  KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
        //Holding d
    [3] = LAYOUT(
        KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,                     KC_NO,   KC_7,   KC_8,   KC_9,   KC_MINS, 
        KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,                     KC_NO,   KC_4,   KC_5,   KC_6,   KC_QUOT, 
        MT(MOD_LSFT,KC_Z),   KC_NO,   _______,   KC_NO,   KC_NO,                     KC_NO,  KC_1, KC_2,   KC_3,   MT(MOD_RSFT,KC_SLSH), 
        KC_LCTL, KC_LALT, KC_LGUI,  LT(2,KC_EQL),     KC_BSPC, KC_DEL,   KC_ENT,  KC_0,  KC_NO,   KC_NO,   KC_DOT,   KC_NO
    )
};

