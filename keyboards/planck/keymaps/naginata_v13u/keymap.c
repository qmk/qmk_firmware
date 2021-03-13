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
#include "twpair_on_jis.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

extern keymap_config_t keymap_config;

enum planck_layers {
  _SRLBY,
  _SHIFT,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum planck_keycodes {
  SRLBY = NG_SAFE_RANGE,
  QWERTY,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  NUMBER,
  DELA,
  DELE,
  ALPH,
  SALPH,
  KANA2,
  EISU,
  LCTOGL,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SFTSPC  SFT_T(KC_SPC)
#define SFTENT  SFT_T(KC_ENT)

// 薙刀式
// 編集モードを追加する場合
#define KC(A) C(KC_##A)
#define KS(A) S(KC_##A)
#define KG(A) G(KC_##A)
// 薙刀式

#define DEG   UC(0x00B0)
#define DELTA UC(0x0394)
#define NTEQ  UC(0x2260)
#define NREQ  UC(0x2260)
#define MICRO UC(0x00B5)
#define EURO  UC(0x20AC)
#define LTE   UC(0x2264)
#define GTE   UC(0x2265)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_SRLBY] = LAYOUT_planck_grid(
    KC_TAB        ,KC_Q          ,KC_W          ,KC_E          ,KC_R          ,KC_T          ,KC_Y          ,KC_U          ,KC_I          ,KC_O          ,KC_P          ,KC_BSPC       , \
    CTL_T(KC_ESC) ,KC_A          ,KC_S          ,KC_D          ,KC_F          ,KC_G          ,KC_H          ,KC_J          ,KC_K          ,KC_L          ,KC_SCLN       ,KC_QUOT       , \
    KC_LSFT       ,KC_Z          ,KC_X          ,KC_C          ,KC_V          ,KC_B          ,KC_N          ,KC_M          ,KC_COMM       ,KC_DOT        ,KC_SLSH       ,KC_UP       , \
    KC_LCTL       ,KC_LALT       ,KC_LCMD       ,MO(_LOWER)    ,XXXXXXX       ,LSFT_T(KC_SPC),XXXXXXX       ,LSFT_T(KC_ENT),MO(_RAISE)    ,KC_LEFT       ,KC_DOWN       ,KC_RGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
    _______,KC(C)  ,XXXXXXX,KC_COLN,KC_SCLN,XXXXXXX,KC_SLSH,KC_7   ,KC_8   ,KC_9   ,KC_MINS,KC_DEL , \
    _______,KC(X)  ,KC_LBRC,KC_LCBR,KC_LPRN,KC_LT  ,KC_ASTR,KC_4   ,KC_5   ,KC_6   ,KC_PLUS,_______, \
    _______,KC(V)  ,KC_RBRC,KC_RCBR,KC_RPRN,KC_GT  ,KC_0   ,KC_1   ,KC_2   ,KC_3   ,KC_EQL ,_______, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

  [_RAISE] = LAYOUT_planck_grid(
    _______   ,KC_TILD   ,KC_AT     ,KC_HASH   ,KC_DLR    ,KC_PERC   ,XXXXXXX   ,KC_HOME   ,KC_UP     ,KC_END    ,XXXXXXX   ,KC_DEL    , \
    _______   ,KC_CIRC   ,KC_AMPR   ,KC_EXLM   ,KC_QUES   ,KC_JYEN   ,XXXXXXX   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,XXXXXXX   ,_______   , \
    _______   ,KC_PIPE   ,KC_GRV    ,KC_QUOT   ,KC_DQT    ,KC_UNDS   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,_______   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    _______,LCTOGL ,XXXXXXX,KC_MAIL,XXXXXXX,KC_WAKE,XXXXXXX,XXXXXXX,NG_MLV,NG_TAYO,NGSW_WIN  ,_______, \
    _______,XXXXXXX,KC_SLEP,XXXXXXX,XXXXXXX,RESET  ,XXXXXXX,XXXXXXX,XXXXXXX,NG_KOTI,NGSW_MAC ,_______, \
    _______,XXXXXXX,XXXXXXX,KC_CALC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,NG_SHOS,NGSW_LNX,_______, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
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

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// static bool nstate = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SRLBY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_SRLBY);
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
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
    // case KANA2:
    //   if (record->event.pressed) {
    //     naginata_on();
    //   }
    //   return false;
    //   break;
    // case EISU:
    //   if (record->event.pressed) {
    //     naginata_off();
    //   }
    //   return false;
    //   break;
    case LCTOGL:
      if (record->event.pressed) {
        mac_live_conversion_toggle();
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

void encoder_update(bool clockwise) {
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
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
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


void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式
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

