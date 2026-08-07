/* Copyright 2018 Nicolas Schodet
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

/* Defines names for use in layer keycodes and the keymap */
enum layer_names { _BASE, _NAV };

#define NAV_SPC LT(_NAV, KC_SPC)
#define CTL_BSP MT(MOD_LCTL, KC_BSPC)
#define KC_GTAB LGUI(KC_TAB)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------+-------.
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,KC_GRV ,     KC_EQL , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     KC_RBRC, KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,KC_APP ,     KC_DEL , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_LBRC,
  //|-------+-------+-------+-------+-------+-------|       |    |       |-------+-------+-------+-------+-------+-------|
     KC_TAB , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,/*-----|    |------*/ KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
  //|-------+-------+-------+-------+-------+-------|       |    |       |-------+-------+-------+-------+-------+-------|
     KC_NUBS, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_GTAB,     KC_ENT , KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLS,
  //`-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------'
                     KC_LGUI,KC_LALT,KC_ESC ,CTL_BSP,KC_LSFT,     KC_RSFT,NAV_SPC,KC_RCTL,KC_RALT,KC_RGUI
  //                `-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------'
  ),
  [_NAV] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------+-------.
     _______,_______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______, QK_BOOT ,
  //|-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------|
     _______,_______, KC_7  , KC_8  , KC_9  ,_______,_______,     _______,KC_DEL ,KC_PGUP, KC_UP ,KC_PGDN,_______,_______,
  //|-------+-------+-------+-------+-------+-------|       |    |       |-------+-------+-------+-------+-------+-------|
     KC_CAPS,_______, KC_4  , KC_5  , KC_6  ,_______,/*-----|    |------*/KC_BSPC,KC_LEFT,KC_DOWN,KC_RGHT,KC_ENT ,_______,
  //|-------+-------+-------+-------+-------+-------|       |    |       |-------+-------+-------+-------+-------+-------|
     _______,_______, KC_1  , KC_2  , KC_3  ,_______,_______,     _______,C(KC_W),KC_HOME,_______,KC_END ,KC_INS ,_______,
  //`-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------'
                      KC_APP, KC_0  ,KC_DOT ,_______,_______,     _______,_______,_______,_______,_______
  //                `-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------'
  ),
};
// clang-format on
