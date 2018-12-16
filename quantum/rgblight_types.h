/*
 * light weight WS2812 lib include
 *
 * Version 2.3  - Nev 29th 2015
 * Author: Tim (cpldcpu@gmail.com)
 *
 * Please do not change this file! All configuration is handled in "ws2812_config.h"
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

#ifndef RGBLIGHT_TYPES
#define RGBLIGHT_TYPES

#ifdef __AVR__
  #include <avr/io.h>
#endif

#ifdef RGBW
  #define LED_TYPE struct cRGBW
#else
  #define LED_TYPE struct cRGB
#endif


/*
 *  Structure of the LED array
 *
 * cRGB:     RGB  for WS2812S/B/C/D, SK6812, SK6812Mini, SK6812WWA, APA104, APA106
 * cRGBW:    RGBW for SK6812RGBW
 */

struct cRGB  { uint8_t g; uint8_t r; uint8_t b; };
struct cRGBW { uint8_t g; uint8_t r; uint8_t b; uint8_t w;};

#endif
