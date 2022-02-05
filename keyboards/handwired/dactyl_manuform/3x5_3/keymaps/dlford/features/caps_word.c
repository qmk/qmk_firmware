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
// https://getreuer.info/posts/keyboards/caps-word

#include "caps_word.h"
bool caps_word_enabled = false;

bool process_caps_word(uint16_t keycode, keyrecord_t* record) {
  static bool shifted = false;

  if (!caps_word_enabled) {
    // Pressing both shift keys at the same time enables caps word.
    if (((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)
        == MOD_MASK_SHIFT) {
      clear_mods();
      clear_oneshot_mods();
      shifted = false;
      caps_word_enabled = true;
      return false;
    }
    return true;
  }

  if (!record->event.pressed) { return true; }

  if (!((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT)) {
    switch (keycode) {
      case QK_MOD_TAP ... QK_MOD_TAP_MAX:
      case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        // Earlier return if this has not been considered tapped yet.
        if (record->tap.count == 0) { return true; }
        // Get the base tapping keycode of a mod- or layer-tap key.
        keycode &= 0xff;
    }

    switch (keycode) {
      // Letter keys should be shifted.
      case KC_A ... KC_Z:
        if (!shifted) { register_code(KC_LSFT); }
        shifted = true;
        return true;

      // Keycodes that continue caps word but shouldn't get shifted.
      case KC_1 ... KC_0:
      case KC_BSPC:
      case KC_MINS:
      case KC_UNDS:
        if (shifted) { unregister_code(KC_LSFT); }
        shifted = false;
        return true;

      // Any other keycode disables caps word.
    }
  }

  // Disable caps word.
  caps_word_enabled = false;
  if (shifted) { unregister_code(KC_LSFT); }
  shifted = false;
  return true;
}

