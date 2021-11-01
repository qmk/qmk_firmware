/*
Copyright 2021 Koobaczech

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all(
		KC_ESC,   RGB_TOG,  RGB_MOD,  KC_MEDIA_PLAY_PAUSE,
		KC_NLCK,  KC_PSLS,  KC_PAST,  MO(1),
		KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
		KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
		KC_P1,    KC_P2,    KC_P3,    KC_PENT,
		KC_P0,    KC_P0,    KC_PDOT,  KC_PENT),

  [1] = LAYOUT_all(
		RESET,    KC_LCTL,  KC_LALT,  KC_TRNS,
		RGB_TOG,  RGB_MOD,  RGB_HUI,  KC_PMNS,
		KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
		KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
		KC_P1,    KC_P2,    KC_P3,    KC_PENT,
		KC_P0,    KC_P0,    KC_PDOT,  KC_PENT),

  [2] = LAYOUT_all(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

  [3] = LAYOUT_all(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)
};

// Encoder rotate function
bool encoder_update_user(uint8_t index, bool clockwise) {
    /* First encoder */
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_AUDIO_VOL_UP);
        } else {
            tap_code(KC_AUDIO_VOL_DOWN);
        }
    }
    return true;
}

//21 characters max
#ifdef OLED_ENABLE
void oled_task_user(void) {
  oled_write_P(PSTR("ZEUSPAD BY KOOBACZECH"), false);
  // Keyboard Layer Status
  oled_write_P(PSTR("LAYER: "), false);

  switch (get_highest_layer(layer_state)) {
    case 1:
        oled_write_ln_P(PSTR("FN"), false);
        break;
    default:
        oled_write_ln_P(PSTR("Default"), false);
    }
    // Keyboard Locking Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("CAPS  ") : PSTR("      "), false);
    oled_write_P(led_state.num_lock ? PSTR("NUM  ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR  ") : PSTR("     "), false);

    switch (rgblight_is_enabled() ? 1 : 2) {
      case 1:
          // Or use the write_ln shortcut over adding '\n' to the end of your string
          oled_write_P(PSTR("RGB"), false);
          static char led_buf[30];
          snprintf(led_buf, sizeof(led_buf) - 1, "\nMODE:%2d BRIGHT:%2d/10",
          (uint8_t)(rgblight_get_mode()),
          (uint8_t)(rgblight_get_val()/25.5));
          oled_write(led_buf, false);
          break;
      default:
          oled_write_ln_P(PSTR(""), false);
          oled_write_P(PSTR("\n"), false);
    }
}
#endif
