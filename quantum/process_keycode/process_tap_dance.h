#ifndef PROCESS_TAP_DANCE_H
#define PROCESS_TAP_DANCE_H

#ifdef TAP_DANCE_ENABLE

#include <stdbool.h>
#include <inttypes.h>

typedef struct
{
  uint8_t count;
  uint16_t keycode;
  uint16_t timer;
} qk_tap_dance_state_t;

#define TD(n) (QK_TAP_DANCE + n)

typedef enum
{
  QK_TAP_DANCE_TYPE_PAIR,
  QK_TAP_DANCE_TYPE_FN,
} qk_tap_dance_type_t;

typedef void (*qk_tap_dance_user_fn_t) (qk_tap_dance_state_t *state);
typedef void (*qk_tap_dance_user_fn_reset_t) (void);

typedef struct
{
  qk_tap_dance_type_t type;
  union {
    struct {
      uint16_t kc1;
      uint16_t kc2;
    } pair;
    struct {
      qk_tap_dance_user_fn_t regular;
      qk_tap_dance_user_fn_t anyway;
      qk_tap_dance_user_fn_reset_t reset;
    } fn;
  };
} qk_tap_dance_action_t;

#define ACTION_TAP_DANCE_DOUBLE(kc1, kc2) { \
    .type = QK_TAP_DANCE_TYPE_PAIR, \
    .pair = { kc1, kc2 }            \
  }

#define ACTION_TAP_DANCE_FN(user_fn) { \
    .type = QK_TAP_DANCE_TYPE_FN, \
    .fn = { user_fn, NULL, NULL } \
  }

#define ACTION_TAP_DANCE_FN_ANYWAY(user_fn, user_fn_anyway) { \
    .type = QK_TAP_DANCE_TYPE_FN,           \
    .fn = { user_fn, user_fn_anyway, NULL } \
  }

#define ACTION_TAP_DANCE_FN_RESET(user_fn, user_fn_reset) { \
    .type = QK_TAP_DANCE_TYPE_FN,          \
    .fn = { user_fn, NULL, user_fn_reset } \
  }

#define ACTION_TAP_DANCE_FN_ANYWAY_RESET(user_fn, user_fn_anyway, user_fn_reset) { \
    .type = QK_TAP_DANCE_TYPE_FN,                    \
    .fn = { user_fn, user_fn_anyway, user_fn_reset } \
  }

extern const qk_tap_dance_action_t tap_dance_actions[];

/* To be used internally */

bool process_tap_dance(uint16_t keycode, keyrecord_t *record);
void matrix_scan_tap_dance (void);
void reset_tap_dance (qk_tap_dance_state_t *state);

#else

#define TD(n) KC_NO

#endif

#endif
