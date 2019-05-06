#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
          send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF"),
          send_unicode_hex_string("0CA0 005F 0CA0")
          )
};
