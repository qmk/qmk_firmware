#include "encoder.h"

void encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
   tap_code(KC_1);
  } else {
   tap_code(KC_0);
  }
}

