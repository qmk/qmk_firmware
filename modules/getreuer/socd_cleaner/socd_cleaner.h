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
 * @file socd_cleaner.h
 * @brief SOCD Cleaner community module: enhance WASD for fast inputs for gaming
 *
 *
 * SOCD Cleaner is a QMK module for Simultaneous Opposing Cardinal Directions
 * (SOCD) filtering, which is popular for fast inputs on the WASD keys in
 * gaming. When two keys of opposing direction are physically held at the same
 * time, a rule is applied to decide which key is sent to the computer.
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
 *    the `socd_cleaner_t`.
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

/** Determines globally whether SOCD cleaner is enabled. */
extern bool socd_cleaner_enabled;

#ifdef __cplusplus
}
#endif
