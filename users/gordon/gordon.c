#include "gordon.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

#if (__has_include("secret.h"))
#include "secret.h"
#else
const char secret[][64] = {
  "test1",
  "test2",
  "test3",
  "test4",
  "test5"
};
#endif

void register_hyper (void) { //Helper function to invoke Hyper
  register_code (KC_LSFT);
  register_code (KC_LCTL);
  register_code (KC_LALT);
  register_code (KC_LGUI);
}
void unregister_hyper (void) { //Helper function to invoke Hyper
  unregister_code (KC_LSFT);
  unregister_code (KC_LCTL);
  unregister_code (KC_LALT);
  unregister_code (KC_LGUI);
}

void register_ctrl_a (void) {
  register_code(KC_LCTL);
  register_code(KC_A);
}

void unregister_ctrl_a (void) {
  unregister_code(KC_LCTL);
  unregister_code(KC_A);
}

void register_alt_f7 (void) {
  register_code (KC_LALT);
  register_code (KC_F7);
}

void unregister_alt_f7 (void) {
  unregister_code (KC_LALT);
  unregister_code (KC_F7);
}

void register_shift_f6 (void) {
  register_code (KC_LSFT);
  register_code (KC_F6);
}

void unregister_shift_f6 (void) {
  unregister_code (KC_LSFT);
  unregister_code (KC_F6);
}

void register_ctrl_shift (void) {
  register_code (KC_LSFT);
  register_code (KC_LCTRL);
}

void unregister_ctrl_shift (void) {
  unregister_code (KC_LSFT);
  unregister_code (KC_LCTRL);
}

void register_alt_shift (void) {
  register_code (KC_LSFT);
  register_code (KC_LALT);
}

void unregister_alt_shift (void) {
  unregister_code (KC_LSFT);
  unregister_code (KC_LALT);
}

// To activate SINGLE_HOLD, you will need to hold for 200ms first.
// This tap dance favors keys that are used frequently in typing like 'f'
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted) {
      //     if (!state->pressed) return SINGLE_TAP;
      //need "permissive hold" here.
      //     else return SINsGLE_HOLD;
      //If the interrupting key is released before the tap-dance key, then it is a single HOLD
      //However, if the tap-dance key is released first, then it is a single TAP
      //But how to get access to the state of the interrupting key????
      return SINGLE_TAP;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
  else if (state->count == 3) return TRIPLE_HOLD;
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//This works well if you want this key to work as a "fast modifier". It favors being held over being tapped.
int hold_cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}


static xtap htap_state = {
  .is_press_action = true,
  .state = 0
};

void h_finished (qk_tap_dance_state_t *state, void *user_data) {
  htap_state.state = cur_dance(state);
  switch (htap_state.state) {
    case SINGLE_TAP: register_code(KC_H); break;
    case SINGLE_HOLD: layer_on(8); register_code(KC_LALT); break;
    case DOUBLE_TAP: layer_invert(8); register_code(KC_LALT); break;
    // case DOUBLE_HOLD: register_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: register_code(KC_H);unregister_code(KC_H);register_code(KC_H);
  }
}

void h_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (htap_state.state) {
    case SINGLE_TAP: unregister_code(KC_H); break;
    case SINGLE_HOLD: layer_off(8); unregister_code(KC_LALT); break;
    case DOUBLE_TAP: unregister_code(KC_LALT);break;
    // case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_H);
  }
  htap_state.state = 0;
}


/**************** QUAD FUNCTION FOR TAB ****************/
// TAB, ALT + SHIFT, TAB TAB, CTRL + SHIFT
static xtap tab_state = {
  .is_press_action = true,
  .state = 0
};

void tab_finished (qk_tap_dance_state_t *state, void *user_data) {
  tab_state.state = cur_dance(state);
  switch (tab_state.state) {
    case SINGLE_TAP: register_code(KC_TAB); break;  //send tab on single press
    case SINGLE_HOLD: register_ctrl_shift(); break;
    case DOUBLE_HOLD: register_alt_shift(); break; //alt shift on single hold
    case DOUBLE_TAP: register_code(KC_TAB); unregister_code(KC_TAB); register_code(KC_TAB); break; //tab tab
    case TRIPLE_TAP: register_code(KC_LSHIFT) ;register_code(KC_ESC); break;
    case TRIPLE_HOLD: register_code(KC_LSHIFT); register_code(KC_LGUI); break;
  }
}

void tab_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tab_state.state) {
    case SINGLE_TAP: unregister_code(KC_TAB); break; //unregister tab
    case DOUBLE_HOLD: unregister_alt_shift(); break; //let go of alt shift
    case DOUBLE_TAP: unregister_code(KC_TAB); break;
    case SINGLE_HOLD: unregister_ctrl_shift(); break;
    case TRIPLE_TAP: unregister_code(KC_LSHIFT); unregister_code(KC_ESC); break;
    case TRIPLE_HOLD: unregister_code(KC_LSHIFT); unregister_code(KC_LGUI); break;
  }
  tab_state.state = 0;
}
/**************** QUAD FUNCTION FOR TAB ****************/

//*************** SUPER COMMA *******************//
// Assumption: we don't care about trying to hit ,, quickly
//*************** SUPER COMMA *******************//
static xtap comma_state = {
  .is_press_action = true,
  .state = 0
};

void comma_finished (qk_tap_dance_state_t *state, void *user_data) {
  comma_state.state = hold_cur_dance(state); //Use the dance that favors being held
  switch (comma_state.state) {
    case SINGLE_TAP: register_code(KC_COMMA); break;
    case SINGLE_HOLD: layer_on(1); break; //turn on symbols layer
    case DOUBLE_TAP: layer_invert(4); break; //toggle numbers layer
    case DOUBLE_HOLD: layer_on(2); break;
    case TRIPLE_TAP: register_code(KC_CALCULATOR); break;
    case TRIPLE_HOLD: layer_on(3);
  }
}

void comma_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (comma_state.state) {
    case SINGLE_TAP: unregister_code(KC_COMMA); break; //unregister comma
    case SINGLE_HOLD: layer_off(1); break;
    case DOUBLE_TAP: ;break;
    case DOUBLE_HOLD: layer_off(2); break;
    case TRIPLE_TAP: unregister_code(KC_CALCULATOR); break;
    case TRIPLE_HOLD: layer_off(3);
  }
  comma_state.state = 0;
}
//*************** SUPER COMMA *******************//
//*************** SUPER COMMA *******************//


//*************** F3 TAP DANCE *******************//
//Good example for accessing multiple layers from the same key.
static xtap S1_state = {
  .is_press_action = true,
  .state = 0
};

void bt_finished (qk_tap_dance_state_t *state, void *user_data) {
  S1_state.state = cur_dance(state);
  switch (S1_state.state) {
    case SINGLE_TAP: register_code(KC_F3); break;
    case SINGLE_HOLD: layer_on(_MACROS); break;
    case DOUBLE_TAP: layer_invert(_MACROS); break;
    case DOUBLE_HOLD: layer_on(5); break;
    case DOUBLE_SINGLE_TAP: layer_invert(_MACROS); break;
  }
}

void bt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (S1_state.state) {
    case SINGLE_TAP: unregister_code(KC_F3); break;
    case SINGLE_HOLD: layer_off(_MACROS); break;
    case DOUBLE_TAP: break; //already inverted. Don't do anything.
    case DOUBLE_HOLD: layer_off(5); break;
    case DOUBLE_SINGLE_TAP: break;
  }
  S1_state.state = 0;
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // simple tap dance
  [F12ETAPS] = ACTION_TAP_DANCE_DOUBLE(KC_F12,LSFT(LCTL(KC_F10))),
  [REFRESH]  = ACTION_TAP_DANCE_DOUBLE(KC_R,LCTL(KC_R)),
  [ENDESC]   = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_ESC),
  [Q_ESCAPE] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
  [ENDHOME]  = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_HOME),
  [CALCCOMP] = ACTION_TAP_DANCE_DOUBLE(KC_CALCULATOR, KC_MY_COMPUTER),
  [ALTF4]    = ACTION_TAP_DANCE_DOUBLE(KC_F4,LALT(KC_F4)),
  [F6F7]     = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_F6), LALT(KC_F7)),
  [F1F13]    = ACTION_TAP_DANCE_DOUBLE(KC_F1, KC_F13),
  [F2F14]    = ACTION_TAP_DANCE_DOUBLE(KC_F2, KC_F14),
  [F5F15]    = ACTION_TAP_DANCE_DOUBLE(KC_F5, KC_F15),
  [TABCOMBO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tab_finished, tab_reset),
  [F3D]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bt_finished, bt_reset),
  [COMMA]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, comma_finished, comma_reset),
  [HTAB]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,h_finished, h_reset)
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if (!record->event.pressed) {
//     switch (keycode) {

//       case KC_SECRET_1 ... KC_SECRET_5:
//           send_string(secret[keycode - KC_SECRET_1]);
//           // clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
//           return true; break;

//       case UP_ENTER_RESET:
//           register_code(KC_UP);
//           unregister_code(KC_UP);
//           register_code(KC_ENTER);
//           unregister_code(KC_ENTER);
//           reset_keyboard();
//           return false; break;

//       case TIL_SLASH:
//           SEND_STRING ("~/.");
//           return false; break;

//       case DBMS_OUT:
//           SEND_STRING ("dbms_output.put_line('');");
//           SEND_STRING (SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
//           return false; break;

//       case ID_MAN_IP:
//           SEND_STRING ("http://dev-1967110238.us-east-1.elb.amazonaws.com");
//           return false; break;

//       case MODRESET:
//           clear_mods();
//           return false; break;

//       case DEREF:
//           SEND_STRING ("->");
//           return false; break;

//       case EQRIGHT:
//           SEND_STRING ("=>");
//           return false; break;

//       case TICK3:
//           SEND_STRING ("```");
//           return false; break;

//       case TILD3:
//           SEND_STRING ("~~~");
//           return false; break;
//     }
//   }
//   return true;
// };




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) {
    switch (keycode) {
      case KC_SECRET_1 ... KC_SECRET_5:
          send_string(secret[keycode - KC_SECRET_1]);
          // clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
          return true; break;
      case UP_ENTER_RESET:
          SEND_STRING("make ergodox_infinity:gordon:dfu-util");
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          reset_keyboard();
          return false; break;

      case TIL_SLASH:
          SEND_STRING ("~/.");
          return false; break;

      case DBMS_OUT:
          SEND_STRING ("dbms_output.put_line('');");
          SEND_STRING (SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
          return false; break;
      case DIE_1000X_RIGHT:
          SEND_STRING (SS_TAP(X_G) SS_TAP(X_G) SS_TAP(X_RIGHT) SS_TAP(X_B) SS_TAP(X_J));
          return false; break;
      case DIE_1000X_LEFT:
          SEND_STRING (SS_TAP(X_GRAVE) SS_TAP(X_G) SS_TAP(X_LEFT) SS_TAP(X_B) SS_TAP(X_J));
          return false; break;
      case ID_MAN_IP:
          SEND_STRING ("http://dev-1967110238.us-east-1.elb.amazonaws.com");
          return false; break;

      case MODRESET:
          clear_mods();
          return false; break;

      case DEREF:
          SEND_STRING ("->");
          return false; break;

      case EQRIGHT:
          SEND_STRING ("=>");
          return false; break;

      case TICK3:
          SEND_STRING ("```");

          return false; break;

      case SPRK_TCK:
          SEND_STRING ("```");
          SEND_STRING (SS_DOWN(X_LSHIFT) SS_TAP(X_ENTER) SS_UP(X_LSHIFT));
          SEND_STRING (SS_DOWN(X_LSHIFT) SS_TAP(X_ENTER) SS_UP(X_LSHIFT));
          SEND_STRING ("```");
          SEND_STRING (SS_TAP(X_UP));
          return false; break;

      case TILD3:
          SEND_STRING ("~~~");
          return false; break;
    }
  }
  else { //On key being pressed
    switch (keycode) {
      case KC_SECRET_1 ... KC_SECRET_5:
          clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
          return false; break;
    }
  }
  return true;
};

