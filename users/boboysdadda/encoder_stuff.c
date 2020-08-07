#include "boboysdadda.h"
#include "encoder_stuff.h"

void encoder_update_user(uint8_t index, bool clockwise) {
  uint8_t layer = biton32(layer_state);
  switch (layer) {
    case _LOWER:
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGUP);
      }
      break;
    case _QWERTY:
      if (clockwise) {
        tap_code(KC_WH_D);
      } else {
        tap_code(KC_WH_U);
      }
      break;
    case _RAISE:
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
      break;
  }
}