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

#define MATRIX_OUT_PORTS \
    (Port_D, MCU_GPIO, D0), \
    (Port_C, MCU_GPIO, C0), \
    (Port_E, MCU_GPIO, E0), \
    (Port_B, MCU_GPIO, B0)
#define MATRIX_OUT_PINS  \
    (0, Port_D, 4), \
    (1, Port_C, 6), \
    (2, Port_D, 7), \
    (3, Port_E, 6), \
    (4, Port_B, 4)
#define MATRIX_EXTENSION_74HC157 B5
#define MATRIX_IN_PORTS \
    (Port_Fa, MCU_GPIOa, F0), \
    (Port_Fb, MCU_GPIOb, F0), \
    (Port_Ba, MCU_GPIOa, B0), \
    (Port_Bb, MCU_GPIOb, B0)
#define MATRIX_IN_PINS \
    (0, Port_Fa, 4), \
    (1, Port_Fb, 4), \
    (2, Port_Fa, 5), \
    (3, Port_Fb, 5), \
    (4, Port_Fa, 6), \
    (5, Port_Fb, 6), \
    (6, Port_Fa, 7), \
    (7, Port_Fb, 7), \
    (8, Port_Bb, 6), \
    (9, Port_Ba, 6), \
    (10, Port_Bb, 2), \
    (11, Port_Ba, 2), \
    (12, Port_Bb, 3), \
    (13, Port_Ba, 3), \
    (14, Port_Bb, 1), \
    (15, Port_Ba, 1)
