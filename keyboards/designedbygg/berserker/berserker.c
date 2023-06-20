/* Copyright 2023 Dimitris Mantzouranis <d3xter93@gmail.com>
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
#ifndef RGB_MATRIX_ENABLE
void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int i = 0; i < TIME_US2I(MATRIX_IO_DELAY); ++i) {
        __asm__ volatile("" ::: "memory");
    }
}
#endif
#ifdef LED_WIN_LOCK_PIN
/* Handle the Win Lock LED */
void keyboard_pre_init_kb(void) {
	setPinOutput(LED_WIN_LOCK_PIN);
	writePin(LED_WIN_LOCK_PIN, !LED_PIN_ON_STATE);
}

void housekeeping_task_kb(void) {
	writePin(LED_WIN_LOCK_PIN,!keymap_config.no_gui);
}
#endif
