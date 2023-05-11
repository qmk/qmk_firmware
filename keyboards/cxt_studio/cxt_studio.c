// Copyright 2023 Colin Kinloch (@ColinKinloch)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

static uint8_t anim = 0;

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
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
      }
      break;
      case 2: {
        if (clockwise) {
            rgblight_increase_val();
        } else {
            rgblight_decrease_val();
        }
      }
      break;
      case 3: {
        if (clockwise) {
            anim++;
        } else {
            anim--;
        }
	if (anim >= RGB_MATRIX_EFFECT_MAX) {
		anim = 0;
	} else if (anim < 0) {
		anim = RGB_MATRIX_EFFECT_MAX - 1;
	}
	rgblight_mode(anim);
      }
      break;
    }
    return true;
}
#endif
