// Copyright 2021-2022 Google LLC
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/caps-word

#pragma once

#include "quantum.h"

#ifndef CAPS_WORD_IDLE_TIMEOUT
#    define CAPS_WORD_IDLE_TIMEOUT 5000 // Default timeout of 5 seconds.
#endif                                  // CAPS_WORD_IDLE_TIMEOUT

#if CAPS_WORD_IDLE_TIMEOUT > 0
/** @brief Matrix scan task for Caps Word feature */
void caps_word_task(void);

/** @brief Resets timer for Caps Word idle timeout. */
void caps_word_reset_idle_timer(void);
#else
static inline void caps_word_task(void) {}
#endif // CAPS_WORD_IDLE_TIMEOUT > 0

void caps_word_on(void);     /**< Activates Caps Word. */
void caps_word_off(void);    /**< Deactivates Caps Word. */
void caps_word_toggle(void); /**< Toggles Caps Word. */
bool is_caps_word_on(void);  /**< Gets whether currently active. */

/**
 * @brief Caps Word set callback.
 *
 * @param active True if Caps Word is active, false otherwise
 */
void caps_word_set_user(bool active);
