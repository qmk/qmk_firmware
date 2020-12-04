/* Copyright 2019 /u/KeepItUnder
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

// LAYERS
enum Layer {
    _QWERTY = 0,        // Standard QWERTY layer
    _FUNCTION,          // Function key layer
    _COLOUR             // RGB key layer
};
#define _QW _QWERTY
#define _FN _FUNCTION
#define _CLR _COLOUR

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  DK_SW1,
  DK_SW2,
  DK_SW3,
  DK_SW4,
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_all(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, DK_SW1,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_NUBS, DK_SW2,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  DK_SW3,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          DK_SW4,
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, KC_RGUI, MO(_FN), KC_RCTL
  ),

  [_FUNCTION] = LAYOUT_all(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_TRNS,
    _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______, KC_INS,  _______, KC_UP,   KC_PAUS, KC_PGUP, KC_HOME, KC_PSCR, _______, KC_TRNS,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, KC_SLCK, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_END,  _______, KC_ENT,  KC_TRNS,
    _______, _______, _______, KC_APP,  _______, _______, _______, KC_CALC, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          KC_TRNS,
    _______, _______, MO(_CLR),                  KC_MPLY,                            _______, KC_APP,  _______, _______
  ),
  
  [_COLOUR] = LAYOUT_all(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_TRNS,
    _______, _______, _______, _______, _______, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, KC_TRNS,
    _______, _______, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, KC_TRNS,
    _______, _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______, _______,          KC_TRNS,
    _______, _______, _______,                   RGB_TOG,                            _______, _______, _______, _______
  ),
};
