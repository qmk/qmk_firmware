#include "leader_user.h"

void leader_end_user(void) {
  if (leader_sequence_two_keys(KC_V, KC_Z)){
    // vim: Zoom pane
    tap_code16(LCTL(KC_W));
    tap_code16(LSFT(KC_BSLS));
  }

  if (leader_sequence_two_keys(KC_V, KC_R)) {
    // vim: Substitute and place cursor
    SEND_STRING(":%s///g" SS_TAP(X_LEFT));
    tap_code(KC_LEFT);
    tap_code(KC_LEFT);
  }

  if (leader_sequence_two_keys(KC_V, KC_T)) {
   // vim: move current pane to new tab
   tap_code16(LCTL(KC_W));
   tap_code16(LSFT(KC_T));
  }

  if (leader_sequence_three_keys(KC_BSPC, KC_BSPC, KC_BSPC)){
    // Reset the keyboard
    reset_keyboard();
  }
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void){

#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
//  run_diablo_macro_check();
#endif // TAP_DANCE_ENABLE

#ifdef RGBLIGHT_ENABLE
  matrix_scan_rgb();
#endif // RGBLIGHT_ENABLE

  matrix_scan_keymap();
}
