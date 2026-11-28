// Copyright 2026 Nick Getka (@NickGetka)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

const key_override_t paren_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LPRN, KC_RPRN, 1 << _LOWER);
const key_override_t curly_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR, 1 << _LOWER);
const key_override_t angle_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LABK, KC_RABK, 1 << _LOWER);
const key_override_t bracket_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LBRC, KC_RBRC, 1 << _LOWER);
const key_override_t comma_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, KC_DOT, (1 << _LOWER) | (1 << _RAISE));

const key_override_t *key_overrides[] = {
    &paren_override,
    &curly_override,
    &angle_override,
    &bracket_override,
    &comma_override,
};
