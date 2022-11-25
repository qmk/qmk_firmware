 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  * "who-needs-capslock" and further modifications by Norman Köhring
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

//Setting up what encoder rotation does. If your encoder can be pressed as a button, that function can be set in keymap.c.

#ifdef ENCODER_ENABLE
#    include QMK_KEYBOARD_H

bool encoder_update_user(uint8_t index, bool clockwise) {

    switch (get_highest_layer(layer_state)) {
      case 0: // Base Layer

        switch (index) {
          case 0: // left rotary
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            break;
          case 1: // right rotary
            tap_code(clockwise ? KC_DOWN : KC_UP);
            break;
        }
        break;

      case 1: // Lower Layer

        switch (index) {
          case 0: // left rotary
            tap_code(clockwise ? KC_BRIU : KC_BRID);
            break;
          case 1: // right rotary
            tap_code(clockwise ? KC_PGDN : KC_PGUP);
            break;
        }
        break;
    }

    return false;
}

#endif
