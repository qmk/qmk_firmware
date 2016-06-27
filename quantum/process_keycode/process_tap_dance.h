#ifndef PROCESS_TAP_DANCE_H
#define PROCESS_TAP_DANCE_H

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

typedef struct
{
  qk_tap_dance_type_t type;
  union {
    struct {
      uint16_t kc1;
      uint16_t kc2;
    } pair;
    qk_tap_dance_user_fn_t fn;
  };
} qk_tap_dance_action_t;

#define ACTION_TAP_DANCE_DOUBLE(kc1, kc2) { \
    .type = QK_TAP_DANCE_TYPE_PAIR,         \
    .pair = { kc1, kc2 }                    \
  }

#define ACTION_TAP_DANCE_FN(user_fn) { \
    .type = QK_TAP_DANCE_TYPE_FN, \
    .fn = user_fn                 \
  }

#if TAP_DANCE_ENABLE
extern const qk_tap_dance_action_t tap_dance_actions[];
#endif

/* To be used internally */

bool process_tap_dance(uint16_t keycode, keyrecord_t *record);
void matrix_scan_tap_dance (void);
void reset_tap_dance (qk_tap_dance_state_t *state);

#endif
