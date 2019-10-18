/* Copyright 2019
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

#include "config_common.h"

// wiring of each half
#define MATRIX_ROW_PINS { F5 }
#define MATRIX_COL_PINS { F7 }
#define SPLIT_HAND_PIN F0
#define SOFT_SERIAL_PIN D1

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

// teensy has vbus detection issues - use usb detection instead
#define SPLIT_USB_DETECT
