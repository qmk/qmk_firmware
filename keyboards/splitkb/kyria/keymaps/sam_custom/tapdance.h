#pragma once
#include QMK_KEYBOARD_H

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
} td_state_t;

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

tap_dance_action_t tap_dance_actions[4];

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data);

td_state_t cur_dance(tap_dance_state_t *state);

void tmux_finished(tap_dance_state_t *state, void *user_data);
void tmux_reset(tap_dance_state_t *state, void *user_data);
void win_finished(tap_dance_state_t *state, void *user_data);
void win_reset(tap_dance_state_t *state, void *user_data);
void alt_finished(tap_dance_state_t *state, void *user_data);
void alt_reset(tap_dance_state_t *state, void *user_data);
