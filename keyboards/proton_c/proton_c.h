/* Copyright 2018 Jack Humbert
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
#include "quantum.h"

// readability
#define ___ KC_NO

/* The board is divided into regions. North-East, North-West, South-East, and South-West */
#define LAYOUT( \
  NE00, NE01, NE02, NE03, NE04, NE05, NE06, NE07, NEO8, NE09, \
  NW10, NW11, NW12, NW13, NW14, NW15, NW16, NW17, \
  SE18, SE19, SE20, SE21, \
  SW22, SW23, SW24, SW25, SW26  \
) { \
  {  NE00, NE01, NE02, NE03, NE04, NE05, NE06, NE07, NEO8, NE09 }, \
  {  NW10, NW11, NW12, NW13, NW14, NW15, NW16, NW17, ___, ___ }, \
  {  SE18, SE19, SE20, SE21, ___, ___, ___, ___, ___, ___ }, \
  {  SW22, SW23, SW24, SW25, SW26, ___, ___, ___, ___, ___ }  \
}

