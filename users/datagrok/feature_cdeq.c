// This is a hack to place <question mark> on <shift-comma> and <exclamation
// mark> on <shift-period>, when using an operating system configured for a
// US/qwerty layout.
//
// cdeq = "comma dot exclamation question"

#include QMK_KEYBOARD_H

bool comm_shifted = false;
bool ques_shifted = false;

bool process_record_cdeq(uint16_t keycode, keyrecord_t *record) {
  uint8_t shifted;
  uint16_t s_keycode;
  bool *k_shifted;

  switch (keycode) {
  case KC_COMM:
    s_keycode = KC_SLSH;
    k_shifted = &comm_shifted;
    break;
  case KC_DOT:
    s_keycode = KC_1;
    k_shifted = &ques_shifted;
    break;
  default:
    return true;
  }

  shifted = get_mods() & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT));

  // Keydown. If shift is currently pressed, register its alternate keycode.
  if (record->event.pressed && shifted) {
    *k_shifted = true;
    register_code(s_keycode);
    return false;
    // Keyup. If shift was pressed back when the key was pressed, unregister
    // its alternate keycode.
  } else if (!(record->event.pressed) && *k_shifted) {
    *k_shifted = false;
    unregister_code(s_keycode);
    return false;
    // Otherwise, behave as normal.
  } else {
    return true;
  }
}
