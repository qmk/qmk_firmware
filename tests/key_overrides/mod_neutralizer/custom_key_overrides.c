// Copyright 2023 Vladislav Kucheriavykh (@precondition)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL),
    &ko_make_basic(MOD_BIT_LGUI, KC_H, KC_6),
    &ko_make_basic(MOD_BIT_LGUI, KC_D, LGUI(KC_V)),
    &ko_make_basic(MOD_BIT_LCTRL, KC_D, LCTL(KC_V)),
    &((const key_override_t){.trigger_mods      = MOD_BIT(KC_LALT),
                             .layers            = ~0x0,
                             .suppressed_mods   = 0, // Don't suppress anything
                             .options           = 0,
                             .negative_mod_mask = 0,
                             .custom_action     = NULL,
                             .context           = NULL,
                             .trigger           = KC_1,
                             .replacement       = KC_P1,
                             .enabled           = NULL}),
    &ko_make_basic(MOD_BIT_LGUI | MOD_BIT_LALT, KC_Y, LCTL(LGUI(KC_W))),
    &ko_make_basic(MOD_BIT_LGUI, KC_GRAVE, LCTL(LALT(KC_ESCAPE))),
    NULL // NULL terminates the array of overrides
};
