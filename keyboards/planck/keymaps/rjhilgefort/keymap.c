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


enum planck_layers {
  _MAC,
  _LINUX,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  MAC = SAFE_RANGE,
  LINUX,
  BACKLIT,
};

#define ALT_ESC ALT_T(KC_ESC)
#define CTL_ESC CTL_T(KC_ESC)
#define GUI_ESC GUI_T(KC_ESC)
#define HYPER LGUI(LSFT(KC_LALT))

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_MAC] = LAYOUT_planck_grid(
// ,-----------------------------------------------------------------------------------------------------------.
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______,   RAISE, ALT_ESC, KC_LGUI,  KC_SPC,  KC_SPC,   LOWER,   HYPER, _______, _______, _______
// ,-----------------------------------------------------------------------------------------------------------.
),

[_LINUX] = LAYOUT_planck_grid(
// ,-----------------------------------------------------------------------------------------------------------.
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     ALT_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______,   RAISE, GUI_ESC, KC_LCTL,  KC_SPC,  KC_SPC,   LOWER,   HYPER, _______, _______, _______
// ,-----------------------------------------------------------------------------------------------------------.
),

[_LOWER] = LAYOUT_planck_grid(
// ,-----------------------------------------------------------------------------------------------------------.
     _______, KC_BSLS, KC_SLSH, KC_LBRC, KC_RBRC, KC_TILD, KC_PIPE,  KC_EQL, KC_PLUS, KC_MINS, KC_UNDS, _______,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN,  KC_GRV, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// ,-----------------------------------------------------------------------------------------------------------.
),

[_RAISE] = LAYOUT_planck_grid(
// ,-----------------------------------------------------------------------------------------------------------.
     _______, _______, KC_BRID, KC_VOLU, KC_BRIU, _______, _______,    KC_7,    KC_8,    KC_9, KC_ASTR, _______,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,    KC_4,    KC_5,    KC_6, KC_PLUS, _______,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, KC_VOLD, _______, _______, _______,    KC_1,    KC_2,    KC_3, KC_BSLS, _______,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______, _______, _______,    KC_0,  KC_DOT, _______, _______
// ,-----------------------------------------------------------------------------------------------------------.
),

[_ADJUST] = LAYOUT_planck_grid(
// ,-----------------------------------------------------------------------------------------------------------.
     _______,     MAC,   LINUX, _______, _______, _______, _______, _______, _______, _______, _______, _______,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// ,-----------------------------------------------------------------------------------------------------------.
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MAC:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MAC);
      }
      return false;
      break;
    case LINUX:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LINUX);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
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
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
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
