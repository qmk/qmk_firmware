#include QMK_KEYBOARD_H
#include <stdio.h>

// extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { { { KC_TRNS } } };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static char buf[10] = " ";

    if (record->event.pressed) {
      snprintf(buf, 10, "C%dR%d ", record->event.key.col, record->event.key.row);

      send_string(buf);
    }
    return false;

  return true;
}
