/*
Copyright 2017 Balz Guenat

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#ifdef ACTUATION_DEPTH_ADJUSTMENT
#    include "ad5258.h"

// see keymaps/actuation-point-example to see how these functions can be used.
void actuation_point_up(void);
void actuation_point_down(void);

// be careful with this.
void adjust_actuation_point(int offset);
#endif
