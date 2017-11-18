#include "splinter.h"

#define SS_LSFT(string) SS_DOWN(X_LSHIFT) string SS_UP(X_LSHIFT)

enum {
  CT_SAFE_START = 0,
  CT_N_TILDE,
  CT_ESC_GRV,
  CT_SAFE_END
};

enum {
  NO_TAP = 0,
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  TRIPLE_TAP,
  TRIPLE_HOLD
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

void init_tap_dance(void);
int cur_dance(qk_tap_dance_state_t*);

void n_tilde_finished(qk_tap_dance_state_t*, void*);
void n_tilde_reset(qk_tap_dance_state_t*, void*);

void esc_grv_finished(qk_tap_dance_state_t*, void*);
void esc_grv_reset(qk_tap_dance_state_t*, void*);
