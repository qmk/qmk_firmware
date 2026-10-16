/*
    Copyright (C) 2020 Yaotian Feng, Codetector<codetector@codetector.cn>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include "annepro2.h"

typedef enum {
    ANNEPRO2_BLE_STATUS_IDLE,
    ANNEPRO2_BLE_STATUS_ADVERTISING,
    ANNEPRO2_BLE_STATUS_CONNECTING,
    ANNEPRO2_BLE_STATUS_CONNECTED,
    ANNEPRO2_BLE_STATUS_FAILED,
} annepro2_ble_status_t;

void annepro2_ble_init(void);
void annepro2_ble_task(void);
bool annepro2_ble_process_record(uint16_t keycode, keyrecord_t *record);
void annepro2_ble_bootload(void);
void annepro2_ble_startup(void);
void annepro2_ble_broadcast(uint8_t port);
void annepro2_ble_connect(uint8_t port);
void                   annepro2_ble_slot_press(uint8_t port);
void                   annepro2_ble_slot_release(uint8_t port);
void                   annepro2_ble_disconnect(void);
void                   annepro2_ble_unpair(void);

/*
 * Optional keymap hook for asynchronous BLE status indication.
 * Slot is zero-based (0..3). The default implementation does nothing.
 */
void annepro2_ble_status_changed_user(annepro2_ble_status_t status, uint8_t slot);

/* Feed bytes received from the BLE UART into the AnnePro2 frame parser. */
void annepro2_ble_rx_byte(uint8_t byte);
