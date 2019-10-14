#include "leader.h"

LEADER_EXTERNS();

#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)

// Runs constantly in the background, in a loop.
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

    SEQ_ONE_KEY (KC_1) {
      // ¯\_(ツ)_/¯
      unicode_input_start(); register_hex(0xaf); unicode_input_finish();
      register_code (KC_RALT); TAP_ONCE (KC_MINS); unregister_code (KC_RALT);
      register_code (KC_RSFT); TAP_ONCE (KC_8); unregister_code (KC_RSFT);
      unicode_input_start (); register_hex(0x30c4); unicode_input_finish();
      register_code (KC_RSFT); TAP_ONCE (KC_9); TAP_ONCE(KC_7); unregister_code (KC_RSFT);
      unicode_input_start (); register_hex(0xaf); unicode_input_finish();
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
