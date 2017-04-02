/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "keyboard.h"
#include "hook.h"

/* -------------------------------------------------
 * Definitions of default hooks
 * ------------------------------------------------- */

__attribute__((weak))
void hook_keyboard_loop(void) {}

__attribute__((weak))
void hook_matrix_change(keyevent_t event) {
    (void)event;
}

__attribute__((weak))
void hook_default_layer_change(uint32_t default_layer_state) {
    (void)default_layer_state;
}

__attribute__((weak))
void hook_layer_change(uint32_t layer_state) {
    (void)layer_state;
}

__attribute__((weak))
void hook_keyboard_leds_change(uint8_t led_status) {
    keyboard_set_leds(led_status);
}

__attribute__((weak))
void hook_bootmagic(void) {}
