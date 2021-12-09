/*
Copyright 2021 MajorKoos <github.com/majorkoos>

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
#include "vea.h"

void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) { vea_setleds(start_led, num_leds); }

void vea_rgb_init(void) { i2c_init(); }

// Setleds for standard RGB
void vea_setleds(LED_TYPE *ledarray, uint16_t leds) {
    static bool s_init = false;
    if (!s_init) {
        vea_rgb_init();
        s_init = true;
    }

    i2c_transmit(WS2812_ADDRESS, (uint8_t *)ledarray, sizeof(LED_TYPE) * (leds >> 1), WS2812_TIMEOUT);
    i2c_transmit(WS2812_ADDRESS_SPLIT, (uint8_t *)ledarray+(sizeof(LED_TYPE) * (leds >> 1)), sizeof(LED_TYPE) * (leds - (leds >> 1)), WS2812_TIMEOUT);
};
