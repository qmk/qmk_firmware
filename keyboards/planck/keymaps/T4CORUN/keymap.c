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


#include "T4CORUN.h"
#include "muse.h"
#include "version.h"

#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_4x12_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_ortho_4x12_wrapper( \
    K01,     K02,     K03,     K04,     K05,     _____NONE_2_____, K06,     K07,     K08,     K09,     K0A, \
    K11,     K12,     K13,     K14,     K15,     _____NONE_2_____, K16,     K17,     K18,     K19,     K1A, \
    K21,     K22,     K23,     K24,     K25,     _____NONE_2_____, K26,     K27,     K28,     K29,     K2A, \
    _________NONE_3__________, _________BASE_L3_________, _________BASE_R3_________, _____NONE_2_____, KC_ESC \
  )
#define LAYOUT_base_wrapper(...)       LAYOUT_ortho_4x12_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Review $qmkroot\users\T4CORUN\wrappers.h for definitions

    [_DEFAULT_LAYER_1] = LAYOUT_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_DEFAULT_LAYER_2] = LAYOUT_base_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),

    [_NUMBER] = LAYOUT_ortho_4x12_wrapper(
      //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        _______________NUMBER_PAD_L1_______________, _____NONE_2_____, _______________NUMBER_PAD_R1_______________,
        _______________NUMBER_PAD_L2_______________, _____NONE_2_____, _______________NUMBER_PAD_R2_______________,
        _______________NUMBER_PAD_L3_______________, _____NONE_2_____, _______________NUMBER_PAD_R3_______________,
        _________NONE_3__________, ______NUMBER_PAD_L4______, ______NUMBER_PAD_R4______, _____NONE_2_____, KC_ESC
    ),

    [_NAVIGATION] = LAYOUT_ortho_4x12_wrapper(
      //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        _______________NAVIGATION_L1_______________, _____NONE_2_____, _______________NAVIGATION_R1_______________,
        _______________NAVIGATION_L2_______________, _____NONE_2_____, _______________NAVIGATION_R2_______________,
        _______________NAVIGATION_L3_______________, _____NONE_2_____, _______________NAVIGATION_R3_______________,
        _________NONE_3__________, ______NAVIGATION_L4______, ______NAVIGATION_R4______, _____NONE_2_____, KC_ESC
    ),

    [_FUNCTION] = LAYOUT_ortho_4x12_wrapper(
      //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ______________FUNCTION_PAD_L1______________, _____NONE_2_____, ______________FUNCTION_PAD_R1______________,
        ______________FUNCTION_PAD_L2______________, _____NONE_2_____, ______________FUNCTION_PAD_R2______________,
        ______________FUNCTION_PAD_L3______________, _____NONE_2_____, ______________FUNCTION_PAD_R3______________,
        _________NONE_3__________, _____FUNCTION_PAD_L4_____, _____FUNCTION_PAD_R4_____, _____NONE_2_____, KC_ESC
    ),

    [_MOUSE] = LAYOUT_ortho_4x12_wrapper(
      //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        _________________MOUSE_L1__________________, _____NONE_2_____, _________________MOUSE_R1__________________,
        _________________MOUSE_L2__________________, _____NONE_2_____, _________________MOUSE_R2__________________,
        _________________MOUSE_L3__________________, _____NONE_2_____, _________________MOUSE_R3__________________,
        _________NONE_3__________, ________MOUSE_L4_________, ________MOUSE_R4_________, _____NONE_2_____, KC_ESC
    ),

    [_ADJUST] = LAYOUT_ortho_4x12_wrapper(
      //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        _________________ADJUST_L1_________________, _____NONE_2_____, _________________ADJUST_R1_________________,
        _________________ADJUST_L2_________________, _____NONE_2_____, _________________ADJUST_R2_________________,
        _________________ADJUST_L3_________________, _____NONE_2_____, _________________ADJUST_R3_________________,
        _________NONE_3__________, ________ADJUST_L4________, ________ADJUST_R4________, _____NONE_2_____, KC_ESC
    )

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float lower_song[][2]  = SONG(CAPS_LOCK_ON_SOUND);
  float raise_song[][2]  = SONG(NUM_LOCK_ON_SOUND);
  float fn_song[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
  float adjust_song[][2]  = SONG(UNICODE_WINDOWS);
  float default_sound[][2]  = SONG(AG_NORM_SOUND);  
#endif


layer_state_t layer_state_set_user(layer_state_t state) {
  #ifdef AUDIO_ENABLE
    switch (get_highest_layer(state)) {
      case _NUMBER:
        stop_all_notes();
        PLAY_SONG(lower_song);
        break;
      case _NAVIGATION:
        stop_all_notes();
        PLAY_SONG(default_sound);
        break;
      case _FUNCTION:
        stop_all_notes();
        PLAY_SONG(fn_song);
        break;
      case _MOUSE:
        stop_all_notes();
        PLAY_SONG(default_sound);
        break;
      case _ADJUST:
        stop_all_notes();
        PLAY_SONG(adjust_song);
        break;
      default:
        stop_all_notes();
        PLAY_SONG(default_sound);
        break;
    }
  #endif
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("Mode Switch to QWERTY\n");
        default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case CLMAKDH:
      if (record->event.pressed) {
        print("Mode Switch to COLEMAK DH\n");
        default_layer_set(1UL<<_COLEMAK_DH);
      }
      return false;
      break;
    /*
    case KC_ENT:
      if (record->event.pressed) {
        print("Pressed Enter\n");
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(caps_sound);
        #endif
      }
      return true;
      break;
      */
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

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
    //add all the keys that would be on your base layer that are not defaults. If we don't do this then the sounds do not play
    //Layer Taps do add delays to sounds. Probably the mod Taps too
    case FUN_Z:
    case AD_SLSH:
    case MOU_SPC:
    case NAV_TAB:
    case NUM_BSP:
      return false;
    default:
      return true;
  }
}
