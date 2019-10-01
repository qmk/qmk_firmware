#include QMK_KEYBOARD_H

#define _MAIN 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT(
     RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
     RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD
  )
};
