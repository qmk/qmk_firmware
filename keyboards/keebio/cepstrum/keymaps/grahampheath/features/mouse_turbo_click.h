// Copyright 2022 Google LLC
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
// Mouse Turbo Click - click the mouse rapidly
//
// This library implements a "Turbo Click" button that clicks the mouse rapidly,
// implemented using mouse keys and a periodic callback function:
//
// * Pressing and holding the Turbo Click button sends rapid mouse clicks, about
//   12 clicks per second.
//
// * Quickly double tapping the Turbo Click button "locks" it. Rapid mouse
//   clicks are sent until the Turbo Click button is tapped again.
//
// NOTE: Mouse keys and deferred execution must be enabled; in rules.mk set
// MOUSEKEY_ENABLE = yes, DEFERRED_EXEC_ENABLE = yes.
//
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/mouse-turbo-click

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

// In your keymap, define a custom keycode to use for Turbo Click. Then handle
// Turbo Click from your `process_record_user` function by calling
// `process_mouse_turbo_click`, passing your custom keycode for the
// `turbo_click_keycode` arg:
//
//   #include "features/mouse_turbo_click.h"
//
//   bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//     if (!process_mouse_turbo_click(keycode, record, TURBO)) { return false; }
//     // Your macros ...
//
//     return true;
//   }
bool process_mouse_turbo_click(uint16_t keycode, keyrecord_t* record,
                               uint16_t turbo_click_keycode);

#ifdef __cplusplus
}
#endif

