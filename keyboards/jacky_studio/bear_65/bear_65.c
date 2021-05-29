/* Copyright 2020 MudkipMao
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

#include "bear_65.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
	// Key Matrix to LED Index
	{ NO_LED, 4     , 4     , 4     , 4     , 3     , 3     , 3     , 3     , 2     , 2     , 2     , 2     , 1     , NO_LED},
	{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 6     },
	{ 6     , NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 6     , 0     , 6     },
	{ 7     , 5     , NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 11    },
	{ 7     , NO_LED, NO_LED, 8     , NO_LED, 8     , 9     , NO_LED, 9     , 7     , 10    , 11    , 11    , 11    , 1     },
}, {
	// LED Index to Physical Position
	{224, 32}, {224, 10}, {192, 10}, {128, 25},
    {70, 10}, {16, 10}, {16, 32}, {16, 64},
    {64, 64}, {112, 64}, {176, 64}, {224, 64}
}, {
	// LED Index to Flag
	LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
	LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
} };
#endif
