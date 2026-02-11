// Copyright 2024 Robert Jack Will (@matey-jack)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "keycodes.h"
#include "keymap_common.h"
#include "modifiers.h"

bool is_arrow_keycode(uint16_t keycode);
bool is_modifier_keycode(uint16_t keycode);
bool is_media_keycode(uint8_t keycode);

// This recognizes character keys without modifiers.
bool is_base_character_keycode(uint8_t keycode);

// This recognizes all character-producing key-combinations, including those with Shift and AltGr.
// (It is slightly off on MacOS where the left Option key also acts as AltGr,
// but doesn't matter if users use the ALGR() macro in their keymap.)
bool is_character_keycode(uint16_t keycode);
