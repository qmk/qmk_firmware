#include QMK_KEYBOARD_H
#include "rgblite.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKURL = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    UG_HUEU,  QMKURL
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case QK_UNDERGLOW_HUE_UP:
        rgblite_increase_hue();
        break;
      case QMKURL:
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
        break;
    }
  }
  return true;
}

void keyboard_post_init_user(void) {
  rgblite_init();
  rgblite_increase_hue();
}
