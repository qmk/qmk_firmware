/*
Copyright 2019

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
#pragma once

// Add backwards compatibility for existing keymaps
static inline void backlight_set_value(uint8_t index, uint8_t level) {
  static const uint8_t backlight_pins[] = BACKLIGHT_PINS;
  if (level) {
      gpio_set_pin_output(backlight_pins[index]);
  } else {
      gpio_set_pin_input(backlight_pins[index]);
  }
}

#define backlight_led_off(i) backlight_set_value(i, 0)
#define backlight_led_on(i) backlight_set_value(i, 1)
