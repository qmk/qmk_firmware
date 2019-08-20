#include "tap_dances.h"
void td_parenthesis (qk_tap_dance_state_t *state, void *user_data) {
   if (state->count == 1) {
        SEND_STRING ("\(");
        reset_tap_dance (state);
   }
   else if (state->count == 2) {
        SEND_STRING("()" SS_TAP(X_LEFT));
        //tap_code(KC_2);
        //tap_code(KC_3);
        //tap_code(KC_LEFT);
        reset_tap_dance (state);
   }
   else if (state->count == 3) {
        SEND_STRING("[]" SS_TAP(X_LEFT));
        reset_tap_dance (state);
   }
   else if (state->count == 4) {
        SEND_STRING("{}" SS_TAP(X_LEFT));
        reset_tap_dance (state);
   }
   else if (state->count >= 5) {
        SEND_STRING("<>" SS_TAP(X_LEFT));
        reset_tap_dance (state);
   }
}

void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 3) {
    // Reset the keyboard if you tap the key more than three times
    reset_keyboard();
    reset_tap_dance(state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset),
  [TD_NUM1] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_4),
  [TD_NUM2] = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_5),
  [TD_NUM3] = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_6),
  [TD_QT1] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, MC_QT1),
  [TD_QT2] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_QUOT), MC_QT2),
  [TD_QT3] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, MC_QT3),
  
  [TD_TMX] = ACTION_TAP_DANCE_DOUBLE(KC_T, TM_X),
  [TD_EOL] = ACTION_TAP_DANCE_DOUBLE(KC_E, MC_EOL), // end of line
  [TD_BOL] = ACTION_TAP_DANCE_DOUBLE(KC_A, MC_BOL), // beginning of line
  [TD_NW]  = ACTION_TAP_DANCE_DOUBLE(KC_F, MC_NW),  // next word
  [TD_PW]  = ACTION_TAP_DANCE_DOUBLE(KC_B, MC_PW),  // pevious word
  [TD_DW]  = ACTION_TAP_DANCE_DOUBLE(KC_W, MC_DW),  // pevious word

  [TD_SPC] = ACTION_TAP_DANCE_FN(td_parenthesis),           // \(, (), [], {}, <>
  [TD_PAR] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, MC_PAR),      // () 
  [TD_SQR] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, MC_SQR),      // []
  [TD_CUR] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_LCBR), MC_CUR),// {}
  [TD_ABR] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_COMM), MC_ABR),// 
};
