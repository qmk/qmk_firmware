// Taken from here: https://github.com/callum-oakley/qmk_firmware/tree/d63988caaf86217cfddf903c2c32dc042a8ef4da/users/callum
#include "swapper.h"

#include QMK_KEYBOARD_H
#include "customkeys.h"

bool is_swapper_ignored_key(uint16_t keycode, uint16_t tabish)
{
  if (tabish == KC_GRV) {
    return keycode == KC_LSFT;
  }

  switch (keycode) {
  case KC_LSFT:
  case KC_UP:
  case KC_LEFT:
  case KC_DOWN:
  case KC_RGHT:
    return true;
  default:
    return false;
  }
}

void update_swapper(bool *active, uint16_t cmdish, uint16_t tabish, uint16_t trigger, uint16_t keycode, keyrecord_t *record)
{
  if (keycode == trigger) {
    if (record->event.pressed) {
      if (!*active) {
	*active = true;
	register_code16(cmdish);
      }
      register_code16(tabish);
    } else {
      unregister_code16(tabish);
    }
  } else if (*active && !is_swapper_ignored_key(keycode, tabish)) {
    unregister_code16(cmdish);
    *active = false;
  }
}
