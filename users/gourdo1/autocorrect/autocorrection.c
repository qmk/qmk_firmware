// Copyright 2021-2022 Google LLC
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
// https://getreuer.info/posts/keyboards/autocorrection

#include "autocorrection.h"

#include <string.h>
#include "autocorrection_data.h"

#if AUTOCORRECTION_MIN_LENGTH < 4
// Odd output or hard locks on the board have been observed when the min typo
// length is 3 or lower (https://github.com/getreuer/qmk-keymap/issues/2).
// Additionally, autocorrection entries for short typos are more likely to false
// trigger, so it is suggested that typos be at least 5 characters.
#error "Min typo length is less than 4. Autocorrection may behave poorly."
#endif

bool process_autocorrection(uint16_t keycode, keyrecord_t* record) {
    if (user_config.autocorrect) {
      static uint8_t typo_buffer[AUTOCORRECTION_MAX_LENGTH] = {0};
      static uint8_t typo_buffer_size = 0;

      // Ignore key release; we only process key presses.
      if (!record->event.pressed) { return true; }

    #ifndef NO_ACTION_ONESHOT
      const uint8_t mods = get_mods() | get_oneshot_mods();
    #else
      const uint8_t mods = get_mods();
    #endif  // NO_ACTION_ONESHOT
      // Disable autocorrection while a mod other than shift is active.
      if ((mods & ~MOD_MASK_SHIFT) != 0) {
        typo_buffer_size = 0;
        return true;
      }

      // The following switch cases address various kinds of keycodes. This logic is
      // split over two switches rather than merged into one. The first switch may
      // extract a basic keycode which is then further handled by the second switch,
      // e.g. a layer-tap key with Caps Lock `LT(layer, KC_CAPS)`.
      switch (keycode) {
    #ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:  // Tap-hold keys.
    #ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
    #endif  // NO_ACTION_LAYER
          // Ignore when tap-hold keys are held.
          if (record->tap.count == 0) { return true; }
          // Otherwise when tapped, get the basic keycode.
          // Fallthrough intended.
    #endif  // NO_ACTION_TAPPING

        // Handle shifted keys, e.g. symbols like KC_EXLM = S(KC_1).
        case QK_LSFT ... QK_LSFT + 255:
        case QK_RSFT ... QK_RSFT + 255:
          keycode &= 0xff;  // Get the basic keycode.
          break;

        // NOTE: Space Cadet keys expose no info to check whether they are being
        // tapped vs. held. This makes autocorrection ambiguous, e.g. KC_LCPO might
        // be '(', which we would treat as a word break, or it might be shift, which
        // we would treat as having no effect. To behave cautiously, we allow Space
        // Cadet keycodes to fall to the logic below and clear autocorrection state.
      }

      switch (keycode) {
        // Ignore shifts, Caps Lock, one-shot mods, and layer switch keys.
        case KC_NO:
        case KC_LSFT:
        case KC_RSFT:
        case KC_CAPS:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
          return true;  // Ignore these keys.
      }

      if (keycode == KC_QUOT) {
        // Treat " (shifted ') as a word boundary.
        if ((mods & MOD_MASK_SHIFT) != 0) { keycode = KC_SPC; }
      } else if (!(KC_A <= keycode && keycode <= KC_Z)) {
        if (keycode == KC_BSPC) {
          // Remove last character from the buffer.
          if (typo_buffer_size > 0) { --typo_buffer_size; }
          return true;
        } else if (KC_1 <= keycode && keycode <= KC_SLSH && keycode != KC_ESC) {
          // Set a word boundary if space, period, digit, etc. is pressed.
          // Behave more conservatively for the enter key. Reset, so that enter
          // can't be used on a word ending.
          if (keycode == KC_ENT) { typo_buffer_size = 0; }
          keycode = KC_SPC;
        } else {
          // Clear state if some other non-alpha key is pressed.
          typo_buffer_size = 0;
          return true;
        }
      }

      // If the buffer is full, rotate it to discard the oldest character.
      if (typo_buffer_size >= AUTOCORRECTION_MAX_LENGTH) {
        memmove(typo_buffer, typo_buffer + 1, AUTOCORRECTION_MAX_LENGTH - 1);
        typo_buffer_size = AUTOCORRECTION_MAX_LENGTH - 1;
      }

      // Append `keycode` to the buffer.
      // NOTE: `keycode` must be a basic keycode (0-255) by this point.
      typo_buffer[typo_buffer_size++] = (uint8_t) keycode;
      // Early return if not many characters have been buffered so far.
      if (typo_buffer_size < AUTOCORRECTION_MIN_LENGTH) { return true; }

      // Check whether the buffer ends in a typo. This is done using a trie
      // stored in `autocorrection_data`.
      uint16_t state = 0;
      uint8_t code = pgm_read_byte(autocorrection_data + state);
      for (int i = typo_buffer_size - 1; i >= 0; --i) {
        const uint8_t key_i = typo_buffer[i];

        if (code & 64) { // Check for match in node with multiple children.
          code &= 63;
          for (; code != key_i;
              code = pgm_read_byte(autocorrection_data + (state += 3))) {
            if (!code) { return true; }
          }

          // Follow link to child node.
          state = (uint16_t)(
              (uint_fast16_t)pgm_read_byte(autocorrection_data + state + 1)
              | (uint_fast16_t)pgm_read_byte(autocorrection_data + state + 2) << 8);
        // Otherwise check for match in node with a single child.
        } else if (code != key_i) {
          return true;
        } else if (!(code = pgm_read_byte(autocorrection_data + (++state)))) {
          ++state;
        }

        // Stop if `state` becomes an invalid index. This should not normally
        // happen, it is a safeguard in case of a bug, data corruption, etc.
        if (state >= sizeof(autocorrection_data)) {
          return true;
        }

        // Read first byte of the next node.
        code = pgm_read_byte(autocorrection_data + state);

        if (code & 128) { // A typo was found! Apply autocorrection.
          const int backspaces = code & 63;
          for (int i = 0; i < backspaces; ++i) { tap_code(KC_BSPC); }
            send_string_P((char const*)(autocorrection_data + state + 1));

          if (keycode == KC_SPC) {
            typo_buffer[0] = KC_SPC;
            typo_buffer_size = 1;
            return true;
          } else {
            typo_buffer_size = 0;
            return false;
          }
        }
      }
      return true;
    }
    return true;
}
