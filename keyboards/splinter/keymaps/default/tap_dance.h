#include "splinter.h"

enum {
  CT_SAFE_START = 0,
  CT_N_TILDE,
  CT_ESC_GRV,
  CT_LGUI_ALT,
  CT_RGUI_ALT,
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

void lgui_alt_finished(qk_tap_dance_state_t*, void*);
void lgui_alt_reset(qk_tap_dance_state_t*, void*);

void rgui_alt_finished(qk_tap_dance_state_t*, void*);
void rgui_alt_reset(qk_tap_dance_state_t*, void*);
