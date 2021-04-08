/* Copyright 2020 Joseph Wasson
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

#include "solarized.h"

#define MAKE_COLOR(_H, _S, _V) \
  { .h = (((uint32_t)_H) * 255) / 360, .s = (((uint16_t)_S) * 255) / 100, .v = (((uint16_t)_V) * 255) / 100 }

solarized_t solarized = {
  .base03   = MAKE_COLOR(193, 100,  21),
  .base02   = MAKE_COLOR(192,  90,  26),
  .base01   = MAKE_COLOR(194,  25,  46),
  .base00   = MAKE_COLOR(195,  23,  51),
  .base0    = MAKE_COLOR(186,  13,  59),
  .base1    = MAKE_COLOR(180,   9,  63),
  .base2    = MAKE_COLOR( 44,  11,  93),
  .base3    = MAKE_COLOR( 44,  10,  99),
  .yellow   = MAKE_COLOR( 45, 100,  71),
  .orange   = MAKE_COLOR( 18,  89,  80),
  .red      = MAKE_COLOR(  1,  79,  86),
  .magenta  = MAKE_COLOR(331,  74,  83),
  .violet   = MAKE_COLOR(237,  45,  77),
  .blue     = MAKE_COLOR(205,  82,  82),
  .cyan     = MAKE_COLOR(175,  74,  63),
  .green    = MAKE_COLOR( 68, 100,  60),
};
