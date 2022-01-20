#include "tap_dance.h"
//**************** Definitions needed for quad function to work *********************//
#ifdef QUAD_DANCE
int cur_dance(qk_tap_dance_state_t *state)
{
  if (state->count == 1)
  {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || state->pressed == 0)
      return SINGLE_TAP;
    else
      return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap. In example below, that means to send `xx` instead of `Escape`.
  else if (state->count == 2)
  {
    if (state->interrupted)
      return DOUBLE_SINGLE_TAP;
    else if (state->pressed)
      return DOUBLE_HOLD;
    else
      return DOUBLE_TAP;
  }
  else
    return 6; //magic number. At some point this method will expand to work for more presses
};

//**************** Definitions needed for quad function to work *********************//
# endif

// Slightly better tap dance double: interruption sends double single and any number over double sends the single that number of times
void qk_tap_dance_pair_finished_safe(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
  int count = state->count;
  if (state->count == 2) {
    if (state->interrupted){
      tap_code16(pair->kc1);register_code16 (pair->kc1);
      state->count = 1; // Reset the counter as we are using the first key
    } else register_code16 (pair->kc2);
    return;
  }
  register_code16 (pair->kc1);
  while(--count){
    unregister_code16(pair->kc1);
    register_code16 (pair->kc1);
  }
}

void qk_tap_dance_pair_reset_safe(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
  if (state->count == 2) {
    unregister_code16 (pair->kc2);
    return;
  }
  unregister_code16(pair->kc1);
}

//**************** Tap dance functions *********************//

qk_tap_dance_action_t tap_dance_actions[] = {
    [COPY_CUT] = ACTION_TAP_DANCE_FN(td_copy_cut),
    [PASTE_DANCE] = ACTION_TAP_DANCE_FN(td_paste),
    [_TD_F1] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_F1),
    [_TD_F2] = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_F2),
    [_TD_F3] = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_F3),
    [_TD_F4] = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_F4),
    [_TD_F5] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_F5),
    [_TD_F6] = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_F6),
    [_TD_F7] = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_F7),
    [_TD_F8] = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_F8),
    [_TD_F9] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_F9),
    [_TD_F10] = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_F10),
    [_TD_F11] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_F11),
    [_TD_F12] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_F12),
    [_TD_H_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_ENT),
    [_TD_CLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLON),
    [_TD_SLASH] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_BSLASH),
    // OLD ONES
    [LEFT_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
    [RGT_HOME] = ACTION_TAP_DANCE_DOUBLE_SAFE(KC_RGHT, KC_END),
    [J_ENT] = ACTION_TAP_DANCE_DOUBLE_SAFE(KC_J,KC_ENT),
    [H_MINS] = ACTION_TAP_DANCE_DOUBLE_SAFE(KC_H,KC_SLASH),
    [_TD_COPY] =  ACTION_TAP_DANCE_FN(dance_copy),
    [_TD_CUT] = ACTION_TAP_DANCE_FN(dance_cut),
    [_TD_PASTE] = ACTION_TAP_DANCE_FN(dance_paste)
};

void td_copy_cut(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count == 2)
  {
    onMac ?  SEND_STRING(SS_LGUI("x")) :   SEND_STRING(SS_LCTRL("x"));
  }
  else
  {
    onMac ?  SEND_STRING(SS_LGUI("c")) : SEND_STRING(SS_LCTRL("c"));
  }
  reset_tap_dance(state);
};

void td_paste(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count == 2)
  {
    onMac ?  SEND_STRING(SS_DOWN(X_RSHIFT) SS_LGUI("v") SS_UP(X_RSHIFT)) :   SEND_STRING(SS_DOWN(X_RSHIFT) SS_LCTRL("v") SS_UP(X_RSHIFT));
  }
  else
  {
    onMac ?  SEND_STRING(SS_LGUI("v")) : SEND_STRING(SS_LCTRL("v"));
  }
  reset_tap_dance(state);
};

//===== The awesome tap dance for CUT, COPY and PASTE letters
void dance_copy (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { tap_code16(KC_C); }
  else
  if (state->interrupted) { tap_code16(KC_C);tap_code16(KC_C);}
  else CMD(KC_C);

  reset_tap_dance (state);
}

void dance_cut (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { tap_code16(KC_X); }
  else { CMD(KC_X); }
  reset_tap_dance (state);
}

void dance_paste (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code16(KC_V);
  }
  else {
    CMD(KC_V);
  }
  reset_tap_dance (state);
}
