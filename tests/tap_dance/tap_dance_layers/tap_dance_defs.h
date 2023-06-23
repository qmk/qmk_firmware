// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum custom_keycodes {
    // (FAST|SLOW)_xy = tap KC_x on press, tap KC_y on release.  For FAST_xy
    // process_record_user() returns false to stop processing early; for
    // SLOW_xy process_record_user() returns true, therefore all other key
    // handlers are invoked.
    FAST_AB = SAFE_RANGE,
    FAST_CD,
    SLOW_AB,
    SLOW_CD,
};

enum tap_dance_ids {
    TD_L_MOVE, // ACTION_TAP_DANCE_LAYER_MOVE(KC_APP, 1)
    TD_L_TOGG, // ACTION_TAP_DANCE_LAYER_TOGGLE(KC_APP, 1)
    TD_LT_APP, // similar to LT(1, KC_APP) with KC_RCTL on tap+hold or double tap
};

#ifdef __cplusplus
}
#endif
