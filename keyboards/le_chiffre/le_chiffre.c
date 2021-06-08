/* Copyright 2020 tominabox1
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
#include "le_chiffre.h"

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 3, 4, NO_LED, 5, 6 },
  { NO_LED, NO_LED, 10, NO_LED, NO_LED },
  { NO_LED, NO_LED, 9, NO_LED, NO_LED },
  { 2, 1, 0, 8, 7 }
}, {

  // LED Index to Physical Position
  { 128, 64 }, { 77, 64 }, { 0, 48 }, { 0, 0 }, { 115, 0 }, { 166, 0 }, { 255, 0 }, { 255, 48 }, { 178, 64 }, { 128, 40 }, { 128, 30 }
}, {

  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };
