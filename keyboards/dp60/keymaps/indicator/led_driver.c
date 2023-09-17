/**
 * led_driver.c
 *
 Copyright 2020 astro <yuleiz@gmail.com>
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

#undef WS2812_DI_PIN
#define WS2812_DI_PIN RGB_INDICATOR_PIN
#define ws2812_setleds indicator_setleds
#define ws2812_setleds_pin indicator_setleds_pin
#include "ws2812_bitbang.c"

void indicator_write(LED_TYPE *start_led, uint8_t num_leds)
{
    indicator_setleds(start_led, num_leds);
}
