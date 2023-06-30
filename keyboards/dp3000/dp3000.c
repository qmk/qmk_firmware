/* Copyright 2023 deddia permana (@depermana12)
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
#include "quantum.h"

led_config_t g_led_config = {{
    { NO_LED, NO_LED, NO_LED, NO_LED},
    { 3, 2, 1, 0 },
    { 4, 5, 6, 7 }
},  {
    {  0, 32 }, { 25, 32 }, { 37, 32 }, { 75, 32 },
    { 75, 16 }, { 37, 16 }, { 25, 16 }, { 0, 16  }
},  {
     4, 4, 4, 4, 4, 4, 4, 4
    }
};

