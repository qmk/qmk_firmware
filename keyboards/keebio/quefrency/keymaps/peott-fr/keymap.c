 /* Copyright 2022 peott
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

// Only for actual custom keycodes (not just renaming existing tapdance etc...).
//enum custom_keycodes {
//  QWERTY = SAFE_RANGE,
//};

// Layers by name.
enum custom_layers {
    _BASE,
    _FN,
    _NUM
};

// Keycodes for cleaner code
#define L_CTRL LCTL_T(KC_MPRV)
#define L_GUI LGUI_T(KC_MPLY)
#define L_ALT LALT_T(KC_MNXT)
// Layers defined by function
#define LR_SPC LT(_FN,KC_SPC)
#define LR_BKSP LT(_FN,KC_BSPC)
#define LR_NUM LT(_NUM,KC_HOME)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_with_macro(
    KC_F1, KC_F2,  KC_ESC,  KC_1,  KC_2,  KC_3,   KC_4,   KC_5, KC_6, KC_7,    KC_8,    KC_9,    KC_0,    KC_9,    KC_MINS, KC_GRV,  KC_DEL, 
    KC_F3, KC_F4,  KC_TAB,  KC_Q,  KC_W,  KC_E,   KC_R,   KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, 
    KC_F5, KC_F6,  KC_LCTL, KC_A,  KC_S,  KC_D,   KC_F,   KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, 
    KC_F7, KC_F8,  KC_LSPO, KC_Z,  KC_X,  KC_C,   KC_V,   KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, LR_NUM, 
    KC_F9, KC_F10, L_CTRL,  L_GUI, L_ALT, KC_APP, LR_SPC,             LR_BKSP, LR_BKSP, KC_RALT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    [_FN] = LAYOUT_60_with_macro(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_LSFT, KC_CALC, KC_MYCM, KC_PSCR, KC_ENT,  KC_BSPC,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_LCTL, KC_LGUI, KC_LALT, KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS, KC_RALT, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),
    [_NUM] = LAYOUT_60_with_macro(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_P4,   KC_P5,   KC_P6,   KC_PCMM, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_P0,   KC_P0,   KC_PDOT, KC_PENT, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}
