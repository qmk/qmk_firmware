#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKURL = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    RGB_HUI,  QMKURL
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case QMKURL:
        // Using SEND_STRING here adds 400bytes ...
        // SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
        tap_code(KC_H);
        tap_code(KC_T);
        tap_code(KC_T);
        tap_code(KC_P);
        tap_code(KC_S);
        tap_code16(KC_COLON);
        tap_code(KC_SLASH);
        tap_code(KC_SLASH);
        tap_code(KC_Q);
        tap_code(KC_M);
        tap_code(KC_K);
        tap_code(KC_DOT);
        tap_code(KC_F);
        tap_code(KC_M);
        tap_code(KC_SLASH);
        tap_code(KC_ENTER);
        break;
    }
  }
  return true;
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); // sets mode to Fast breathing without saving
}
