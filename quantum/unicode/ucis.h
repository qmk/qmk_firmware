// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * \file
 *
 * \defgroup ucis UCIS
 * \{
 */

#ifndef UCIS_MAX_INPUT_LENGTH
#    define UCIS_MAX_INPUT_LENGTH 32
#endif

#ifndef UCIS_MAX_CODE_POINTS
#    define UCIS_MAX_CODE_POINTS 3
#endif

typedef struct {
    char*    mnemonic;
    uint32_t code_points[UCIS_MAX_CODE_POINTS];
} ucis_symbol_t;

// clang-format off

#define UCIS_TABLE(...) { \
    __VA_ARGS__,          \
    { NULL, {} }          \
}

#define UCIS_SYM(name, ...) {    \
    .mnemonic    = name,         \
    .code_points = {__VA_ARGS__} \
}

// clang-format on

extern const ucis_symbol_t ucis_symbol_table[];

/**
 * \brief Begin the input sequence.
 */
void ucis_start(void);

/**
 * \brief Whether UCIS is currently active.
 *
 * \return `true` if UCIS is active.
 */
bool ucis_active(void);

/**
 * \brief Get the number of characters in the input sequence buffer.
 *
 * \return The current input sequence buffer length.
 */
uint8_t ucis_count(void);

/**
 * \brief Add the given keycode to the input sequence buffer.
 *
 * \param keycode The keycode to add. Must be between `KC_A` and `KC_Z`, or `KC_1` and `KC_0`.
 *
 * \return `true` if the keycode was added.
 */
bool ucis_add(uint16_t keycode);

/**
 * \brief Remove the last character from the input sequence.
 *
 * \return `true` if the sequence was not empty.
 */
bool ucis_remove_last(void);

/**
 * Mark the input sequence as complete, and attempt to match.
 */
void ucis_finish(void);

/**
 * \brief Cancel the input sequence.
 */
void ucis_cancel(void);

/**
 * Send the code point(s) for the given UCIS index.
 *
 * \param index The index into the UCIS symbol table.
 */
void register_ucis(uint8_t index);

/** \} */
