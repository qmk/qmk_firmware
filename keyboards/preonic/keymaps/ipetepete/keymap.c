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
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _GAMER,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _SPCFN,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  GAMER,
  COLEMAK,
  LOWER,
  RAISE,
  SPCFN,
  BACKLIT,
  ESCCTRL
};

#define MEDIA_KEY_DELAY 10

#define ESCCTRL CTL_T(KC_ESC)
#define KC_SPFN LT(_SPCFN, KC_SPC) // press for space, hold for function layer (aka spacefn)
#define HYPER MT(MOD_HYPR, KC_ENT)
#define ENTSFT SFT_T(KC_ENT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  \
  ESCCTRL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,\
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ENTSFT,  \
  KC_RALT, KC_LCTRL, KC_LGUI, KC_LALT, LOWER,   KC_SPFN, KC_SPFN, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

[_GAMER] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  BACKLIT, KC_LCTRL, KC_LGUI, KC_LALT, LOWER,   KC_SPC, KC_SPC, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),
[_COLEMAK] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______,  KC_Q,    KC_W,   KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______, \
  _______,  KC_A,    KC_R,   KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______, \
  _______,  KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    _______, _______, _______, _______, \
  KC_RALT, KC_LCTRL, KC_LGUI, KC_LALT, LOWER,   KC_SPFN, KC_SPFN, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),
[_SPCFN] = LAYOUT_preonic_grid( \
_______, _______, _______, _______, _______, _______, _______, _______,_______,KC_MINS,  KC_EQL, KC_DEL,   \
KC_GRV,  _______, _______, KC_PGUP, _______, KC_LBRC, KC_RBRC, _______, KC_UP,   _______, _______, _______,\
_______, _______, KC_HOME, KC_PGDN, KC_END,  KC_LCBR, KC_RCBR, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______,\
_______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, _______, _______, _______, _______, _______,\
_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),
[_RAISE] = LAYOUT_preonic_grid( \
  KC_HOME,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_END, \
  KC_TILD, KC_F11,   KC_F2,   KC_F13, _______,  _______, _______,_______, _______, _______, _______, _______,\
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PIPE, KC_BSLS, KC_MINS, KC_PLUS, KC_LPRN, KC_RPRN, KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

[_LOWER] = LAYOUT_preonic_grid( \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,   _______, \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_PIPE, KC_BSLS,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,  \
  _______, _______, _______, _______, _______, _______, _______, _______,  KC_RGUI, KC_RALT, KC_RCTL, HYPER   \
),
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, QWERTY,  GAMER,   COLEMAK, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  RESET,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DEBUG\
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case GAMER:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_GAMER);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
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
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            PORTE &= ~(1<<6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            PORTE |= (1<<6);
            #endif
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  uint16_t held_keycode_timer = timer_read();

  switch(biton32(layer_state)){
    case _LOWER:
      if(clockwise){
        tap_code(KC_MNXT);
      }else{
        tap_code(KC_MPRV);

      }
      break;
    case _RAISE:
      if (muse_mode) {
          if (clockwise) {
            muse_offset++;
          } else {
            muse_offset--;
          }
      }else{
        if(clockwise){
          register_code(KC_PGUP);
          while(timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){
            // noop
          }
          unregister_code(KC_PGUP);
        }else{
        tap_code();
          }
        }
      break;
    case _SPCFN:
      if(clockwise){
        tap_code(KC_WH_U);
      }else{
        tap_code(KC_WH_D);
      }
      break;
    default:
      if (clockwise) {
        register_code(KC_VOLU);
        while(timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){
          // noop
        }
        unregister_code(KC_VOLU);
      } else {
        register_code(KC_VOLD);
        while(timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){
          // noop
        }
        unregister_code(KC_VOLD);
      }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
