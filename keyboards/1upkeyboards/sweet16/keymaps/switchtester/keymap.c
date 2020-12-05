#include QMK_KEYBOARD_H
#include "switches.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT_ortho_4x4(
    KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_NO, KC_NO, KC_NO 
  )
};

struct mechswitch switches[MATRIX_ROWS][MATRIX_COLS] = {
  {CHERRY_MX_BLUE, CHERRY_MX_RED, CHERRY_MX_BLACK, CHERRY_MX_BROWN},
  {GATERON_BLUE, GATERON_RED, GATERON_BLACK, GATERON_BROWN},
  {KAILH_BLUE, KAILH_RED, KAILH_BLACK, KAILH_BROWN},
  {HAKO_CLEAR, HAKO_TRUE, HAKO_VIOLET, HAKO_ROYAL_TRUE}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t col = record->event.key.col;
  uint8_t row = record->event.key.row;

  if (record->event.pressed) {
    char name[MAX_SWITCH_NAME_LENGTH];
    switch_name(switches[row][col], name);
    send_string(name);
    SEND_STRING("\n");
  }
  return false;
}
