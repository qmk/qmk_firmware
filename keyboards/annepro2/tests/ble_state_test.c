#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "../annepro2_ble_state.h"

static bool has(ap2_ble_actions_t actions, ap2_ble_action_t action) {
    return (actions & action) != 0;
}

static void test_startup_restore(void) {
    ap2_ble_state_t state;

    ap2_ble_actions_t actions = ap2_ble_state_startup(&state, 1, 100);
    assert(actions == AP2_BLE_ACTION_SEND_WAKEUP);
    assert(state.state == AP2_BLE_STATE_STARTUP_PASSIVE);
    assert(state.selected_slot == 1);

    actions = ap2_ble_state_task(&state, 599);
    assert(actions == AP2_BLE_ACTION_NONE);
    actions = ap2_ble_state_task(&state, 600);
    assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
    assert(has(actions, AP2_BLE_ACTION_SEND_BROADCAST));
    assert(!has(actions, AP2_BLE_ACTION_SEND_SLOT_STATE));
    assert(state.state == AP2_BLE_STATE_WAIT_BROADCAST_ACK);

    actions = ap2_ble_state_startup(&state, 2, 1000);
    assert(actions == AP2_BLE_ACTION_SEND_WAKEUP);
    actions = ap2_ble_state_handshake(&state);
    assert(has(actions, AP2_BLE_ACTION_ROUTE_BLE));
    assert(has(actions, AP2_BLE_ACTION_SAVE_SLOT));
    assert(state.state == AP2_BLE_STATE_ACTIVE);
    assert(state.selected_slot == 2);

    actions = ap2_ble_state_startup(&state, -1, 2000);
    assert(actions == AP2_BLE_ACTION_SEND_WAKEUP);
    assert(state.state == AP2_BLE_STATE_USB);
    assert(ap2_ble_state_task(&state, 3000) == AP2_BLE_ACTION_NONE);
}

static void test_tap_and_hold(void) {
    ap2_ble_state_t state;
    ap2_ble_state_reset(&state);

    assert(ap2_ble_state_slot_press(&state, 0, 10) == AP2_BLE_ACTION_NONE);
    ap2_ble_actions_t actions = ap2_ble_state_slot_release(&state, 0, 100);
    assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
    assert(has(actions, AP2_BLE_ACTION_SEND_SLOT_STATE));
    assert(has(actions, AP2_BLE_ACTION_SEND_CONNECT));
    assert(state.state == AP2_BLE_STATE_WAIT_CONNECT_ACK);
    assert(state.selected_slot == 0);
    assert(!state.command_slot_broadcast);

    ap2_ble_state_reset(&state);
    assert(ap2_ble_state_slot_press(&state, 3, 1000) == AP2_BLE_ACTION_NONE);
    assert(ap2_ble_state_task(&state, 1499) == AP2_BLE_ACTION_NONE);
    actions = ap2_ble_state_task(&state, 1500);
    assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
    assert(has(actions, AP2_BLE_ACTION_SEND_SLOT_STATE));
    assert(has(actions, AP2_BLE_ACTION_SEND_BROADCAST));
    assert(state.command_slot_broadcast);
    assert(ap2_ble_state_slot_release(&state, 3, 1501) == AP2_BLE_ACTION_NONE);
}

static void test_all_four_slots_connect_and_pair(void) {
    for (uint8_t slot = 0; slot < 4; slot++) {
        ap2_ble_state_t state;
        ap2_ble_state_reset(&state);

        ap2_ble_actions_t actions = ap2_ble_state_connect(&state, slot, 100);
        assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
        assert(has(actions, AP2_BLE_ACTION_SEND_SLOT_STATE));
        assert(has(actions, AP2_BLE_ACTION_SEND_CONNECT));
        assert(state.selected_slot == slot);
        assert(state.state == AP2_BLE_STATE_WAIT_CONNECT_ACK);

        assert(ap2_ble_state_command_ack(&state, 0x04, 200) == AP2_BLE_ACTION_NONE);
        assert(state.state == AP2_BLE_STATE_WAIT_HANDSHAKE);
        actions = ap2_ble_state_handshake(&state);
        assert(has(actions, AP2_BLE_ACTION_ROUTE_BLE));
        assert(has(actions, AP2_BLE_ACTION_SAVE_SLOT));
        assert(state.state == AP2_BLE_STATE_ACTIVE);
        assert(state.selected_slot == slot);

        actions = ap2_ble_state_disconnect(&state);
        assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
        assert(has(actions, AP2_BLE_ACTION_CLEAR_SLOT));

        actions = ap2_ble_state_broadcast(&state, slot, 300);
        assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
        assert(has(actions, AP2_BLE_ACTION_SEND_SLOT_STATE));
        assert(has(actions, AP2_BLE_ACTION_SEND_BROADCAST));
        assert(state.selected_slot == slot);
        assert(state.state == AP2_BLE_STATE_WAIT_BROADCAST_ACK);

        assert(ap2_ble_state_command_ack(&state, 0x01, 400) == AP2_BLE_ACTION_NONE);
        assert(state.state == AP2_BLE_STATE_WAIT_HANDSHAKE);
        actions = ap2_ble_state_handshake(&state);
        assert(has(actions, AP2_BLE_ACTION_ROUTE_BLE));
        assert(has(actions, AP2_BLE_ACTION_SAVE_SLOT));
        assert(state.state == AP2_BLE_STATE_ACTIVE);
        assert(state.selected_slot == slot);
    }
}

static void test_command_retry_and_handshake(void) {
    ap2_ble_state_t state;
    ap2_ble_state_reset(&state);

    ap2_ble_actions_t actions = ap2_ble_state_connect(&state, 1, 0);
    assert(has(actions, AP2_BLE_ACTION_SEND_SLOT_STATE));
    assert(has(actions, AP2_BLE_ACTION_SEND_CONNECT));

    actions = ap2_ble_state_task(&state, ANNEPRO2_BLE_COMMAND_TIMEOUT);
    assert(actions == AP2_BLE_ACTION_SEND_CONNECT);
    assert(!has(actions, AP2_BLE_ACTION_SEND_SLOT_STATE));
    assert(state.command_retries == 1);

    actions = ap2_ble_state_task(&state, ANNEPRO2_BLE_COMMAND_TIMEOUT * 2);
    assert(actions == AP2_BLE_ACTION_SEND_CONNECT);
    assert(state.command_retries == 2);

    actions = ap2_ble_state_task(&state, ANNEPRO2_BLE_COMMAND_TIMEOUT * 3);
    assert(actions == AP2_BLE_ACTION_NONE);
    assert(state.state == AP2_BLE_STATE_WAIT_HANDSHAKE);

    actions = ap2_ble_state_command_ack(&state, 0x04, 1600);
    assert(actions == AP2_BLE_ACTION_NONE);
    assert(state.state == AP2_BLE_STATE_WAIT_HANDSHAKE);

    actions = ap2_ble_state_handshake(&state);
    assert(has(actions, AP2_BLE_ACTION_ROUTE_BLE));
    assert(has(actions, AP2_BLE_ACTION_SAVE_SLOT));
    assert(state.state == AP2_BLE_STATE_ACTIVE);
}

static void test_ack_is_not_connection(void) {
    ap2_ble_state_t state;
    ap2_ble_state_reset(&state);
    ap2_ble_state_connect(&state, 1, 0);

    assert(ap2_ble_state_command_ack(&state, 0x01, 10) == AP2_BLE_ACTION_NONE);
    assert(state.state == AP2_BLE_STATE_WAIT_CONNECT_ACK);

    assert(ap2_ble_state_command_ack(&state, 0x04, 20) == AP2_BLE_ACTION_NONE);
    assert(state.state == AP2_BLE_STATE_WAIT_HANDSHAKE);
    assert(!has(ap2_ble_state_command_ack(&state, 0x04, 30), AP2_BLE_ACTION_ROUTE_BLE));
    assert(state.state == AP2_BLE_STATE_WAIT_HANDSHAKE);
}

static void test_latest_slot_intent_wins(void) {
    ap2_ble_state_t state;
    ap2_ble_state_reset(&state);
    ap2_ble_state_connect(&state, 1, 0);

    assert(ap2_ble_state_connect(&state, 2, 100) == AP2_BLE_ACTION_ROUTE_USB);
    assert(state.pending_slot == 2);
    assert(ap2_ble_state_connect(&state, 0, 200) == AP2_BLE_ACTION_ROUTE_USB);
    assert(state.pending_slot == 0);
    assert(ap2_ble_state_task(&state, 1199) == AP2_BLE_ACTION_NONE);

    ap2_ble_actions_t actions = ap2_ble_state_task(&state, 1200);
    assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
    assert(has(actions, AP2_BLE_ACTION_SEND_SLOT_STATE));
    assert(has(actions, AP2_BLE_ACTION_SEND_CONNECT));
    assert(state.selected_slot == 0);
    assert(state.pending_slot == -1);
    assert(state.state == AP2_BLE_STATE_WAIT_CONNECT_ACK);

    /* An ACK for a different command family cannot advance the new request. */
    assert(ap2_ble_state_command_ack(&state, 0x01, 1201) == AP2_BLE_ACTION_NONE);
    assert(state.state == AP2_BLE_STATE_WAIT_CONNECT_ACK);
}

static void test_handshake_timeout_recovery_is_bounded(void) {
    ap2_ble_state_t state;
    ap2_ble_state_reset(&state);
    ap2_ble_state_connect(&state, 3, 0);
    ap2_ble_state_command_ack(&state, 0x04, 10);

    ap2_ble_actions_t actions = ap2_ble_state_task(&state, 10 + ANNEPRO2_BLE_HANDSHAKE_TIMEOUT);
    assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
    assert(has(actions, AP2_BLE_ACTION_SEND_WAKEUP));
    assert(state.state == AP2_BLE_STATE_USB);
    assert(state.startup_slot == 3);
    assert(state.handshake_recoveries == 1);

    actions = ap2_ble_state_task(&state, 10 + ANNEPRO2_BLE_HANDSHAKE_TIMEOUT + ANNEPRO2_BLE_STARTUP_DELAY);
    assert(has(actions, AP2_BLE_ACTION_SEND_BROADCAST));
    assert(!has(actions, AP2_BLE_ACTION_SEND_SLOT_STATE));
    assert(state.state == AP2_BLE_STATE_WAIT_BROADCAST_ACK);

    ap2_ble_state_command_ack(&state, 0x01, 11000);
    actions = ap2_ble_state_task(&state, 11000 + ANNEPRO2_BLE_HANDSHAKE_TIMEOUT);
    assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
    assert(has(actions, AP2_BLE_ACTION_NOTIFY_FAILURE));
    assert(!has(actions, AP2_BLE_ACTION_SEND_WAKEUP));
    assert(state.state == AP2_BLE_STATE_USB);
    assert(state.startup_slot == -1);
    assert(state.handshake_recoveries == 1);
}

static void test_disconnect_and_unpair_clear_transient_state(void) {
    ap2_ble_state_t state;
    ap2_ble_state_reset(&state);
    ap2_ble_state_slot_press(&state, 2, 0);
    ap2_ble_state_connect(&state, 1, 1);
    ap2_ble_state_connect(&state, 3, 2);

    ap2_ble_actions_t actions = ap2_ble_state_disconnect(&state);
    assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
    assert(has(actions, AP2_BLE_ACTION_CLEAR_SLOT));
    assert(state.state == AP2_BLE_STATE_USB);
    assert(state.held_slot == -1);
    assert(state.pending_slot == -1);
    assert(state.startup_slot == -1);
    assert(!state.handshake_timeout_enabled);

    ap2_ble_state_connect(&state, 0, 100);
    actions = ap2_ble_state_unpair(&state);
    assert(has(actions, AP2_BLE_ACTION_SEND_UNPAIR));
    assert(has(actions, AP2_BLE_ACTION_ROUTE_USB));
    assert(has(actions, AP2_BLE_ACTION_CLEAR_SLOT));
    assert(state.state == AP2_BLE_STATE_USB);
}

static void test_timer_wraparound(void) {
    ap2_ble_state_t state;
    ap2_ble_state_reset(&state);
    ap2_ble_state_connect(&state, 0, UINT32_MAX - 100);
    assert(ap2_ble_state_task(&state, 398) == AP2_BLE_ACTION_NONE);
    assert(ap2_ble_state_task(&state, 399) == AP2_BLE_ACTION_SEND_CONNECT);
}

int main(void) {
    test_startup_restore();
    test_tap_and_hold();
    test_all_four_slots_connect_and_pair();
    test_command_retry_and_handshake();
    test_ack_is_not_connection();
    test_latest_slot_intent_wins();
    test_handshake_timeout_recovery_is_bounded();
    test_disconnect_and_unpair_clear_transient_state();
    test_timer_wraparound();
    return 0;
}
