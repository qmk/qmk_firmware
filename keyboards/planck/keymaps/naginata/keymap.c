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

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

extern keymap_config_t keymap_config;

enum planck_layers {
  _WORKMAN,
  _QWERTY,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _EDIT1R,
  _EDIT1L,
  _EDIT2R,
  _EDIT2L,
  _LOWER,
  _RAISE,
  _NUMBER,
  _ADJUST,
};

enum planck_keycodes {
  WORKMAN = NG_SAFE_RANGE,
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
};

// 薙刀式
enum combo_events {
  NAGINATA_ON_CMB,
  NAGINATA_OFF_CMB,
  EDITR1_CMB,
  EDITL1_CMB,
  EDITR2_CMB,
  EDITL2_CMB,
  ENTER_CMB,
};

#if defined(DWORKMAN)
const uint16_t PROGMEM ngon_combo[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_I, KC_U, COMBO_END};
const uint16_t PROGMEM editr1_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM editl1_combo[] = {KC_T, KC_K, COMBO_END};
const uint16_t PROGMEM editr2_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM editl2_combo[] = {KC_H, KC_J, COMBO_END};
#else
const uint16_t PROGMEM ngon_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_F, KC_G, COMBO_END};
#endif
const uint16_t PROGMEM enter_combo[] = {KC_V, KC_H, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [NAGINATA_ON_CMB] = COMBO_ACTION(ngon_combo),
  [NAGINATA_OFF_CMB] = COMBO_ACTION(ngoff_combo),
  [EDITR1_CMB] = COMBO_ACTION(editr1_combo),
  [EDITL1_CMB] = COMBO_ACTION(editl1_combo),
  [EDITR2_CMB] = COMBO_ACTION(editr2_combo),
  [EDITL2_CMB] = COMBO_ACTION(editl2_combo),
  [ENTER_CMB] = COMBO(enter_combo, KC_ENT),
};
// 薙刀式

// 薙刀式
// IME ONのcombo
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case NAGINATA_ON_CMB:
      if (pressed) {
        naginata_on();
      }
      break;
    case NAGINATA_OFF_CMB:
      if (pressed) {
        naginata_off();
      }
      break;
    case EDITR1_CMB:
      if (pressed) {
        layer_on(_EDIT1R);
      } else {
        layer_off(_EDIT1R);
      }
      break;
    case EDITL1_CMB:
      if (pressed) {
        layer_on(_EDIT1L);
      } else {
        layer_off(_EDIT1L);
      }
      break;
    case EDITR2_CMB:
      if (pressed) {
        layer_on(_EDIT2R);
      } else {
        layer_off(_EDIT2R);
      }
      break;
    case EDITL2_CMB:
      if (pressed) {
        layer_on(_EDIT2L);
      } else {
        layer_off(_EDIT2L);
      }
      break;
  }
}
// 薙刀式

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
/* _WORKMAN
  +------+------+------+------+------+------+------+------+------+------+------+------+
  | ESC  |  Q   |  D   |  R   |  W   |  B   |  J   |  F   |  U   |  P   |  ;   | BSPC |
  +------+------+------+------+------+------+------+------+------+------+------+------+
  | TAB  |  A   |  S   |  H   |  T   |  G   |  Y   |  N   |  E   |  O   |  I   | ENT  |
  +------+------+------+------+------+------+------+------+------+------+------+------+
  | ALPH |  Z   |  X   |  M   |  C   |  V   |  K   |  L   |  ,   |  .   |  /   |SALPH |
  +------+------+------+------+------+------+------+------+------+------+------+------+
  | LCMD |      |      |      |LOWER |SFTSPC|SFTSPC|RAISE |      |      |      | RCMD |
  +------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_WORKMAN] = LAYOUT_planck_grid(
    KC_ESC ,KC_Q   ,KC_D   ,KC_R   ,KC_W   ,KC_B   ,KC_J   ,KC_F   ,KC_U   ,KC_P   ,KC_SCLN,KC_BSPC, \
    KC_TAB ,KC_A   ,KC_S   ,KC_H   ,KC_T   ,KC_G   ,KC_Y   ,KC_N   ,KC_E   ,KC_O   ,KC_I   ,KC_ENT , \
    ALPH   ,KC_Z   ,KC_X   ,KC_M   ,KC_C   ,KC_V   ,KC_K   ,KC_L   ,KC_COMM,KC_DOT ,KC_SLSH,SALPH  , \
    KC_LCMD,XXXXXXX,XXXXXXX,XXXXXXX,LOWER  ,SFTSPC ,SFTSPC ,RAISE  ,XXXXXXX,XXXXXXX,XXXXXXX,KC_RCMD
  ),

/* _EDIT1L
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |G(Q) |G(W) |G(N) | F2  |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |G(Y) |G(S) |PGDN |PGUP |     | __  | __  |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |G(Z) |G(X) |G(C) |G(V) |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT1L] = LAYOUT_planck_grid(
    XXXXXXX,G(KC_Q),G(KC_W),G(KC_N),KC_F2  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,G(KC_Y),G(KC_S),KC_PGDN,KC_PGUP,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,G(KC_Z),G(KC_X),G(KC_C),G(KC_V),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _EDIT1R
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       | DELE  |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |  __   |  __   |G(LEFT)| LEFT  |S(LEFT)|  UP   |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |G(RGHT)| RGHT  |S(RGHT)| DOWN  |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_EDIT1R] = LAYOUT_planck_grid(
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,DELE      ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,_______   ,_______   ,G(KC_LEFT),KC_LEFT   ,S(KC_LEFT),KC_UP     ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,G(KC_RGHT),KC_RGHT   ,S(KC_RGHT),KC_DOWN   ,XXXXXXX   ,XXXXXXX   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

/* _EDIT2L
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |  ~  |  @  |  #  |  $  |  %  |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |  ^  |  &  |  !  |  ?  |  \  | __  | __  |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |  |  |  `  |  '  |  "  |  _  |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT2L] = LAYOUT_planck_grid(
    XXXXXXX,KC_TILD,KC_AT  ,KC_HASH,KC_DLR ,KC_PERC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,KC_CIRC,KC_AMPR,KC_EXLM,KC_QUES,KC_BSLS,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,KC_PIPE,KC_GRV ,KC_QUOT,KC_DQT ,KC_UNDS,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _EDIT2R
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |DELA |  +  |  -  |  =  |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     | __  | __  |  :  |  (  |  [  |  {  |  <  |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |  ;  |  )  |  ]  |  }  |  >  |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT2R] = LAYOUT_planck_grid(
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,DELA   ,KC_PLUS,KC_MINS,KC_EQL ,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,KC_COLN,KC_LPRN,KC_LBRC,KC_LCBR,KC_LT  ,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_SCLN,KC_RPRN,KC_RBRC,KC_RCBR,KC_GT  ,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _LOWER
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     | UP  |     |     |  /  |  7  |  8  |  9  |  -  |  :  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |LEFT |DOWN |RGHT |     |  *  |  4  |  5  |  6  |  +  |  .  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |  0  |  1  |  2  |  3  |  =  |  ,  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  |KANA2| __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_LOWER] = LAYOUT_planck_grid(
    XXXXXXX,XXXXXXX,XXXXXXX,KC_UP  ,XXXXXXX,XXXXXXX,KC_SLSH,KC_7   ,KC_8   ,KC_9   ,KC_MINS,KC_COLN, \
    XXXXXXX,XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT,XXXXXXX,KC_ASTR,KC_4   ,KC_5   ,KC_6   ,KC_PLUS,KC_DOT , \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_0   ,KC_1   ,KC_2   ,KC_3   ,KC_EQL ,KC_COMM, \
    _______,_______,_______,_______,_______,_______,KANA2  ,_______,_______,_______,_______,_______
  ),

/* _RAISE
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |  UP   |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       | LEFT  | DOWN  | RGHT  |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |S(LEFT)|       |S(RGHT)|       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   | EISU  |  __   |  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_RAISE] = LAYOUT_planck_grid(
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,KC_UP     ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,S(KC_LEFT),XXXXXXX   ,S(KC_RGHT),XXXXXXX   ,XXXXXXX   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,EISU      ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

/* _ADJUST
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |KC_WAKE|       | RESET |       |       |       |       |       |KC_PWR |EUCALYN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |EEP_RST|       |       |       |       |       |       |WORKMAN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |KC_SLEP|KC_CALC|       |       |       |       |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_ADJUST] = LAYOUT_planck_grid(
    XXXXXXX,XXXXXXX,KC_WAKE,XXXXXXX,RESET  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_PWR ,QWERTY, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,EEP_RST,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,WORKMAN, \
    XXXXXXX,XXXXXXX,KC_SLEP,KC_CALC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _NAGINATA
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   | NG_Q  | NG_W  | NG_E  | NG_R  | NG_T  | NG_Y  | NG_U  | NG_I  | NG_O  | NG_P  |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   | NG_A  | NG_S  | NG_D  | NG_F  | NG_G  | NG_H  | NG_J  | NG_K  | NG_L  |NG_SCLN|  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  | ALPH  | NG_Z  | NG_X  | NG_C  | NG_V  | NG_B  | NG_N  | NG_M  |NG_COMM|NG_DOT |NG_SLSH| SALPH |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   |NG_SHFT|NG_SHFT|  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_NAGINATA] = LAYOUT_planck_grid(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    ALPH   ,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,SALPH  , \
    _______,_______,_______,_______,_______,NG_SHFT,NG_SHFT,_______,_______,_______,_______,_______ \
  ),

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

static bool nstate = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
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
    case KANA2:
      if (record->event.pressed) {
        naginata_on();
      }
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        naginata_off();
      }
      return false;
      break;
    case ALPH:
      if (record->event.pressed) {
        nstate = naginata_state();
        if (nstate) naginata_off();
      } else {
        if (nstate) naginata_on();
      }
      break;
    case SALPH:
      if (record->event.pressed) {
        nstate = naginata_state();
        if (nstate) naginata_off();
        register_code(KC_LSFT);
      } else {
        unregister_code(KC_LSFT);
        if (nstate) naginata_on();
      }
      break;
  }

  // 薙刀式
  bool a = true;
  if (naginata_state()) {
    naginata_mode(keycode, record);
    a = process_naginata(keycode, record);
  }
  return a;
  // 薙刀式

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
  set_naginata(_NAGINATA);
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

