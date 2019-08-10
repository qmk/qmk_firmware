    
/* Copyright 2019
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
#include "cospad.h"

#ifdef BACKLIGHT_ENABLE

void backlight_init_ports(void) {
  setPinOutput(F7);
}

void backlight_set(uint8_t level) {
  writePin(F7, !!level);
}

void backlight_task(void) {
    // do nothing - as default implementation of software PWM does not work
}

#endif //BACKLIGHT_ENABLE
