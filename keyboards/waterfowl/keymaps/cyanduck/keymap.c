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
    _COLEMAKDH,
    _NAVNUM,
    _SYM,
    _FUNC,
    _GAME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak-DH
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |                      |   J  |   L  |   U  |   Y  |   ;  |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * |   A  |   R  |   S  |   T  |   G  |                      |   M  |   N  |   E  |   I  |   O  |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  |   V  |  |  2  |    |  3  |  |   K  |   H  |   ,  |   .  |   /  |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----. 
 *          |  1  |   | DEL | SPACE | TAB  |            | TO(0) | BS | ENTER |   |  4  |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_COLEMAKDH] = LAYOUT(
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
  KC_A,    MT(MOD_LALT, KC_R),    MT(MOD_LCTL, KC_S),    MT(MOD_LSFT, KC_T),    KC_G,         KC_M,    MT(MOD_LSFT, KC_N),    MT(MOD_LCTL, KC_E),    MT(MOD_LALT, KC_I),    KC_O,
  KC_Z,    KC_X,    KC_C,    MT(MOD_LGUI, KC_D),    KC_V,         KC_K,    MT(MOD_LGUI, KC_H),    KC_COMM, KC_DOT,  KC_SLSH,
  KC_1, LT(3,KC_DEL), LT(1,KC_SPC), KC_TAB, KC_2,         KC_3, TO(0), KC_BSPC, LT(2,KC_ENT), KC_4
),

/* NAVNUM
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |  ESC | PgUp |  UP  | PgDn | TO(4)|                      |   /  |   7  |   8  |   9  |   -  |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * | Home | Left | Down | Right| End  |                      |   =  |   4  |   5  |   6  |   +  |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * |      |      |  INS | TO(2)|      |  |  2  |    |  3  |  |   0  |   1  |   2  |   3  |   *  |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----. 
 *          |  1  |   | DEL | SPACE | MO(3)|            | TO(0) | BS | ENTER |   |  4  |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_NAVNUM] = LAYOUT(
  KC_ESC,    KC_PGUP,    KC_UP,    KC_PGDN,   TO(4),    KC_SLSH,    KC_7,    KC_8,    KC_9,    KC_MINS,
  KC_HOME,   KC_LEFT,    KC_DOWN,  KC_RGHT,   KC_END,  KC_EQL,     KC_4,    KC_5,    KC_6,    KC_PLUS,
  KC_NO,    KC_NO,      KC_INS,   TO(2),     KC_NO,    KC_0,       KC_1,    KC_2,    KC_3,    KC_ASTR,
  KC_1, LT(3,KC_DEL), LT(1,KC_SPC), KC_ESC, KC_2,         KC_3, TO(0), KC_BSPC, LT(2,KC_ENT), KC_4
),

/* SYM
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |   %  |   @  |   [  |   ]  |   \  |                      |   ¦  |   ¬  |   ^  |      |      |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * |   #  |   !  |   (  |   )  |   |  |                      |   _  |   '  |   "  |   ~  |   `  |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * |   $  |   £  |   {  |   }  |   &  |  |  2  |    |  3  |  | TO(1)|      |      |      |      |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----. 
 *          |  1  |   | DEL | SPACE | TAB  |            | TO(0) | BS | ENTER |   |  4  |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_SYM] = LAYOUT(
  KC_PERC, S(KC_QUOT),   KC_LBRC, KC_RBRC,  KC_NUBS,     RALT(KC_GRV), S(KC_GRV), KC_CIRC, KC_NO,   KC_NO,
  KC_NONUS_HASH, KC_EXLM, KC_LPRN, KC_RPRN, S(KC_NUBS),      KC_UNDS, KC_QUOT, S(KC_2), S(KC_NUHS), KC_GRV,
  KC_DLR, S(KC_3),  KC_LCBR, KC_RCBR, KC_AMPR,      TO(1), KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_1, LT(3,KC_DEL), LT(1,KC_SPC), KC_TAB, KC_2,         KC_3, TO(0), KC_BSPC, LT(2,KC_ENT), KC_4
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
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----. 
 *          |  1  |   | DEL | SPACE | TAB  |            | TO(0) | BS | ENTER |   |  4  |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_FUNC] =  LAYOUT(
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F11,
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_F4,   KC_F5,   KC_F6,   KC_F12,
  RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F13,
  KC_1, LT(3,KC_DEL), LT(1,KC_SPC), KC_TAB, KC_2,         KC_3, TO(0), KC_BSPC, LT(2,KC_ENT), KC_4
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
  KC_1, KC_T, KC_SPC, KC_TAB, KC_2,         KC_3, TO(0), KC_BSPC, LT(2,KC_ENT), KC_4
),
};
