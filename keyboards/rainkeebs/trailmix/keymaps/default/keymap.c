/* Copyright 2021 Regan Palmer
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
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T,               KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G,               KC_H, KC_J, KC_K, KC_L, KC_ENTER,
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MPLY,      KC_PSCR, KC_N, KC_M, KC_COMM, KC_DOT, KC_BSPC,
        KC_LCTL, KC_LALT, KC_LGUI, LOWER,KC_LSFT,   KC_SPC, RAISE, KC_RGUI, KC_ESC, KC_TAB
    ),

    [_LOWER] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5,                                   KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_ESC, KC_HOME, KC_PGDN, KC_PGUP, KC_END,                      KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, KC_TRNS,
        KC_TAB, KC_INSERT, KC_DELETE, KC_BACKSLASH,KC_MINUS, KC_TRNS,   KC_TRNS, KC_PLUS, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_LGUI, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_RGUI, KC_TRNS, KC_TRNS
    ),

    [_RAISE] = LAYOUT(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_GRAVE, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,            KC_LCBR, KC_RCBR, KC_COLN, KC_DQT, KC_TRNS,
        KC_TRNS, KC_CAPS, KC_TRNS, KC_PIPE, KC_UNDS, KC_TRNS,   KC_TRNS, KC_EQUAL, KC_QUESTION, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, ADJUST, KC_TRNS, KC_TRNS
    ),

    [_ADJUST] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                  KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
        KC_F11, KC_F12, KC_PRINT_SCREEN, KC_SCROLL_LOCK,    KC_PAUSE, KC_H, KC_J, KC_K, KC_L, KC_ENTER,
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MPLY,              KC_PSCR, KC_N, KC_M, KC_COMM, KC_DOT, KC_BSPC,
        KC_LCTL, KC_LALT, ADJUST, RAISE, KC_SPC,            KC_LSFT, LOWER, ADJUST, KC_RALT, KC_RCTL
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [_LOWER]  = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_HOME, KC_END)},
    [_RAISE]  = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_WH_L, KC_WH_R)},
    [_ADJUST] = {ENCODER_CCW_CW(KC_MS_LEFT, KC_MS_RIGHT), ENCODER_CCW_CW(KC_MS_UP, KC_MS_DOWN)},
};
#endif
