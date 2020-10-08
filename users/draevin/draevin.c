#include "draevin.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CM_QW:
      if (record->event.pressed) {
        layer_invert(_CM);
        layer_invert(_QW);
      }
      return false;
    case KC_MAKE:
      if (!record->event.pressed) {
        SEND_STRING ("make " QMK_KEYBOARD ":" QMK_KEYMAP ":flash");
        tap_code(KC_ENT);
        reset_keyboard();
      }
      break;
  }
  return true;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};
