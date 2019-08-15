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
    // Q is for TMUX
    // Z is for OS related things
    // other single key sequences are mostly for terminals and vim

    SEQ_ONE_KEY(KC_W) {
      // Vim + Tmux Macro, when in command mode in vim: write to file, change to the other pane in the current session and repeat the last command
      SEND_STRING(":w" SS_TAP(X_ENTER));
      tmux_pane_switch_repeat();
      }
    
    SEQ_ONE_KEY(KC_T) {
      // Send the Tmux Prefix
      tmux_prefix();
    }

    SEQ_ONE_KEY(KC_A) {
      // Send the Tmux Prefix and press 'right' arrow
      tmux_prefix();
      tap_code(KC_RIGHT);
    }

    SEQ_TWO_KEYS(KC_T, KC_T) {
      // Send the Tmux Prefix to a nested session
      tmux_prefix();
      tmux_prefix();
    }
    SEQ_TWO_KEYS(KC_Q, KC_A) {
      // Switch pane and repeat last action
      tmux_pane_switch_repeat();
    }

    SEQ_TWO_KEYS(KC_Z, KC_P){
      // Press windows key, send string 'plex' and press enter
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);

      unregister_code(KC_LGUI);
      SEND_STRING("plex");
      tap_code(KC_ENTER);
    }

    SEQ_TWO_KEYS(KC_Z, KC_F) {
      // Open a search
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }

    SEQ_TWO_KEYS(KC_Z, KC_Z) {
      SEND_STRING("https://start.duckduckgo.com"SS_TAP(X_ENTER));
    }

    SEQ_THREE_KEYS(KC_BSPC, KC_BSPC, KC_BSPC){
        // Reset the keyboard
        reset_keyboard();
    }
  }

  matrix_scan_keymap();
}
