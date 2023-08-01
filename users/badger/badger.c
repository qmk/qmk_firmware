/*
Copyright 2020 Dan White <opensource@bluetufa.com>

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
#include "badger.h"

bool      _capsLockState;

__attribute__ ((weak))
void keyboard_post_init_user(void) {
  _capsLockState = false;
}

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CS_RIGHT:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_B)SS_TAP(X_ENTER)));
        return false;
      }
      break;
    case CS_DOWN:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_V)SS_TAP(X_ENTER)));
        return false;
      }
      break;
    case KC_CAPS:
      if (record->event.pressed) {
        _capsLockState = !_capsLockState;
        return true;
      }
      break;
    default:
      return true;
  }
  return true;
}
