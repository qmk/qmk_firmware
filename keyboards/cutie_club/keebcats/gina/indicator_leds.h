/*
Copyright 2023 Cutie Club

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

#pragma once

#define SYNCHRONISE_HOST_LED_STATUS() led_update_kb(host_keyboard_led_state());

enum indicator_key {
    NUM_LOCK = 0,
    SCROLL_LOCK = 1,
    CAPS_LOCK = 2
};

int indicator_leds_init(void);

void set_enabled_indicator_key(enum indicator_key key);
enum indicator_key get_enabled_indicator_key(void);
