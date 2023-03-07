/* Copyright 2023 Christoph Jabs (BifbofII)
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

// Configuration for HID OLED
#ifdef HID_OLED
#    define SPLIT_TRANSACTION_IDS_USER USER_SYNC_HID_OLED
#    define RAW_USAGE_PAGE 0xFF61
#    define RAW_USAGE_ID 0x42
#endif

#ifdef GAMING_ENABLE
#    define TRI_LAYER_LOWER_LAYER 6
#else
#    define TRI_LAYER_LOWER_LAYER 5
#endif
#define TRI_LAYER_UPPER_LAYER TRI_LAYER_LOWER_LAYER + 1
#define TRI_LAYER_ADJUST_LAYER TRI_LAYER_UPPER_LAYER + 1
