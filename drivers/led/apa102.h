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

#if defined(RGBLIGHT_APA102)
#    define APA102_LED_COUNT RGBLIGHT_LED_COUNT
#elif defined(RGB_MATRIX_APA102)
#    define APA102_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#ifndef APA102_DEFAULT_BRIGHTNESS
#    define APA102_DEFAULT_BRIGHTNESS 31
#endif

#define APA102_MAX_BRIGHTNESS 31

void apa102_init(void);
void apa102_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void apa102_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void apa102_flush(void);

void apa102_set_brightness(uint8_t brightness);
