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

#define LAYOUT_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Review $qmkroot\users\T4CORUN\wrappers.h for definitions
  [_DEFAULT_LAYER_1] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    _________________QWERTY_L1_________________, ___x___, ___x___, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, ___x___, ___x___, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, ___x___, ___x___, _________________QWERTY_R3_________________,
    ___x___, ___x___, _________BASE_L4_________, ___x___, ___x___, _________BASE_R4_________, ___x___, KC_ESC
  ),

  [_DEFAULT_LAYER_2] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ________________COLEMAKDH_L1_______________, ___x___, ___x___, ________________COLEMAKDH_R1_______________,
    ________________COLEMAKDH_L2_______________, ___x___, ___x___, ________________COLEMAKDH_R2_______________,
    ________________COLEMAKDH_L3_______________, ___x___, ___x___, ________________COLEMAKDH_R3_______________,
    ___x___, ___x___, _________BASE_L4_________, ___x___, ___x___, _________BASE_R4_________, ___x___, KC_ESC
  ),

#if defined(GAMELAYER_ENABLE)
  [_DEFAULT_LAYER_3] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______________GAMING_BASE_L1______________, ___x___, ___x___, _______________GAMING_BASE_R1______________,
    _______________GAMING_BASE_L2______________, ___x___, ___x___, _______________GAMING_BASE_R2______________,
    _______________GAMING_BASE_L3______________, ___x___, ___x___, _______________GAMING_BASE_R3______________,
    ___x___, ___x___, ______GAMING_BASE_L4_____, ___x___, ___x___, ______GAMING_BASE_R4_____, ___x___, KC_ESC 
  ),
#endif //GAMELAYER_ENABLE

  [_NUMBER] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    _________________NUMPAD_L1_________________, ___x___, ___x___, _________________NUMPAD_R1_________________,
    _________________NUMPAD_L2_________________, ___x___, ___x___, _________________NUMPAD_R2_________________,
    _________________NUMPAD_L3_________________, ___x___, ___x___, _________________NUMPAD_R3_________________,
    ___x___, ___x___, ________NUMPAD_L4________, ___x___, ___x___, ________NUMPAD_R4________, ___x___, KC_ESC
  ),

  [_NAVIGATION] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ___________________NAV_L1__________________, ___x___, ___x___, ___________________NAV_R1__________________,
    ___________________NAV_L2__________________, ___x___, ___x___, ___________________NAV_R2__________________,
    ___________________NAV_L3__________________, ___x___, ___x___, ___________________NAV_R3__________________,
    ___x___, ___x___, __________NAV_L4_________, ___x___, ___x___, __________NAV_R4_________, ___x___, KC_ESC
  ),

  [_FUNCTION] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    _________________FUNCPAD_L1________________, ___x___, ___x___, _________________FUNCPAD_R1________________,
    _________________FUNCPAD_L2________________, ___x___, ___x___, _________________FUNCPAD_R2________________,
    _________________FUNCPAD_L3________________, ___x___, ___x___, _________________FUNCPAD_R3________________,
    ___x___, ___x___, ________FUNCPAD_L4_______, ___x___, ___x___, ________FUNCPAD_R4_______, ___x___, KC_ESC
  ),

#if defined(MOUSELAYER_ENABLE)
  [_MOUSE] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    __________________MOUSE_L1_________________, ___x___, ___x___, __________________MOUSE_R1_________________,
    __________________MOUSE_L2_________________, ___x___, ___x___, __________________MOUSE_R2_________________,
    __________________MOUSE_L3_________________, ___x___, ___x___, __________________MOUSE_R3_________________,
    ___x___, ___x___, _________MOUSE_L4________, ___x___, ___x___, _________MOUSE_R4________, ___x___, KC_ESC
  ),
#endif //MOUSELAYER_ENABLE

#if defined(GAMELAYER_ENABLE)
  [_GAMENUMBER] = LAYOUT_wrapper(
    _______________GAMING_NUM_L1_______________, ___x___, ___x___, _______________GAMING_BASE_R1______________,
    _______________GAMING_NUM_L2_______________, ___x___, ___x___, _______________GAMING_BASE_R2______________,
    _______________GAMING_NUM_L3_______________, ___x___, ___x___, _______________GAMING_BASE_R3______________,
    ___x___, ___x___, ______GAMING_NUM_L4______, ___x___, ___x___, ______GAMING_BASE_R4_____, ___x___, KC_ESC
  ),
#endif //GAMELAYER_ENABLE

  [_ADJUST] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    _________________ADJUST_L1_________________, ___x___, ___x___, _________________ADJUST_R1_________________,
    _________________ADJUST_L2_________________, ___x___, ___x___, _________________ADJUST_R2_________________,
    _________________ADJUST_L3_________________, ___x___, ___x___, _________________ADJUST_R3_________________,
    ___x___, ___x___, ________ADJUST_L4________, ___x___, ___x___, ________ADJUST_R4________, ___x___, KC_ESC
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
    case MOU_C:
    case FUN_Z:
    case AD_SLSH:
    case MOU_TOG:
      return false;
    default:
      return true;
  }
}
