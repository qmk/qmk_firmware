// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "sixkeyboard.h"
#include "matrix.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = {
	{KC_A, KC_B, KC_C},
  {KC_D, KC_E, KC_F}
  }
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
};

void matrix_scan_user(void) {
  // jump to bootloaer when all keys are pressed
  if (matrix_get_row(0) == 0b111 && matrix_get_row(1) == 0b111) {
    clear_keyboard();
    bootloader_jump();
  }
};