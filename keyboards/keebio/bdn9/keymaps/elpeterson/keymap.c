/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layer {
    LYR0,
    LYR1,
};

enum encoder_names {
  _LEFT,
  _RIGHT,
};

/* Toggle between layers */
#define LYRTOG TG(LYR1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |              | Knob 2: Page Dn/Up |
        | Press: Mute       | Toggle Layer | Press: App View    |
        | Home              | Up           | End                |
        | Left              | Down         | Right              |
     */
    [LYR0] = LAYOUT(
        KC_AUDIO_MUTE, LYRTOG,  G(KC_TAB),
        KC_HOME,       KC_UP,   KC_END,
        KC_LEFT,       KC_DOWN, KC_RGHT
    ),
    /*
        | Knob 1: Vol Dn/Up |              | Knob 2: Page Dn/Up |
        | Press: Mute       | Toggle Layer | Press: App View    |
        | Hue +             | Sat +        | Brightness +       |
        | Hue -             | Sat -        | Brightness -       |
     */
    [LYR1] = LAYOUT(
        RGB_TOG, KC_TRNS, RGB_MOD,
        RGB_HUI, RGB_SAI, RGB_VAI,
        RGB_HUD, RGB_SAD, RGB_VAD
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == _LEFT) { /* Left encoder */
    if (clockwise) {
      tap_code(KC_AUDIO_VOL_UP);
    } else {
      tap_code(KC_AUDIO_VOL_DOWN);
    }
  } else if (index == _RIGHT) { /* Right encoder */
    if (clockwise) {
      tap_code16(G(C(KC_RGHT)));
    } else {
      tap_code16(G(C(KC_LEFT)));
    }
  }
  return true;
}
