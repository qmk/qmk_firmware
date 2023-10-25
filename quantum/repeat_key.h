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

#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "keyboard.h"

uint16_t get_last_keycode(void);             /**< Keycode of the last key. */
uint8_t  get_last_mods(void);                /**< Mods active with the last key. */
void     set_last_keycode(uint16_t keycode); /**< Sets the last key. */
void     set_last_mods(uint8_t mods);        /**< Sets the last mods. */

/** @brief Gets the record for the last key. */
keyrecord_t* get_last_record(void);

/** @brief Sets keycode and record info for the last key. */
void set_last_record(uint16_t keycode, keyrecord_t* record);

/**
 * @brief Signed count of times the key has been repeated or alternate repeated.
 *
 * @note The count is nonzero only while a repeated or alternate-repeated key is
 *       being processed.
 *
 * When a key is pressed normally, the count is 0. When the Repeat Key is used
 * to repeat a key, the count is 1 on the first repeat, 2 on the second repeat,
 * and continuing up to 127.
 *
 * Negative counts are used similarly for alternate repeating. When the
 * Alternate Repeat Key is used, the count is -1 on the first alternate repeat,
 * -2 on the second, continuing down to -127.
 */
int8_t get_repeat_key_count(void);

/**
 * @brief Calls `process_record()` on a generated record repeating the last key.
 * @param event Event information in the generated record.
 */
void repeat_key_invoke(const keyevent_t* event);

#ifndef NO_ALT_REPEAT_KEY

/**
 * @brief Keycode to be used for alternate repeating.
 *
 * Alternate Repeat performs this keycode based on the last eligible pressed key
 * and mods, get_last_keycode() and get_last_mods(). For example, when the last
 * key was KC_UP, this function returns KC_DOWN. The function returns KC_NO if
 * the last key doesn't have a defined alternate.
 */
uint16_t get_alt_repeat_key_keycode(void);

/**
 * @brief Calls `process_record()` to alternate repeat the last key.
 * @param event Event information in the generated record.
 */
void alt_repeat_key_invoke(const keyevent_t* event);

/**
 * @brief Optional user callback to define additional alternate keys.
 *
 * When `get_alt_repeat_key_keycode()` is called, it first calls this callback.
 * It should return a keycode representing the "alternate" of the given keycode
 * and mods. Returning KC_NO defers to the default definitions in
 * `get_alt_repeat_key_keycode()`.
 */
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods);

#endif // NO_ALT_REPEAT_KEY
