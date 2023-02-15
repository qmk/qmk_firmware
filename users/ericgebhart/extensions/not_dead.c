/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

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

#include USERSPACE_H

inline void not_dead(uint16_t kc1, keyrecord_t *record) {
  if (record->event.pressed) {
    tap_code16(kc1);
    tap_code16(KC_SPACE);
  }
}

#define NOT_DEAD(KCKEY, KC01)             \
  case KCKEY:                             \
  not_dead(KC01, record);                 \
  break;                                  \

void process_not_dead(uint16_t keycode, keyrecord_t *record) {
  switch(keycode){
#include "not_dead.def"
  }
}
