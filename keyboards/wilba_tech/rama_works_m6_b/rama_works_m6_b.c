/* Copyright 2018 Jason Williams (Wilba)
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
#ifndef RGB_BACKLIGHT_M6_B
#    error RGB_BACKLIGHT_M6_B not defined, you done goofed somehao, brah
#else
#    include "drivers/led/issi/is31fl3218.h"
#endif

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_BACKLIGHT_M6_B)
const is31fl3218_led_t PROGMEM g_is31fl3218_leds[IS31FL3218_LED_COUNT] = {
    {OUT1,  OUT2,  OUT3},
    {OUT4,  OUT5,  OUT6},
    {OUT7,  OUT8,  OUT9},
    {OUT10, OUT11, OUT12},
    {OUT13, OUT14, OUT15},
    {OUT16, OUT17, OUT18}
};
#endif
