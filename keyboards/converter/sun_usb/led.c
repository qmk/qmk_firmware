/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include "led.h"
#include "print.h"
#include "uart.h"

bool led_update_kb(led_t led_state)
{
    bool res = led_update_user(led_state);
    if (res) {
        uint8_t sun_led = 0;
        if (led_state.num_lock)    sun_led |= (1<<0);
        if (led_state.compose)     sun_led |= (1<<1);
        if (led_state.scroll_lock) sun_led |= (1<<2);
        if (led_state.caps_lock)   sun_led |= (1<<3);

        uart_write(0x0E);
        uart_write(sun_led);
    }
    return res;
}
