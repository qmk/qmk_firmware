enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
  SPECIAL = 8
};

int cur_dance (qk_tap_dance_state_t *state);
int hold_cur_dance (qk_tap_dance_state_t *state);
