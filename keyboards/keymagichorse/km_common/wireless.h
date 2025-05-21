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
    WT_STATE_RESET,               // 复位状态           0
    WT_STATE_INITIALIZED,         // 初始化完成状态      1
    WT_STATE_ADV_UNPAIRED,        // 非配对蓝牙广播中    2
    WT_STATE_ADV_PAIRING,         // 正在配对的广播中    3
    WT_STATE_DISCONNECTED,        // 未连接、未广播      4
    WT_STATE_CONNECTED,           // 已连接             5
} wt_state_t;

void wireless_ble_hanlde_kb(uint8_t host_index,uint8_t advertSta,uint8_t connectSta,uint8_t pairingSta);
void wireless_rf24g_hanlde_kb(uint8_t connectSta,uint8_t pairingSta);
wt_state_t wireless_get(void);
