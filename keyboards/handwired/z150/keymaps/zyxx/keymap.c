/* Copyright 2020 DmNosachev
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
    _BASE,
    _FN1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * ,---------------------------------------------------------------------------------------------------------------------------.
 * |  F1 |  F2 | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |Backspace| ~`  |  ScrLk |  FN1   |
 * |---------------------------------------------------------------------------------------------------------------------------|
 * |  F3 |  F4 |  Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]   |      |Home |  ↑  |PgUp |PrnSc|
 * |---------------------------------------------------------------------------------------------      ------------------------|
 * |  F5 |  F6 |  Ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;: |  '" |     Enter  |  ←  |  ↓  |  →  | wh+ |
 * |---------------------------------------------------------------------------------------------------------------------------|
 * |  F7 |  F8 |   Shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /? |  Shift  |  |\ |End  |     |PgDn | wh- |
 * |----------------------------------------------------------------------------------------------------------------------     |
 * |  F9 | F10 |  Alt   |FN1 |                        Space                            |  Alt    |    Ins    |   Del     |     |
 * `---------------------------------------------------------------------------------------------------------------------------'
*/
    [_BASE] = LAYOUT(
    KC_F1,  KC_F2, KC_ESC,   KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_GRV,   KC_SLCK,       MO(_FN1),
    KC_F3,  KC_F4, KC_TAB,   KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,            KC_HOME, KC_UP,   KC_PGUP, KC_PSCR,
    KC_F5,  KC_F6, KC_LCTRL, KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,    KC_LEFT, KC_DOWN, KC_RGHT, KC_WH_U,
    KC_F7,  KC_F8, KC_LSFT,           KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_BSLS,   KC_END,  KC_NO,   KC_PGDN, KC_WH_D,
    KC_F9,  KC_F10,KC_LALT,        MO(_FN1),                                KC_SPC,                                            KC_RALT,       KC_INS,            KC_DEL
    ),
/*
 * ,---------------------------------------------------------------------------------------------------------------------------.
 * |reset|     |    | F11 | F12 | au+ | au- | clk | clk+| clk-| clkr|     |     |     |     |  Delete  |NumLk|   /    |  FN1   |
 * |---------------------------------------------------------------------------------------------------------------------------|
 * |     |     |       |     | mlb | m↑  | mrb |     |     |     |     |     |     |     |      |      |  7  |  8  |  9  |  *  |
 * |---------------------------------------------------------------------------------------------      ------------------------|
 * |     |     |        |     | m←  | m↓  | m→  |     |     |     |     |     |     |     |            |  4  |  5  |  6  |  -  |
 * |---------------------------------------------------------------------------------------------------------------------------|
 * |     |     |           |     |     |     |     |     |     |     |     |     |     |         |     |  1  |  2  |  3  |  +  |
 * |----------------------------------------------------------------------------------------------------------------------     |
 * |     |     |        |FN1 |                                                         | CapsLock|   0 Ins   |    . Del  |     |
 * `---------------------------------------------------------------------------------------------------------------------------'
*/
    [_FN1] = LAYOUT(
    RESET,   _______, _______,  KC_F11,  KC_F12,  AU_ON,   AU_OFF,  CK_TOGG, CK_UP,   CK_DOWN, CK_RST,  _______, _______, _______, _______, KC_DEL,    KC_NLCK,    KC_PSLS,       _______,
    _______, _______, _______,  _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, _______, _______, _______, _______, _______,            KC_P7,   KC_P8,   KC_P9,   KC_PAST,
    _______, _______, _______ , _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______,          _______,   KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
    _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_P1,   KC_P2,   KC_P3,   KC_PPLS,
    _______, _______, _______,         _______,                                 _______,                                           KC_CAPS,       KC_P0,            KC_PDOT
    )
};
