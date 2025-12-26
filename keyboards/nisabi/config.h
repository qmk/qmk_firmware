/* Copyright 2024 RaijuInc (@RaijuInc)
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

#define JP_KEYCODES_ENABLE

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 3000
#define VBUS_DETECT_PIN D0  // USB電源検出用ピンの設定

#define EE_HANDS

#define STARTUP_DELAY 1000
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS {B5, B4, D7, D6, D4}
#define MATRIX_COL_PINS {B0, B1, B2, B3, B7, D3, D5, NO_PIN}

#define MATRIX_ROW_PINS_RIGHT {F0, F1, F4, F5, F6}
#define MATRIX_COL_PINS_RIGHT {C7, C6, B6, B5, B4, D7, D6, D4}
