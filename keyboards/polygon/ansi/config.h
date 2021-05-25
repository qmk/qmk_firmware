/*
Copyright 2020 Adam Naldal

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

#include "config_common.h"

#define DRIVER_ADDR_1 0b0110000
#define DRIVER_ADDR_2 0b0110000 // this is here for compliancy reasons.

#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 66
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

#define RGB_DISABLE_TIMEOUT 20000
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_MATRIX_CENTER { 108, 30 }
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
