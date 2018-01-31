#include "jrolfs.h"


//
// Keymap (placeholders)

__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}
__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}


//
// User

void matrix_init_user(void) {
  matrix_init_keymap();
}

void matrix_scan_user(void) {
  matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_RESET:
      if (!record->event.pressed) {
        reset_keyboard();
      }
      return false;
  }

  return process_record_keymap(keycode, record);
}

uint32_t layer_state_set_user (uint32_t state) {
  return layer_state_set_keymap (state);
}

void led_set_user(uint8_t usb_led) {
   led_set_keymap(usb_led);
}
