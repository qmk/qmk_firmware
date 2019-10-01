#include "four_banger.h"

enum custom_keycodes {
  UP_URL = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT_ortho_2x2(
    KC_1, KC_U,
    KC_P, UP_URL
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case UP_URL:
      if (record->event.pressed) {
        SEND_STRING("http://1upkeyboards.com");
      }
      return false;
      break;
  }
  return true;
}
