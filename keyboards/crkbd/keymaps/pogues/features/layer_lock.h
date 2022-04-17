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
// Layer Lock, a key to stay in the current layer.
//
// Layers are often accessed by holding a button, e.g. with a momentary layer
// switch `MO(layer)` or layer tap `LT(layer, key)` key. But you may sometimes
// want to "lock" or "toggle" the layer so that it stays on without having to
// hold down a button. One way to do that is with a tap-toggle `TT` layer key,
// but here is an alternative.
//
// This library implements a "Layer Lock key". When tapped, it "locks" the
// highest layer to stay active, assuming the layer was activated by one of the
// following keys:
//
//  * `MO(layer)` momentary layer switch
//  * `LT(layer, key)` layer tap
//  * `OSL(layer)` one-shot layer
//  * `TT(layer)` layer tap toggle
//
// Tapping the Layer Lock key again unlocks and turns off the layer.
//
// NOTE: When a layer is "locked", other layer keys such as `TO(layer)` or
// manually calling `layer_off(layer)` will override and unlock the layer.
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/layer-lock

#pragma once

#include "quantum.h"

// In your keymap, define a custom keycode to use for Layer Lock. Then handle
// Layer Lock from your `process_record_user` function by calling
// `process_layer_lock`, passing your custom keycode for the `lock_keycode` arg:
//
//   #include "features/layer_lock.h"
//
//   bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//     if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
//     // Your macros ...
//
//     return true;
//   }
bool process_layer_lock(uint16_t keycode, keyrecord_t* record,
                        uint16_t lock_keycode);

// Returns true if `layer` is currently locked.
bool is_layer_locked(uint8_t layer);

// Locks and turns on `layer`.
void layer_lock_on(uint8_t layer);

// Unlocks and turns off `layer`.
void layer_lock_off(uint8_t layer);

// Toggles whether `layer` is locked.
void layer_lock_invert(uint8_t layer);

// An optional callback that gets called when a layer is locked or unlocked.
// This is useful to represent the current lock state, e.g. by setting an LED or
// playing a sound. In your keymap, define
//
//   void layer_lock_set_user(layer_state_t locked_layers) {
//     // Do something like `set_led(is_layer_locked(NAV));`
//   }
void layer_lock_set_user(layer_state_t locked_layers);

