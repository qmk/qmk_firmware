#include QMK_KEYBOARD_H
#include "xulkal.h"

#include "muse.h"

#define EXPAND_LAYOUT(...) LAYOUT_preonic_grid(__VA_ARGS__)

// Define your non-alpha grouping in this define's LAYOUT, and all your BASE_LAYERS will share the same mod/macro columns

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty Layout
   * ,------------------------------------------------.  ,------------------------------------------------.
   * | GESC |   1  |   2  |  3   |  4   |  5   |   -  |  |   =  |  6   |  7   |  8   |  9   |  0   | BkSp |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |  E   |  R   |  T   |   [  |  |   ]  |  Y   |  U   |  I   |  O   |  P   |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |FN(CAPS)| A  |   S  |   D  |  F   |  G   |   `  |  |   '  |  H   |  J   |  K   |  L   |  ;   | Enter|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Sft[ |   Z  |   X  |   C  |  V   |  B   | RGB  |  |RGBRST|  N   |  M   |  ,   |  .   |  /   | Sft] |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Win | LOWER| RAISE| Alt  | Space|RGBRMOD| |RGBMOD| Space| Left |  Up  | Down | Right| Ctrl |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Space| DEL  |  | Enter| Space|
   *                                    `-------------'  `-------------'
   */
  [_QWERTY] = EXPAND_LAYOUT( \
    _________________QWERTY_L1_________________,  _________________QWERTY_R1_________________, \
    _________________QWERTY_L2_________________,  _________________QWERTY_R2_________________, \
    _________________QWERTY_L3_________________,  _________________QWERTY_R3_________________, \
    _________________QWERTY_L4_________________,  _________________QWERTY_R4_________________, \
    _________________QWERTY_L5_________________,  _________________QWERTY_R5_________________ \
  ),

#ifndef GAMELAYER_DISABLE
  [_GAME] = EXPAND_LAYOUT( \
    ___________________GAME_L1_________________,  ___________________GAME_R1_________________, \
    ___________________GAME_L2_________________,  ___________________GAME_R2_________________, \
    ___________________GAME_L3_________________,  ___________________GAME_R3_________________, \
    ___________________GAME_L4_________________,  ___________________GAME_R4_________________, \
    ___________________GAME_L5_________________,  ___________________GAME_R5_________________ \
  ),
#endif

  [_LOWER] =  EXPAND_LAYOUT( \
    __________________LOWER_L1_________________,  __________________LOWER_R1_________________, \
    __________________LOWER_L2_________________,  __________________LOWER_R2_________________, \
    __________________LOWER_L3_________________,  __________________LOWER_R3_________________, \
    __________________LOWER_L4_________________,  __________________LOWER_R4_________________, \
    __________________LOWER_L5_________________,  __________________LOWER_R5_________________ \
  ),

  [_RAISE] = EXPAND_LAYOUT( \
    __________________RAISE_L1_________________,  __________________RAISE_R1_________________, \
    __________________RAISE_L2_________________,  __________________RAISE_R2_________________, \
    __________________RAISE_L3_________________,  __________________RAISE_R3_________________, \
    __________________RAISE_L4_________________,  __________________RAISE_R4_________________, \
    __________________RAISE_L5_________________,  __________________RAISE_R5_________________ \
  ),

#ifdef TRILAYER_ENABLED
  [_ADJUST] = EXPAND_LAYOUT( \
    _________________ADJUST_L1_________________,  _________________ADJUST_R1_________________, \
    _________________ADJUST_L2_________________,  _________________ADJUST_R2_________________, \
    _________________ADJUST_L3_________________,  _________________ADJUST_R3_________________, \
    _________________ADJUST_L4_________________,  _________________ADJUST_R4_________________, \
    _________________ADJUST_L5_________________,  _________________ADJUST_R5_________________ \
  ),
#endif
};

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
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
    return true;
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
