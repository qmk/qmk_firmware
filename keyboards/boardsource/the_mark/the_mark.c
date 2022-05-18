/* Copyright 2020 Boardsource
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

#include "the_mark.h"

/* Map physical under glow LEDs for RGB matrix support */
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
	// Key Matrix to LED Index
	{ 10    , NO_LED, 9     , NO_LED, 8     , 7     , NO_LED, 6     , 5     , NO_LED, 4     , 3     , NO_LED, 2     , NO_LED, 1      },
	{ 11    , NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 0      },
	{ 12    , NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 23     },
	{ 13    , NO_LED, 14    , NO_LED, 15    , 16    , NO_LED, 17    , 18    , NO_LED, 19    , 20    , NO_LED, 21    , NO_LED, NO_LED },
	{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 22     },
}, {
	// LED Index to Physical Position
	{224, 42}, {224, 21}, {209, 21}, {179, 21}, {164, 21}, {134, 21}, {119, 21}, {89, 21}, {74, 21}, {45, 21}, {30, 21}, {30, 42},
	{30, 64}, {30, 85}, {45, 85}, {74, 85}, {89, 85}, {119, 85}, {134, 85}, {164, 85}, {179, 85}, {209, 85}, {224, 85}, {224, 64}
}, {
	// LED Index to Flag
	LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
	LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
	LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
} };


void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
