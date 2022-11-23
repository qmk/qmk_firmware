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
#include "g/keymap_combo.h"
#include "muse.h"

#define COMBO_ONLY_FROM_LAYER QWERTY

enum planck_layers {
  QWERTY,
  COLMAK,
  NAVNUM,
  FUNC
  
};

#define BspNAV LT(NAVNUM, KC_BSPC)
#define SpcFUN LT(FUNC, KC_SPC)
#define OneSFT OSM(MOD_LSFT)
#define OneALT OSM(MOD_LALT)
#define OneCTL OSM(MOD_LCTL)
#define OneWIN OSM(MOD_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |  ; : |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  | ,  < | .  > |  ' " |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |                    | Ctrl |NAVNUM|             |Space |BspNAV|                    |
 * `-----------------------------------------------------------------------------------'
 */
[QWERTY] = LAYOUT_planck_grid(
    KC_Q,   KC_W,    KC_E,     KC_R,    KC_T,	   _______, _______, KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,
    KC_A,   KC_S,    KC_D,     KC_F,    KC_G,	   _______, _______, KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN,
    KC_Z,   KC_X,    KC_C,     KC_V,    KC_B,	   _______, _______, KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_QUOT,
    _______, _______, _______, KC_LCTL, MO(NAVNUM),_______, _______, KC_SPC, BspNAV, _______, _______, _______
),

[COLMAK] = LAYOUT_planck_grid(
    KC_Q,   KC_W,    KC_F,     KC_P,    KC_B,	   _______, _______, KC_J,   KC_L,   KC_U,    KC_Y,    KC_SCLN,
    KC_A,   KC_R,    KC_S,     KC_T,    KC_G,	   _______, _______, KC_M,   KC_N,   KC_E,    KC_I,    KC_O,
    KC_Z,   KC_X,    KC_C,     KC_D,    KC_V,	   _______, _______, KC_K,   KC_H,   KC_COMM, KC_DOT,  KC_QUOT,
    _______, _______, _______, KC_LCTL, MO(NAVNUM),_______, _______, KC_SPC, BspNAV, _______, _______, _______

),
/* NAVNUM
 * ,-----------------------------------------------------------------------------------.
 * |Enter | Home |  Up  | End  |      |         RST |  -   |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |OneSFT| Left | Down |Right | ` ~  |        CLMK |  +   |   4  |   5  |   6  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |OneCTL|OneALT| Tab  |   _  |OneWIN|        QWER |  =   |   1  |   2  |   3  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |                    |      |      |             |SpcFUN| Ctrl |                    |
 * `-----------------------------------------------------------------------------------'
 */
[NAVNUM] = LAYOUT_planck_grid(
  KC_ENT,  KC_HOME, KC_UP,   KC_END, _______,  _______, RESET,      KC_PMNS, KC_7,    KC_8,   KC_9,     KC_0,
  OneSFT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_GRV,  _______, DF(COLMAK), KC_PPLS, KC_4,    KC_5,   KC_6,     KC_ENT,
  OneCTL,   OneALT, KC_TAB,  KC_UNDS, OneWIN,  _______, DF(QWERTY), KC_EQL,  KC_1,    KC_2,   KC_3,     _______,
  _______, _______, _______, _______, _______, _______, _______,    SpcFUN,  KC_LCTL, _______, _______, _______
),
/* FUNC: Mousekeys + F keys
 * ,-----------------------------------------------------------------------------------.
 * |      |Rclick| MsUp |Lclick| WhUp |             |      |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | MsLt | MsDn | MsRt | WhDn |             |OneALT|  F4  |  F5  |  F6  |  F11 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |Mclick|      |      |             |      |  F1  |  F2  |  F3  |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |                    |      |      |             |      |      |                    |
 * `-----------------------------------------------------------------------------------'
 */
[FUNC] = LAYOUT_planck_grid(
  _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,
  _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, _______, OneALT , KC_F4,   KC_F5,   KC_F6,   KC_F11,
  _______, _______, KC_BTN3, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

};

