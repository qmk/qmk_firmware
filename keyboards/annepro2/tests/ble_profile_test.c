#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "../annepro2_ble_profile.h"

static void test_empty_consumer_report(void) {
    uint8_t report[ANNEPRO2_BLE_CONSUMER_REPORT_SIZE];

    assert(annepro2_ble_encode_consumer(NULL, 0, report));
    for (size_t i = 0; i < sizeof(report); i++) {
        assert(report[i] == 0);
    }
}

#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
static void test_consumer_report(void) {
    const uint16_t usages[]   = {0x0001, 0x0183, 0x1234, 0xFFFF};
    const uint8_t  expected[] = {0x01, 0x00, 0x83, 0x01, 0x34, 0x12, 0xFF, 0xFF};
    uint8_t        report[ANNEPRO2_BLE_CONSUMER_REPORT_SIZE];

    assert(sizeof(report) == 8);
    assert(annepro2_ble_encode_consumer(usages, 4, report));
    for (size_t i = 0; i < sizeof(report); i++) {
        assert(report[i] == expected[i]);
    }
    assert(!annepro2_ble_encode_consumer(usages, 5, report));
}
#else
static void test_consumer_report(void) {
    static const uint16_t usages[] = {
        0x00E2, // Mute
        0x00E9, // Volume up
        0x00EA, // Volume down
        0x00CD, // Play/pause
        0x00B5, // Next track
        0x00B6, // Previous track
        0x006F, // Brightness up
        0x0070, // Brightness down
    };
    uint8_t report[ANNEPRO2_BLE_CONSUMER_REPORT_SIZE];

    assert(sizeof(report) == 4);
    for (uint8_t bit = 0; bit < 8; bit++) {
        assert(annepro2_ble_encode_consumer(&usages[bit], 1, report));
        assert(report[0] == (uint8_t)(1U << bit));
        assert(report[1] == 0 && report[2] == 0 && report[3] == 0);
    }
    assert(annepro2_ble_encode_consumer(usages, 8, report));
    assert(report[0] == 0xFF);

    const uint16_t unsupported = 0x0183;
    assert(!annepro2_ble_encode_consumer(&unsupported, 1, report));
}
#endif

static void test_slot_state(void) {
    annepro2_ble_slot_state_t state;

    annepro2_ble_encode_slot_state(true, &state);
    assert(state.command == 0x0B);
    assert(state.action == 1);

    annepro2_ble_encode_slot_state(false, &state);
#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
    assert(state.command == 0x24);
    assert(state.action == 2);
#else
    assert(state.command == 0x0B);
    assert(state.action == 0);
#endif
}

static void test_caps_lock(void) {
    uint8_t frame[] = {
        0x7B, 0x12, 0x35, 0x00, 0x03, 0x00, 0x00, 0x7D, 0x20, 0x07, 0x00,
    };
    bool caps_lock = true;

    assert(annepro2_ble_decode_caps_lock(frame, sizeof(frame), &caps_lock));
    assert(!caps_lock);

    frame[10] = 1;
    assert(annepro2_ble_decode_caps_lock(frame, sizeof(frame), &caps_lock));
    assert(caps_lock);

    frame[10] = 2;
    assert(!annepro2_ble_decode_caps_lock(frame, sizeof(frame), &caps_lock));
    frame[10] = 0;

    frame[9] = 0x0C;
    assert(!annepro2_ble_decode_caps_lock(frame, sizeof(frame), &caps_lock));
    frame[9] = 0x07;

    assert(!annepro2_ble_decode_caps_lock(frame, sizeof(frame) - 1, &caps_lock));
    assert(!annepro2_ble_decode_caps_lock(NULL, sizeof(frame), &caps_lock));
    assert(!annepro2_ble_decode_caps_lock(frame, sizeof(frame), NULL));
}

static void test_slot_config_has_no_runtime_profile(void) {
    for (int8_t expected = -1; expected <= 3; expected++) {
        uint32_t config;
        int8_t   slot;

        assert(annepro2_ble_encode_config(expected, &config));
        assert(annepro2_ble_decode_config(config, &slot));
        assert(slot == expected);
        assert(!annepro2_ble_decode_config(config ^ 0x00000100, &slot));
        assert(!annepro2_ble_decode_config(config ^ 0x01000000, &slot));
    }

    uint32_t config;
    int8_t   slot;
    assert(!annepro2_ble_encode_config(-2, &config));
    assert(!annepro2_ble_encode_config(4, &config));
    assert(!annepro2_ble_encode_config(0, NULL));
    assert(!annepro2_ble_decode_config(0, &slot));
    assert(!annepro2_ble_decode_config(0, NULL));
}

int main(void) {
    test_empty_consumer_report();
    test_consumer_report();
    test_slot_state();
    test_caps_lock();
    test_slot_config_has_no_runtime_profile();
    return 0;
}
