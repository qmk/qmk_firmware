// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include "steno_keycodes.h"

#define BOLT_STROKE_SIZE 4
#define GEMINI_STROKE_SIZE 6

#if defined(STENO_ENABLE_GEMINI)
#    define MAX_STROKE_SIZE GEMINI_STROKE_SIZE
#else
#    define MAX_STROKE_SIZE BOLT_STROKE_SIZE
#endif

/**
 * \enum steno_mode_t
 *
 * An enumeration of the possible modes.
 */
typedef enum {
    STENO_MODE_GEMINI,
    STENO_MODE_BOLT,
} steno_mode_t;

/**
 * \brief Initialize the subsystem.
 *
 * This function must be called only once, before any of the below functions can be called.
 */
void steno_init(void);

/**
 * \brief Reset configuration to defaults.
 *
 */
void eeconfig_update_steno_default(void);

/**
 * \brief Clear any currently pressed chords.
 *
 */
void steno_clear_chord(void);

/**
 * \brief Get currently configured mode.
 *
 * \return 'steno_mode_t' of the configured mode.
 */
steno_mode_t steno_get_mode(void);

#if NUM_STENO_PROTOCOLS > 1

/**
 * \brief Set current mode. New state is not written to EEPROM.
 *
 * \param mode The mode to configure.
 */
void steno_set_mode_noeeprom(steno_mode_t mode);

/**
 * \brief Set current mode.
 *
 * \param mode The mode to configure.
 */
void steno_set_mode(steno_mode_t mode);

/**
 * \brief Move to the next potential mode. New state is not written to EEPROM.
 *
 */
void steno_mode_next_noeeprom(void);

/**
 * \brief Move to the next potential mode.
 *
 */
void steno_mode_next(void);

/**
 * \brief Move to the previous potential mode. New state is not written to EEPROM.
 *
 */
void steno_mode_previous_noeeprom(void);

/**
 * \brief Move to the previous potential mode.
 *
 */
void steno_mode_previous(void);

#endif
