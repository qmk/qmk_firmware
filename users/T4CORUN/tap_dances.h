#pragma once
#include "T4CORUN.h"

enum tap_dance_keys {
  TD_LEFTBRACKETS,
  TD_RIGHTBRACKETS,
  TD_QUOTES,
  TD_COLONS
};

void dance_left_brackets(tap_dance_state_t *state, void *user_data);
void dance_right_brackets(tap_dance_state_t *state, void *user_data);
void dance_quotes(tap_dance_state_t *state, void *user_data);
void dance_colons(tap_dance_state_t *state, void *user_data);