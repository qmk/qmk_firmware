/* Copyright 2020 MechMerlin
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
#include "keymap_italian.h"

// this keymap allows you to have a standard ansi layout, but use italian accented letters
// to do so, keep the language of your operating system set to italian

enum layers {
  _QWERTY,
  _SHIFT,
  _NUMBER,
  _SYMBOL,
  _ACCENT,
  _NAVIGATOR,
  _SERVICE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
        KC_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    IT_MINS, IT_EQL,  KC_BSPC, KC_MUTE,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    IT_LBRC, IT_RBRC, IT_BSLS,
        SFT_T(KC_CAPS), KC_A,    KC_S,    LT(_NAVIGATOR, KC_D),    SFT_T(KC_F),    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    IT_SCLN, IT_QUOT,  SFT_T(KC_ENT),
        LT(_SHIFT, KC_DEL),     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  LT(_SHIFT, KC_PSLS), LT(_SHIFT, KC_UP), LT(_SHIFT, KC_PSLS),
        KC_LCTL,        KC_LALT, KC_LGUI,                        LT(_ACCENT, KC_SPC),                    KC_RALT, MO(_SERVICE),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_SHIFT] = LAYOUT(
        S(KC_GESC), IT_EXLM,    IT_AT,   IT_SHRP, IT_DLR,  IT_PERC, IT_CIRC, IT_AMPR, IT_ASTR,    IT_LPRN,   IT_RPRN,    IT_UNDS,    IT_PLUS,    KC_DEL,     S(KC_MUTE),
        S(KC_TAB),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I),    S(KC_O),   S(KC_P),    IT_LCBR,    IT_RCBR,    IT_PIPE,
        KC_LSFT,    S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K),    S(KC_L),   IT_COLN,    IT_DQUO,                S(KC_ENT),
        KC_LSFT,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_LESS,    IT_MORE,        IT_QST,                S(KC_UP),   IT_QST,
        S(KC_LCTL), S(KC_LALT), S(KC_LGUI),                      S(KC_SPC),                    S(KC_RALT), MO(_SERVICE), S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)
    ),
    [_ACCENT] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IT_SECT, XXXXXXX, IT_DEG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, IT_EURO, XXXXXXX, IT_EGRV, XXXXXXX, XXXXXXX, XXXXXXX, IT_UGRV, IT_IGRV, IT_OGRV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, IT_AGRV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, IT_CCED, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, KC_UP, XXXXXXX,
        KC_LCTL, KC_LALT, KC_LGUI,                      KC_SPC,                    KC_RALT, MO(_SERVICE),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_NAVIGATOR] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, C(KC_ENT),
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                      KC_BSPC,                    XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_SERVICE] = LAYOUT(
        RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_HOME,
        XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
        _______, RGB_SPI, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        _______, _______, _______,                            _______,                   _______, _______, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    return encoder_update_user(index, clockwise);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLD);
        rgb_matrix_disable();
    } else {
        tap_code(KC_VOLU);
        rgb_matrix_enable();
    }
    return true;
}
