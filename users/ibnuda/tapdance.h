#pragma once
#include "ibnuda.h"

#ifdef TAP_DANCE_ENABLE
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
} td_state_t;

int current_dance(qk_tap_dance_state_t *state);

void dance_tmb_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_tmb_reset(qk_tap_dance_state_t *state, void *user_data);

// enum for tap dances.
enum {
    TD_DLT_CTLDLT = 0,
    TD_SCLN_CLN,
    TD_LEFT_THUMB,
};

#endif // TAP_DANCE_ENABLE
