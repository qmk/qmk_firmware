/* Copyright 2015-2021 Jack Humbert
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
#include "os_detection.h"

#ifdef AUDIO_ENABLE
#    include "muse.h"
#endif

#include "twpair_on_jis.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;

enum planck_layers {
  _WIN,
  _MAC,
  _NAGINATA,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum planck_keycodes {
  QWERTY = NG_SAFE_RANGE,
  BACKLIT,
  EXT_PLV
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_WIN] = LAYOUT_planck_grid(
          KC_TAB,  KC_K   ,KC_D   ,KC_N    ,KC_F   ,KC_Q,    KC_J   ,KC_BSPC,KC_R   ,KC_U   ,KC_P,    KC_QUOT,
    CTL_T(KC_ESC), KC_W   ,KC_I   ,KC_S    ,KC_A   ,KC_G,    KC_Y   ,KC_E   ,KC_T   ,KC_H   ,KC_B    ,KC_SCLN,
          KC_LSFT, KC_Z   ,KC_X   ,KC_V    ,KC_C   ,KC_L,    KC_M   ,KC_O   ,KC_COMM,KC_DOT ,KC_SLSH ,KC_UP ,
          KC_LCTL, KC_LALT,KC_LWIN,LOWER   ,XXXXXXX,LSFT_T(KC_SPC)  ,XXXXXXX,LSFT_T(KC_ENT) ,RAISE   ,KC_LEFT,KC_DOWN, KC_RGHT
),

[_MAC] = LAYOUT_planck_grid(
          KC_TAB,  KC_K   ,KC_D   ,KC_N    ,KC_F   ,KC_Q,    KC_J   ,KC_BSPC,KC_R   ,KC_U   ,KC_P,    KC_QUOT,
    CMD_T(KC_ESC), KC_W   ,KC_I   ,KC_S    ,KC_A   ,KC_G,    KC_Y   ,KC_E   ,KC_T   ,KC_H   ,KC_B    ,KC_SCLN,
          KC_LSFT, KC_Z   ,KC_X   ,KC_V    ,KC_C   ,KC_L,    KC_M   ,KC_O   ,KC_COMM,KC_DOT ,KC_SLSH ,KC_UP ,
          KC_LCTL, KC_LALT,KC_LGUI,LOWER   ,XXXXXXX,LSFT_T(KC_SPC)  ,XXXXXXX,LSFT_T(KC_ENT) ,RAISE   ,KC_LEFT,KC_DOWN, KC_RGHT
),

[_LOWER] = LAYOUT_planck_grid(
    _______ ,XXXXXXX ,XXXXXXX ,KC_COLN ,KC_SCLN ,XXXXXXX ,KC_SLSH ,KC_7   ,KC_8   ,KC_9   ,KC_MINS ,KC_DEL , \
    _______ ,XXXXXXX ,KC_LBRC ,KC_LCBR ,KC_LPRN ,KC_LT   ,KC_ASTR ,KC_4   ,KC_5   ,KC_6   ,KC_PLUS ,_______, \
    _______ ,XXXXXXX ,KC_RBRC ,KC_RCBR ,KC_RPRN ,KC_GT   ,KC_0    ,KC_1   ,KC_2   ,KC_3   ,KC_EQL  ,_______, \
    _______, _______, _______, _______, _______, _______, _______, _______,_______,_______ ,_______, _______
),

[_RAISE] = LAYOUT_planck_grid(
    _______   ,KC_TILD   ,KC_AT     ,KC_HASH   ,KC_DLR    ,XXXXXXX,   XXXXXXX   ,KC_HOME   ,KC_UP     ,KC_END    ,XXXXXXX   ,KC_DEL    , \
    _______   ,KC_CIRC   ,KC_AMPR   ,KC_QUES   ,KC_PERC   ,KC_INT3,   XXXXXXX   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,XXXXXXX   ,XXXXXXX   , \
    _______   ,KC_GRV    ,KC_PIPE   ,KC_EXLM   ,KC_UNDS   ,LALT(KC_INT3),XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,_______   , \
    _______, _______, _______, _______, _______, _______, _______, _______, _______,_______ ,_______, _______
),

[_ADJUST] = LAYOUT_planck_grid(
    _______,  EE_CLR, QK_BOOT, _______, _______, _______, NG_TAYO, NGSW_WIN, _______, _______, _______, _______ ,
    _______, _______, KC_SLEP, _______, _______, _______, NG_KOTI, NGSW_MAC,  NG_MLV, _______, _______, _______,
    _______, _______, KC_WAKE, _______, _______, _______, NG_SHOS, NGSW_LNX, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

  [_NAGINATA] = LAYOUT_planck_grid(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______, \
    _______,_______,_______,_______,XXXXXXX,NG_SHFT,XXXXXXX,NG_SHFT2,_______,_______,_______,_______
  ),


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
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_WIN);
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

    // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  // typewriter pairing on jis keyboard
  if (!twpair_on_jis(keycode, record))
    return false;
  
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

void keyboard_post_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_Y, KC_E};
  uint16_t ngoffkeys[] = {KC_A, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式

  wait_ms(400);
  switch (detected_host_os()) {
    case OS_WINDOWS:
      layer_move(_WIN);
      switchOS(NG_WIN);
      break;
    case OS_MACOS:
    case OS_IOS:
      layer_move(_MAC);
      switchOS(NG_MAC);
      break;
    case OS_LINUX:
      layer_move(_WIN);
      switchOS(NG_LINUX);
      break;
    default:
      layer_move(_WIN);
      switchOS(NG_WIN);
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
