#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
// Custom one-or-more-shot implementation that does not rely on timers
// and persists across layer changes. Based on the users/callum implementation
// at https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum
// make it easy to put unicode keys into process_record


void process_unicode_strs(uint16_t keycode, keyrecord_t *record);
