 /* Copyright 2020 E.Zelianin
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

// Each layer gets a name for readability.
enum zergo_layers {
    l_main,
    l_arrows,
};

//define keycode custom names to better structure view of layout
#define K_SPCFN LT(l_arrows,KC_SPC)     // tap for space, hold for arrows layer
#define K_SHHOME MT(MOD_LSFT,KC_HOME)   // tap for home, hold for shift
#define K_CEND MT(MOD_LCTL,KC_END)      // tap for end, hoild for control
#define K_SHPGUP MT(MOD_RSFT,KC_PGUP)   // tap for pageup, hoLd for shift
#define K_CPGDN MT(MOD_RCTL, KC_PGDN)   // tap for pagedown, hold for control
#define K_LNG LCTL(KC_LSFT)             // control+shift (to change lahguage)
#define K_CENTER MT(MOD_RCTL,KC_ENTER)  // tap for enter, hold for control

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[l_main] = LAYOUT(
  KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,         KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,
  KC_DEL,   KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,          K_LNG,         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_BSLS,
  KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  K_CENTER,
  K_SHHOME, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,          KC_BSPC,       KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RBRC,  K_SHPGUP,
  K_CEND,   KC_NO,    KC_NO,    KC_LALT,            KC_SPC,        KC_ENT,        K_SPCFN,                      KC_RALT,  KC_APP,   KC_RGUI,  K_CPGDN),

[l_arrows] = LAYOUT(
  _______,            _______,  _______,  _______,  _______,      _______,    _______,  _______,  _______,      _______,  _______,  _______,  QK_BOOT,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,       _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,                      KC_ENT,   KC_UP,    KC_BSPC,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,       _______,       KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,            _______,       KC_INS,        _______,                      _______,  _______,  _______,  _______),

};
