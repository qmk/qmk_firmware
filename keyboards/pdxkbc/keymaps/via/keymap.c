/* Copyright 2019 Franklin Harding
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    PDXKBCREDDIT = SAFE_RANGE,
    PDXKBCDISCORD,
    BADGELIFE,
    HACKTHEPLANET
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      PDXKBCREDDIT, PDXKBCDISCORD,
      BADGELIFE,    HACKTHEPLANET,
      KC_VOLU,      KC_VOLD
    ),

    [1] = LAYOUT(
      _______, _______,
      _______, _______,
      _______, _______
    ),

    [2] = LAYOUT(
      _______, _______,
      _______, _______,
      _______, _______
    ),

    [3] = LAYOUT(
      _______, _______,
      _______, _______,
      _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PDXKBCREDDIT:
      if (record->event.pressed) {
        SEND_STRING("https://reddit.com/r/pdxkbc\n");
      }
      break;
    case PDXKBCDISCORD:
      if (record->event.pressed) {
        SEND_STRING("https://discordapp.com/invite/bHwjHXh\n");
      }
      break;
    case BADGELIFE:
      if (record->event.pressed) {
        SEND_STRING("#badgelife\n");
      }
      break;
    case HACKTHEPLANET:
      if (record->event.pressed) {
        SEND_STRING("HACK THE PLANET!\n");
      }
      break;
  }

  return true;
}
