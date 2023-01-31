/* Copyright 2022 Duccio Breschi <ducciobreschi@gmail.com>
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

enum layers {
    _BASE = 0,
    _SYM1,
    _EXT,
    _FNC,
    _SYM2,
    _ACC,
    _SET,
};

// Combo Layers
enum combos {
  ACC,
  SET,
};
const uint16_t PROGMEM accent_combo[] = {KC_SPC, MO(_SYM1), COMBO_END};
const uint16_t PROGMEM settings_combo[] = {MO(_EXT), SFT_T(KC_SPC), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  [ACC] = COMBO(accent_combo, MO(_ACC)),
  [SET] = COMBO(settings_combo, MO(_SET)),
};
// -----

// Layer Aliases
#define SYM1 MO(_SYM1)
#define EXT MO(_EXT)
#define FNC MO(_FNC)
#define SYM2 MO(_SYM2)
// #define ACC MO(_ACC)
// #define SET MO(_SET)
// Oneshot Aliases
#define OS_CTL OSM(MOD_LCTL)
#define OS_ALT OSM(MOD_LALT)
#define OS_SFT OSM(MOD_LSFT)
#define OS_GUI OSM(MOD_LGUI)
#define OS_RALT OSM(MOD_RALT)
// Other Aliases
#define DEL_WORD LCTL(KC_BSPC)
#define UNDO LCTL(KC_Z)
#define COPY LCTL(KC_C)
#define CUT LCTL(KC_X)
#define PASTE LCTL(KC_V)
#define BACKTICK RALT(KC_MINS)
#define TILDE RALT(KC_EQL)
#define CEGR RSA(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_split_3x5_3(
  IT_Q,   IT_W,    IT_E,    IT_R,    IT_T,        IT_Y,    IT_U,    IT_I,    IT_O,    IT_P,
  IT_A,   IT_S,    IT_D,    IT_F,    IT_G,        IT_H,    IT_J,    IT_K,    IT_L,    IT_OGRV,
  IT_Z,   IT_X,    IT_C,    IT_V,    IT_B,        IT_N,    IT_M,    IT_COMM, IT_DOT,  IT_UGRV,
                   XXXXXXX, EXT, SFT_T(KC_SPC),      KC_SPC,  SYM1,  XXXXXXX
),
[_SYM1] = LAYOUT_split_3x5_3(
  IT_1,   IT_2,    IT_3,    IT_4,    IT_5,        IT_6,    IT_7,    IT_8,    IT_9,    IT_0,
  IT_LABK,   IT_PERC,    IT_LPRN,    IT_LCBR,    IT_LBRC,        IT_EQL,    IT_QUES,    IT_QUOT,    IT_PLUS,    IT_ASTR,
  IT_RABK,   IT_DLR,    IT_RPRN,    IT_RCBR,    IT_RBRC,        IT_AT,    IT_EXLM,    IT_DQUO, IT_MINS,  IT_SLSH,
                   XXXXXXX, FNC, SYM2,          _______,  _______,  XXXXXXX
),
[_EXT] = LAYOUT_split_3x5_3(
  KC_ESC, _______, _______, _______, _______,        KC_PAGE_UP, KC_HOME, KC_UP, KC_END, KC_CAPS,
  OS_ALT, OS_GUI, OS_SFT, OS_CTL, OS_RALT,        KC_PAGE_DOWN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DELETE,
  UNDO, CUT, COPY, KC_TAB, PASTE,                 DEL_WORD, KC_BSPC, _______, _______, _______, 
                    _______, _______, _______,        KC_ENT, FNC, _______
),
[_FNC] = LAYOUT_split_3x5_3(
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, 
  OS_ALT, OS_GUI, OS_SFT, OS_CTL, OS_RALT,           KC_F11, KC_F12, KC_PSCR, _______, _______, 
  _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______,  
                    _______, _______, _______,        _______, _______, _______
),
[_SYM2] = LAYOUT_split_3x5_3(
  IT_CIRC, IT_UNDS, IT_PND, IT_EURO, IT_HASH,        _______, _______, _______, _______, _______, 
  BACKTICK, TILDE, IT_BSLS, IT_PIPE, IT_AMPR,        _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______,  
                    _______, _______, _______,        _______, _______, _______
),
[_ACC] = LAYOUT_split_3x5_3(
  _______, _______, _______, CEGR, _______,        _______, _______, _______, _______, _______, 
  IT_AGRV, IT_IGRV, IT_OGRV, IT_EGRV, IT_EACU,        _______, _______, _______, _______, _______, 
  _______, _______, _______, IT_UGRV, _______,        _______, _______, _______, _______, _______,  
                    _______, _______, _______,        _______, _______, _______
),
[_SET] = LAYOUT_split_3x5_3(
  _______, _______, _______, RGB_RMOD, RGB_MOD,        RGB_VAI, RGB_VAD, _______, _______, _______, 
  _______, _______, _______, RGB_M_B, RGB_M_P,        RGB_HUI, RGB_HUD, _______, _______, _______, 
  QK_BOOT, _______, _______, RGB_M_R, RGB_TOG,        RGB_SAI, RGB_SAD, _______, _______, QK_BOOT,  
                    _______, _______, _______,        _______, _______, _______
),
// [_TEMP] = LAYOUT_split_3x5_3(
//   _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, 
//   _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, 
//   _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______,  
//                     _______, _______, _______,        _______, _______, _______
// ),
};
