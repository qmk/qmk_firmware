// Copyright 2025 Google LLC
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
 * @file tap_flow.c
 * @brief Tap Flow module implementation
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/tap-flow>
 */

#include "tap_flow.h"

#pragma message \
    "Tap Flow has evolved into core QMK feature Flow Tap! To use it, update your QMK set up and see https://docs.qmk.fm/tap_hold#flow-tap"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

// Either the Combos feature or Repeat Key (or both) need to be enabled. Either
// of these features enables the .keycode field in keyrecord_t, which the
// tap_flow implementation relies on.
#if !defined(COMBO_ENABLE) && !defined(REPEAT_KEY_ENABLE)
#error "tap_flow: Please enable Combos (COMBO_ENABLE = true) or Repeat Key (REPEAT_KEY_ENABLE = yes), or both, in rules.mk."
#else

uint32_t last_input = 0;
uint16_t g_tap_flow_term = TAP_FLOW_TERM;

static uint16_t prev_keycode = KC_NO;
// Events bypass tap_flow when there are unsettled LT keys in action_tapping's
// waiting_queue. Particularly, supposing an LT settles as held, the layer state
// will change and buffered events following the LT will be reconsidered as keys
// on that layer. That may change whether tap_flow is enabled or the timeout
// to use on those keys. We don't know in advance how the LT will settle.
static uint16_t settle_timer = 0;
static uint8_t is_tapped[(MATRIX_ROWS * MATRIX_COLS + 7) / 8] = {0};

static uint16_t get_tap_keycode(uint16_t keycode) {
  switch (keycode) {
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
      return QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
#ifndef NO_ACTION_LAYER
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
      return QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
#endif  // NO_ACTION_LAYER
  }
  return keycode;
}

#ifdef COMBO_ENABLE
#include "keymap_introspection.h"

static bool is_combo_key(uint16_t keycode) {
  for (uint16_t i = 0; i < combo_count(); ++i) {
    const uint16_t* keys = combo_get(i)->keys;
    uint16_t key;
    do {
      key = pgm_read_word(keys++);
      if (key == keycode) { return true; }
    } while (key != COMBO_END);
  }
  return false;
}
#else
#define is_combo_key(keycode) false
#endif  // COMBO_ENABLE

void housekeeping_task_tap_flow(void) {
  if (settle_timer && timer_expired(timer_read(), settle_timer)) {
#ifdef TAP_FLOW_DEBUG
    dprintf("tap_flow: settled.\n");
#endif  // TAP_FLOW_DEBUG
    settle_timer = 0;
  }
}

bool pre_process_record_tap_flow(uint16_t keycode, keyrecord_t* record) {
  const keypos_t pos = record->event.key;

  if (IS_KEYEVENT(record->event) && pos.row < MATRIX_ROWS
      && pos.col < MATRIX_COLS &&
      (IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode))) {
    // The event is on an MT or LT with a valid matrix position.
    const uint16_t tap_keycode = get_tap_keycode(keycode);

    // Determine the key's index in the bit arrays.
    const uint16_t index = pos.row * MATRIX_COLS + pos.col;
    const uint16_t array_index = index / 8;
    const uint8_t bit_mask = UINT8_C(1) << (index % 8);

    if (record->event.pressed) {  // On press.
      const uint32_t idle_time = timer_elapsed32(last_input);
      uint16_t tap_flow_term = get_tap_flow(keycode, record, prev_keycode);
      if (tap_flow_term > 500) {
        tap_flow_term = 500;
      }

      if (!settle_timer && !is_combo_key(keycode) &&
          idle_time < 500 && idle_time < tap_flow_term) {
#ifdef TAP_FLOW_DEBUG
        dprintf("tap_flow: %02x%02xd within term (%u < %u) converted to tap.\n",
                pos.row, pos.col, (uint16_t)idle_time, tap_flow_term);
#endif  // TAP_FLOW_DEBUG

        // Rewrite the event as a press of the tap keycode. This way, it
        // bypasses the usual action_tapping logic.
        record->keycode = tap_keycode;
        // Record this key as tapped.
        is_tapped[array_index] |= bit_mask;
      } else {
        // Otherwise if this is an LT key, track when it will settle according
        // to its tapping term.
        // NOTE: To be precise, the key could settle before the tapping term.
        // This is an approximation.
#ifdef TAP_FLOW_DEBUG
        if (settle_timer) {
          dprintf("tap_flow: %02x%02xd unchanged (unsettled state).\n",
                  pos.row, pos.col);
        } else if (is_combo_key(keycode)) {
          dprintf("tap_flow: %02x%02xd unchanged (combo key).\n",
                  pos.row, pos.col);
        } else {
          dprintf("tap_flow: %02x%02xd unchanged (outside time).\n",
                  pos.row, pos.col);
        }
#endif  // TAP_FLOW_DEBUG

        if (IS_QK_LAYER_TAP(keycode)) {
          const uint16_t term = GET_TAPPING_TERM(keycode, record);
          const uint16_t now = timer_read();
          if (!settle_timer || term > TIMER_DIFF_16(settle_timer, now)) {
            settle_timer = (now + term) | 1;
          }
        }
      }
    } else if ((is_tapped[array_index] & bit_mask) != 0) {  // On tap release.
#ifdef TAP_FLOW_DEBUG
      dprintf("tap_flow: %02x%02xu tap release.\n", pos.row, pos.col);
#endif  // TAP_FLOW_DEBUG

      // Rewrite the event as a release of the tap keycode.
      record->keycode = tap_keycode;
      // Record the key as released.
      is_tapped[array_index] &= ~bit_mask;
    }
  }

  if (record->event.pressed) {  // Track the previous key press.
    prev_keycode = keycode;
  }

  // Update last input time. Ignore mods and mod-tap keys in this update to
  // allow for chording multiple mods for hotkeys like "Ctrl+Shift+arrow".
  if (!IS_MODIFIER_KEYCODE(keycode) && !IS_QK_MOD_TAP(keycode)) {
    last_input = timer_read32();
  }

  return true;
}

bool process_record_tap_flow(uint16_t keycode, keyrecord_t* record) {
  if (record->event.pressed) {
    switch (keycode) {
      case TAP_FLOW_PRINT:
        send_string(get_u16_str(g_tap_flow_term, ' '));
        return false;
      case TAP_FLOW_UP:
        g_tap_flow_term += 5;
        return false;
      case TAP_FLOW_DOWN:
        g_tap_flow_term -= 5;
        return false;
    }
  }
  return true;
}

// By default, enable Tap Flow for Space, A-Z, or main alphas area punctuation.
__attribute__((weak)) bool is_tap_flow_key(uint16_t keycode) {
  switch (get_tap_keycode(keycode)) {
    case KC_SPC:
    case KC_A ... KC_Z:
    case KC_DOT:
    case KC_COMM:
    case KC_SCLN:
    case KC_SLSH:
      return true;
  }
  return false;
}

__attribute__((weak)) uint16_t get_tap_flow_term(
    uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {
  return get_tap_flow(keycode, record, prev_keycode);
}

// By default, enable filtering when both the tap-hold key and previous key
// return true for `is_tap_flow_key()`.
__attribute__((weak)) uint16_t get_tap_flow(
    uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {
  if (is_tap_flow_key(keycode) && is_tap_flow_key(prev_keycode)) {
    return g_tap_flow_term;
  }
  return 0;  // Disable Tap Flow.
}

#endif  // !defined(COMBO_ENABLE) && !defined(REPEAT_KEY_ENABLE)

