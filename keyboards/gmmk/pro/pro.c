/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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
#include "pro.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  { 0,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { 1,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { 2,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { 3,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}
}, {
    { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }
}, {
    4, 4, 4, 4
} };
#endif
