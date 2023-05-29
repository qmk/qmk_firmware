/* Copyright 2022 Jens Peter Secher <jpsecher@gmail.com>
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

#define SPC_CTL LCTL_T(KC_SPC)
#define DEL_GUI LGUI_T(KC_DEL)
#define DEL_CTL LCTL_T(KC_SPC)
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_ALT OSM(MOD_LALT)
#define ESC_CTL LCTL_T(KC_ESC)
#define BS_GUI LGUI_T(KC_BSPC)
#define BS_SYM LT(_SYM_NUM, KC_BSPC)
#define SPC_NAV LT(_NAVI_FN, KC_SPC)
#define OSM_AGR OSM(MOD_RALT)

enum layer_names {
    _QWERTY,
    _NAVI_FN,
    _SYM_NUM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_B,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_H,    KC_U,    KC_I,    KC_O,    KC_P,    KC_Y,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_N,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
             KC_Z,    KC_X,    KC_C,    KC_V,                         KC_M,    KC_COMM, KC_DOT,  KC_QUOT,
             KC_MNXT, OSM_ALT, BS_SYM,  ESC_CTL, OSM_SFT,    OSM_AGR, DEL_GUI, SPC_NAV, OSM_ALT, KC_MPLY, DB_TOGG
  ),
  [_NAVI_FN] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TAB,  KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_TILD,    KC_GRV,  KC_LEFT, KC_UP,   KC_RGHT, KC_WREF, KC_ENT,
             KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE,                      KC_BTN1, KC_DOWN, KC_BTN2, KC_WBAK,
             KC_MPRV, _______, BS_GUI, _______, _______,     _______, _______, _______, _______, KC_PWR,  _______
  ),
  [_SYM_NUM] = LAYOUT(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,    KC_AMPR, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_PLUS,
    KC_QUES, KC_SLSH, KC_LBRC, KC_LCBR, KC_LPRN, KC_PIPE,    KC_0,    KC_4,    KC_5,    KC_6,    KC_MINS, KC_EQL,
             KC_BSLS, KC_RBRC, KC_RCBR, KC_RPRN,                      KC_1,    KC_2,    KC_3,    KC_UNDS,
             KC_VOLD, _______, _______, _______, _______,    _______, _______, SPC_CTL, _______, KC_VOLU, _______
  )
};
