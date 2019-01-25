#ifndef TAP_DANCE_H
#define TAP_DANCE_H

#include "zer09.h"

typedef struct {
  int state;
} tap;

enum {
  DEFAULT_TAP,
  DEFAULT_HOLD,
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  TRIPLE_TAP,
  TRIPLE_HOLD
};

enum {
  DA_SAFE_START,
  DA_LCTL,
  DA_LSPR,
  DA_RCTL,
  DA_RALT,
  DA_UPLY,
  DA_DWLY,
  DA_SAFE_END
};

extern volatile uint8_t active_layer;

void layer_switcher_tap(uint8_t);
int cur_dance(qk_tap_dance_state_t *);

void dance_lctl_finished(qk_tap_dance_state_t *, void *);
void dance_lctl_reset(qk_tap_dance_state_t *, void *);

void dance_lspr_finished(qk_tap_dance_state_t *, void *);
void dance_lspr_reset(qk_tap_dance_state_t *, void *);

void dance_rctl_finished(qk_tap_dance_state_t *, void *);
void dance_rctl_reset(qk_tap_dance_state_t *, void *);

void dance_ralt_finished(qk_tap_dance_state_t *, void *);
void dance_ralt_reset(qk_tap_dance_state_t *, void *);

void dance_uply_finished(qk_tap_dance_state_t *, void *);
void dance_uply_reset(qk_tap_dance_state_t *, void *);

void dance_dwly_finished(qk_tap_dance_state_t *, void *);
void dance_dwly_reset(qk_tap_dance_state_t *, void *);

#endif
