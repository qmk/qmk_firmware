/* Copyright 2023 Tom Sennewald (@beelzebubi)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once
#include "nazu.h"

enum tap_dance {
    TD_WIN,
    TD_ESC,
    TD_RCTL,
    TD_LSFT_CAPS,
    TD_SPACE_DOT,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t dance_space_dot(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);

// `finished` and `reset` functions for each tapdance keycode
void spc_dot_finished (qk_tap_dance_state_t *state, void *user_data);
void spc_dot_reset (qk_tap_dance_state_t *state, void *user_data);

