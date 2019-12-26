/* Copyright 2019 Josh Hinnebusch
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

// place overrides here

#ifndef HSV_SOFT_PINK
    #define HSV_SOFT_PINK  255, 110, 100 // Define custom "soft pink" color
#endif

#ifndef HSV_SOFT_WHITE
    #define HSV_SOFT_WHITE  0, 0, 90 // Define custom "soft white" color
#endif

#ifndef HSV_WARM_WHITE
    #define HSV_WARM_WHITE  41, 105, 90 // Define custom "warm white" color
#endif

#ifndef HSV_SOFT_RED
    #define HSV_SOFT_RED  0, 240, 160 // Define custom "soft red" color
#endif

#ifndef HSV_SOFT_BLUE
    #define HSV_SOFT_BLUE  159, 180, 160 // Define custom "soft blue" color
#endif

#ifndef HSV_BLACK
    #define HSV_BLACK  0, 0, 0  // Define 'black' color, more like 'LED off' (H, S, V)
#endif
// not sure why i need to also define this here, as it is already in hbcp.h
