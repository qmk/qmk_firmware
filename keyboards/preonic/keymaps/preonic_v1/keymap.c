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
#define ARROWS MO(_ARROWS)
#define RGB MO(_RGB)
#define MEDIA MO(_MEDIA)
#define SYMBOLS OSL(_SYMBOLS)
#define SHORTCUTS OSL(_SHORTCUTS)
#define NAV OSL(_NAV)

enum preonic_layers {
    _BASE,
    _SYMBOLS,
    _ARROWS,
    _NAV,
    _SHORTCUTS,
    _MEDIA,
    _RGB
};

enum custom_keycodes {
    FT_ARR = SAFE_RANGE,
    CLN_EQ
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_ortho_5x12(
  KC_ESC,  KC_1,    KC_2,    KC_3, KC_4,    KC_5,          KC_6,   KC_7,   KC_8,         KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R,    KC_T,          KC_Y,   KC_U,   KC_I,         KC_O,    KC_P,    SHORTCUTS,
  ARROWS,  KC_A,    KC_S,    KC_D, KC_F,    KC_G,          KC_H,   KC_J,   KC_K,         KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V,    KC_B,          KC_N,   KC_M,   KC_COMM,      KC_DOT,  KC_SLSH, SYMBOLS,
  KC_LCTL, KC_LALT, MEDIA, NAV,  KC_LGUI, LSFT(KC_LGUI), KC_ENT, KC_SPC, LALT(KC_ENT),   RGB,     KC_CAPS, C(G(KC_Q))
),
[_SYMBOLS] = LAYOUT_ortho_5x12(
    _______, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, _______, KC_PLUS,  KC_LCBR, KC_RCBR, FT_ARR,  CLN_EQ,   KC_EQL,  KC_AMPR, _______, _______, _______,
    _______, KC_UNDS, KC_MINUS, KC_LPRN, KC_RPRN, KC_GRV,  KC_TILDE, KC_DLR,  KC_PIPE, KC_BSLS, _______, _______,
    _______, _______, _______,  KC_LBRC, KC_RBRC, _______, _______,  _______, _______, _______, _______, _______,
    _______, _______, _______,  _______, _______, _______, _______,  _______, _______, _______, _______, _______
),
[_ARROWS] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,        KC_UP,   _______, _______,  _______,
    _______, _______, _______, _______, _______, _______, KC_RALT, KC_LEFT,        KC_DOWN, KC_RGHT, C(KC_G),  _______,
    _______, _______, _______, _______, _______, _______, _______, C(KC_A),        _______, C(KC_E), _______,  _______,
    _______, _______, _______, _______, _______, _______, _______, LSFT_T(KC_SPC), _______, _______, _______,  _______
),
[_NAV] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______,       _______,    _______,    _______,    _______,       _______,
    _______, _______, _______, _______, _______, _______, _______,       _______,    G(KC_U),    _______,    _______,       _______,
    _______, _______, _______, _______, _______, _______, G(S(KC_LBRC)), G(KC_LBRC), G(A(KC_B)), G(KC_RBRC), G(S(KC_RBRC)), _______,
    _______, _______, _______, _______, _______, _______, _______,       C(KC_M),    _______,    _______,    _______,       _______,
    _______, _______, _______, _______, _______, _______, _______,       _______,    _______,    _______,    _______,       _______
),
[_SHORTCUTS] = LAYOUT_ortho_5x12(
    _______, _______, _______,    _______, _______,    _______, _______, _______, _______,    _______, _______, _______,
    _______, _______, _______,    _______, C(KC_T),    _______, _______, _______, G(A(KC_I)), _______, _______, _______,
    _______, _______, G(A(KC_T)), _______, G(A(KC_L)), _______, _______, _______, _______,    _______, _______, _______,
    _______, _______, _______,    _______, _______,    _______, _______, _______, _______,    _______, _______, _______,
    _______, _______, _______,    _______, _______,    _______, _______, _______, _______,    _______, _______, RESET
),
[_MEDIA] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_RGB] = LAYOUT_ortho_5x12(
    _______, RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______,
    _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______,
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/*
[_NEW] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
 */
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CLN_EQ:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING(":=");
        } else {
            // when keycode is released
        }
        break;
    case FT_ARR:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING("=>");
        } else {
            // when keycode is released
        }
        break;
    }
    return true;
};
