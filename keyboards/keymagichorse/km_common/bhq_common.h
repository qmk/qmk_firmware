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
#include "quantum.h"
#include "config.h"
#include "km_printf.h"
#include "transport.h"
#include "wireless.h"


// 切换输出通道（蓝牙 / 2.4G / USB）
// 切换到蓝牙输出，并开启广播（非配对类型）
#ifndef BLE_TOG
#   define BLE_TOG OU_BT       
#endif
// 切换到 2.4GHz 输出
#ifndef RF_TOG
#   define RF_TOG OU_2P4G      
#endif
// 切换到 USB 输出
#ifndef USB_TOG
#   define USB_TOG OU_USB      
#endif

// 蓝牙通道控制（短按开启广播，长按进入配对广播）
// 蓝牙通道 0
#ifndef BL_SW_0
#   define BL_SW_0 BT_PRF1     
#endif
// 蓝牙通道 1
#ifndef BL_SW_1
#   define BL_SW_1 BT_PRF2      
#endif
// 蓝牙通道 2
#ifndef BL_SW_2
#   define BL_SW_2 BT_PRF3      
#endif

// 蓝牙控制功能
// 蓝牙复位
#ifndef BLE_RESET
#   define BLE_RESET    QK_USER_28      
#endif
 // 关闭蓝牙连接
#ifndef BLE_OFF
#   define BLE_OFF      QK_USER_29       
#endif

bool process_record_bhq(uint16_t keycode, keyrecord_t *record);
void bhq_switch_host_task(void);
bool via_command_bhq(uint8_t *data, uint8_t length);