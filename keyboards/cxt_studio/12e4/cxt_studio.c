// Copyright 2023 Colin Kinloch (@ColinKinloch)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    switch (index) {
      case 0: {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
      }
      break;
      case 1: {
        if (clockwise) {
            rgb_matrix_increase_hue();
        } else {
            rgb_matrix_decrease_hue();
        }
      }
      break;
      case 2: {
        if (clockwise) {
            rgb_matrix_increase_val();
        } else {
            rgb_matrix_decrease_val();
        }
      }
      break;
      case 3: {
        if (clockwise) {
            rgb_matrix_step();
        } else {
            rgb_matrix_step_reverse();
        }
      }
      break;
    }
    return true;
}
#endif
