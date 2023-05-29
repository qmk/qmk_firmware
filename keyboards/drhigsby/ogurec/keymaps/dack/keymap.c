/* Copyright 2021 drhigsby
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

enum custom_layers {
    _BASE,
    _CLOSE,
    _FAR,
    _FUNKY,
};
#define CLS_SPC LT(_CLOSE, KC_SPC)
#define FAR_F LT(_FAR, KC_F)
#define FNK_D LT(_FUNKY, KC_D)
#define SFT_Z LSFT_T(KC_Z)
#define SFT_ENT RSFT_T(KC_ENT)
#define CTL_X LCTL_T(KC_X)
#define CTL_DOT RCTL_T(KC_DOT)
#define WIN_C LWIN_T(KC_C)
#define WIN_COMM RWIN_T(KC_COMM)
#define ALT_V LALT_T(KC_V)
#define ALT_M LALT_T(KC_M)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define CUT LCTL(KC_X)
#define UNDO LCTL(KC_Z)
#define RUS_TGL RALT(KC_LSFT)
#define LOCK LWIN(KC_L)
#define vvv KC_TRNS

enum custom_keycodes {
    TYPEDON = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch (keycode) {
        case TYPEDON:
            SEND_STRING("[typed on an ogurec]");
            return false;
        }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_3x12(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC, KC_RBRC, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, FNK_D, FAR_F, KC_G, KC_GRAVE, KC_SCLN, KC_H, KC_J, KC_K, KC_L, KC_QUOT,
        SFT_Z, CTL_X, WIN_C, ALT_V, KC_B, KC_BSPC, CLS_SPC, KC_N, ALT_M, WIN_COMM, CTL_DOT, SFT_ENT
  ),

    [_CLOSE] = LAYOUT_ortho_3x12(
        KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,       KC_8,     KC_9,    KC_0,
        KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC, KC_AMPR,    KC_ASTR,  KC_LPRN, KC_RPRN,
        KC_MINUS, KC_UNDS, KC_EQL,  KC_PLUS, _______, _______, vvv,     _______, KC_SCLN,    KC_COLON, KC_SLSH, KC_QUES
  ),

    [_FAR] = LAYOUT_ortho_3x12(
        KC_ESC,  TYPEDON, KC_BSLS, RUS_TGL,_______,  _______,  _______,  KC_PGUP,   KC_HOME,    KC_UP,    KC_END,    KC_INS,
        KC_CAPS, KC_TAB,  KC_PIPE, vvv,    LOCK,     _______,  _______,  KC_PGDN,   KC_LEFT,    KC_DOWN,  KC_RIGHT,  KC_DEL,
        UNDO,    CUT,     COPY,    PASTE,  KC_LBRC,  KC_RBRC,  KC_LCBR,  KC_RCBR,   _______,    _______,  _______,   _______
  ),
    [_FUNKY] = LAYOUT_ortho_3x12(
        KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,    KC_F6,   KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
        _______,  _______,  vvv,     _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______, _______,  _______,  KC_VOLD, KC_VOLU,  _______,  _______,  _______,  _______,  _______
  )

};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case FAR_F:
        return TAPPING_TERM - 50;
    case CLS_SPC:
        return TAPPING_TERM - 50;
    case SFT_Z:
        return TAPPING_TERM - 80;
    case SFT_ENT:
        return TAPPING_TERM - 75;
    default:
        return TAPPING_TERM;
    }
}
