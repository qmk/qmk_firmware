/* Copyright 2021 bbrfkr
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY_BASE,
	_EUCALYN_BASE,
    _LOWER,
    _RAISE,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                 KC_LCTL, KC_LSFT,                   KC_LALT, KC_SPC,  KC_ENT,  KC_RGUI,                   KC_RSFT, KC_RCTL,
                                                     MO(2),                     MO(3)
    ),
    [_EUCALYN_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_COMM, KC_DOT,  KC_SCLN,                                     KC_M,    KC_R,    KC_D,    KC_Y,    KC_P,
        KC_A,    KC_O,    KC_E,    KC_I,    KC_U,                                        KC_G,    KC_T,    KC_K,    KC_S,    KC_N,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_F,                                        KC_B,    KC_H,    KC_J,    KC_L,    KC_SLSH,
                 KC_LCTL, KC_LSFT,                   KC_LALT, KC_SPC,  KC_ENT,  KC_RGUI,                   KC_RSFT, KC_RCTL,
                                                     MO(2),                     MO(3)
    ),
    [_LOWER] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_F2,   KC_F3,   MS_WHLU, KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_UP,   KC_F8,   KC_F9,
        KC_F1,   MS_BTN2, MS_WHLD, MS_BTN1, KC_F11,                                      KC_F12,  KC_LEFT, KC_DOWN, KC_RGHT, KC_F10,
                 KC_LCTL, KC_LSFT,                   KC_LALT, KC_SPC,  KC_ENT,  KC_RGUI,                   KC_RSFT, KC_RCTL,
                                                     KC_TRNS,                   MO(4)
    ),
    [_RAISE] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_ESC,  KC_DEL,  KC_BSPC, KC_GRV,  KC_BSLS,                                     KC_MINS, KC_EQL,  KC_QUOT, KC_LCBR, KC_RCBR,
        KC_CAPS, KC_TAB,  KC_PSCR, KC_TILD, KC_PIPE,                                     KC_UNDS, KC_PLUS, KC_DQUO, KC_LBRC, KC_RBRC,
                 KC_LCTL, KC_LSFT,                   KC_LALT, KC_SPC,  KC_ENT,  KC_RGUI,                   KC_RSFT, KC_RCTL,
                                                     MO(4),                     KC_TRNS
    ),
    [_FN] = LAYOUT(
        KC_VOLU, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BRIU,
        KC_VOLD, KC_NO,   KC_NO,   KC_NO,   DF(0),                                       DF(1),   KC_NO,   KC_NO,   KC_NO,   KC_BRID,
        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_LCTL, KC_LSFT,                   KC_LALT, KC_SPC,  KC_ENT,  KC_RGUI,                   KC_RSFT, KC_RCTL,
                                                     KC_TRNS,                   KC_TRNS
    )
};
