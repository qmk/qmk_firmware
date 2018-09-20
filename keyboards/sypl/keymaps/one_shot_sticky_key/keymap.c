/* Copyright 2015-2017 Steven Liu
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

#include "sypl.h"
#include "action_layer.h"
#include "quantum_keycodes.h"

extern keymap_config_t keymap_config;

#undef ONESHOT_TIMEOUT

#define SK_LALT OSM(MOD_LALT)
#define SK_LCTL OSM(MOD_LCTL)
#define SK_LSFT OSM(MOD_LSFT)
#define SK_LGUI OSM(MOD_LGUI)
#define SK_RALT OSM(MOD_RALT)
#define SK_RCTL OSM(MOD_RCTL)
#define SK_RSFT OSM(MOD_RSFT)
#define SK_RGUI OSM(MOD_RGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
  * ,-------------------------------------------------------------------------------------.
  * | Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del   |
  * |-------+------+------+------+------+------+------+------+------+------+------+-------|
  * | Esc   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter |
  * |-------+------+------+------+------+------+------+------+------+------+------+-------|
  * |       |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |       |
  * |---- --+------+------+------+------+------+------+------+------+------+------+-------|
  * | Debug | LAlt |LCtrl |LShift| LGUI |    Space    | RGUI |RShift|RCtrl | RAlt | Reset |
  * `-------------------------------------------------------------------------------------'
  */
  LAYOUT_planck_mit(
    KC_TAB,  KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_DEL,
    KC_ESC,  KC_A,    KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, KC_ENT,
    _______, KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, _______,
    DEBUG,   SK_LALT, SK_LCTL,  SK_LSFT, SK_LGUI,      KC_SPC,      SK_RGUI, SK_RSFT, SK_RCTL,  SK_RALT, RESET
  )
};
