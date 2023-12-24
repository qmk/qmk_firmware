/* Copyright 2021 Islam Sharabash
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


/* key matrix size */
// rows are doubled for split
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define RGB_MATRIX_LED_COUNT 132

#ifdef RGB_MATRIX_ENABLE
// At the default flush limit of 16ms (~62.5 fps), the matrix scan rate is approximately
// ~140 scans per second under full load (when changes are being made to the LED state).
// Such a low scan rate will have impact the keyboard's accuracy for faster typists.
//
// With RGB completely disabled, the matrix scan rate is ~660 scans per second, and typing
// accuracy feels on par with the Dygma Raise Neuron.
//
// At 100ms (10 fps), the matrix scan rate is ~355 scans per second under full load, and typing
// accuracy is reasonably good.
#define RGB_MATRIX_LED_FLUSH_LIMIT 100
#define RGB_MATRIX_SLEEP // turn off effects when suspended

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
//#    define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#endif
