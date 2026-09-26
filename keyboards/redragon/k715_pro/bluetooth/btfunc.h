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

#include "stdint.h"

void k715bt_send_ble_req_bt_info(void);
void k715bt_send_ble_req_bt_name(void);
void k715bt_send_mcu_req_ble_fwver(void);
void k715bt_send_ble_set_device_name(uint8_t *dev_name, uint8_t dev_name_len);
void k715bt_send_ble_switch_device_mode(uint8_t mode);
void k715bt_send_ble_set_bt_channel(uint8_t bt_channel);
void k715bt_send_ble_pair(uint8_t pair_timeout, uint8_t *adv_data, uint8_t adv_data_len);
void k715bt_send_ble_reconnect_bt(uint8_t reconn_timeout);
void k715bt_send_ble_disconnect_bt(void);
void k715bt_switch_channel(uint8_t bt_channel);
