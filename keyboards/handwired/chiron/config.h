/*
Copyright 2019 Mike Hix

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


// Pro Micro Pins          4,  6,  7,  8,  9
#define MATRIX_ROW_PINS { D4, D7, E6, B4, B5 }
// Pro Micro Pins         A3, A2, A1, A0, 15, 14, 16
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }


// Pro Micro Pins      RX1
#define SPLIT_HAND_PIN D2

#define DIODE_DIRECTION COL2ROW

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN D3
#define RGBLED_NUM 4
