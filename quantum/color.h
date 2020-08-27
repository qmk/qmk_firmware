/* Copyright 2017 Jason Williams
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

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <stdbool.h>

#if defined(__GNUC__)
#    define PACKED __attribute__((__packed__))
#else
#    define PACKED
#endif

#if defined(_MSC_VER)
#    pragma pack(push, 1)
#endif

#ifdef RGBW
#    define LED_TYPE cRGBW
#else
#    define LED_TYPE RGB
#endif

// only set if using WS2812B-2020, fixes LED bit order
// If define is not set, the red and green are reversed
#ifdef LED_TYPE_WS2812B_2020
// WS2812B-2020 specific layout
typedef struct PACKED {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} cRGB;
#else // WS2812C
typedef struct PACKED {
    uint8_t g;
    uint8_t r;
    uint8_t b;
} cRGB;

#endif
typedef cRGB RGB;

// WS2812 specific layout
typedef struct PACKED {
    uint8_t g;
    uint8_t r;
    uint8_t b;
    uint8_t w;
} cRGBW;

typedef struct PACKED {
    uint8_t h;
    uint8_t s;
    uint8_t v;
} HSV;

#if defined(_MSC_VER)
#    pragma pack(pop)
#endif

RGB hsv_to_rgb(HSV hsv);
#ifdef RGBW
void convert_rgb_to_rgbw(LED_TYPE *led);
#endif
#endif  // COLOR_H
