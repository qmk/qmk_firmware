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

#pragma once

#include "quantum.h"

/**
 * @brief Process handler for Repeat Key feature.
 *
 * @param keycode  Keycode registered by matrix press, per keymap
 * @param record   keyrecord_t structure
 * @return true    Continue processing keycodes, and send to host
 * @return false   Stop processing keycodes, and don't send to host
 */
bool process_repeat_key(uint16_t keycode, keyrecord_t* record);

/**
 * @brief Optional callback defining which keys are eligible for repeating.
 *
 * The callback is called on every key press. Returning true means the key may
 * be repeated, and returning false means the key is ignored.
 *
 * The default implementation ignores modifier and layer switch keys so that it
 * is possible to set some mods and change layers between pressing a key and
 * repeating it.
 */
bool get_repeat_key_eligible(uint16_t keycode, keyrecord_t* record);
