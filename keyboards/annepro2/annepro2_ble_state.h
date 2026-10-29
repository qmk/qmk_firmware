/*
 * Copyright 2026 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifndef ANNEPRO2_BLE_COMMAND_TIMEOUT
#    define ANNEPRO2_BLE_COMMAND_TIMEOUT 500
#endif

#ifndef ANNEPRO2_BLE_COMMAND_RETRIES
#    define ANNEPRO2_BLE_COMMAND_RETRIES 2
#endif

#ifndef ANNEPRO2_BLE_STARTUP_DELAY
#    define ANNEPRO2_BLE_STARTUP_DELAY 500
#endif

#ifndef ANNEPRO2_BLE_SLOT_HOLD_TIME
#    define ANNEPRO2_BLE_SLOT_HOLD_TIME 500
#endif

#ifndef ANNEPRO2_BLE_HANDSHAKE_TIMEOUT
#    define ANNEPRO2_BLE_HANDSHAKE_TIMEOUT 10000
#endif

#ifndef ANNEPRO2_BLE_SLOT_SWITCH_DELAY
#    define ANNEPRO2_BLE_SLOT_SWITCH_DELAY 1000
#endif

typedef enum {
    AP2_BLE_STATE_USB,
    AP2_BLE_STATE_WAIT_BROADCAST_ACK,
    AP2_BLE_STATE_WAIT_CONNECT_ACK,
    AP2_BLE_STATE_WAIT_HANDSHAKE,
    AP2_BLE_STATE_ACTIVE,
    AP2_BLE_STATE_STARTUP_PASSIVE,
} ap2_ble_state_id_t;

typedef enum {
    AP2_BLE_ACTION_NONE            = 0,
    AP2_BLE_ACTION_ROUTE_USB       = 1 << 0,
    AP2_BLE_ACTION_ROUTE_BLE       = 1 << 1,
    AP2_BLE_ACTION_SEND_WAKEUP     = 1 << 2,
    AP2_BLE_ACTION_SEND_SLOT_STATE = 1 << 3,
    AP2_BLE_ACTION_SEND_BROADCAST  = 1 << 4,
    AP2_BLE_ACTION_SEND_CONNECT    = 1 << 5,
    AP2_BLE_ACTION_SEND_UNPAIR     = 1 << 6,
    AP2_BLE_ACTION_SAVE_SLOT       = 1 << 7,
    AP2_BLE_ACTION_CLEAR_SLOT      = 1 << 8,
    AP2_BLE_ACTION_NOTIFY_FAILURE  = 1 << 9,
} ap2_ble_action_t;

typedef uint16_t ap2_ble_actions_t;

typedef struct {
    ap2_ble_state_id_t state;
    int8_t             startup_slot;
    int8_t             held_slot;
    int8_t             pending_slot;
    uint8_t            selected_slot;
    bool               held_slot_broadcast;
    bool               pending_broadcast;
    bool               command_slot_state_pending;
    bool               command_slot_broadcast;
    bool               handshake_timeout_enabled;
    uint8_t            command_retries;
    uint8_t            handshake_recoveries;
    uint32_t           startup_timer;
    uint32_t           slot_hold_timer;
    uint32_t           handshake_timer;
    uint32_t           command_timer;
    uint32_t           pending_timer;
} ap2_ble_state_t;

void              ap2_ble_state_reset(ap2_ble_state_t *state);
ap2_ble_actions_t ap2_ble_state_startup(ap2_ble_state_t *state, int8_t saved_slot, uint32_t now);
ap2_ble_actions_t ap2_ble_state_connect(ap2_ble_state_t *state, uint8_t slot, uint32_t now);
ap2_ble_actions_t ap2_ble_state_broadcast(ap2_ble_state_t *state, uint8_t slot, uint32_t now);
ap2_ble_actions_t ap2_ble_state_slot_press(ap2_ble_state_t *state, uint8_t slot, uint32_t now);
ap2_ble_actions_t ap2_ble_state_slot_release(ap2_ble_state_t *state, uint8_t slot, uint32_t now);
ap2_ble_actions_t ap2_ble_state_task(ap2_ble_state_t *state, uint32_t now);
ap2_ble_actions_t ap2_ble_state_command_ack(ap2_ble_state_t *state, uint8_t command, uint32_t now);
ap2_ble_actions_t ap2_ble_state_handshake(ap2_ble_state_t *state);
ap2_ble_actions_t ap2_ble_state_disconnect(ap2_ble_state_t *state);
ap2_ble_actions_t ap2_ble_state_unpair(ap2_ble_state_t *state);

bool ap2_ble_state_route_requested(const ap2_ble_state_t *state);
bool ap2_ble_state_operation_pending(const ap2_ble_state_t *state);
