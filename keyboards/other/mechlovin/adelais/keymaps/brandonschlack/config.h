/* Copyright 2020 Brandon Schlack
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
#pragma once

#define USE_LEDS_FOR_LAYERS
#define STOPLIGHT_LED

// LEDs
#define TOP_LED    B2
#define MIDDLE_LED C15
#define BOTTOM_LED B9
// #define LED_PIN_FLIP
#ifdef LED_PIN_FLIP
    #define LED_ON(flag) !flag
#else
    #define LED_ON(flag) flag
#endif
