/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2018 Kenneth A. <github.com/krusli>

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

#include "ymdk_np21.h"

#include <avr/pgmspace.h>

#include "action_layer.h"
#include "quantum.h"

#include "i2c.h"

#include "backlight.h"
#include "backlight_custom.h"

extern rgblight_config_t rgblight_config;

// for keyboard subdirectory level init functions
// @Override
void matrix_init_kb(void) {
  // call user level keymaps, if any
  // matrix_init_user();
}

#ifdef BACKLIGHT_ENABLE
/// Overrides functions in `quantum.c`
void backlight_init_ports(void) {
  b_led_init_ports();
}

void backlight_task(void) {
  b_led_task();
}

void backlight_set(uint8_t level) {
  b_led_set(level);
}
#endif

// custom RGB driver
void rgblight_set(void) {
  if (!rgblight_config.enable) {
    for (uint8_t i=0; i<RGBLED_NUM; i++) {
      led[i].r = 0;
      led[i].g = 0;
      led[i].b = 0;
    }
  }

  i2c_init();
  i2c_send(0xb0, (uint8_t*)led, 3 * RGBLED_NUM);
}

bool rgb_init = false;
void matrix_scan_user(void) {
  // if LEDs were previously on before poweroff, turn them back on
  if (rgb_init == false && rgblight_config.enable) {
    i2c_init();
    i2c_send(0xb0, (uint8_t*)led, 3 * RGBLED_NUM);
    rgb_init = true;
  }

  rgblight_task();
  /* Nothing else for now. */
}
