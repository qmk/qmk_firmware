// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include "progmem.h"

/**
 * \file
 *
 * \defgroup unicodemap Unicode Map
 * \{
 */

extern const uint32_t unicode_map[] PROGMEM;

/**
 * \brief Get the index into the `unicode_map` array for the given keycode, respecting shift state for pair keycodes.
 *
 * \param keycode The Unicode Map keycode to get the index of.
 *
 * \return An index into the `unicode_map` array.
 */
uint8_t unicodemap_index(uint16_t keycode);

/**
 * \brief Get the code point for the given index in the `unicode_map` array.
 *
 * \param index The index into the `unicode_map` array.
 *
 * \return A Unicode code point value.
 */
uint32_t unicodemap_get_code_point(uint8_t index);

/**
 * \brief Send the code point for the given index in the `unicode_map` array.
 *
 * \param index The index into the `unicode_map` array.
 */
void register_unicodemap(uint8_t index);

/** \} */
