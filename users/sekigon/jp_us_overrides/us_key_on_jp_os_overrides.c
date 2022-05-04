// Copyright 2022 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keymap_jp.h"
#include "dynamic_key_override.h"

// Perform as a US keyboard on JIS systems
static const key_override_t *us_key_on_jp_os_overrides[] = {
    // KC_GRV override depends on OS
    w_shift(KC_GRV, JP_TILD),
    w_shift(KC_2, JP_AT),
    w_shift(KC_6, JP_CIRC),
    w_shift(KC_7, JP_AMPR),
    w_shift(KC_8, JP_ASTR),
    w_shift(KC_9, JP_LPRN),
    w_shift(KC_0, JP_RPRN),
    w_shift(KC_MINS, JP_UNDS),
    wo_shift(KC_EQL, JP_EQL),
    w_shift(KC_EQL, JP_PLUS),
    wo_shift(KC_LBRC, JP_LBRC),
    w_shift(KC_LBRC, JP_LCBR),
    wo_shift(KC_RBRC, JP_RBRC),
    w_shift(KC_RBRC, JP_RCBR),
    wo_shift(KC_BSLS, JP_BSLS),
    w_shift(KC_BSLS, JP_PIPE),
    w_shift(KC_SCLN, JP_COLN),
    wo_shift(KC_QUOT, JP_QUOT),
    w_shift(KC_QUOT, JP_DQUO),
};

// If ALT+GRV is pressed, send JP_ZKHK on windows
// To do this, mask ALT in override config
static const key_override_t *grv_override_win = {
    &ko_make_with_layers_and_negmods(0, KC_GRV, JP_GRV, ~0,
                                     (uint8_t)MOD_MASK_SHIFT | MOD_MASK_ALT)};

// Always override KC_GRV to JP_GRV on Mac
static const key_override_t *grv_override_mac = {wo_shift(KC_GRV, JP_GRV)};

void register_us_key_on_jp_os_overrides(void) {
    remove_all_overrides();

    for (int idx = 0; idx < sizeof(us_key_on_jp_os_overrides) /
                                sizeof(us_key_on_jp_os_overrides[0]);
         idx++) {
        register_override(us_key_on_jp_os_overrides[idx]);
    }

    if (keymap_config.swap_lalt_lgui) {
        register_override(grv_override_mac);
    } else {
        register_override(grv_override_win);
    }
}
