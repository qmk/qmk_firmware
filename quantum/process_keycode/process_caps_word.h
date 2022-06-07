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

#pragma once

#include "quantum.h"
#include "caps_word.h"

/**
 * @brief Process handler for Caps Word feature.
 *
 * @param keycode  Keycode registered by matrix press, per keymap
 * @param record   keyrecord_t structure
 * @return true    Continue processing keycodes, and send to host
 * @return false   Stop processing keycodes, and don't send to host
 */
bool process_caps_word(uint16_t keycode, keyrecord_t* record);

/**
 * @brief Weak function for user-level Caps Word press modification.
 *
 * @param keycode   Keycode registered by matrix press, per keymap
 * @return true     Continue Caps Word
 * @return false    Stop Caps Word
 */
bool caps_word_press_user(uint16_t keycode);
