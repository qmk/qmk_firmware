/* Copyright 2019 Kyle Terry
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
#include "rev2.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#ifdef SSD1306OLED
  return process_record_gfx(keycode,record) && process_record_user(keycode, record);
#else
  return process_record_user(keycode, record);
#endif
}
