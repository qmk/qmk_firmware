// Copyright 2024 Robert Jack Will (@matey-jack)
// SPDX-License-Identifier: GPL-2.0-or-later#pragma once

#include "keycodes.h"
#include "keymap_common.h"
#include "modifiers.h"

bool is_arrow_keycode(uint16_t keycode);
bool is_modifier_keycode(uint16_t keycode);
bool is_media_keycode(uint8_t keycode);
bool is_base_character_keycode(uint8_t keycode);

// Note that checking for a right modifier excludes the left one, but checking for the left one, includes both left and right.
#define HAS_SHIFT_MOD(keycode) (((((keycode) >> 8) & MOD_LSFT) == MOD_LSFT))
#define HAS_ALT_MOD(keycode) (((((keycode) >> 8) & MOD_LALT) == MOD_LALT))
#define HAS_RIGHT_ALT_MOD(keycode) (((((keycode) >> 8) & MOD_RALT) == MOD_RALT))
#define HAS_CTRL_OR_GUI_MOD(keycode) (((((keycode) >> 8) & (MOD_LCTL | MOD_LGUI)) != 0))

/*
    Any combination of Shift and Right Alt mods with a character key is also a character.
*/
bool is_character_keycode(uint16_t keycode);
