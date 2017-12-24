#include "splinter.h"

enum {
  TP_SAFE_START,
  TP_LCTL,
  TP_LSFT,
  TP_LALT,
  TP_RCTL,
  TP_RSFT,
  TP_RALT,
  TP_TILD,
  TP_EGRV,
  TP_SAFET_END
};

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
int cur_dance(qk_tap_dance_state_t *);

void dance_lctl_finished(qk_tap_dance_state_t *, void *);
void dance_lctl_reset(qk_tap_dance_state_t *, void *);

void dance_lsft_finished(qk_tap_dance_state_t *, void *);
void dance_lsft_reset(qk_tap_dance_state_t *, void *);

void dance_lalt_finished(qk_tap_dance_state_t *, void *);
void dance_lalt_reset(qk_tap_dance_state_t *, void *);

void dance_rctl_finished(qk_tap_dance_state_t *, void *);
void dance_rctl_reset(qk_tap_dance_state_t *, void *);

void dance_rsft_finished(qk_tap_dance_state_t *, void *);
void dance_rsft_reset(qk_tap_dance_state_t *, void *);

void dance_ralt_finished(qk_tap_dance_state_t *, void *);
void dance_ralt_reset(qk_tap_dance_state_t *, void *);

void dance_tild_finished(qk_tap_dance_state_t *, void *);
void dance_tild_reset(qk_tap_dance_state_t *, void *);

void dance_egrv_finished(qk_tap_dance_state_t *, void *);
void dance_egrv_reset(qk_tap_dance_state_t *, void *);

void n_tilde_finished(qk_tap_dance_state_t *, void *);
void n_tilde_reset(qk_tap_dance_state_t *, void *);

void esc_grv_finished(qk_tap_dance_state_t *, void *);
void esc_grv_reset(qk_tap_dance_state_t *, void *);

void lgui_alt_finished(qk_tap_dance_state_t *, void *);
void lgui_alt_reset(qk_tap_dance_state_t *, void *);

void rgui_alt_finished(qk_tap_dance_state_t *, void *);
void rgui_alt_reset(qk_tap_dance_state_t *, void *);
