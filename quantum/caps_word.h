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

#include <stdbool.h>

#ifndef CAPS_WORD_IDLE_TIMEOUT
#    define CAPS_WORD_IDLE_TIMEOUT 5000 // Default timeout of 5 seconds.
#endif

/** @brief Matrix scan task for Caps Word feature */
void caps_word_task(void);

#if CAPS_WORD_IDLE_TIMEOUT > 0
/** @brief Resets timer for Caps Word idle timeout. */
void caps_word_reset_idle_timer(void);
#endif

/** @brief Activates Caps Word. */
void caps_word_on(void);

/** @brief Deactivates Caps Word. */
void caps_word_off(void);

/** @brief Toggles Caps Word. */
void caps_word_toggle(void);

/** @brief Gets whether currently active. */
bool is_caps_word_on(void);

/**
 * @brief Caps Word set callback.
 *
 * @param active True if Caps Word is active, false otherwise
 */
void caps_word_set_user(bool active);
