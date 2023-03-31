/*
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { F4, F7, C6, D4, B5 }
#define MATRIX_COL_PINS \
    { F6, F5, B6, D7, E6, B4 }

/* Handedness. */
#define MASTER_RIGHT

/* RGB settings. */
#define RGB_DI_PIN D3

/* PMW3360 settings. */
#define POINTING_DEVICE_CS_PIN F0
