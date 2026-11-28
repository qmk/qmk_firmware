// Copyright 2026 Nick Getka (@NickGetka)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

const key_override_t dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COMM);
const key_override_t comma_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_EXLM);
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_SLSH);
const key_override_t angle_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_ANGLE_BRACKET, KC_RIGHT_ANGLE_BRACKET);
const key_override_t curly_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE);
const key_override_t paren_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_PAREN, KC_RIGHT_PAREN);
const key_override_t bracket_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_BRACKET, KC_RIGHT_BRACKET);

#ifdef CUSTOM_SLASH_OVERRIDE
const key_override_t slash_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLASH, KC_BACKSLASH);
#endif

const key_override_t *key_overrides[] = {
    &dot_key_override,
    &comma_key_override,
#ifdef CUSTOM_SLASH_OVERRIDE
    &slash_key_override,
#endif
    &angle_key_override,
    &curly_key_override,
    &paren_key_override,
    &bracket_key_override,
    &ques_key_override,
    NULL,
};
