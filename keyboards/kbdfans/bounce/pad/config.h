/* Copyright 2022 DZTECH <moyi4681@Live.cn>
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

#define MATRIX_ROWS 6
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { C7, B7, B6, B0, B1, B2 }
#define MATRIX_COL_PINS { B5, B4, D0, C2 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define LED_NUM_LOCK_PIN C6
#define LED_PIN_ON_STATE 1
#define DEBOUNCE 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
