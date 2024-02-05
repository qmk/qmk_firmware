// Copyright 2022-2023 Google LLC
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
 * @file layer_lock.h
 * @brief Layer Lock, a key to stay in the current layer.
 *
 * Overview
 * --------
 *
 * Layers are often accessed by holding a button, e.g. with a momentary layer
 * switch `MO(layer)` or layer tap `LT(layer, key)` key. But you may sometimes
 * want to "lock" or "toggle" the layer so that it stays on without having to
 * hold down a button. One way to do that is with a tap-toggle `TT` layer key,
 * but here is an alternative.
 *
 * This library implements a "Layer Lock key". When tapped, it "locks" the
 * highest layer to stay active, assuming the layer was activated by one of the
 * following keys:
 *
 *  * `MO(layer)` momentary layer switch
 *  * `LT(layer, key)` layer tap
 *  * `OSL(layer)` one-shot layer
 *  * `TT(layer)` layer tap toggle
 *  * `LM(layer, mod)` layer-mod key (the layer is locked, but not the mods)
 *
 * Tapping the Layer Lock key again unlocks and turns off the layer.
 *
 * @note When a layer is "locked", other layer keys such as `TO(layer)` or
 * manually calling `layer_off(layer)` will override and unlock the layer.
 *
 * Configuration
 * -------------
 *
 * Optionally, a timeout may be defined so that Layer Lock disables
 * automatically if not keys are pressed for `LAYER_LOCK_IDLE_TIMEOUT`
 * milliseconds. Define `LAYER_LOCK_IDLE_TIMEOUT` in your config.h, for instance
 *
 *     #define LAYER_LOCK_IDLE_TIMEOUT 60000  // Turn off after 60 seconds.
 *
 * and call `layer_lock_task()` from your `matrix_scan_user()` in keymap.c:
 *
 *     void matrix_scan_user(void) {
 *       layer_lock_task();
 *       // Other tasks...
 *     }
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/layer-lock>
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

bool process_layer_lock(uint16_t keycode, keyrecord_t* record);
