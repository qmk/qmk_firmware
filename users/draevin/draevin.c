#include "draevin.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CM_QW:
      if (record->event.pressed) {
        layer_invert(_CM);
        layer_invert(_QW);
      }
      return false;
    default:
      return true;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};
