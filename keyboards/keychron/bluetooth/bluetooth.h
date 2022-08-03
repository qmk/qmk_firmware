/* Copyright 2022 @ lokher (https://www.keychron.com)
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

#include "bluetooth_event_type.h"

/* Low power mode */
#ifndef LOW_POWER_MODE
#    define LOW_POWER_MODE PM_STOP1
#endif

/* Wake pin used for blueooth module/controller to wake up MCU in low power mode*/
#ifndef BLUETOOTH_INT_INPUT_PIN
#    define WAKE_PIN A5
#endif

/* Type of an enumeration of the possible BT state.*/
typedef enum {
    BLUETOOTH_RESET,
    BLUETOOTH_INITIALIZED,   // 1
    BLUETOOTH_DISCONNECTED,  // 2
    BLUETOOTH_CONNECTED,     // 3
    BLUETOOTH_PARING,        // 4
    BLUETOOTH_RECONNECTING,  // 5
    BLUETOOTH_SUSPEND
} bluetooth_state_t;

extern event_listener_t bt_driver;

typedef struct {
    void (*init)(bool);
    void (*connect_ex)(uint8_t, uint16_t);
    void (*pairing_ex)(uint8_t, void *);
    void (*disconnect)(void);
    void (*send_keyboard)(uint8_t *);
    void (*send_nkro)(uint8_t *);
    void (*send_consumer)(uint16_t);
    void (*send_system)(uint16_t);
    void (*send_mouse)(uint8_t *);
    void (*task)(void);
} bluetooth_transport_t;

void bluetooth_init(void);
void bluetooth_set_transport(bluetooth_transport_t *transport);
void bluetooth_task(void);

bool bluetooth_event_queue_enqueue(bluetooth_event_t event);

void bluetooth_connect(void);
void bluetooth_connect_ex(uint8_t host_idx, uint16_t timeout);
void bluetooth_disconnect(void);

void bluetooth_pairing(void);
void bluetooth_pairing_ex(uint8_t host_idx, void *param);
bool bluetooth_is_activated(void);

void bluetooth_enter_reset_kb(uint8_t reason);
void bluetooth_enter_discoverable_kb(uint8_t host_idx);
void bluetooth_enter_reconnecting_kb(uint8_t host_idx);
void bluetooth_enter_connected_kb(uint8_t host_idx);
void bluetooth_enter_disconnected_kb(uint8_t host_idx);
void bluetooth_enter_pin_code_entry_kb(void);
void bluetooth_exit_pin_code_entry_kb(void);

void              bluetooth_task(void);
void              bluetooth_pre_task(void);
void              bluetooth_post_task(void);
bluetooth_state_t bluetooth_get_state(void);

void bluetooth_low_battery_shutdown(void);

