// Copyright 2021-2025 Google LLC
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
 * @file select_word.h
 * @brief Select Word community module: select words and lines.
 *
 * Overview
 * --------
 *
 * Implements a button that selects the current word, assuming conventional text
 * editor hotkeys. Pressing it again extends the selection to the following
 * word. The effect is similar to word selection (W) in the Kakoune editor.
 *
 * Pressing the button with shift selects the current line, and pressing the
 * button again extends the selection to the following line.
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/select-word>
 */

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Registers (presses) selection `action`.
 *
 * The `action` argument in these functions specifies the type of selection:
 *
 *     'W' = word selection
 *     'B' = backward word selection, left of the cursor
 *     'L' = line selection
 *
 * A selection is first registered with `select_word_register(action)`. This
 * should be followed by a call to `select_word_unregister()` to unregister the
 * hotkeys. The point of these separate register and unregister calls is to
 * enable holding the hotkey as a means to extend the selection range.
 *
 * @warning Forgetting to unregister results in stuck keys:
 * `select_word_register()` must be followed by `select_word_unregister()`.
 *
 * @param action  Type of selection to perform.
 */
void select_word_register(char action);

/** Unregisters (releases) selection hotkey. */
void select_word_unregister(void);

/** Registers and unregisters ("taps") selection `action.` */
static inline void select_word_tap(char action) {
  select_word_register(action);
  wait_ms(TAP_CODE_DELAY);
  select_word_unregister();
}

#if defined(SELECT_WORD_OS_DYNAMIC) || defined(OS_DETECTION_ENABLE)
/**
 * @brief Callback for whether the host uses Mac vs. Windows/Linux hotkeys.
 *
 * Optionally, this callback may be defined to indicate dynamically whether the
 * keyboard is being used with a Mac or non-Mac system.
 *
 * For instance suppose layer 0 is your base layer for Windows and layer 1 is
 * your base layer for Mac. Indicate this by adding in keymap.c:
 *
 *     bool select_word_host_is_mac(void) {
 *       return IS_LAYER_ON(1);  // Supposing layer 1 = base layer for Mac.
 *     }
 */
bool select_word_host_is_mac(void);
#endif  // defined(SELECT_WORD_OS_DYNAMIC) || defined(OS_DETECTION_ENABLE)

#ifdef __cplusplus
}
#endif
