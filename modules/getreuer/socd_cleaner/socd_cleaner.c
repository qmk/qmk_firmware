// Copyright 2024-2025 Google LLC
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

/**
 * @file socd_cleaner.c
 * @brief SOCD Cleaner community module implementation
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/socd-cleaner>
 */

#include "socd_cleaner.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

// Defined in introspection.c.
uint16_t socd_opposing_pairs_count(void);
socd_cleaner_t* socd_opposing_pairs_get(uint16_t index);

bool socd_cleaner_enabled = true;

static void update_key(uint8_t keycode, bool press) {
  if (press) {
    add_key(keycode);
  } else {
    del_key(keycode);
  }
}

static bool process_opposing_pair(
    uint16_t keycode, keyrecord_t* record, socd_cleaner_t* state) {
  if (!state || !state->resolution ||
      (keycode != state->keys[0] && keycode != state->keys[1])) {
    return true;  // Quick return when disabled or on unrelated events.
  }

  // The current event corresponds to index `i`, 0 or 1, in the SOCD key pair.
  const uint8_t i = (keycode == state->keys[1]);
  const uint8_t opposing = i ^ 1;  // Index of the opposing key.

  // Track which keys are physically held (vs. keys in the report).
  state->held[i] = record->event.pressed;

  // Perform SOCD resolution for events where the opposing key is held.
  if (state->held[opposing]) {
    switch (state->resolution) {
      case SOCD_CLEANER_LAST:  // Last input priority with reactivation.
        // If the current event is a press, then release the opposing key.
        // Otherwise if this is a release, then press the opposing key.
        update_key(state->keys[opposing], !state->held[i]);
        break;

      case SOCD_CLEANER_NEUTRAL:  // Neutral resolution.
        // Same logic as SOCD_CLEANER_LAST, but skip default handling so that
        // the current key has no effect while the opposing key is held.
        update_key(state->keys[opposing], !state->held[i]);
        // Send updated report (normally, default handling would do this).
        send_keyboard_report();
        return false;  // Skip default handling.

      case SOCD_CLEANER_0_WINS:  // Key 0 wins.
      case SOCD_CLEANER_1_WINS:  // Key 1 wins.
        if (opposing == (state->resolution - SOCD_CLEANER_0_WINS)) {
          // The opposing key is the winner. The current key has no effect.
          return false;  // Skip default handling.
        } else {
          // The current key is the winner. Update logic is same as above.
          update_key(state->keys[opposing], !state->held[i]);
        }
        break;
    }
  }
  return true;  // Continue default handling to press/release current key.
}

bool process_record_socd_cleaner(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case SOCDON:  // Turn SOCD Cleaner on.
      if (record->event.pressed) {
        socd_cleaner_enabled = true;
      }
      return false;
    case SOCDOFF:  // Turn SOCD Cleaner off.
      if (record->event.pressed) {
        socd_cleaner_enabled = false;
      }
      return false;
    case SOCDTOG:  // Toggle SOCD Cleaner.
      if (record->event.pressed) {
        socd_cleaner_enabled = !socd_cleaner_enabled;
      }
      return false;
  }

  if (socd_cleaner_enabled) {
    for (int i = 0; i < (int)socd_opposing_pairs_count(); ++i) {
      socd_cleaner_t* state = socd_opposing_pairs_get(i);
      if (!process_opposing_pair(keycode, record, state)) {
        return false;
      }
    }
  }
  return true;
}

