/* Copyright 2019-2020 DMQ Design
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 * 
 * The k03, k13, and k23 keys are the encoder pushbuttons.
 */
#define LAYOUT(k00, k01, k02, k03, \
               k10, k11, k12, k13, \
               k20, k21, k22, k23, \
               k30, k31, k32  \
               ) {            \
            {k00, k10, k20, k30, k23}, \
            {k01, k11, k21, k31, k13}, \
            {k02, k12, k22, k32, k03}, \
            }
