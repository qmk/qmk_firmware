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
};

enum keys {
  MODESW = SAFE_RANGE,
};

uint32_t layer = 0;

bool updateLayerState(uint16_t keycode, keyrecord_t* record) {
  if (record-> event.pressed)
  {
    switch (keycode)
    {
      case MODESW:
        if (layer == 0)
        {
          layer_on(MEDIA);
          layer = 1;
        } else {
          layer_off(MEDIA);
          layer = 0;
        }
        return false;
        break;

      default:
        break;
    }
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  return updateLayerState(keycode, record);
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_APP , MODESW,   KC_ENT ,   \
        KC_PGUP, KC_UP,   KC_PGDN, \
        KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [MEDIA] = LAYOUT(
        KC_MUTE, MODESW,   KC_MSTP, \
        KC_BRID, KC_CALC,  KC_BRIU, \
        KC_MPRV, KC_MPLY,  KC_MNXT \
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
      switch (layer)
      {
        case 0:
          if (clockwise) {
            tap_code(KC_DOWN);
          } else {
            tap_code(KC_UP);
          }
          break;
        case 1:
          if (clockwise) {
            tap_code(KC_VOLU);
          } else {
            tap_code(KC_VOLD);
          }
          break;
      }
    }
}
