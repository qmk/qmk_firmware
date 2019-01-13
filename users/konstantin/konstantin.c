#include "konstantin.h"

#ifdef LAYER_NUMPAD
static void toggle_numpad(void) {
  layer_invert(L_NUMPAD);
  bool num_lock = host_keyboard_leds() & 1<<USB_LED_NUM_LOCK;
  if (num_lock != (bool)IS_LAYER_ON(L_NUMPAD)) {
    tap_code(KC_NLCK); // Toggle Num Lock to match layer state
  }
}
#endif

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

#ifdef LAYER_FN
  static bool fn_lock;

  case FN_FNLK:
    if (record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
      fn_lock = !IS_LAYER_ON(L_FN); // Fn layer will be toggled after this
    }
    return true;
#endif

#ifdef LAYER_NUMPAD
  case NUMPAD:
    if (record->event.pressed) {
      toggle_numpad();
    }
    return false;
#endif

  case KC_ESC:
    if (record->event.pressed) {
#ifdef LAYER_NUMPAD
      if (IS_LAYER_ON(L_NUMPAD)) {
        toggle_numpad();
        return false;
      }
#endif
#ifdef LAYER_FN
      if (IS_LAYER_ON(L_FN) && fn_lock) {
        layer_off(L_FN);
        return fn_lock = false;
      }
#endif
    }
    return true;

  default:
    return true;
  }
}

__attribute__((weak))
uint32_t layer_state_set_keymap(uint32_t state) {
  return state;
}

uint32_t layer_state_set_user(uint32_t state) {
  return layer_state_set_keymap(state);
}
