/*
Copyright 2022 Yoga Benggolo

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

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D2  // Pin D2 is labeled with RX on the PCB

// Refers to AVR Pins, not Arduino Pins
#undef MATRIX_COL_PINS
#undef MATRIX_ROW_PINS
#define MATRIX_COL_PINS { D0, D4, C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS { F5, F6, F7, B1, B3, B2, B6 }

