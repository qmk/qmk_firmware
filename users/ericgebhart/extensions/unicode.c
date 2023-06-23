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
#include "process_unicode_common.h"

#undef UC_STR
#define UC_STR(KEYC, STRING)                    \
  case KEYC:                                    \
  if (record->event.pressed) {                  \
    send_unicode_string(STRING);                \
  }                                             \
  break;

void process_unicode_strs(uint16_t keycode, keyrecord_t *record){
#if defined(UNICODE_ENABLE) && defined(SEND_UNICODE_ENABLE)
  switch (keycode) {
#include "unicode.def"
      }
#endif
}
