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

#include "orthodox.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _COLEMAK 1
#define _QWERTY  2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  COLEMAK,
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
};

//Tap Dance Declarations
enum {
  TD_LOWER_ADJUST = 0
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LS__SPC MT(MOD_LSFT, KC_SPC)
#define LW__ADJ TD(TD_LOWER_ADJUST)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_DVORAK] = KEYMAP( \
  KC_ESC,  KC_QUOT, KC_COMM, KC_DOT, KC_P,    KC_Y,                                                                     KC_F,    KC_G,   KC_C,  KC_R,   KC_L,    KC_SLSH, \
  KC_TAB,  KC_A,    KC_O,    KC_E,   KC_U,    KC_I,    KC_ENT,  XXXXXXX, KC_LALT,           KC_DEL,   XXXXXXX, KC_LGUI, KC_D,    KC_H,   KC_T,  KC_N,   KC_S,    KC_MINS, \
  KC_EQL,  KC_SCLN, KC_Q,    KC_J,   KC_K,    KC_X,    LW__ADJ,   KC_LSFT, KC_LCTL,           KC_BSPC, LS__SPC,  RAISE,   KC_B,    KC_M,   KC_W,  KC_V,   KC_Z,    KC_BSLS, \
),

[_QWERTY] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT, XXXXXXX, KC_DOWN,          KC_UP,   XXXXXXX, KC_RIGHT,KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LW__ADJ,   KC_BSPC, KC_ENT,           KC_RALT, LS__SPC, RAISE,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LGUI \
),

[_LOWER] = KEYMAP( \
  _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR,                                                                _______, KC_P7, KC_P8, KC_P9, KC_PMNS, _______, \
  _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR,   _______, XXXXXXX, _______,          _______, XXXXXXX, _______, _______, KC_P4, KC_P5, KC_P6, KC_PPLS, _______, \
  _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, _______, _______, _______, _______,          _______, _______, KC_KP_0, _______, KC_P1, KC_P2, KC_P3, KC_PENT, _______, \
),

[_RAISE] = KEYMAP( \
  _______, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP,                                                                  KC_VOLU, KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,\
  KC_CAPS, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,   _______, XXXXXXX, _______,          _______, XXXXXXX, _______, KC_VOLD, KC_F4,   KC_F5,   KC_F6,   KC_F11,  XXXXXXX,\
  XXXXXXX, KC_NLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______, _______, _______,          _______, _______, _______,  KC_MUTE, KC_F1,   KC_F2,   KC_F3,   KC_F12,  XXXXXXX,\
),

[_ADJUST] =  KEYMAP( \
  _______, RESET,   _______, _______, _______, _______,                                                                _______, _______, _______, _______, _______, KC_DEL,  \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, _______, XXXXXXX, _______,          _______, XXXXXXX, _______, AG_SWAP, QWERTY , COLEMAK, DVORAK,  _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}



//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_LOWER_ADJUST]  = ACTION_TAP_DANCE_DOUBLE(LOWER, ADJUST)
// Other declarations would go here, separated by commas, if you have them
};

//In Layer declaration, add tap dance item in place of a key code
//TD(TD_LOWER_ADJUST)
