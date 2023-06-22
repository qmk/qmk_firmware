/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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
#include "version.h"

#define SEND_STR(KEYC, STRING)                  \
  case KEYC:                                    \
  if (record->event.pressed) {                  \
    SEND_STRING(STRING);                        \
  }                                             \
  break;

#define SEND_STR_DELAY(KEYC, STRING)                    \
  case KEYC:                                            \
  if (record->event.pressed) {                          \
    SEND_STRING_DELAY(STRING, TAP_CODE_DELAY);     \
  }                                                \
  break;

void process_send_strs(uint16_t keycode, keyrecord_t *record){
#ifdef SEND_STRING_ENABLE
  switch (keycode) {
#include "send_string.def"
  }
#endif
}
