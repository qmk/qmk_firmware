#include "leader.h"

LEADER_EXTERNS();

void matrix_scan_user(void){
  static bool has_ran_yet;
  if (!has_ran_yet) {
    has_ran_yet = true;
    startup_user();
  }

#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
//  run_diablo_macro_check();
#endif // TAP_DANCE_ENABLE

#ifdef RGBLIGHT_ENABLE
  matrix_scan_rgb();
#endif // RGBLIGHT_ENABLE

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_TWO_KEYS(KC_Q, KC_Q) {
      // switch to layer L_A Adjust
      // layer_on(L_A);
    }
    SEQ_TWO_KEYS(KC_Q, KC_C) {
      // switch to layer L_A Adjust
      // layer_on(L_C);
    }
    SEQ_TWO_KEYS(KC_Q, KC_D) {
      // switch to layer L_A Adjust
      // layer_on(L_D);
    }
    SEQ_ONE_KEY(KC_T) {
      tmux_prefix();
      register_code(KC_RIGHT);
      unregister_code(KC_RIGHT);
    }
    SEQ_ONE_KEY(KC_W) {
      // Vim + Tmux Macro, when in command mode in vim: write to file, change to the other pane in the current session and repeat the last command
      SEND_STRING(":w" SS_TAP(X_ENTER));
      tmux_pane_switch_repeat();
      }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com"SS_TAP(X_ENTER));
    }
    SEQ_THREE_KEYS(KC_BSPC, KC_BSPC, KC_BSPC){
        reset_keyboard();
    }
    SEQ_TWO_KEYS(KC_S, KC_P){
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
      SEND_STRING("plex" SS_TAP(X_ENTER));
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }

  matrix_scan_keymap();
}
