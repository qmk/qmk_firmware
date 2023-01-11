/* Copyright 2020 Joseph Wasson
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
#include "talljoe.h"

extern keymap_config_t keymap_config;

ostype_t get_os() {
  if(keymap_config.swap_lalt_lgui) {
    return MACOSX;
  }

  return WINDOWS;
}

#define IS_OSX() (get_os() == MACOSX)

#define MOD_SEND(KEY) (IS_OSX() ? SEND_STRING(SS_LCMD(KEY)) : SEND_STRING(SS_LCTL(KEY)))

void macro_copy() { MOD_SEND("c"); }
void macro_paste() { MOD_SEND("v"); }
void macro_lock() {
  if (IS_OSX()) {
    SEND_STRING(SS_LCTL(SS_LCMD("q")));
  } else {
    SEND_STRING(SS_LGUI("l"));
  }
}
