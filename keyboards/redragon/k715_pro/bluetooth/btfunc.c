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

#include <stdbool.h>
#include "quantum.h"
#include "btfunc.h"
#include "btspi.h"
#include "k715_pro.h"

extern user_settings_config g_config;
extern tDevInfo dev_info;

void k715bt_send_ble_req_bt_info(void)
{
    k715bt_send_spi_extend_single_packet(KBD_CMD_GET_INFO, NULL, 0);
}

void k715bt_send_ble_req_bt_name(void)
{
    k715bt_send_spi_extend_single_packet(KBD_CMD_BT_GETNAME, NULL, 0);
}

void k715bt_send_mcu_req_ble_fwver(void)
{
    k715bt_send_spi_extend_single_packet(KBD_CMD_MCU_REQ_BT_FWVER, NULL, 0);
}

void k715bt_send_ble_switch_device_mode(uint8_t mode)
{
    k715bt_send_spi_extend_single_packet(KBD_CMD_MODE_SET, &mode, 1);
}

void k715bt_send_ble_pair(uint8_t pair_timeout, uint8_t *adv_data, uint8_t adv_data_len)
{
    k715bt_send_spi_extend_single_packet(KBD_CMD_BT_PAIR, NULL, 0);
}

void k715bt_send_ble_reconnect_bt(uint8_t reconn_timeout)
{
    k715bt_send_spi_extend_single_packet(KBD_CMD_BT_BACK, &reconn_timeout, 1);
}

void k715bt_send_ble_disconnect_bt(void)
{
    k715bt_send_spi_extend_single_packet(KBD_CMD_BT_DISCONNECT, NULL, 0);
}

void k715bt_send_ble_set_device_name(uint8_t *dev_name, uint8_t dev_name_len)
{
    k715bt_send_spi_extend_single_packet(KBD_CMD_BT_SETNAME, dev_name, dev_name_len);
}

void k715bt_send_ble_set_bt_channel(uint8_t bt_channel)
{
    k715bt_send_spi_extend_single_packet(KBD_CMD_BT_SETCHN, &bt_channel, 1);
}

void k715bt_switch_channel(uint8_t bt_channel)
{
    if(g_config.bt_ch != bt_channel)
    {
        k715bt_send_ble_set_bt_channel(bt_channel);
        g_config.bt_ch = bt_channel;
    }
}
