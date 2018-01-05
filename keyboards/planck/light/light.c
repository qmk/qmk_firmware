/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
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

#include "light.h"

void matrix_init_kb(void) {

    // Turn status LED on
    DDRD |= (1<<6);
    PORTD |= (1<<6);

    matrix_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{   
    return process_record_user(keycode, record);
}

uint16_t backlight_task_counter = 0;

void matrix_scan_kb(void)
{
    matrix_scan_user();
}