/*
Copyright 2019 Ryota Goto

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

// Fix for prototype missing COL0, COL1, using backlight and RGB underglow I/O pins
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { C4, B7, C6, C7, B6, B5, B4, B3, B2, B1, B0, D6 }

// This directs backlight code to use a disconnected pin, so the firwmare still has
// backlight code and VIA support even though it doesn't do anything.
#undef BACKLIGHT_PIN
#define BACKLIGHT_PIN D1