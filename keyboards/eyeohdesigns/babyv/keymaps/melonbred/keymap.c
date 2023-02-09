/* Copyright 2020 melonbred
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
    LAYER0,
    LAYER1,
    LAYER2,
};


// Tap Dance Declarations
enum {
  TD_M_D = 0,
  TD_P_M
};
  
// Tap Dance Definition
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for minus, tap twice for divide
  [TD_M_D] = ACTION_TAP_DANCE_DOUBLE(KC_PMNS, KC_PSLS),
  //Tap once for plus, tap twice for multiply
  [TD_P_M] = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_PAST)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [LAYER0] = LAYOUT_2u(
        KC_ESC,        KC_Q,    KC_W,    KC_E,      KC_R,       KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,     KC_P,    KC_BSPC,
        CTL_T(KC_TAB), KC_A,    KC_S,    KC_D,      KC_F,       KC_G,    KC_H,    KC_J,    KC_K,      KC_L,     KC_SCLN, KC_ENT, 
        KC_LSFT,       KC_Z,    KC_X,    KC_C,      KC_V,       KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,   KC_SLSH, KC_RSFT,
        MO(LAYER2),                      KC_LALT,   LT(LAYER1, KC_SPC),           KC_SPC,  KC_RALT,                      KC_LGUI
    ),

   [LAYER1] = LAYOUT_2u(
        KC_GRV,  KC_QUOT, _______, KC_UP,   _______, _______, KC_7, KC_8, KC_9, KC_PMNS, KC_PSLS, KC_DEL,
        KC_CAPS, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_4, KC_5, KC_6, KC_PPLS, KC_PAST, KC_ENT,
        KC_LSFT, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_1, KC_2, KC_3, XXXXXXX, XXXXXXX, KC_RSFT,
        XXXXXXX,                   _______, _______,                   KC_0,       KC_PDOT,       _______
    ),

    [LAYER2] = LAYOUT_2u(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_VOLU, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
        KC_VOLD, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, KC_RCTL, KC_RALT, KC_DEL,  XXXXXXX, 
        _______,                   KC_NUM,  XXXXXXX,                   XXXXXXX, XXXXXXX,                   XXXXXXX
    ),
};
