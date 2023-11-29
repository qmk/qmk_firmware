/* Copyright 2020 Aldehir Rojas
 * Copyright 2017 Mikkel (Duckle29)
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

#include "color.h"

#if defined(RGBLED_NUM)
#    define APA102_LED_COUNT RGBLED_NUM
#elif defined(RGB_MATRIX_LED_COUNT)
#    define APA102_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#ifndef APA102_DEFAULT_BRIGHTNESS
#    define APA102_DEFAULT_BRIGHTNESS 31
#endif

#define APA102_MAX_BRIGHTNESS 31

extern uint8_t apa102_led_brightness;

/* User Interface
 *
 * Input:
 *         start_led:          An array of GRB data describing the LED colors
 *         num_leds:           The number of LEDs to write
 *
 * The functions will perform the following actions:
 *         - Set the data-out pin as output
 *         - Send out the LED data
 */
void apa102_setleds(rgb_led_t *start_led, uint16_t num_leds);
void apa102_set_brightness(uint8_t brightness);
