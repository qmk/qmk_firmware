/* Copyright 2021 Caffeinism (@caffeinism)
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
#include "pathfinder.h"
#include "print.h"

uint32_t loop_timeout_timer;
void keyboard_post_init_kb(void) {
    loop_timeout_timer = timer_read32();
    debug_enable=true;
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if (timer_elapsed32(loop_timeout_timer) > LOOP_TIMEOUT){
        reset_keyboard();
    }
}