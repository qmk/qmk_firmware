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
//
//
// Custom shift keys.
//
// This library implements custom shift keys, keys where you can customize
// what keycode is produced when shifted.
//
// Step 1: In your keymap.c, define a table of custom shift keys like
//
//   #include "features/custom_shift_keys.h"
//
//   const custom_shift_key_t custom_shift_keys[] = {
//     {KC_DOT , KC_QUES}, // Shift . is ?
//     {KC_COMM, KC_EXLM}, // Shift , is !
//     {KC_MINS, KC_EQL }, // Shift - is =
//     {KC_COLN, KC_SCLN}, // Shift : is ;
//   };
//
// Each row defines one key. The first field is the keycode as it appears in
// your layout and determines what is typed normally. The second entry is what
// you want the key to type when shifted.
//
// Step 2: Handle custom shift keys from your `process_record_user` function as
//
//   bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//     if (!process_custom_shift_keys(keycode, record)) { return false; }
//     // Your macros ...
//
//     return true;
//   }
//
// Step 3: add `features/custom_shift_keys.c` to your rules.mk as
//
//   SRC += features/custom_shift_keys.c
//
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/custom-shift-keys

#pragma once

#include "quantum.h"

typedef struct {
  uint16_t keycode;
  uint16_t shifted_keycode;
} custom_shift_key_t;

extern const custom_shift_key_t custom_shift_keys[];
extern uint8_t NUM_CUSTOM_SHIFT_KEYS;

bool process_custom_shift_keys(uint16_t keycode, keyrecord_t *record);

