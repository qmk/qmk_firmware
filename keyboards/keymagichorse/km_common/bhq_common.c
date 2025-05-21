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

#include "bhq_common.h"
#include "bhq.h"
#include "wireless.h"
#include "transport.h"
#include "km_printf.h"

#include "outputselect.h"
#include "usb_main.h"
# if defined(KB_LPM_ENABLED)
#   include "lpm.h"
#endif


// --------------------  都是用于处理按键触发的变量 --------------------
uint16_t this_down_wireless_keycode = 0;
uint32_t down_wirlees_keycode_time = 0;
static uint8_t key_ble_host_index = 0;         // 蓝牙索引
// --------------------  都是用于处理按键触发的变量 --------------------



bool process_record_bhq(uint16_t keycode, keyrecord_t *record) {

    // TODO: 使用QMK的无线键值，并且提取这里的逻辑到km_common文件夹
#   if defined(KB_LPM_ENABLED)
    lpm_timer_reset();  // 这里用于低功耗，按下任何按键刷新低功耗计时器
#endif

    // 如果是无线模式 且 没有连接的情况下 按下任意按键触发广播
    if ( (IS_WIRELESS_TRANSPORT(transport_get()) == true)  && wireless_get() != WT_STATE_CONNECTED ) 
    {
        // 检查按键值是否不在 BT_1 到 BT_11 范围
        if (keycode < BT_1 || keycode > BT_11) 
        {
            // 检查传输模式是否为蓝牙模式
            // KB_TRANSPORT_BLUETOOTH_1 在枚举 里面是2、在蓝牙通道内是0
            // 那么 2 - 2 = 0 那就是host = 0;
            // 重新打开非配对蓝牙广播。如已开启蓝牙广播或已连接，那么不会断开当前的蓝牙连接。
            bhq_AnewOpenBleAdvertising(transport_get() - 1, 15);
        }
    }

    // 蓝牙模式点按
    if(keycode == BL_SW_0 || keycode == BL_SW_1 || keycode == BL_SW_2)
    {
        if(record->event.pressed)
        {   // 赋值 并记录当前时间
            this_down_wireless_keycode = keycode;
            down_wirlees_keycode_time = timer_read32();
        }
        else
        {
            if(timer_elapsed32(down_wirlees_keycode_time) >= 80 && timer_elapsed32(down_wirlees_keycode_time) <= 800)
            {
                switch (keycode)
                {
                    case BL_SW_0:
                        key_ble_host_index = 0;
                        break;  
                    case BL_SW_1:
                        key_ble_host_index = 1;
                        break;  
                    case BL_SW_2:
                        key_ble_host_index = 2;
                        break;  
                }
                // 打开非配对模式蓝牙广播 10 = 10S
                bhq_OpenBleAdvertising(key_ble_host_index, 30);
                transport_set(key_ble_host_index + KB_TRANSPORT_BLUETOOTH_1);  
            }
            this_down_wireless_keycode = 0;
            down_wirlees_keycode_time = 0;
        }
        return false;
    }


    switch (keycode)
    {
        case BLE_TOG:
        {
            if(!record->event.pressed)
            {
                key_ble_host_index = 0;
                // 打开非配对模式蓝牙广播 10 = 10S
                bhq_OpenBleAdvertising(key_ble_host_index, 30);
                transport_set(KB_TRANSPORT_BLUETOOTH_1);
            }
            return false;
        }
        case RF_TOG:
        {
            if(!record->event.pressed)
            {
                bhq_switch_rf_easy_kb();
                transport_set(KB_TRANSPORT_RF);  
            }
            return false;
        }
        case USB_TOG:
        {
            if(!record->event.pressed)
            {
                // 切换到usb模式 并 关闭蓝牙广播
                bhq_CloseBleAdvertising();
                transport_set(KB_TRANSPORT_USB);  
            }
            return false;
        }
        case BLE_OFF:
        {
            if(!record->event.pressed)
            {
                // 关闭蓝牙广播
                bhq_CloseBleAdvertising();
            }
            return false;
        }
    }
    if(IS_WIRELESS_TRANSPORT(transport_get()) == true && wireless_get()  != WT_STATE_CONNECTED )
    {
        return false;
    }
    return true;
}

//  切换主机任务
void bhq_switch_host_task(void){
    static bool has_switched = false;
    // 蓝牙模式长按的
    if (this_down_wireless_keycode == BL_SW_0 ||
        this_down_wireless_keycode == BL_SW_1 ||
        this_down_wireless_keycode == BL_SW_2)
    {
        if (!has_switched && timer_elapsed32(down_wirlees_keycode_time) >= 1000)
        {
            has_switched = true;  // 标志位，用于只执行一次
            switch (this_down_wireless_keycode)
            {
                case BL_SW_0:
                    key_ble_host_index = 0;
                    break;
                case BL_SW_1:
                    key_ble_host_index = 1;
                    break;
                case BL_SW_2:
                    key_ble_host_index = 2;
                    break;
            }
            // 打开配对广播
            bhq_SetPairingMode(key_ble_host_index, 30);
            transport_set(key_ble_host_index + KB_TRANSPORT_BLUETOOTH_1);  
        }
    }
    else
    {
        has_switched = false;  // 按键释放或变更后重置状态
    }
}


// Keyboard level code can override this, but shouldn't need to.
// Controlling custom features should be done by overriding
// via_custom_value_command_kb() instead.
bool via_command_bhq(uint8_t *data, uint8_t length) {
    // 此逻辑删除 会失去蓝牙模块升级功能 以及蓝牙改键功能！！！！！！！
    uint8_t command_id   = data[0];
    uint8_t i = 0;

#   if defined(KB_LPM_ENABLED)
    lpm_timer_reset();  // 这里用于低功耗，刷新低功耗计时器
#endif

    km_printf("cmdid:%02x  length:%d\r\n",command_id,length);
    km_printf("read host app of data \r\n[");
    for (i = 0; i < length; i++)
    {
        km_printf("%02x ",data[i]);
    }
    km_printf("]\r\n");

    if(command_id == 0xF1)
    {
        // cmdid + 2 frame headers 
        // The third one is isack the fourth one is length and the fifth one is data frame
        BHQ_SendCmd(0, &data[4], data[3]);
        return true;
    }
    return false;
}