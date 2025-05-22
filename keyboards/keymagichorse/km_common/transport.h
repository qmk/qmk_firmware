/* Copyright 2025 keymagichorse
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

// Very few codes are borrowed from https://www.keychron.com

#pragma once
typedef enum {
    KB_TRANSPORT_NONE,          // 0
    KB_TRANSPORT_USB,           // 1
    KB_TRANSPORT_BLUETOOTH_1,   // 2
    KB_TRANSPORT_BLUETOOTH_2,   // 3
    KB_TRANSPORT_BLUETOOTH_3,   // 4
    KB_TRANSPORT_RF,            // 5
} kb_transport_t;
// 判断是否为蓝牙通道（通道 1~3）
#define IS_BLE_TRANSPORT(t) \
    ((t) >= KB_TRANSPORT_BLUETOOTH_1 && (t) <= KB_TRANSPORT_BLUETOOTH_3)

// 判断是否为无线通信（蓝牙或 2.4G）
#define IS_WIRELESS_TRANSPORT(t) \
    ((t) >= KB_TRANSPORT_BLUETOOTH_1 && (t) <= KB_TRANSPORT_RF)

// 判断是否为无线通信（蓝牙或 2.4G）
#define IS_RF_TRANSPORT(t) \
    ((t) == KB_TRANSPORT_RF)


// 判断是否为 USB
#define IS_USB_TRANSPORT(t) \
    ((t) == KB_TRANSPORT_USB)

void transport_set(kb_transport_t new_transport);
kb_transport_t transport_get(void);