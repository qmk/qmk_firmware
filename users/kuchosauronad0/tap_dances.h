#pragma once
#include "kuchosauronad0.h"

#ifdef TAP_DANCE_ENABLE
enum {
  TD_RESET = 0,
  TD_SPC,  // for special function td_parenthesis testing
  TD_NUM1, // compact gaming numpad
  TD_NUM2, // 
  TD_NUM3, //
  TD_TMX,  // tmux control sequence
  TD_EOL,  // end of line
  TD_BOL,  // beginning of line
  TD_NW,   // next word
  TD_PW,   // pevious word
  TD_DW,   // delete word
  TD_QT1,  // single double quote for '
  TD_QT2,  // single double quote for "
  TD_QT3,  // single double quote for `
  TD_PAR,  // single double parenthesis
  TD_CUR,  // single double curly braces
  TD_SQR,  // single double square brackets
  TD_ABR   // single double angle brackets
};
#endif // TAP_DANCE_ENABLE
void td_parenthesis (qk_tap_dance_state_t *state, void *user_data);
