// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/select-word

#include "select_word.h"

// Mac users, uncomment this line:
// #define MAC_HOTKEYS

enum { STATE_NONE, STATE_SELECTED, STATE_WORD, STATE_FIRST_LINE, STATE_LINE };

bool process_select_word(uint16_t keycode, keyrecord_t* record,
                         uint16_t sel_keycode) {
  static uint8_t state = STATE_NONE;

  if (keycode == KC_LSFT || keycode == KC_RSFT) { return true; }

  if (keycode == sel_keycode && record->event.pressed) {  // On key press.
    const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    const uint8_t all_mods = mods | get_oneshot_mods();
#else
    const uint8_t all_mods = mods;
#endif  // NO_ACTION_ONESHOT
    if ((all_mods & MOD_MASK_SHIFT) == 0) {  // Select word.
#ifdef MAC_HOTKEYS
      register_code(KC_LALT);
#else
      register_code(KC_LCTL);
#endif  // MAC_HOTKEYS
      if (state == STATE_NONE) {
        tap_code(KC_RGHT);
        tap_code(KC_LEFT);
      }
      register_code(KC_LSFT);
      register_code(KC_RGHT);
      state = STATE_WORD;
    } else {  // Select line.
      if (state == STATE_NONE) {
        clear_mods();
#ifndef NO_ACTION_ONESHOT
        clear_oneshot_mods();
#endif  // NO_ACTION_ONESHOT
#ifdef MAC_HOTKEYS
        register_code16(LCTL(KC_A));
        tap_code16(LSFT(KC_E));
        unregister_code16(LCTL(KC_A));
#else
        tap_code(KC_HOME);
        tap_code16(LSFT(KC_END));
#endif  // MAC_HOTKEYS
        set_mods(mods);
        state = STATE_FIRST_LINE;
      } else {
        register_code(KC_DOWN);
        state = STATE_LINE;
      }
    }
    return false;
  }

  // `sel_keycode` was released, or another key was pressed.
  switch (state) {
    case STATE_WORD:
      unregister_code(KC_RGHT);
      unregister_code(KC_LSFT);
#ifdef MAC_HOTKEYS
      unregister_code(KC_LALT);
#else
      unregister_code(KC_LCTL);
#endif  // MAC_HOTKEYS
      state = STATE_SELECTED;
      break;

    case STATE_FIRST_LINE:
      state = STATE_SELECTED;
      break;

    case STATE_LINE:
      unregister_code(KC_DOWN);
      state = STATE_SELECTED;
      break;

    case STATE_SELECTED:
      if (keycode == KC_ESC) {
        tap_code(KC_RGHT);
        state = STATE_NONE;
        return false;
      }
      // Fallthrough.
    default:
      state = STATE_NONE;
  }

  return true;
}
