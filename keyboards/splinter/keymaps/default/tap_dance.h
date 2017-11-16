#include "splinter.h"

#define SS_LSFT(string) SS_DOWN(X_LSHIFT) string SS_UP(X_LSHIFT)

enum {
  CT_N_TILDE = 0
};

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

void cur_dance(qk_tap_dance_state_t *state);
void n_tilde_finished(qk_tap_dance_state_t *state, void *user_data);
void n_tilde_reset(qk_tap_dance_state_t *state, void *user_data);
