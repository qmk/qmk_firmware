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
 * @brief Process handler for remembering the last key.
 *
 * @param keycode  Keycode registered by matrix press, per keymap
 * @param record   keyrecord_t structure
 * @return true    Continue processing keycodes, and send to host
 * @return false   Stop processing keycodes, and don't send to host
 */
bool process_last_key(uint16_t keycode, keyrecord_t* record);

/**
 * @brief Optional callback defining which keys are remembered.
 *
 * @param keycode          Keycode that was just pressed
 * @param record           keyrecord_t structure
 * @param remembered_mods  Mods that will be remembered with this key
 * @return true            Key is remembered
 * @return false           Key is ignored
 *
 * Modifier and layer switch keys are always ignored. For all other keys, this
 * callback is called on every key press. Returning true means that the key is
 * remembered, false means it is ignored. By default, all non-modifier,
 * non-layer switch keys are remembered.
 *
 * The `remembered_mods` arg represents the mods that will be remembered with
 * this key. It can be modified to forget certain mods, for instance to forget
 * capitalization when repeating shifted letters:
 *
 *     // Forget Shift on letter keys.
 *     if (KC_A <= keycode && keycode <= KC_Z && (*remembered_mods & ~MOD_MASK_SHIFT) == 0) {
 *         *remembered_mods = 0;
 *     }
 */
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods);

/**
 * @brief Process handler for Repeat Key feature.
 *
 * @param keycode  Keycode registered by matrix press, per keymap
 * @param record   keyrecord_t structure
 * @return true    Continue processing keycodes, and send to host
 * @return false   Stop processing keycodes, and don't send to host
 */
bool process_repeat_key(uint16_t keycode, keyrecord_t* record);
