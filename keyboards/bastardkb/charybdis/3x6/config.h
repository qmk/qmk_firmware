/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#define MATRIX_ROWS 8 // Rows are doubled-up.
#define MATRIX_COLS 6

#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed. */
#define DEBOUNCE 5

/* Trackball angle adjustment. */
#define ROTATIONAL_TRANSFORM_ANGLE -25

/* RGB settings. */
#ifdef RGB_MATRIX_ENABLE
#    define RGBLED_NUM 42
#    define RGBLED_SPLIT \
        { 21, 21 }
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#endif
