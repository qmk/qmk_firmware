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

enum layers {
  BASE,
  MEDIA
}

uint32_t layer = BASE;

uint32_t layer_state_set_user(uint32_t state)
{
  layer = biton32(state);
  return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_APP , DF(MEDIA),   KC_ENT ,   \
        KC_PGUP, KC_UP,   KC_PGDN, \
        KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [MEDIA] = LAYOUT(
        KC_MUTE, DF(BASE),    KC_MSTP, \
        KC_BRIU, KC_CALC,  KC_BRID , \
        KC_MPRV, KC_MPLY,  KC_MNXT \
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
      switch (layer)
      {
        case BASE:
          if (clockwise) {
            tap_code(KC_UP);
          } else {
            tap_code(KC_DOWN);
          }
          break;
        case MEDIA:
          if (clockwise) {
            tap_code(KC_VOLU);
          } else {
            tap_code(KC_VOLD);
          }
          break;
      }
    }
}
