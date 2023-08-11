/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>, @possumvibes

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

// written by @dnaq.
#if defined( global_quick_tap) && defined(CONSOLE_KEY_LOGGER_ENABLE)
    bool process_global_quick_tap(uint16_t keycode, keyrecord_t *record) {
      static uint16_t global_quick_tap_timer = 0;
      if (keycode < QK_MOD_TAP || keycode > QK_MOD_TAP_MAX) {
        global_quick_tap_timer = timer_read();
        return true;
      }
      if (timer_elapsed(global_quick_tap_timer) > TAPPING_TERM) {
        return true;
      }
      if (record->event.pressed) {
        keycode = keycode & 0xFF;
        global_quick_tap_timer = timer_read();
        tap_code(keycode);
        return false;
      }
      return true;
    }
#endif
