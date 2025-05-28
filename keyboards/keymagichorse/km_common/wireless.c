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
#include "bhq.h"
#include "report_buffer.h"
#include "wireless.h"
#include "transport.h"
#include "battery.h"
#include "km_printf.h"
#ifdef RAW_ENABLE
#   include "raw_hid.h"
#endif

// 这里用于处理连接的回调
static wt_state_t wt_state = WT_STATE_INITIALIZED;  // 默认初始化

// 无线模块 蓝牙状态回调
__attribute__((weak))  void wireless_ble_hanlde_kb(uint8_t host_index,uint8_t advertSta,uint8_t connectSta,uint8_t pairingSta){}
void wireless_ble_hanlde(uint8_t host_index, uint8_t advertSta,uint8_t connectSta,uint8_t pairingSta)
{

    // 蓝牙没有连接 && 蓝牙广播开启  && 蓝牙配对模式
    if(connectSta != 1 && advertSta == 1 && pairingSta == 1)
    {
        wt_state = WT_STATE_ADV_PAIRING;
    }
    // 蓝牙没有连接 && 蓝牙广播开启  && 蓝牙非配对模式
    else if(connectSta != 1 && advertSta == 1 && pairingSta == 0)
    {
        wt_state = WT_STATE_ADV_UNPAIRED;
    }
    // 无连接 无广播
    else if(connectSta == 0 && advertSta == 0)
    {
        wt_state = WT_STATE_DISCONNECTED;
    }
    // 蓝牙已连接
    if(connectSta == 1)
    {
        report_buffer_clear();// 已连接时，清空一下
        battery_read_and_update_data();
        wt_state = WT_STATE_CONNECTED;
    }
    wireless_ble_hanlde_kb(host_index, advertSta, connectSta, pairingSta);
}

// 无线模块 2.4g状态回调
__attribute__((weak))  void wireless_rf24g_hanlde_kb(uint8_t connectSta,uint8_t pairingSta){}
void wireless_rf24g_hanlde(uint8_t connectSta,uint8_t pairingSta)
{   // 配对状态目前没有使用上，暂时没有做无线配对的功能
    if(connectSta == 1)
    {
        wt_state = WT_STATE_CONNECTED;
        report_buffer_clear();// 已连接时，清空一下
    }
    else if(connectSta == 0)
    {
        wt_state = WT_STATE_DISCONNECTED;
    }
    wireless_rf24g_hanlde_kb(connectSta, pairingSta);
}

// bhq模块状态返回处理
void BHQ_wireless_state_handle(uint8_t cmdid, uint8_t *dat) 
{
    uint8_t advertSta = 0;      // 蓝牙广播状态
    uint8_t connectSta = 0;     // 连接状态
    uint8_t pairingSta = 0;     // 蓝牙是否开启配对广播
    uint8_t host_index = 255;   // 蓝牙通道 这里是模块返回的

    if(cmdid != BHQ_ACK_RUN_STA_CMDID)
    {
        return;
    }
    host_index = dat[2];
    advertSta = BHQ_GET_BLE_ADVERT_STA(dat[1]);
    connectSta = BHQ_GET_BLE_CONNECT_STA(dat[1]);
    pairingSta = BHQ_GET_BLE_PAIRING_STA(dat[1]);

        
    km_printf("[RSSI:%d]\t",dat[0]);
    km_printf("[advertSta: %d]\t", advertSta);
    km_printf("[connectSta: %d]\t", connectSta); // 0 = 断开, 1 = 已连接, 2 = 超时
    km_printf("[pairingSta: %d]\t", pairingSta);
    km_printf("[host_index:%d]\n",host_index);
    
    // 返回运行状态时,这边把host_index也处理好给用户
    switch (transport_get())
    {
        case KB_TRANSPORT_BLUETOOTH_1:
        case KB_TRANSPORT_BLUETOOTH_2:
        case KB_TRANSPORT_BLUETOOTH_3:
        {

            wireless_ble_hanlde(host_index , advertSta, connectSta, pairingSta);
            break;
        }
        case KB_TRANSPORT_RF:
        {
            wireless_rf24g_hanlde(connectSta, pairingSta);
            break;
        }
        default:
        {
            break;
        }
    }
}


// 模块协议处理 用户函数
void BHQ_Protocol_Process_user(uint8_t *dat, uint16_t length) 
{
    uint8_t cmdid = 0;
    // uint8_t cmd_length = 0;
    cmdid = dat[3];
    // cmd_length = dat[2];
    uint8_t i = 0 ;
    uint8_t hid_data[32] = {0};
    switch(cmdid)
    {
        case 0x93:  // 无线状态处理
            BHQ_wireless_state_handle(cmdid, &dat[4]);
            break;
        case 0x27:  // RAW数据
            raw_hid_receive(&dat[5],dat[4]);  
            break;
        case 0x96:  // 复位模块 ack
        case 0x97:  // 设置参数 ack
        case 0x92:  // 读取模块信息 ack
        case 0xB1:  // ota ack
        case 0xB2:  // ota ack
            for (i = 0; i < length; i++)
            {
                hid_data[i] = dat[i];
            }
            raw_hid_send(hid_data, 32);
            break;
    }
    // km_printf("BHQ cmdid:%02x user\n",dat[3]);
}


wt_state_t wireless_get(void)
{
    return wt_state;
}