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
    KC_K,
    KC_L,
    KC_SCLN,
    KC_TAB,
    KC_LCTL,
    KC_LGUI,
    KC_LALT,
    KC_LSFT,
    KC_RSFT,

    L_NAV,
    L_SYM,

    SAFE_RANGE
} keycodes;

#define FLOW_COUNT 6
const uint16_t flow_config[FLOW_COUNT][3] = {
    {L_NAV, KC_A, KC_LALT},
    {L_NAV, KC_S, KC_LGUI},
    {L_NAV, KC_D, KC_LCTL},
    {L_SYM, KC_K, KC_LCTL},
    {L_SYM, KC_L, KC_LGUI},
    {L_SYM, KC_SCLN, KC_LALT},
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

uint16_t timer = 0;

uint16_t timer_read(void) {
    return timer;
}

uint16_t timer_elapsed(uint16_t from) {
    return timer - from;
}

#include "../flow.c"

void advance_timer_and_scan(uint16_t byUnits) {
    timer += byUnits;
    flow_matrix_scan();
}

void reset() {
    last_registered_code = KC_NO;
    registered_codes_count = 0;
    last_unregistered_code = KC_NO;
    unregistered_codes_count = 0;
    timer = 0;

    for (int i = 0; i < FLOW_COUNT; i++) {
        flow_state[i] = flow_up_unqueued;
        flow_pressed[i][0] = false;
        flow_pressed[i][1] = false;
        flow_timers_active[i] = false;
        flow_timeout_timers_active[i] = false;
    }
}

MAIN

TEST("navD + aD = alt")
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

TEST("navD + aD + aU + navU + aD + aU + aD + aU = alt+a a")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_A);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 3);
    ASSERT_EQ(UINT, last_registered_code, KC_A);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + aD + navU + aU + aD + aU + aD + aU  = alt+a")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_A);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 3);
    ASSERT_EQ(UINT, last_registered_code, KC_A);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + aD + navU + sD + sU + aU + sD + sU = alt+s s")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_S, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_S);

    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 3);
    ASSERT_EQ(UINT, last_registered_code, KC_S);

    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + aD + navU + sD + sU + sD + sU + aU + sD + sU = alt+s alt+s s")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_S, true);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_S);

    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_S, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 3);
    ASSERT_EQ(UINT, last_registered_code, KC_S);

    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 4);
    ASSERT_EQ(UINT, last_registered_code, KC_S);
    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + aD + tabD + tabU + navU + aU + sD + sU = alt+tab s")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_TAB, true);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_TAB, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_S);

    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + aD + dD + dU + aU + navU + sD + sU + sD + sU = alt+ctrl+s s")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    pass = update_flow(KC_D, true);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_LCTL);

    pass = update_flow(KC_D, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_S, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 3);
    ASSERT_EQ(UINT, last_registered_code, KC_S);

    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 2);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LCTL);

    pass = update_flow(KC_S, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 4);
    ASSERT_EQ(UINT, last_registered_code, KC_S);

    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 2);
END_TEST

TEST("navD + aD + navU + navD + tabD + tabU + navU + aU + sD + sU = alt+tab s")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, true);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_TAB, true);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_TAB, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_S);

    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + aD + navU + aU + navD = alt canceled")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, true);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);
END_TEST

TEST("navD + aD + navU + aU + navD + aD = alt canceled + alt")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, true);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + aD + navU + aU + symD = alt canceled")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_SYM, true);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);
END_TEST

// One shot works properly when subsequent keys are pressed almost at once
// but released one by one.
TEST("navD + aD + navU + aU + sD + kD + sU + kU = alt+s k")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_S, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_S);

    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_K, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 3);
    ASSERT_EQ(UINT, last_registered_code, KC_K);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);

    pass = update_flow(KC_K, false);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("aD + navD30ms + tab = alt + tab")
    reset();

    bool pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, registered_codes_count, 0);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);
    ASSERT_EQ(UINT, pass, false);

    advance_timer_and_scan(30);
    ASSERT_EQ(UINT, registered_codes_count, 0);

    pass = update_flow(L_NAV, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_TAB, true);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);
END_TEST

TEST("aD + navD31ms + tab = a + tab")
    reset();

    bool pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, registered_codes_count, 0);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);
    ASSERT_EQ(UINT, pass, false);

    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(L_NAV, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_A);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_TAB, true);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);
END_TEST

TEST("navD + aD + aU + navU + 501ms + aD + aU + aD + aU = a a")
    reset();

    bool pass = update_flow(L_NAV, true);
    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, false);
    pass = update_flow(L_NAV, false);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    advance_timer_and_scan(501);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_A);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);

    pass = update_flow(KC_A, true);
    ASSERT_EQ(UINT, pass, false);
    advance_timer_and_scan(31);
    ASSERT_EQ(UINT, registered_codes_count, 3);
    ASSERT_EQ(UINT, last_registered_code, KC_A);

    pass = update_flow(KC_A, false);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

END
