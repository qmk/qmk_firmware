/* Copyright 2023 @ lokher (https://www.keychron.com)
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

#include "wireless_event_type.h"
#include "action.h"

#ifdef KC_DEBUG
#    define kc_printf dprintf
#else
#    define kc_printf(format, ...)
#endif

/* Low power mode */
#ifndef LOW_POWER_MODE
#    define LOW_POWER_MODE PM_STOP
#endif

/* Wake pin used for blueooth module/controller to wake up MCU in low power mode*/
#ifndef BLUETOOTH_INT_INPUT_PIN
#    define WAKE_PIN A5
#endif

// clang-format off
/* Type of an enumeration of the possible wireless transport state.*/
typedef enum {
    WT_RESET,
    WT_INITIALIZED,   // 1
    WT_DISCONNECTED,  // 2
    WT_CONNECTED,     // 3
    WT_PARING,        // 4
    WT_RECONNECTING,  // 5
    WT_SUSPEND
} wt_state_t;

//extern event_listener_t wireless_driver;

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
    void (*update_bat_level)(uint8_t);
    void (*task)(void);
} wt_func_t;
// clang-format on

extern void register_wt_tasks(void);

void wireless_init(void);
void wireless_set_transport(wt_func_t *transport);
void wireless(void);

bool wireless_event_enqueue(wireless_event_t event);

void wireless_connect(void);
void wireless_connect_ex(uint8_t host_idx, uint16_t timeout);
void wireless_disconnect(void);

void wireless_pairing(void);
void wireless_pairing_ex(uint8_t host_idx, void *param);
// bool bluetooth_is_activated(void);

void wireless_enter_reset_kb(uint8_t reason);
void wireless_enter_discoverable_kb(uint8_t host_idx);
void wireless_enter_reconnecting_kb(uint8_t host_idx);
void wireless_enter_connected_kb(uint8_t host_idx);
void wireless_enter_disconnected_kb(uint8_t host_idx, uint8_t reason);
void wireless_enter_bluetooth_pin_code_entry_kb(void);
void wireless_exit_bluetooth_pin_code_entry_kb(void);
void wireless_enter_sleep_kb(void);

void wireless_task(void);
void wireless_pre_task(void);
void wireless_post_task(void);
void send_string_task(void);

wt_state_t wireless_get_state(void);

void wireless_low_battery_shutdown(void);

bool process_record_wireless(uint16_t keycode, keyrecord_t *record);
