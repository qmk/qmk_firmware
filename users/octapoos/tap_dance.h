#pragma once
#include "octapoos.h"

void dance_right_paren_reset(qk_tap_dance_state_t *state, void *user_data);
void dance_right_paren_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_left_paren_reset(qk_tap_dance_state_t *state, void *user_data);
void dance_left_paren_finished(qk_tap_dance_state_t *state, void *user_data);

#ifdef TAP_DANCE_ENABLE
enum {
  TD_L = 0,
  TD_R,
  TD_ESC_CAPS
};
#endif
