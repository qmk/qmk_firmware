/* Copyright 2022  CyanDuck
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
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
    _QWERTY,
    _SYM,
    _NAV,
    _FUNC,
    _GAME,
    _WOW,
    _WOW2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 *
 * ,----------------------------------.                        ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |                        |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|                        |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |                        |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|  ,------.    ,------.  |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  | M(F) |    |  PY  |  |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------'  `------'    `------'  `----------------------------------'
 *         ,------.   ,--------------------.               ,-------------------.   ,-----.
 *         | M(G) |   | GUI | SPACE | TAB  |               |  TAB | BS | ENTER |   |     |
 *         `------'   `--------------------'               `-------------------'   `-----'
 */
[_QWERTY] = LAYOUT(
  KC_Q,      KC_W,            KC_E,           LSFT_T(KC_R),   KC_T,               KC_Y,               LSFT_T(KC_U),     KC_I,            KC_O,           KC_P,
  KC_A,      KC_S,            KC_D,           LCTL_T(KC_F),   MT(MOD_LGUI, KC_G), MT(MOD_LGUI, KC_H), RCTL_T(KC_J),     KC_K,            KC_L,           LT(_NAV, KC_SCLN),
  KC_Z,      KC_X,            KC_C,           LALT_T(KC_V),   KC_B,               KC_N,               LALT_T(KC_M),     KC_COMM,         KC_DOT,         KC_SLSH,
  TO(_GAME), LALT_T(KC_LGUI), LSFT_T(KC_SPC), LCTL_T(KC_TAB), MO(_FUNC),          KC_MPLY,            LT(_SYM, KC_TAB), LSFT_T(KC_BSPC), LALT_T(KC_ENT), TO(_WOW)
),

/* SYM
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |   1  |  2   |  3  |   +   |  *   |                      |   ¬  |   (  |   )  |   |   |     |
 * |------+------+-----+-------+------|                      |------+------+------+-------+-----|
 * |   4  |  5   |  6  |   -   |  =   |                      |   '  |   {  |   }  |   &   |  ^  |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+-------+-----|
 * |   7  |  8   |  9  |   0   |  _   |  |  2  |    |  3  |  |   `  |   [  |   ]  |  CTL  |  \  |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *         ,------.   ,--------------------.               ,-------------------.   ,-----.
 *         | M(G) |   | GUI | SPACE | TAB  |               |  TAB | BS | ENTER |   |     |
 *         `------'   `--------------------'               `-------------------'   `-----'
 */
[_SYM] = LAYOUT(
  KC_1,    KC_2,            KC_3,           KC_PPLS,            KC_PAST,      KC_GRV,   KC_LPRN, KC_RPRN,         S(KC_BSLS),     KC_NO,
  KC_4,    KC_5,            KC_6,           KC_PMNS,            KC_EQL,       KC_QUOT,  KC_LCBR, KC_RCBR,         KC_AMPR,        KC_CIRC,
  KC_7,    KC_8,            KC_9,           KC_0,               KC_UNDS,      KC_GRAVE, KC_LBRC, KC_RBRC,         KC_RCTL,        KC_BSLS,
  KC_NO,   LALT_T(KC_LGUI), LSFT_T(KC_SPC), LCTL_T(KC_TAB),     MO(_FUNC),    KC_MPLY,  KC_TRNS, LSFT_T(KC_BSPC), LALT_T(KC_ENT), KC_NO
),

/* NAM
 *
 * ,----------------------------------.                      ,------------------------------------.
 * |  C1  | BTN1 | M_UP | BTN2 | W_UP |                      | INST | HOME |   UP  |  END  |      |
 * |------+------+------+------+------|                      |------+------+-------+-------+------|
 * |  C2  | M_LF | M_DW | M_RG | BTN3 |                      |  DEL | LEFT |  DOWN | RIGHT |      |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+-------+-------+------|
 * |      | BTN4 | ESC  | BTN5 | W_DW |  |  2  |    |  3  |  |  CUT | COPY | PASTE |       |      |
 * `----------------------------------'  `-----'    `-----'  `------------------------------------'
 *         ,------.   ,--------------------.               ,-------------------.   ,-----.
 *         |      |   | GUI | SPACE | TAB  |               |  TAB | BS | ENTER |   |     |
 *         `------'   `--------------------'               `-------------------'   `-----'
 */
[_NAV] = LAYOUT(
  KC_ACL1, KC_MS_BTN1,         KC_MS_UP,       KC_MS_BTN2,     KC_MS_WH_UP,           KC_INSERT, KC_HOME, KC_UP,           KC_END,         KC_NO,
  KC_ACL2, KC_MS_LEFT,         KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_BTN3,            KC_DEL,    KC_LEFT, KC_DOWN,         KC_RIGHT,       KC_TRNS,
  KC_NO,   KC_MS_BTN4,         KC_ESCAPE,      KC_MS_BTN5,     KC_MS_WH_DOWN,         KC_CUT,    KC_COPY, KC_PASTE,        KC_NO,          KC_NO,
  KC_NO,   LALT_T(KC_LGUI),    LSFT_T(KC_SPC), LCTL_T(KC_TAB), KC_NO,                 KC_MPLY,   KC_LCTL,  LSFT_T(KC_BSPC), LALT_T(KC_ENT), KC_NO
),

/* FUNC
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |      |      |      |      |      |                      |      |  F7  |  F8  |  F9  |  F11 |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * |      |      |      |      |      |                      |      |  F4  |  F5  |  F6  |  F12 |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * | Reset|      |      |      |      |  |  2  |    |  3  |  |  F10 |  F1  |  F2  |  F3  |  F13 |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *         ,------.   ,--------------------.               ,-------------------.   ,-----.
 *         | M(G) |   | GUI | SPACE | TAB  |               |  TAB | BS | ENTER |   |     |
 *         `------'   `--------------------'               `-------------------'   `-----'
 */
[_FUNC] =  LAYOUT(
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F11,
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_F4,   KC_F5,   KC_F6,   KC_F12,
  QK_BOOT, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F13,
  KC_NO, LALT_T(KC_LGUI),    LSFT_T(KC_SPC), LCTL_T(KC_TAB), KC_NO,                 KC_MPLY,   KC_TAB,  LSFT_T(KC_BSPC), LALT_T(KC_ENT), KC_NO
),

/* GAME
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |  ESC |   Q  |   W  |   E  |   R  |                      |      |      |      |      |      |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * |Shift |   A  |   S  |   D  |   F  |                      |      |      |      |      |      |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |  |  2  |    |  3  |  |      |      |      |      |      |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
 *          |  1  |   |  T  | SPACE | TAB  |            | TO(0) | BS | ENTER |   |  4  |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_GAME] = LAYOUT(
  KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,         KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,         KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,         KC_NO,    KC_NO,    KC_NO, KC_NO,  KC_NO,
  KC_1, KC_T, KC_SPC, KC_TAB, KC_2,         KC_3, TO(_QWERTY), KC_BSPC, LT(2,KC_ENT), KC_4
),

/* WOW
 *
 * ,----------------------------------.                        ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |                        |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|                        |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |                        |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|  ,------.    ,------.  |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  | M(F) |    |  PY  |  |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------'  `------'    `------'  `----------------------------------'
 *         ,------.   ,--------------------.               ,-------------------.   ,-----.
 *         | M(G) |   | GUI | SPACE | TAB  |               |  TAB | BS | ENTER |   |     |
 *         `------'   `--------------------'               `-------------------'   `-----'
 */
[_WOW] = LAYOUT(
  KC_Q,        KC_W, KC_E,      KC_R,   KC_T,               KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
  KC_A,        KC_S, KC_D,      KC_F,   KC_G,               KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
  KC_Z,        KC_X, KC_C,      KC_V,   KC_B,               KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
  TO(_QWERTY), KC_N, MO(_WOW2), KC_SPC, KC_H,               KC_MPLY, KC_NO, KC_NO, KC_NO, KC_NO
),

/* WOW2
 *
 * ,----------------------------------.                        ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |                        |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|                        |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |                        |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|  ,------.    ,------.  |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  | M(F) |    |  PY  |  |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------'  `------'    `------'  `----------------------------------'
 *         ,------.   ,--------------------.               ,-------------------.   ,-----.
 *         | M(G) |   | GUI | SPACE | TAB  |               |  TAB | BS | ENTER |   |     |
 *         `------'   `--------------------'               `-------------------'   `-----'
 */
[_WOW2] = LAYOUT(
  KC_1,  KC_2,    KC_E,  KC_3,  KC_4,               KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
  KC_5,  KC_S,    KC_D,  KC_F,  KC_6,               KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
  KC_7,  KC_8,    KC_9,  KC_0,  KC_UNDS,            KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
  KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO,              KC_MPLY, KC_NO, KC_NO, KC_NO, KC_NO
),
};
