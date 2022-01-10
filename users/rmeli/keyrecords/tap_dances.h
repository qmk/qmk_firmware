#pragma once
#include QMK_KEYBOARD_H

// https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance#example-4-quad-function-tap-dance-id-example-4

// + ---------- +
// + TAP DANCES |
// + ---------- +

// Tap dance enums
enum {
    TD_LSPO_CAPS, // Tap once for (, hold once for LSFT, tap twice for CAPS
    TD_RSPC_CAPS, // Tap once for ), hold once for RSFT, tap twice for CAPS
    TD_ESC_DEL, // Tap once for KC_ESC, twice for KC_DEL
};

// Rename tap dances for keymap with shortcuts
#define TD_LSPC TD(TD_LSPO_CAPS)
#define TD_RSPC TD(TD_RSPC_CAPS)
#define TD_ED TD(TD_ESC_DEL)

// + ----------- +
// + KEY PRESSES |
// + ----------- +

// Different types of key presses
typedef enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
} td_state_t;

// Key press state
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// + --------- +
// + FUNCTIONS |
// + --------- +

// Tap dance for fast modifiers; favors being held over being tapped.
td_state_t hold_cur_dance(qk_tap_dance_state_t *state);

// Left Shift Parenthesis Open (LSPO) and Caps Lock (CAPS) on DOUBLE_TAP
void LSPO_CAPS_finished(qk_tap_dance_state_t *state, void *user_data);
void LSPO_CAPS_reset(qk_tap_dance_state_t *state, void *user_data);

// Right Shift Parenthesis Close (RSPC) and Caps Lock (CAPS) on DOUBLE_TAP
void RSPC_CAPS_finished(qk_tap_dance_state_t *state, void *user_data);
void RSPC_CAPS_reset(qk_tap_dance_state_t *state, void *user_data);
