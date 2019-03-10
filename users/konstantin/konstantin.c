#include "konstantin.h"

__attribute__((weak))
void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
  keyboard_pre_init_keymap();
}

__attribute__((weak))
void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
  eeconfig_init_keymap();
}

__attribute__((weak))
void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
  keyboard_post_init_keymap();
}

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_keymap(keycode, record)) {
    return false;
  }

#ifdef LAYER_NUMPAD
  void toggle_numpad(void) {
    layer_invert(L_NUMPAD);
    bool numpad = IS_LAYER_ON(L_NUMPAD), num_lock = IS_HOST_LED_ON(USB_LED_NUM_LOCK);
    if (num_lock != numpad) {
      tap_code(KC_NLCK);  // Toggle Num Lock to match layer state
    }
  }
#endif

  switch (keycode) {
  case CLEAR:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("a") SS_TAP(X_DELETE));
    }
    return false;

  case DST_P_R:
    (record->event.pressed ? register_code16 : unregister_code16)(
      (get_mods() & DST_MOD_MASK) ? DST_REM : DST_PRV
    );
    return false;

  case DST_N_A:
    (record->event.pressed ? register_code16 : unregister_code16)(
      (get_mods() & DST_MOD_MASK) ? DST_ADD : DST_NXT
    );
    return false;

#ifdef LAYER_FN
    static bool fn_lock;

  case FN_FNLK:
    if (record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
      fn_lock = !IS_LAYER_ON(L_FN);  // Fn layer will be toggled after this
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
