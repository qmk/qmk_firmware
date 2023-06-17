// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    CATROT = SAFE_RANGE,
    CATZOM,
    CATPAN,
    CATCNL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x4(
        KC_PMNS,   KC_P7,   KC_P8,   KC_P9,  
        KC_PPLS,   KC_P4,   KC_P5,   KC_P6,  
        KC_P0,     KC_P1,   KC_P2,   KC_P3,  
        KC_PDOT,   KC_PEQL, KC_PENT, TG(1)
    ),
    [1] = LAYOUT_ortho_4x4(
        KC_F21,   KC_F22,   KC_F23,   KC_F24,  
        KC_F17,   KC_F18,   KC_F19,   KC_F20,  
        KC_F13,   KC_F14,   KC_F15,   KC_F16,  
        CATPAN,   CATZOM,   CATROT,   TG(1)
    ),
    [2] = LAYOUT_ortho_4x4(
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
    [3] = LAYOUT_ortho_4x4(
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case CATROT:
      if (record->event.pressed) {
        register_code(KC_BTN3);
        wait_ms(50);
        register_code(KC_BTN1);
      } else {
        unregister_code(KC_BTN3);
        wait_ms(50);
        unregister_code(KC_BTN1);
      }
      return false;
      break;
    case CATZOM:
      if (record->event.pressed) {
        register_code(KC_BTN3);
        wait_ms(50);
        register_code(KC_BTN1);
        wait_ms(50);
        unregister_code(KC_BTN1);
      } else {
        unregister_code(KC_BTN3);
        wait_ms(50);
        unregister_code(KC_BTN1);
      }
      return false;
      break;
    case CATPAN:
      if (record->event.pressed) {
        register_code(KC_BTN3);
      } else {
        unregister_code(KC_BTN3);
        wait_ms(50);
        unregister_code(KC_BTN1);
      }
      return false;
      break;
    case CATCNL:
      if (record->event.pressed) {
        clear_keyboard();
      }
      return false;
      break;
  }

  return true;
}
