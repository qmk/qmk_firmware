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

#include "quantum.h"

#ifdef ACTUATION_DEPTH_ADJUSTMENT
#include "actuation_point.h"
#endif

void matrix_init_kb(void) {
#ifdef ACTUATION_DEPTH_ADJUSTMENT
    adjust_actuation_point(ACTUATION_DEPTH_ADJUSTMENT);
#endif

	matrix_init_user();
}
