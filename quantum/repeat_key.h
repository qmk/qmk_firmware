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
 * @brief The number of times the last key has been repeated.
 *
 * @note The count is nonzero only while a repeated key is being processed.
 *
 * When a key is pressed normally, the count is 0. When the Repeat Key is used
 * to repeat a key, the count is 1 on the first repeat, 2 on the second repeat,
 * and so on.
 */
uint8_t get_repeat_key_count(void);

uint16_t get_repeat_key_keycode(void);             /**< Keycode of the key to be repeated. */
uint8_t  get_repeat_key_mods(void);                /**< Mods to be applied when repeating. */
void     set_repeat_key_keycode(uint16_t keycode); /**< Sets the keycode to repeat. */
void     set_repeat_key_mods(uint8_t mods);        /**< Sets the mods to repeat. */

/** @brief Sets keycode and record info for the key to be repeated. */
void set_repeat_key_record(uint16_t keycode, keyrecord_t* record);

/**
 * @brief Calls `process_record()` on a generated record repeating the last key.
 * @param event Event information in the generated record.
 */
void repeat_key_invoke(keyevent_t event);
