#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "../annepro2_ble_213_slot.h"

static bool has(ap2_ble_213_slot_actions_t actions, ap2_ble_213_slot_action_t action) {
    return (actions & action) != 0;
}

static void test_first_command_only(void) {
    assert(ap2_ble_213_slot_should_prepare(0));
    assert(!ap2_ble_213_slot_should_prepare(1));
}

static void assert_bytes(const uint8_t *actual, const uint8_t *expected, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        assert(actual[i] == expected[i]);
    }
}

static void test_ap2d_308_wire_frames(void) {
    static const uint8_t expected_query[]   = {0x7b, 0x12, 0x53, 0x00, 0x02, 0x00, 0x00, 0x7d, 0xc0, 0x17};
    static const uint8_t expected_select[]  = {0x7b, 0x12, 0x53, 0x00, 0x03, 0x00, 0x00, 0x7d, 0x40, 0x17, 0x02};
    static const uint8_t expected_prepare[] = {0x7b, 0x10, 0x53, 0x00, 0x03, 0x00, 0x00, 0x7d, 0x02, 0x01, 0x01};
    uint8_t              frame[AP2_BLE_213_SLOT_FRAME_MAX_SIZE];

    uint8_t size = ap2_ble_213_slot_encode_query(frame);
    assert(size == sizeof(expected_query));
    assert_bytes(frame, expected_query, size);

    size = ap2_ble_213_slot_encode_select(2, frame);
    assert(size == sizeof(expected_select));
    assert_bytes(frame, expected_select, size);

    size = ap2_ble_213_slot_encode_prepare(1, frame);
    assert(size == sizeof(expected_prepare));
    assert_bytes(frame, expected_prepare, size);
}

static void test_current_slot_response(void) {
    uint8_t frame[] = {0x7b, 0x12, 0x35, 0x00, 0x03, 0x00, 0x00, 0x7d, 0xc0, 0x17, 0x03};
    uint8_t slot    = 0xff;

    assert(ap2_ble_213_slot_decode_response(frame, sizeof(frame), &slot));
    assert(slot == 3);

    frame[10] = 4;
    assert(!ap2_ble_213_slot_decode_response(frame, sizeof(frame), &slot));
    frame[10] = 0;
    frame[8]  = 0x40;
    assert(!ap2_ble_213_slot_decode_response(frame, sizeof(frame), &slot));
    assert(!ap2_ble_213_slot_decode_response(frame, sizeof(frame) - 1, &slot));
    assert(!ap2_ble_213_slot_decode_response(NULL, sizeof(frame), &slot));
    assert(!ap2_ble_213_slot_decode_response(frame, sizeof(frame), NULL));
}

static void test_same_slot_dispatches_after_query(void) {
    ap2_ble_213_slot_state_t state;
    uint16_t                 deferred = 0;
    ap2_ble_213_slot_reset(&state);

    assert(ap2_ble_213_slot_begin(&state, 2, 0x123, 100) == AP2_BLE_213_SLOT_ACTION_QUERY);
    ap2_ble_213_slot_response(&state, 2);
    assert(ap2_ble_213_slot_task(&state, 104, &deferred) == AP2_BLE_213_SLOT_ACTION_NONE);

    const ap2_ble_213_slot_actions_t actions = ap2_ble_213_slot_task(&state, 105, &deferred);
    assert(actions == AP2_BLE_213_SLOT_ACTION_DISPATCH);
    assert(deferred == 0x123);
    assert(!ap2_ble_213_slot_active(&state));
}

static void test_changed_slot_uses_full_prepare_sequence(void) {
    ap2_ble_213_slot_state_t state;
    uint16_t                 deferred = 0;
    ap2_ble_213_slot_reset(&state);

    assert(ap2_ble_213_slot_begin(&state, 3, 0x321, 1000) == AP2_BLE_213_SLOT_ACTION_QUERY);
    ap2_ble_213_slot_response(&state, 0);

    ap2_ble_213_slot_actions_t actions = ap2_ble_213_slot_task(&state, 1005, &deferred);
    assert(has(actions, AP2_BLE_213_SLOT_ACTION_SELECT));
    assert(has(actions, AP2_BLE_213_SLOT_ACTION_PREPARE_1));
    assert(!has(actions, AP2_BLE_213_SLOT_ACTION_DISPATCH));
    assert(deferred == 0);

    assert(ap2_ble_213_slot_task(&state, 1024, &deferred) == AP2_BLE_213_SLOT_ACTION_NONE);
    assert(ap2_ble_213_slot_task(&state, 1025, &deferred) == AP2_BLE_213_SLOT_ACTION_PREPARE_2);
    assert(ap2_ble_213_slot_task(&state, 1044, &deferred) == AP2_BLE_213_SLOT_ACTION_NONE);

    actions = ap2_ble_213_slot_task(&state, 1045, &deferred);
    assert(actions == AP2_BLE_213_SLOT_ACTION_DISPATCH);
    assert(deferred == 0x321);
    assert(!ap2_ble_213_slot_active(&state));
}

static void test_missing_or_invalid_query_response_prepares_slot(void) {
    ap2_ble_213_slot_state_t state;
    uint16_t                 deferred;
    ap2_ble_213_slot_reset(&state);

    ap2_ble_213_slot_begin(&state, 1, 1, 10);
    ap2_ble_213_slot_response(&state, 4);
    const ap2_ble_213_slot_actions_t actions = ap2_ble_213_slot_task(&state, 15, &deferred);
    assert(has(actions, AP2_BLE_213_SLOT_ACTION_SELECT));
    assert(has(actions, AP2_BLE_213_SLOT_ACTION_PREPARE_1));
}

static void test_reset_cancels_deferred_command(void) {
    ap2_ble_213_slot_state_t state;
    uint16_t                 deferred = 0xffff;
    ap2_ble_213_slot_reset(&state);
    ap2_ble_213_slot_begin(&state, 1, 0x123, 10);
    ap2_ble_213_slot_reset(&state);

    assert(ap2_ble_213_slot_task(&state, 1000, &deferred) == AP2_BLE_213_SLOT_ACTION_NONE);
    assert(deferred == 0);
}

static void test_timer_wraparound(void) {
    ap2_ble_213_slot_state_t state;
    uint16_t                 deferred;
    ap2_ble_213_slot_reset(&state);
    ap2_ble_213_slot_begin(&state, 0, 1, UINT32_MAX - 2);
    ap2_ble_213_slot_response(&state, 0);

    assert(ap2_ble_213_slot_task(&state, 1, &deferred) == AP2_BLE_213_SLOT_ACTION_NONE);
    assert(ap2_ble_213_slot_task(&state, 2, &deferred) == AP2_BLE_213_SLOT_ACTION_DISPATCH);
}

int main(void) {
    test_first_command_only();
    test_ap2d_308_wire_frames();
    test_current_slot_response();
    test_same_slot_dispatches_after_query();
    test_changed_slot_uses_full_prepare_sequence();
    test_missing_or_invalid_query_response_prepares_slot();
    test_reset_cancels_deferred_command();
    test_timer_wraparound();
    return 0;
}
