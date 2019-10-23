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

    SEQ_ONE_KEY(KC_W) {
      // vim/tmux: Use in command mode in vim: write to file, switch tmux pane in the current session window and repeat the last command
      SEND_STRING(":w" SS_TAP(X_ENTER));
      tmux_pane_switch_repeat();
      }
    
    SEQ_ONE_KEY(KC_T) {
      // Send the Tmux Prefix
      tmux_prefix();
    }

    SEQ_ONE_KEY(KC_A) {
       // tmux: Send the prefix and press 'right' arrow
      tmux_prefix();
      tap_code(KC_RIGHT);
    }

    SEQ_TWO_KEYS(KC_T, KC_T) {
      // tmux: Send the prefix to a nested session
      tmux_prefix();
      tmux_prefix();
    }
    SEQ_TWO_KEYS(KC_T, KC_R) {
      // tmux: Switch pane and repeat last action
      tmux_pane_switch_repeat();
    }

    SEQ_TWO_KEYS(KC_V, KC_Z){
      // vim: Zoom pane
      tap_code16(LCTL(KC_W));
      tap_code16(LSFT(KC_BSLS));
    }

    SEQ_TWO_KEYS(KC_V, KC_R) {
      // vim: Substitute and place cursor
      SEND_STRING(":%s///g" SS_TAP(X_LEFT));
      tap_code(KC_LEFT);
      tap_code(KC_LEFT);
    }

    SEQ_TWO_KEYS(KC_V, KC_T) {
     // vim: move current pane to new tab
     tap_code16(LCTL(KC_W));
     tap_code16(LSFT(KC_T));
    }

    SEQ_THREE_KEYS(KC_BSPC, KC_BSPC, KC_BSPC){
        // Reset the keyboard
        reset_keyboard();
    }
  }

  matrix_scan_keymap();
}
