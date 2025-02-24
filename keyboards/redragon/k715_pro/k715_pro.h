/* Copyright 2023 temp4gh
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

#include "quantum.h"

#define BLE_HID_REPORT_TYPE_NORMAL_KEY  0x1
#define BLE_HID_REPORT_TYPE_MOUSE_KEY   0x2
#define BLE_HID_REPORT_TYPE_EXTRA_KEY   0x3
#define BLE_HID_REPORT_TYPE_SYSTEM_KEY  0x4
#define BLE_HID_REPORT_TYPE_ALL_KEY     0x5

enum {
    BT_CHN1,
    BT_CHN2,
    BT_CHN3,
	NEW_SAFE_RANGE
};

#define NORMAL_LED_FLAG_BIT    (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER)

