/* Copyright 2017 benlyall, MechMerlin, Lukewh
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
#pragma once

#include "quantum.h"

#ifdef RGBLIGHT_ENABLE

#include "rgblight.h"

void rgb_init(void);
void set_rgb_color(uint8_t pin, uint8_t value, uint8_t timer_value);

enum my_keycodes {
  RGB_RI = QK_KB_0,
  RGB_RD,
  RGB_GI,
  RGB_GD,
  RGB_BI,
  RGB_BD
};
#endif
