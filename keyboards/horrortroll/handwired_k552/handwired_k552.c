/* Copyright 2021 HorrorTroll <https://github.com/HorrorTroll>
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

#include "handwired_k552.h"

// OLED animation
#include "lib/logo.c"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    { }
}, {
    {152,  0}, {165,  0}, {190,  0}, {205,  0},
    {224, 21}, {224, 43}, {224, 54},
    {188, 64}, {172, 64}, {156, 64}, {140, 64}, {115, 64}, {99 , 64}, {75 , 64}, {59 , 64}, {43 , 64}, {26 , 64},
    {0  , 15}, {0  , 50}, {0  , 39},
    {18 ,  0}, {36 ,  0}, {57 ,  0}, {67 ,  0}
}, {
    2, 2, 2, 2,       2, 2, 2, 2,
    2,                         2,
    2,                         2,
    2,                         2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
} };
#endif

#ifdef OLED_ENABLE
    uint16_t startup_timer; 

    oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
        startup_timer = timer_read();

        return rotation;
    }

    bool oled_task_kb(void) {
        static bool finished_logo = false;

        if ((timer_elapsed(startup_timer) < 5000) && !finished_logo) {
            render_logo();
        } else {
            finished_logo = true;
			
            if (!oled_task_user()) {
                return false;
            }
        }

        return true;
    }
#endif
