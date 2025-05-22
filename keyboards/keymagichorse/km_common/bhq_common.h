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
#include "km_printf.h"
#include "transport.h"
#include "wireless.h"

enum keyboard_user_keycodes {
    BT_1 = QK_USER_28,
    BT_2,
};
#define BLE_TOG     OU_BT    // 切换蓝牙输出 并 开启蓝牙广播（非配对类型）
#define RF_TOG      OU_2P4G    // 切换 2.4ghz输出
#define USB_TOG     OU_USB    // 打开USB
#define BL_SW_0     BT_PRF1    // 开启蓝牙通道0  短按打开广播 长按开启配对广播
#define BL_SW_1     BT_PRF2    // 开启蓝牙通道1  短按打开广播 长按开启配对广播
#define BL_SW_2     BT_PRF3    // 开启蓝牙通道2  短按打开广播 长按开启配对广播
#define BLE_RESET   BT_1    // 删除当前蓝牙绑定
#define BLE_OFF     BT_2    // 关闭蓝牙连接

bool process_record_bhq(uint16_t keycode, keyrecord_t *record);
void bhq_switch_host_task(void);
bool via_command_bhq(uint8_t *data, uint8_t length);