#include "quantum.h"
extern bool CMD(uint16_t kc);
extern bool onMac;


#define ACTION_TAP_DANCE_DOUBLE_SAFE(kc1, kc2) { \
    .fn = { NULL, qk_tap_dance_pair_finished_safe, qk_tap_dance_pair_reset_safe }, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }),  \
  }

#ifdef QUAD_DANCE
//Enums used to clearly convey the state of the tap dance
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5 //send SINGLE_TAP twice - NOT DOUBLE_TAP
  // Add more enums here if you want for triple, quadruple, etc.
};
int cur_dance (qk_tap_dance_state_t *state);
# endif

enum tap_dance {
  COPY_CUT,
  PASTE_DANCE,
  _TD_F1,
  _TD_F2,
  _TD_F3,
  _TD_F4,
  _TD_F5,
  _TD_F6,
  _TD_F7,
  _TD_F8,
  _TD_F9,
  _TD_F10,
  _TD_F11,
  _TD_F12,
  _TD_H_ENTER,
  _TD_CLN,
  _TD_SLASH,
  // old ones
  LEFT_HOME,
  J_ENT,
  H_MINS,
  RGT_HOME,
  _TD_COPY,
  _TD_CUT,
  _TD_PASTE,
};
void qk_tap_dance_pair_finished_safe(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_pair_reset_safe(qk_tap_dance_state_t *state, void *user_data);
void td_copy_cut (qk_tap_dance_state_t *state, void *user_data);
void td_paste(qk_tap_dance_state_t *state, void *user_data);
int cur_dance (qk_tap_dance_state_t *state);
void dance_cut (qk_tap_dance_state_t *state, void *user_data);
void dance_copy (qk_tap_dance_state_t *state, void *user_data);
void dance_paste (qk_tap_dance_state_t *state, void *user_data);

// Ready to use Tap dance definitions, just put them on your layout
#define TD_COPY TD(_TD_COPY)
#define TD_CUT TD(_TD_CUT)
#define KC_TD_COPY TD(_TD_COPY) // Declarations for macros that add KC_
#define KC_TD_CUT TD(_TD_CUT)
#define KC_TD_PASTE TD(_TD_PASTE)
#define KC_E_GRV ES_GRV
#define TD_F1 TD(_TD_F1)
#define TD_F2 TD(_TD_F2)
#define TD_F3 TD(_TD_F3)
#define TD_F4 TD(_TD_F4)
#define TD_F5 TD(_TD_F5)
#define TD_F6 TD(_TD_F6)
#define TD_F7 TD(_TD_F7)
#define TD_F8 TD(_TD_F8)
#define TD_F9 TD(_TD_F9)
#define TD_F10 TD(_TD_F10)
#define TD_F11 TD(_TD_F11)
#define TD_F12 TD(_TD_F12)
#define H_ENTER TD(_TD_H_ENTER)
#define TD_CLN TD(_TD_CLN)
#define TD_SLASH TD(_TD_SLASH)
