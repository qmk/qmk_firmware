/* Copyright 2022 3araht
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

#define USB_VBUS_PIN GP24

/* ws2812 RGB LED */
#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral

/* ws2812 RGB MATRIX */
#define RGB_MATRIX_KEYPRESSES  // reacts to keypresses

//  for all fingers used at once.
#define LED_HITS_TO_REMEMBER 10

/*              RGB darker COLORS             */
#define RGB_DARKWHITE 0x66, 0x66, 0x66
#define RGB_DARKRED 0x66, 0x0, 0x0
#define RGB_DARKCORAL 0x66, 0x31, 0x1E
#define RGB_DARKORANGE 0x66, 0x33, 0x0
#define RGB_DARKGOLDENROD 0x56, 0x42, 0xD
#define RGB_DARKGOLD 0x66, 0x56, 0x0
#define RGB_DARKYELLOW 0x66, 0x66, 0x0
#define RGB_DARKCHARTREUSE 0x33, 0x66, 0x0
#define RGB_DARKGREEN 0x0, 0x66, 0x0
#define RGB_DARKSPRINGGREEN 0x0, 0x66, 0x33
#define RGB_DARKTURQUOISE 0x1C, 0x2C, 0x2A
#define RGB_DARKTEAL 0x0, 0x33, 0x33
#define RGB_DARKCYAN 0x0, 0x66, 0x66
#define RGB_DARKAZURE 0x3D, 0x62, 0x66
#define RGB_DARKBLUE 0x0, 0x0, 0x66
#define RGB_DARKPURPLE 0x30, 0x0, 0x66
#define RGB_DARKMAGENTA 0x66, 0x0, 0x66
#define RGB_DARKPINK 0x66, 0x33, 0x4C

#define MIDI_ADVANCED
// Initial velocity value (avoid using 127 since it is used as a special number in some sound sources.)
#define MIDI_INITIAL_VELOCITY 117
