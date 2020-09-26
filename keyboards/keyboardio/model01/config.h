/*
Copyright 2018 James Laird-Wah

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

#include <config_common.h>

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1209
#define PRODUCT_ID      0x2301
#define DEVICE_VER      0x0001
#define MANUFACTURER    Keyboardio
#define PRODUCT         Model 01
#define DESCRIPTION     (QMK)

/* key matrix size; rows are doubled for split */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* The scanners already debounce for us */
#define DEBOUNCE 0

/* RGB matrix constants */
#define DRIVER_LED_TOTAL 64
