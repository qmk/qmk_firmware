#ifndef PROCESS_TAP_DANCE_H
#define PROCESS_TAP_DANCE_H

#ifdef TAP_DANCE_ENABLE

#include <stdbool.h>
#include <inttypes.h>

typedef struct
{
  uint8_t count;
  uint8_t oneshot_mods;
  uint16_t keycode;
  uint16_t timer;
  bool interrupted;
  bool pressed;
  bool finished;
} qk_tap_dance_state_t;

#define TD(n) (QK_TAP_DANCE + n)

typedef void (*qk_tap_dance_user_fn_t) (qk_tap_dance_state_t *state, void *user_data);

typedef struct
{
  struct {
    qk_tap_dance_user_fn_t on_each_tap;
    qk_tap_dance_user_fn_t on_dance_finished;
    qk_tap_dance_user_fn_t on_reset;
  } fn;
  qk_tap_dance_state_t state;
  void *user_data;
} qk_tap_dance_action_t;

typedef struct
{
  uint16_t kc1;
  uint16_t kc2;
} qk_tap_dance_pair_t;

#define ACTION_TAP_DANCE_DOUBLE(kc1, kc2) { \
    .fn = { NULL, qk_tap_dance_pair_finished, qk_tap_dance_pair_reset }, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }),  \
  }

#define ACTION_TAP_DANCE_FN(user_fn) {  \
    .fn = { NULL, user_fn, NULL }, \
    .user_data = NULL, \
  }

#define ACTION_TAP_DANCE_FN_ADVANCED(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset) { \
    .fn = { user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset }, \
    .user_data = NULL, \
  }

extern qk_tap_dance_action_t tap_dance_actions[];

/* To be used internally */

bool process_tap_dance(uint16_t keycode, keyrecord_t *record);
void matrix_scan_tap_dance (void);
void reset_tap_dance (qk_tap_dance_state_t *state);

void qk_tap_dance_pair_finished (qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_pair_reset (qk_tap_dance_state_t *state, void *user_data);

#else

#define TD(n) KC_NO

#endif

#endif
