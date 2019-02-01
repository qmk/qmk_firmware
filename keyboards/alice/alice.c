/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#include <string.h>

#include "rgblight.h"

#include "i2c_master.h"
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;

void matrix_init_kb(void) {
  i2c_init();
  // call user level keymaps, if any
  matrix_init_user();
}

// custom RGB driver
void rgblight_set(void) {
  if (!rgblight_config.enable) {
    memset(led, 0, 3 * RGBLED_NUM);
  }

  i2c_transmit(0xb0, (uint8_t*)led, 3 * RGBLED_NUM, 100);
}

bool rgb_init = false;

void matrix_scan_kb(void) {
  // if LEDs were previously on before poweroff, turn them back on
  if (rgb_init == false && rgblight_config.enable) {
    i2c_transmit(0xb0, (uint8_t*)led, 3 * RGBLED_NUM, 100);
    rgb_init = true;
  }

  rgblight_task();
  matrix_scan_user();
}
#endif
