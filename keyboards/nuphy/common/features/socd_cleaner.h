// Copyright 2024 Google LLC
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
 * @file socd_cleaner.h
 * @brief SOCD Cleaner - enhance WASD for fast inputs for gaming
 *
 * Overview
 * --------
 *
 * SOCD Cleaner is a QMK library for Simultaneous Opposing Cardinal Directions
 * (SOCD) filtering, which is popular for fast inputs on the WASD keys in
 * gaming. When two keys of opposing direction are physically held at the same
 * time, a rule is applied to decide which key is sent to the computer.
 *
 *
 * Add it to your keymap
 * ---------------------
 *
 * In rules.mk, add `SRC += features/socd_cleaner.c`. Then in keymap.c, add
 *
 *     #include "features/socd_cleaner.h"
 *
 *     socd_cleaner_t socd_v = {{KC_W, KC_S}, SOCD_CLEANER_LAST};
 *     socd_cleaner_t socd_h = {{KC_A, KC_D}, SOCD_CLEANER_LAST};
 *
 *     bool process_record_user(uint16_t keycode, keyrecord_t* record) {
 *       if (!process_socd_cleaner(keycode, record, &socd_v)) { return false; }
 *       if (!process_socd_cleaner(keycode, record, &socd_h)) { return false; }
 *       // Your macros...
 *       return true;
 *     }
 *
 * Each `socd_cleaner_t` instance defines a pair of opposing keys and an SOCD
 * resolution strategy (explained below). In `process_record_user()`, handler
 * `process_socd_cleaner()` is called with each `socd_cleaner_t` instance.
 *
 * NOTE: The keys don't have to be WASD. But they must be basic keycodes
 * (https://docs.qmk.fm/keycodes_basic).
 *
 *
 * Enabling / disabling
 * --------------------
 *
 * SOCD filtering is enabled/disabled globally by assigning to variable
 * `socd_cleaner_enabled`. For instance, to enable only on a GAME layer:
 *
 *     layer_state_t layer_state_set_user(layer_state_t state) {
 *       socd_cleaner_enabled = IS_LAYER_ON_STATE(state, GAME);
 *       return state;
 *     }
 *
 * Or filtering can be disabled per `socd_cleaner_t` instance by setting its
 * resolution to SOCD_CLEANER_OFF.
 *
 *
 * Resolution strategies
 * ---------------------
 *
 * As controls vary across games, there are multiple possible SOCD resolution
 * strategies. SOCD Cleaner implements the following resolutions:
 *
 *  - SOCD_CLEANER_LAST: (Recommended) Last input priority with reactivation.
 *    The last key pressed wins. Rapid alternating inputs can be made.
 *    Repeatedly tapping the D key while A is held sends "ADADADAD."
 *
 *  - SOCD_CLEANER_NEUTRAL: Neutral resolution. When both keys are pressed, they
 *    cancel and neither is sent.
 *
 *  - SOCD_CLEANER_0_WINS: Key 0 always wins, the first key listed in defining
 *    the `socd_cleaner_t`. For example, the W key always wins in
 *
 *        socd_cleaner_t socd_ud = {{KC_W, KC_S}, SOCD_CLEANER_0_WINS};
 *
 *  - SOCD_CLEANER_1_WINS: Key 1 always wins, the second key listed.
 *
 * If you don't know what to pick, SOCD_CLEANER_LAST is recommended. The
 * resolution strategy on a `socd_cleaner_t` may be changed at run time by
 * assigning to `.resolution`.
 *
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/socd-cleaner>
 */

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

enum socd_cleaner_resolution {
  // Disable SOCD filtering for this key pair.
  SOCD_CLEANER_OFF,
  // Last input priority with reactivation.
  SOCD_CLEANER_LAST,
  // Neutral resolution. When both keys are pressed, they cancel.
  SOCD_CLEANER_NEUTRAL,
  // Key 0 always wins.
  SOCD_CLEANER_0_WINS,
  // Key 1 always wins.
  SOCD_CLEANER_1_WINS,
  // Sentinel to count the number of resolution strategies.
  SOCD_CLEANER_NUM_RESOLUTIONS,
};

typedef struct {
  uint8_t keys[2];  // Basic keycodes for the two opposing keys.
  uint8_t resolution;  // Resolution strategy.
  bool held[2];  // Tracks which keys are physically held.
} socd_cleaner_t;

/**
 * Handler function for SOCD cleaner.
 *
 * This function should be called from process_record_user(). The function may
 * be called multiple times with different socd_cleaner_t instances to filter
 * more than one SOCD key pair.
 */
bool process_socd_cleaner(uint16_t keycode, keyrecord_t* record,
                          socd_cleaner_t* state);

/** Determines globally whether SOCD cleaner is enabled. */
extern bool socd_cleaner_enabled;

#ifdef __cplusplus
}
#endif
