/*
This is the keymap for the keyboard

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Art Ortenburger

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "drashna.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_wrapper(\
  KC_ESC,  _________________QWERTY_L1_________________,                                                               _________________QWERTY_R1_________________, KC_BSPC,
  KC_TAB,  _________________QWERTY_L2_________________,          KC_UP,   KC_DOWN,         KC_LEFT, KC_RIGHT,         _________________QWERTY_R2_________________, KC_QUOT,
  KC_MLSF, _________________QWERTY_L3_________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________QWERTY_R3_________________, KC_LGUI
),

[_COLEMAK] = LAYOUT_wrapper(\
  KC_ESC,  _________________COLEMAK_L1________________,                                                               _________________COLEMAK_R1________________, KC_BSPC,
  KC_TAB,  _________________COLEMAK_L2________________,          KC_UP,   KC_DOWN,         KC_LEFT, KC_RIGHT,         _________________COLEMAK_R2________________, KC_QUOT,
  KC_MLSF, _________________COLEMAK_L3________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________COLEMAK_R3________________, KC_LGUI
),

[_DVORAK] = LAYOUT_wrapper(\
  KC_ESC,  _________________DVORAK_L1_________________,                                                               _________________DVORAK_R1_________________, KC_BSPC,
  KC_TAB,  _________________DVORAK_L2_________________,          KC_UP,   KC_DOWN,         KC_LEFT, KC_RIGHT,         _________________DVORAK_R2_________________, KC_MINS,
  KC_MLSF, _________________DVORAK_L3_________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________DVORAK_R3_________________, KC_LGUI
),
[_WORKMAN] = LAYOUT_wrapper(\
  KC_ESC,  _________________WORKMAN_L1________________,                                                               _________________WORKMAN_R1________________, KC_BSPC,
  KC_TAB,  _________________WORKMAN_L2________________,          KC_UP,   KC_DOWN,         KC_LEFT, KC_RIGHT,         _________________WORKMAN_R2________________, KC_MINS,
  KC_MLSF, _________________WORKMAN_L3________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________WORKMAN_R3________________, KC_LGUI
),
[_MODS] = LAYOUT_wrapper(\
  _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,          _______, _______,         _______, _______,          _______, _______, _______, _______, _______, _______,
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_LOWER] = LAYOUT_wrapper(\
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_PGUP, KC_PGDN,         KC_HOME, KC_END,           _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,         _______, _______, _______, _______, _______, KC_COMM, KC_DOT,  _______, _______
),

[_RAISE] = LAYOUT_wrapper(\
  KC_GRV,  ________________NUMBER_LEFT________________,                                                               ________________NUMBER_RIGHT_______________, KC_BSPC,
  _______, _______, _______, _______, _______, _______,          KC_PGUP, KC_PGDN,         KC_HOME, KC_END,           _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, KC_COMM, KC_DOT,  _______, _______
),

[_ADJUST] = LAYOUT_wrapper(\
  KC_MAKE,KC_RESET, EPRM,    _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
  RGB_SMOD,RGB_HUI, CK_TOGG, AU_ON,   AU_OFF,  AG_NORM,          _______, _______,         _______, _______,          AG_SWAP, KC_QWERTY, KC_COLEMAK, KC_DVORAK, KC_WORKMAN, TG(_MODS),
  KC_RGB_T,RGB_HUD, MU_ON,   MU_OFF,  MU_TOG,  MU_MOD,  _______, _______, _______,         _______, _______, _______, MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY
)


};

#ifdef RGBLIGHT_ENABLE
uint32_t layer_state_set_keymap (uint32_t state) {
  uint8_t modifiders = get_mods();
  uint8_t led_usb_state = host_keyboard_leds();
  uint8_t one_shot = get_oneshot_mods();


  if (modifiders & MODS_SHIFT_MASK || led_usb_state & (1<<USB_LED_CAPS_LOCK) || one_shot & MODS_SHIFT_MASK) {
    rgblight_sethsv_at(0, 255, 255, 5);
    rgblight_sethsv_at(0, 255, 255, 10);
  }
  if (modifiders & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK) {
    rgblight_sethsv_at(51, 255, 255, 6);
    rgblight_sethsv_at(51, 255, 255, 9);
  }
  if (modifiders & MODS_ALT_MASK || one_shot & MODS_ALT_MASK) {
    rgblight_sethsv_at(120, 255, 255, 7);
    rgblight_sethsv_at(120, 255, 255, 8);
  }

  return state;
}


void matrix_scan_keymap (void) {
  static uint8_t current_mods;
  static uint8_t current_host_leds;
  static uint8_t current_oneshot_mods;
  static bool has_status_changed = true;

  if ( current_mods != get_mods() || current_host_leds != host_keyboard_leds() || current_oneshot_mods != get_oneshot_mods()) {
    has_status_changed = true;
    current_mods = get_mods();
    current_host_leds = host_keyboard_leds();
    current_oneshot_mods = get_oneshot_mods();
  }
  if (has_status_changed) {
    has_status_changed = false;

    if (current_mods & MODS_SHIFT_MASK || current_host_leds & (1<<USB_LED_CAPS_LOCK) || current_oneshot_mods & MODS_SHIFT_MASK) {
      rgblight_sethsv_at(0, 255, 255, 5);
      rgblight_sethsv_at(0, 255, 255, 10);
    } else {
      rgblight_sethsv_default_helper(5);
      rgblight_sethsv_default_helper(10);
    }
    if (current_mods & MODS_CTRL_MASK || current_oneshot_mods & MODS_CTRL_MASK) {
      rgblight_sethsv_at(51, 255, 255, 6);
      rgblight_sethsv_at(51, 255, 255, 9);
    } else {
      rgblight_sethsv_default_helper(6);
      rgblight_sethsv_default_helper(9);
    }
    if (current_mods & MODS_GUI_MASK || current_oneshot_mods & MODS_GUI_MASK) {
      rgblight_sethsv_at(120, 255, 255, 7);
      rgblight_sethsv_at(120, 255, 255, 8);
    } else {
      rgblight_sethsv_default_helper(7);
      rgblight_sethsv_default_helper(8);

    }
  }
}
#endif
