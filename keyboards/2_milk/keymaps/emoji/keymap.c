#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
          SEND_STRING("¯\\_(ツ)_/¯"),
          SEND_STRING("༼ つ ◕◡◕ ༽つ")
          )
};
