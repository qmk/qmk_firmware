#include QMK_KEYBOARD_H

enum custom_keycodes {
  DISSA,
  SHRUG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
          SHRUG,
          DISSA
          )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SHRUG:
      if (record->event.pressed) {
        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
      } else {
      }
      break;
    case DISSA:
      if (record->event.pressed) {
          send_unicode_hex_string("0CA0 005F 0CA0");
      } else {
      }
      break;
  }
  return true;
};
