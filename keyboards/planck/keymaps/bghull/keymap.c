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
#include "keymap_steno.h"

enum planck_layers {
  _QWERTY,
  _STENO,
  _NUMPAD,
  _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |NUMPAD|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | ;  : | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  | ,  < | .  > |  up  | /  ? |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Es/Ctl|MACROS|STENO |  Alt | Bspc |    Space    | Ctrl | '  " |  lt  |  dn  |  rt  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    LGUI_T(KC_TAB),             KC_Q,      KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,    KC_P, KC_DEL,
    MO(_NUMPAD),        KC_A,      KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L, KC_SCLN, KC_ENT,
    KC_LSFT,            KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,   KC_DOT,   KC_UP, KC_SLSH,
    LCTL_T(KC_ESC),MO(_FUNC),DF(_STENO), KC_LALT, KC_BSPC, KC_SPC ,_______ , KC_LCTL, KC_QUOT,  KC_LEFT, KC_DOWN, KC_RGHT
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  FN  |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |QWERTY|   A  |   O  |             |   E  |   U  |  PWR | RES1 | RES2 |
 * `-----------------------------------------------------------------------------------'
 */
[_STENO] = LAYOUT_planck_grid(
  STN_N1,  STN_N2,  STN_N3,     STN_N4,      STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC ,
  STN_FN,  STN_S1,  STN_TL,     STN_PL,      STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR ,
  XXXXXXX, STN_S2,  STN_KL,     STN_WL,      STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR ,
  XXXXXXX, XXXXXXX, DF(_QWERTY),STN_A,STN_O, XXXXXXX, XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2
),

/* 
 * ,-----------------------------------------------------------------------------------.
 * |      |RClick|  MsU |LClick|WheelU|   (  |  )   |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  MsL |  MsD |  MsR |WheelD|  [{  |  ]}  |   4  |   5  |   6  |   +  |  -_  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Mute | VolD | VolU |  `~  |   _  |  =   |   1  |   2  |   3  | PgUp | \  | |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |RESET |      |      |             |      |   .  | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
  _______, KC_BTN2, KC_MS_U, KC_BTN1,  KC_WH_U, KC_LPRN, KC_RPRN,    KC_7,     KC_8,    KC_9,    KC_0, _______,
  _______, KC_MS_L, KC_MS_D, KC_MS_R,  KC_WH_D, KC_LBRC, KC_RBRC,    KC_4,     KC_5,    KC_6, KC_PPLS, KC_MINS,
  _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_GRAVE, KC_UNDS,  KC_EQL,    KC_1,     KC_2,    KC_3, KC_PGUP, KC_BSLS,
  _______, XXXXXXX,   RESET, _______,  _______, _______, _______, _______,  KC_PDOT, KC_HOME, KC_PGDN, KC_END
),

/* Dynamic macros + Winkey combos
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  W2  |      |      |      |      |      |      |      |      |      |      | RESET|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  W3  |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  W4  |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = LAYOUT_planck_grid(
     KC_F1  ,  KC_F2 ,  KC_F3 ,  KC_F4  , KC_F5  , KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 ,  KC_F10 , KC_F11 , KC_F12,
  LGUI(KC_2), _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, RESET,
  LGUI(KC_3), _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
  LGUI(KC_4), _______, DM_REC1, DM_PLY1, DM_RSTP, _______, _______, _______, _______,  _______, _______, _______
),

};
