/*
Copyright 2021 mtei

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

#define MATRIX_OUT_PORTS  (Port_A, MCU_GPIO, A0)
#define MATRIX_OUT_PINS  \
    (0, Port_A, 4), \
    (1, Port_A, 5), \
    (2, Port_A, 6), \
    (3, Port_A, 7), \
    (4, Port_A, 8)
#define MATRIX_IN_PORTS \
    (Port_A, MCU_GPIO, A0), (Port_B, MCU_GPIO, B0)
#define MATRIX_IN_PINS \
    (0, Port_A, 2), \
    (1, Port_A, 1), \
    (2, Port_A, 0), \
    (3, Port_B, 8), \
    (4, Port_B, 13), \
    (5, Port_B, 14), \
    (6, Port_B, 15), \
    (7, Port_B, 9), \
    (8, Port_B, 0), \
    (9, Port_B, 1), \
    (10, Port_B, 2), \
    (11, Port_B, 3), \
    (12, Port_B, 4), \
    (13, Port_B, 5), \
    (14, Port_B, 6), \
    (15, Port_B, 7)
