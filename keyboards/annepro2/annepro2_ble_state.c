/*
 * Copyright 2026 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include "annepro2_ble_state.h"

#include <string.h>

static uint32_t elapsed(uint32_t now, uint32_t then) {
    return now - then;
}

static uint8_t clamp_slot(uint8_t slot) {
    return slot > 3 ? 3 : slot;
}

static void clear_transient_state(ap2_ble_state_t *state) {
    state->command_retries            = 0;
    state->handshake_recoveries       = 0;
    state->handshake_timeout_enabled  = false;
    state->command_slot_state_pending = false;
    state->startup_slot               = -1;
    state->held_slot                  = -1;
    state->held_slot_broadcast        = false;
    state->pending_slot               = -1;
}

static ap2_ble_actions_t start_broadcast(ap2_ble_state_t *state, uint8_t slot, int8_t slot_state, bool handshake_timeout, uint32_t now) {
    state->state                      = AP2_BLE_STATE_WAIT_BROADCAST_ACK;
    state->startup_slot               = -1;
    state->selected_slot              = clamp_slot(slot);
    state->command_slot_state_pending = slot_state >= 0;
    state->command_slot_broadcast     = slot_state > 0;
    state->handshake_timeout_enabled  = handshake_timeout;
    state->command_retries            = 0;
    state->command_timer              = now;

    ap2_ble_actions_t actions = AP2_BLE_ACTION_ROUTE_USB | AP2_BLE_ACTION_SEND_BROADCAST;
    if (state->command_slot_state_pending) {
        state->command_slot_state_pending = false;
        actions |= AP2_BLE_ACTION_SEND_SLOT_STATE;
    }
    return actions;
}

static ap2_ble_actions_t start_connect(ap2_ble_state_t *state, uint8_t slot, uint32_t now) {
    state->state                      = AP2_BLE_STATE_WAIT_CONNECT_ACK;
    state->startup_slot               = -1;
    state->selected_slot              = clamp_slot(slot);
    state->command_slot_state_pending = false;
    state->command_slot_broadcast     = false;
    state->handshake_timeout_enabled  = true;
    state->command_retries            = 0;
    state->command_timer              = now;
    return AP2_BLE_ACTION_ROUTE_USB | AP2_BLE_ACTION_SEND_SLOT_STATE | AP2_BLE_ACTION_SEND_CONNECT;
}

static void queue_intent(ap2_ble_state_t *state, uint8_t slot, bool broadcast, uint32_t now) {
    /*
     * Stop retrying the old transaction immediately. The quiet window before
     * dispatching the latest intent makes command-family ACKs from the old
     * slot stale while the state is USB.
     */
    state->state                      = AP2_BLE_STATE_USB;
    state->command_retries            = 0;
    state->command_slot_state_pending = false;
    state->handshake_timeout_enabled  = false;
    state->pending_slot               = clamp_slot(slot);
    state->pending_broadcast          = broadcast;
    state->pending_timer              = now;
}

void ap2_ble_state_reset(ap2_ble_state_t *state) {
    memset(state, 0, sizeof(*state));
    state->state        = AP2_BLE_STATE_USB;
    state->startup_slot = -1;
    state->held_slot    = -1;
    state->pending_slot = -1;
}

ap2_ble_actions_t ap2_ble_state_startup(ap2_ble_state_t *state, int8_t saved_slot, uint32_t now) {
    ap2_ble_state_reset(state);
    if (saved_slot >= 0 && saved_slot <= 3) {
        state->startup_slot  = saved_slot;
        state->selected_slot = (uint8_t)saved_slot;
        state->startup_timer = now;
        state->state         = AP2_BLE_STATE_STARTUP_PASSIVE;
    }
    return AP2_BLE_ACTION_SEND_WAKEUP;
}

ap2_ble_actions_t ap2_ble_state_connect(ap2_ble_state_t *state, uint8_t slot, uint32_t now) {
    slot                = clamp_slot(slot);
    state->startup_slot = -1;
    if (state->state == AP2_BLE_STATE_STARTUP_PASSIVE) {
        state->state = AP2_BLE_STATE_USB;
    }
    if (state->pending_slot >= 0) {
        queue_intent(state, slot, false, now);
        return AP2_BLE_ACTION_ROUTE_USB;
    }
    if (ap2_ble_state_operation_pending(state)) {
        if (state->selected_slot == slot) {
            state->pending_slot = -1;
        } else {
            queue_intent(state, slot, false, now);
        }
        return AP2_BLE_ACTION_ROUTE_USB;
    }

    state->pending_slot         = -1;
    state->handshake_recoveries = 0;
    return start_connect(state, slot, now);
}

ap2_ble_actions_t ap2_ble_state_broadcast(ap2_ble_state_t *state, uint8_t slot, uint32_t now) {
    slot                = clamp_slot(slot);
    state->startup_slot = -1;
    if (state->state == AP2_BLE_STATE_STARTUP_PASSIVE) {
        state->state = AP2_BLE_STATE_USB;
    }
    if (state->pending_slot >= 0) {
        queue_intent(state, slot, true, now);
        return AP2_BLE_ACTION_ROUTE_USB;
    }
    if (ap2_ble_state_operation_pending(state)) {
        queue_intent(state, slot, true, now);
        return AP2_BLE_ACTION_ROUTE_USB;
    }

    state->pending_slot         = -1;
    state->handshake_recoveries = 0;
    return start_broadcast(state, slot, 1, false, now);
}

ap2_ble_actions_t ap2_ble_state_slot_press(ap2_ble_state_t *state, uint8_t slot, uint32_t now) {
    state->startup_slot = -1;
    if (state->state == AP2_BLE_STATE_STARTUP_PASSIVE) {
        state->state = AP2_BLE_STATE_USB;
    }
    state->held_slot           = (int8_t)clamp_slot(slot);
    state->held_slot_broadcast = false;
    state->slot_hold_timer     = now;
    return AP2_BLE_ACTION_NONE;
}

ap2_ble_actions_t ap2_ble_state_slot_release(ap2_ble_state_t *state, uint8_t slot, uint32_t now) {
    slot = clamp_slot(slot);
    if (state->held_slot != (int8_t)slot) {
        return AP2_BLE_ACTION_NONE;
    }

    state->held_slot = -1;
    if (!state->held_slot_broadcast) {
        state->held_slot_broadcast = false;
        return ap2_ble_state_connect(state, slot, now);
    }
    state->held_slot_broadcast = false;
    return AP2_BLE_ACTION_NONE;
}

ap2_ble_actions_t ap2_ble_state_task(ap2_ble_state_t *state, uint32_t now) {
    ap2_ble_actions_t actions = AP2_BLE_ACTION_NONE;

    if (state->held_slot >= 0 && !state->held_slot_broadcast && elapsed(now, state->slot_hold_timer) >= ANNEPRO2_BLE_SLOT_HOLD_TIME) {
        state->held_slot_broadcast = true;
        actions |= ap2_ble_state_broadcast(state, (uint8_t)state->held_slot, now);
    }

    if (state->startup_slot >= 0 && elapsed(now, state->startup_timer) >= ANNEPRO2_BLE_STARTUP_DELAY) {
        const uint8_t slot = (uint8_t)state->startup_slot;
        actions |= start_broadcast(state, slot, -1, true, now);
    }

    if (state->pending_slot >= 0 && elapsed(now, state->pending_timer) >= ANNEPRO2_BLE_SLOT_SWITCH_DELAY) {
        const uint8_t slot                = (uint8_t)state->pending_slot;
        const bool    broadcast           = state->pending_broadcast;
        state->pending_slot               = -1;
        state->command_slot_state_pending = false;
        state->handshake_timeout_enabled  = false;
        state->handshake_recoveries       = 0;
        state->state                      = AP2_BLE_STATE_USB;
        actions |= broadcast ? start_broadcast(state, slot, 1, false, now) : start_connect(state, slot, now);
    }

    if (state->state == AP2_BLE_STATE_WAIT_HANDSHAKE) {
        if (!state->handshake_timeout_enabled || elapsed(now, state->handshake_timer) < ANNEPRO2_BLE_HANDSHAKE_TIMEOUT) {
            return actions;
        }

        state->state                      = AP2_BLE_STATE_USB;
        state->command_slot_state_pending = false;
        state->handshake_timeout_enabled  = false;
        actions |= AP2_BLE_ACTION_ROUTE_USB;
        if (state->handshake_recoveries == 0) {
            state->handshake_recoveries = 1;
            state->startup_slot         = state->selected_slot;
            state->startup_timer        = now;
            actions |= AP2_BLE_ACTION_SEND_WAKEUP;
        } else {
            actions |= AP2_BLE_ACTION_NOTIFY_FAILURE;
        }
        return actions;
    }

    if (state->state != AP2_BLE_STATE_WAIT_BROADCAST_ACK && state->state != AP2_BLE_STATE_WAIT_CONNECT_ACK) {
        return actions;
    }
    if (elapsed(now, state->command_timer) < ANNEPRO2_BLE_COMMAND_TIMEOUT) {
        return actions;
    }

    if (state->command_retries >= ANNEPRO2_BLE_COMMAND_RETRIES) {
        state->handshake_timer = now;
        state->state           = AP2_BLE_STATE_WAIT_HANDSHAKE;
        return actions;
    }

    state->command_retries++;
    state->command_timer = now;
    actions |= state->state == AP2_BLE_STATE_WAIT_BROADCAST_ACK ? AP2_BLE_ACTION_SEND_BROADCAST : AP2_BLE_ACTION_SEND_CONNECT;
    return actions;
}

ap2_ble_actions_t ap2_ble_state_command_ack(ap2_ble_state_t *state, uint8_t command, uint32_t now) {
    if ((command == 0x01 && state->state != AP2_BLE_STATE_WAIT_BROADCAST_ACK) || (command == 0x04 && state->state != AP2_BLE_STATE_WAIT_CONNECT_ACK)) {
        return AP2_BLE_ACTION_NONE;
    }
    if (command != 0x01 && command != 0x04) {
        return AP2_BLE_ACTION_NONE;
    }
    state->command_retries = 0;
    state->handshake_timer = now;
    state->state           = AP2_BLE_STATE_WAIT_HANDSHAKE;
    return AP2_BLE_ACTION_NONE;
}

ap2_ble_actions_t ap2_ble_state_handshake(ap2_ble_state_t *state) {
    if (!ap2_ble_state_route_requested(state)) {
        return AP2_BLE_ACTION_NONE;
    }

    state->command_slot_state_pending = false;
    state->startup_slot               = -1;
    state->command_retries            = 0;
    state->handshake_recoveries       = 0;
    state->handshake_timeout_enabled  = false;
    state->state                      = AP2_BLE_STATE_ACTIVE;
    return AP2_BLE_ACTION_ROUTE_BLE | AP2_BLE_ACTION_SAVE_SLOT;
}

ap2_ble_actions_t ap2_ble_state_disconnect(ap2_ble_state_t *state) {
    clear_transient_state(state);
    state->state = AP2_BLE_STATE_USB;
    return AP2_BLE_ACTION_ROUTE_USB | AP2_BLE_ACTION_CLEAR_SLOT;
}

ap2_ble_actions_t ap2_ble_state_unpair(ap2_ble_state_t *state) {
    return AP2_BLE_ACTION_SEND_UNPAIR | ap2_ble_state_disconnect(state);
}

bool ap2_ble_state_route_requested(const ap2_ble_state_t *state) {
    return state->state != AP2_BLE_STATE_USB;
}

bool ap2_ble_state_operation_pending(const ap2_ble_state_t *state) {
    return state->state == AP2_BLE_STATE_WAIT_BROADCAST_ACK || state->state == AP2_BLE_STATE_WAIT_CONNECT_ACK || state->state == AP2_BLE_STATE_WAIT_HANDSHAKE;
}
