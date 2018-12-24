#ifndef TAP_DANCE_H
#define TAP_DANCE_H
#include "othi.h"

void dance_CTL_NM_finished (qk_tap_dance_state_t *state, void *user_data);
void dance_CTL_NM_reset (qk_tap_dance_state_t *state, void *user_data);
void dance_GUI_NM_finished (qk_tap_dance_state_t *state, void *user_data);
void dance_GUI_NM_reset (qk_tap_dance_state_t *state, void *user_data);
void dance_ALT_NM_finished (qk_tap_dance_state_t *state, void *user_data);
void dance_ALT_NM_reset (qk_tap_dance_state_t *state, void *user_data);
void dance_SFT_NM_finished (qk_tap_dance_state_t *state, void *user_data);
void dance_SFT_NM_reset (qk_tap_dance_state_t *state, void *user_data);

//Tap Dance Declarations
enum {
  CTL_NM,
  ALT_NM,
  SFT_NM,
  GUI_NM
};
#endif
