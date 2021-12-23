#include <stdint.h>
#include "minunit.h"

// Stubs
#define QMK_KEYBOARD_H "tests/qmk.h"

// Keycodes necessary for testing
typedef enum {
    KC_NO,
    KC_A,
    KC_S,
    KC_D,
    KC_LCTL,
    KC_LGUI,
    KC_LALT,
    KC_LSFT,
    KC_RSFT,

    L_NAV,

    SAFE_RANGE
} keycodes;

#define FLOW_COUNT 3
const uint16_t flow_config[FLOW_COUNT][3] = {
    {L_NAV, KC_A, KC_LALT},
    {L_NAV, KC_S, KC_LGUI},
    {L_NAV, KC_D, KC_LCTL},
};

keycodes last_registered_code = KC_NO;
uint16_t registered_codes_count = 0;
keycodes last_unregistered_code = KC_NO;
uint16_t unregistered_codes_count = 0;

void register_code(uint16_t keycode) {
    last_registered_code = keycode;
    registered_codes_count++;
}

void unregister_code(uint16_t keycode) {
    last_unregistered_code = keycode;
    unregistered_codes_count++;
}

#include "../flow.c"

void reset() {
    last_registered_code = KC_NO;
    registered_codes_count = 0;
    last_unregistered_code = KC_NO;
    unregistered_codes_count = 0;

    for (int i = 0; i < FLOW_COUNT; i++) {
        flow_state[i] = flow_up_unqueued;
        flow_pressed[i][0] = false;
        flow_pressed[i][1] = false;
    }
}

MAIN

TEST("L_NAV d + KC_A d = KC_LALT d")
    reset();

    bool pass = update_flow(L_NAV, true);
    ASSERT_EQ(UINT, registered_codes_count, 0);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);
    ASSERT_EQ(UINT, pass, false);
END_TEST

// TODO: fix test after delayed press implementation
// TEST("KC_A d + L_NAV d = KC_LALT d")
//     reset();
//
//     bool pass = update_flow(KC_A, true);
//     ASSERT_EQ(UINT, registered_codes_count, 0);
//     ASSERT_EQ(UINT, unregistered_codes_count, 0);
//     ASSERT_EQ(UINT, pass, true);
//
//     pass = update_flow(L_NAV, true);
//     ASSERT_EQ(UINT, registered_codes_count, 1);
//     ASSERT_EQ(UINT, last_registered_code, KC_LALT);
//     ASSERT_EQ(UINT, unregistered_codes_count, 1);
//     ASSERT_EQ(UINT, last_unregistered_code, KC_A);
//     ASSERT_EQ(UINT, pass, true);
// END_TEST

TEST("L_NAV d + KC_A d + KC_A u + L_NAV u + KC_A d + KC_A u = KC_LALT d + KC_A d")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);
END_TEST

END
