/*
 * Copyright 2026 BHE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include "annepro2_ble_213_slot.h"

#include <string.h>

/*
 * AP2D KEY 3.08 queries and selects the BLE module's internal slot before
 * issuing a pairing or connect command. This module is compiled only for the
 * AP2D BLE 2.13 transport.
 */
static const uint8_t query_slot_frame[] = {
    0x7b, 0x12, 0x53, 0x00, 0x02, 0x00, 0x00, 0x7d, 0xc0, 0x17,
};

static const uint8_t select_slot_frame[] = {
    0x7b, 0x12, 0x53, 0x00, 0x03, 0x00, 0x00, 0x7d, 0x40, 0x17,
};

static const uint8_t prepare_slot_frame[] = {
    0x7b, 0x10, 0x53, 0x00, 0x03, 0x00, 0x00, 0x7d, 0x02, 0x01,
};

static uint32_t elapsed(uint32_t now, uint32_t then) {
    return now - then;
}

void ap2_ble_213_slot_reset(ap2_ble_213_slot_state_t *state) {
    memset(state, 0, sizeof(*state));
    state->phase = AP2_BLE_213_SLOT_IDLE;
}

bool ap2_ble_213_slot_should_prepare(uint8_t command_retries) {
    return command_retries == 0;
}

ap2_ble_213_slot_actions_t ap2_ble_213_slot_begin(ap2_ble_213_slot_state_t *state, uint8_t target_slot, uint16_t deferred_actions, uint32_t now) {
    state->phase                   = AP2_BLE_213_SLOT_WAIT_QUERY;
    state->target_slot             = target_slot > 3 ? 3 : target_slot;
    state->query_response_received = false;
    state->deferred_actions        = deferred_actions;
    state->timer                   = now;
    return AP2_BLE_213_SLOT_ACTION_QUERY;
}

void ap2_ble_213_slot_response(ap2_ble_213_slot_state_t *state, uint8_t current_slot) {
    if (state->phase != AP2_BLE_213_SLOT_WAIT_QUERY || current_slot > 3) {
        return;
    }
    state->current_slot            = current_slot;
    state->query_response_received = true;
}

ap2_ble_213_slot_actions_t ap2_ble_213_slot_task(ap2_ble_213_slot_state_t *state, uint32_t now, uint16_t *deferred_actions) {
    if (deferred_actions != NULL) {
        *deferred_actions = 0;
    }

    switch (state->phase) {
        case AP2_BLE_213_SLOT_WAIT_QUERY:
            if (elapsed(now, state->timer) < ANNEPRO2_BLE_213_SLOT_QUERY_DELAY) {
                return AP2_BLE_213_SLOT_ACTION_NONE;
            }
            if (state->query_response_received && state->current_slot == state->target_slot) {
                if (deferred_actions != NULL) {
                    *deferred_actions = state->deferred_actions;
                }
                state->phase            = AP2_BLE_213_SLOT_IDLE;
                state->deferred_actions = 0;
                return AP2_BLE_213_SLOT_ACTION_DISPATCH;
            }
            state->phase        = AP2_BLE_213_SLOT_WAIT_PREPARE_2;
            state->current_slot = state->target_slot;
            state->timer        = now;
            return AP2_BLE_213_SLOT_ACTION_SELECT | AP2_BLE_213_SLOT_ACTION_PREPARE_1;

        case AP2_BLE_213_SLOT_WAIT_PREPARE_2:
            if (elapsed(now, state->timer) < ANNEPRO2_BLE_213_SLOT_PREPARE_DELAY) {
                return AP2_BLE_213_SLOT_ACTION_NONE;
            }
            state->phase = AP2_BLE_213_SLOT_WAIT_COMMAND;
            state->timer = now;
            return AP2_BLE_213_SLOT_ACTION_PREPARE_2;

        case AP2_BLE_213_SLOT_WAIT_COMMAND:
            if (elapsed(now, state->timer) < ANNEPRO2_BLE_213_SLOT_PREPARE_DELAY) {
                return AP2_BLE_213_SLOT_ACTION_NONE;
            }
            if (deferred_actions != NULL) {
                *deferred_actions = state->deferred_actions;
            }
            state->phase            = AP2_BLE_213_SLOT_IDLE;
            state->deferred_actions = 0;
            return AP2_BLE_213_SLOT_ACTION_DISPATCH;

        case AP2_BLE_213_SLOT_IDLE:
            return AP2_BLE_213_SLOT_ACTION_NONE;
    }

    return AP2_BLE_213_SLOT_ACTION_NONE;
}

bool ap2_ble_213_slot_active(const ap2_ble_213_slot_state_t *state) {
    return state->phase != AP2_BLE_213_SLOT_IDLE;
}

uint8_t ap2_ble_213_slot_encode_query(uint8_t out[AP2_BLE_213_SLOT_FRAME_MAX_SIZE]) {
    memcpy(out, query_slot_frame, sizeof(query_slot_frame));
    return sizeof(query_slot_frame);
}

uint8_t ap2_ble_213_slot_encode_select(uint8_t slot, uint8_t out[AP2_BLE_213_SLOT_FRAME_MAX_SIZE]) {
    memcpy(out, select_slot_frame, sizeof(select_slot_frame));
    out[sizeof(select_slot_frame)] = slot > 3 ? 3 : slot;
    return sizeof(select_slot_frame) + 1;
}

uint8_t ap2_ble_213_slot_encode_prepare(uint8_t value, uint8_t out[AP2_BLE_213_SLOT_FRAME_MAX_SIZE]) {
    memcpy(out, prepare_slot_frame, sizeof(prepare_slot_frame));
    out[sizeof(prepare_slot_frame)] = value;
    return sizeof(prepare_slot_frame) + 1;
}

bool ap2_ble_213_slot_decode_response(const uint8_t *frame, size_t size, uint8_t *slot) {
    if (frame == NULL || slot == NULL || size != AP2_BLE_213_SLOT_FRAME_MAX_SIZE || frame[0] != 0x7b || frame[1] != 0x12 || frame[2] != 0x35 || frame[4] != 0x03 || frame[5] != 0x00 || frame[7] != 0x7d || frame[8] != 0xc0 || frame[9] != 0x17 || frame[10] > 3) {
        return false;
    }

    *slot = frame[10];
    return true;
}
