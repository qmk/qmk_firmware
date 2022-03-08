// Copyright 2021-2022 Google LLC
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/caps-word

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

