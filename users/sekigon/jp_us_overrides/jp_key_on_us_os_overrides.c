// Copyright 2022 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycode.h"
#include "keycode_config.h"
#include "quantum_keycodes.h"
#include "dynamic_key_override.h"

// Perform as a JP keyboard on US systems
static const key_override_t *jp_key_on_us_os_overrides[] = {
    w_shift(KC_2, KC_DQT),
    w_shift(KC_6, KC_AMPR),
    w_shift(KC_7, KC_QUOT),
    w_shift(KC_8, KC_LPRN),
    w_shift(KC_9, KC_RPRN),
    w_shift(KC_0, KC_NO),
    w_shift(KC_MINS, KC_EQL),
    wo_shift(KC_EQL, KC_CIRC),
    w_shift(KC_EQL, KC_TILD),
    wo_shift(KC_INT3, KC_BSLS),
    w_shift(KC_INT3, KC_PIPE),
    wo_shift(KC_LBRC, KC_AT),
    w_shift(KC_LBRC, KC_GRV),
    wo_shift(KC_RBRC, KC_LBRC),
    w_shift(KC_RBRC, KC_LCBR),
    w_shift(KC_SCLN, KC_PLUS),
    wo_shift(KC_QUOT, KC_COLN),
    w_shift(KC_QUOT, KC_ASTR),
    wo_shift(KC_NUHS, KC_RBRC),
    w_shift(KC_NUHS, KC_RCBR),
    wo_shift(KC_INT1, KC_BSLS),
    w_shift(KC_INT1, KC_UNDS),
};

static const key_override_t *grv_override_win = {
    wo_shift(KC_GRV, LALT(KC_GRV))};
static const key_override_t *grv_override_mac = {
    wo_shift(KC_GRV, LCTL(KC_SPC))};

void register_jp_key_on_us_os_overrides(void) {
    remove_all_overrides();

    for (int idx = 0; idx < sizeof(jp_key_on_us_os_overrides) /
                                sizeof(jp_key_on_us_os_overrides[0]);
         idx++) {
        register_override(jp_key_on_us_os_overrides[idx]);
    }

    if (keymap_config.swap_lalt_lgui) {
        register_override(grv_override_mac);
    } else {
        register_override(grv_override_win);
    }
}
