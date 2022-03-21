/* Copyright 2022 frooastside
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define MANUFACTURER    frooastside
#define PRODUCT         Frooastboard Walnut

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 8

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define ISSI_TIMEOUT 100
#define ISSI_PERSISTENCE 0
#define ISSI_SWPULLUP PUR_0R
#define ISSI_CSPULLUP PUR_0R
#define DRIVER_COUNT 1
#define DRIVER_LED_TOTAL 48
#define DRIVER_ADDR_1 0b1010000

#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON
