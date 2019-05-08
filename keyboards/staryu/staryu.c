/*
Copyright 2018 Cole Markham

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
#include "staryu.h"

#ifdef BACKLIGHT_ENABLE

#ifdef BACKLIGHT_PIN
  #pragma error "BACKLIGHT_PIN must stay undefined otherwise software pwm is incorrectly used"
#endif

#define BACKLIGHT_PIN_COUNT 5
static const pin_t backlight_pins[BACKLIGHT_PIN_COUNT] = { C2, C7, D5, D6, B0 };

void backlight_init_ports(void) {
  for (uint8_t index = 0; index < BACKLIGHT_PIN_COUNT; index++) {
    setPinOutput(backlight_pins[index]);
  }
}

void backlight_set_value(uint8_t index, uint8_t level) {
  writePin(backlight_pins[index], !!level);
}

void backlight_set(uint8_t level) {
  for (uint8_t index = 0; index < BACKLIGHT_PIN_COUNT; index++) {
    backlight_set_value(index, level);
  }
}

#endif //BACKLIGHT_ENABLE
