#pragma once
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

// Stuff we need for locale and layer switching
// there can be more but we need to know where they start and end.
// remember there's limitations on layers.
// Our locales. so it's easy to switch between them.

bool process_locales(uint16_t keycode, keyrecord_t *record);

#define PROCESS_LOCALES                                         \
  if (!process_locales(keycode, record)) { return false; }
