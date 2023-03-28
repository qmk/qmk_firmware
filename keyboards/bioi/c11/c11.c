/* Copyright 2022 Basic I/O Instruments (@scottywei)
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

#include "c11.h"

led_config_t g_led_config = {{// Key Matrix to LED Index
                              {5, 6, 7, 8, 9, 10},
                              {4, 3, 2, 1, 0}},
                             {// LED Index to Physical Position
                              {202, 64},
                              {156, 64},
                              {113, 64},
                              {67, 64},
                              {23, 64},
                              {0, 0},
                              {45, 0},
                              {90, 0},
                              {134, 0},
                              {179, 0},
                              {224, 0}},
                             {// LED Index to Flag
                              1, 4, 4, 4, 1, 1, 4, 4, 4, 4, 1}};

void keyboard_pre_init_kb(void) {
    setPinOutput(RGB_UG_CONTROL_PIN);
    setPinInput(BATT_LEVEL_PIN);
    keyboard_pre_init_user();
}