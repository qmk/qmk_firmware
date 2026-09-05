/*
 * Copyright 2026 BHE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef ANNEPRO2_BLE_213_SLOT_QUERY_DELAY
#    define ANNEPRO2_BLE_213_SLOT_QUERY_DELAY 5
#endif

#ifndef ANNEPRO2_BLE_213_SLOT_PREPARE_DELAY
#    define ANNEPRO2_BLE_213_SLOT_PREPARE_DELAY 20
#endif

#define AP2_BLE_213_SLOT_FRAME_MAX_SIZE 11

typedef enum {
    AP2_BLE_213_SLOT_IDLE,
    AP2_BLE_213_SLOT_WAIT_QUERY,
    AP2_BLE_213_SLOT_WAIT_PREPARE_2,
    AP2_BLE_213_SLOT_WAIT_COMMAND,
} ap2_ble_213_slot_phase_t;

typedef enum {
    AP2_BLE_213_SLOT_ACTION_NONE      = 0,
    AP2_BLE_213_SLOT_ACTION_QUERY     = 1 << 0,
    AP2_BLE_213_SLOT_ACTION_SELECT    = 1 << 1,
    AP2_BLE_213_SLOT_ACTION_PREPARE_1 = 1 << 2,
    AP2_BLE_213_SLOT_ACTION_PREPARE_2 = 1 << 3,
    AP2_BLE_213_SLOT_ACTION_DISPATCH  = 1 << 4,
} ap2_ble_213_slot_action_t;

typedef uint8_t ap2_ble_213_slot_actions_t;

typedef struct {
    ap2_ble_213_slot_phase_t phase;
    uint8_t                  target_slot;
    uint8_t                  current_slot;
    bool                     query_response_received;
    uint16_t                 deferred_actions;
    uint32_t                 timer;
} ap2_ble_213_slot_state_t;

void                       ap2_ble_213_slot_reset(ap2_ble_213_slot_state_t *state);
bool                       ap2_ble_213_slot_should_prepare(uint8_t command_retries);
ap2_ble_213_slot_actions_t ap2_ble_213_slot_begin(ap2_ble_213_slot_state_t *state, uint8_t target_slot, uint16_t deferred_actions, uint32_t now);
void                       ap2_ble_213_slot_response(ap2_ble_213_slot_state_t *state, uint8_t current_slot);
ap2_ble_213_slot_actions_t ap2_ble_213_slot_task(ap2_ble_213_slot_state_t *state, uint32_t now, uint16_t *deferred_actions);
bool                       ap2_ble_213_slot_active(const ap2_ble_213_slot_state_t *state);
uint8_t                    ap2_ble_213_slot_encode_query(uint8_t out[AP2_BLE_213_SLOT_FRAME_MAX_SIZE]);
uint8_t                    ap2_ble_213_slot_encode_select(uint8_t slot, uint8_t out[AP2_BLE_213_SLOT_FRAME_MAX_SIZE]);
uint8_t                    ap2_ble_213_slot_encode_prepare(uint8_t value, uint8_t out[AP2_BLE_213_SLOT_FRAME_MAX_SIZE]);
bool                       ap2_ble_213_slot_decode_response(const uint8_t *frame, size_t size, uint8_t *slot);
