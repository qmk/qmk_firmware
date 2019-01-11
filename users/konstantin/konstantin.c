#include "konstantin.h"

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_keymap(keycode, record)) {
    return false;
  }

  switch (keycode) {
  case CLEAR:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("a") SS_TAP(X_DELETE));
    }
    return false;

#ifdef LAYER_NUMPAD
  case NUMPAD:
    if (record->event.pressed) {
      layer_invert(L_NUMPAD);
      bool num_lock = host_keyboard_leds() & 1<<USB_LED_NUM_LOCK;
      if (num_lock != (bool)IS_LAYER_ON(L_NUMPAD)) {
        tap_code(KC_NLCK); // Toggle Num Lock to match layer state.
      }
    }
    return false;
#endif

  default:
    return true;
  }
}
