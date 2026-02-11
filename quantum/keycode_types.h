// Copyright 2024 Robert Jack Will (@matey-jack)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "keycodes.h"
#include "keymap_common.h"
#include "modifiers.h"

/**
 * \brief Check if keycode is a modifier key
 *
 * Returns true if this keycode either represents a modifier key or a QK keycode which behaves like a modifier.
 */
bool is_modifier_keycode(uint16_t keycode);

/**
 * \brief Check if keycode is a base character key
 *
 * Returns true if this is a plain (printable) character key without modifiers.
 */
bool is_base_character_keycode(uint8_t keycode);

/**
 * \brief Check if keycode is a (optionally modified) character key
 *
 * Recognizes all character-producing key-combinations, including those with Shift and AltGr.
 * On MacOS the left Option key also acts similar to AltGr, but all the codes defined
 * in quantum/keymap_extras use ALGR().
 */
bool is_character_keycode(uint16_t keycode);

bool is_arrow_keycode(uint16_t keycode);

bool is_media_keycode(uint8_t keycode);
