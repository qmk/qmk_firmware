#include "leader.h"

LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_user(void){

#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
//  run_diablo_macro_check();
#endif // TAP_DANCE_ENABLE

#ifdef RGBLIGHT_ENABLE
  matrix_scan_rgb();
#endif // RGBLIGHT_ENABLE

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

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
