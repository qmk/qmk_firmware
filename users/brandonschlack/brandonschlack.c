#include "brandonschlack.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LAUNCHPAD: // Launchpad: Sends as APP+F4, karabiner interprets as fn+F4 -> launchpad
      if (record->event.pressed) {
        register_code16(KC_APP);
        tap_code16(KC_F4);
      } else {
        clear_keyboard();
      }
      break;
  }
  return process_record_keymap(keycode, record);
}
