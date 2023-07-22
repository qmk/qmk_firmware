// Copyright 2021-2022 Google LLC
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
 * @file custom_shift_keys.h
 * @brief Custom shift keys: customize what keycode is produced when shifted.
 *
 * Overview
 * --------
 *
 * This library implements custom shift keys, keys where you can customize
 * what keycode is produced when shifted.
 *
 * Step 1: In your keymap.c, define a table of custom shift keys like
 *
 *     #include "features/custom_shift_keys.h"
 *
 *     const custom_shift_key_t custom_shift_keys[] = {
 *       {KC_DOT , KC_QUES}, // Shift . is ?
 *       {KC_COMM, KC_EXLM}, // Shift , is !
 *       {KC_MINS, KC_EQL }, // Shift - is =
 *       {KC_COLN, KC_SCLN}, // Shift : is ;
 *     };
 *
 * Each row defines one key. The first field is the keycode as it appears in
 * your layout and determines what is typed normally. The second entry is what
 * you want the key to type when shifted.
 *
 * Step 2: Handle custom shift keys from your `process_record_user` function as
 *
 *     bool process_record_user(uint16_t keycode, keyrecord_t* record) {
 *       if (!process_custom_shift_keys(keycode, record)) { return false; }
 *       // Your macros ...
 *
 *       return true;
 *     }
 *
 * Step 3: add `features/custom_shift_keys.c` to your rules.mk as
 *
 *     SRC += features/custom_shift_keys.c
 *
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/custom-shift-keys>
 */

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Custom shift key entry. The `keycode` field is the keycode as it appears in
 * your layout and determines what is typed normally. The `shifted_keycode` is
 * what you want the key to type when shifted.
 */
typedef struct {
    uint16_t keycode;
    uint16_t shifted_keycode;
} custom_shift_key_t;

/** Table of custom shift keys. */
extern const custom_shift_key_t custom_shift_keys[];
/** Number of entries in the `custom_shift_keys` table. */
extern uint8_t NUM_CUSTOM_SHIFT_KEYS;

/**
 * Handler function for custom shift keys.
 *
 * In keymap.c, call this function from your `process_record_user` function as
 *
 *     #include "features/custom_shift_keys.h"
 *
 *     bool process_record_user(uint16_t keycode, keyrecord_t* record) {
 *       if (!process_custom_shift_keys(keycode, record)) { return false; }
 *       // Your macros ...
 *
 *       return true;
 *     }
 */
bool process_custom_shift_keys(uint16_t keycode, keyrecord_t *record);

#ifdef __cplusplus
}
#endif