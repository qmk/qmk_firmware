#include "k70_vengeance_rgb.h"
#include <hal.h>

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    tap_code(KC_KB_VOLUME_UP);
  } else {
    tap_code(KC_KB_VOLUME_DOWN);
  }
  return false;
}
