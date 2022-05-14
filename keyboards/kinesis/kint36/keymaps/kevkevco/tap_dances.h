// Copyright 2022 Kevin Goldberg @kevkevco <hello@kevkev.co>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "features/caps_word.h"
#include "features/num_word.h"
#include "layers.h"
#include "action.h"
#include "action_layer.h"
#include "process_keycode/process_tap_dance.h"
#include "quantum.h"

// Tap Dance Declarations
enum {
  SPOT = 0,
  CMAG,
  PDAG,
  NVUD,
  WIND,
  ISPT,
  GVES,
  ENTR,
  SLSH,
  LPINKY,
  RPINKY,
  COLON,
  SPACE
};


// Define a type for as many tap dance states as needed
typedef enum {
    TD_NONE,
    UNKNOWN,
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
} td_state_t;

// Functions and structs associated with all full tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Band-aid fix for oneshot timing issues
bool oneshot_symbols_timer_state;
uint16_t oneshot_symbols_timer;