/*
Copyright 2018 QMK Contributors

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
#include "bigswitch.h"

volatile uint8_t runonce = true;
static uint16_t my_timer;

__attribute__ ((weak))
void matrix_init_user(void) {
  my_timer = timer_read();
}

__attribute__ ((weak))
void matrix_scan_user(void) {
#if defined(RGBLIGHT_ENABLE)
  if (runonce && timer_elapsed(my_timer) > 1000) {
    runonce = false;
    rgblight_sethsv_noeeprom(0x0, 0xff, 0x80);
    rgblight_mode_noeeprom(9);
    rgblight_enable_noeeprom();
  }
#endif
}
