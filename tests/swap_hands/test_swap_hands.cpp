// Copyright 2023 Stefan Kerkmann (@KarlK90)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "action.h"
#include "config.h"
#include "gtest/gtest.h"
#include "keyboard_report_util.hpp"
#include "keycodes.h"
#include "quantum.h"
#include "keycode.h"
#include "test_common.h"
#include "test_driver.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

extern "C" {
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
    {{9, 1}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
    {{9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
    {{9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
};
}

using testing::_;
using testing::InSequence;

class SwapHands : public TestFixture {};

TEST_F(SwapHands, functions) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_a(0, 9, 0, KC_A);
    KeymapKey  key_z(0, 0, 0, KC_Z);
    set_keymap({key_a, key_z});

    // tap all keys without swapping
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // turn on swap hands
    swap_hands_on();
    EXPECT_TRUE(is_swap_hands_on());

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands
    swap_hands_off();
    EXPECT_FALSE(is_swap_hands_on());

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // toggle on swap hands
    swap_hands_toggle();
    EXPECT_TRUE(is_swap_hands_on());

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands
    swap_hands_toggle();
    EXPECT_FALSE(is_swap_hands_on());

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SwapHands, on_off) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_a(0, 9, 0, KC_A);
    KeymapKey  key_z(0, 0, 0, KC_Z);
    KeymapKey  key_swap_hands_on(0, 4, 0, QK_SWAP_HANDS_ON);
    KeymapKey  key_swap_hands_off(0, 5, 0, QK_SWAP_HANDS_OFF);
    set_keymap({key_a, key_z, key_swap_hands_on, key_swap_hands_off});

    // tap all keys without swapping
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // turn on swap hands
    tap_keys(key_swap_hands_on);
    EXPECT_TRUE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands by tapping the now swapped in hands off key
    tap_keys(key_swap_hands_on);
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);
    EXPECT_FALSE(is_swap_hands_on());

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SwapHands, momentary_on_off) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_a(0, 9, 0, KC_A);
    KeymapKey  key_z(0, 0, 0, KC_Z);
    KeymapKey  key_momentary_on(0, 4, 0, QK_SWAP_HANDS_MOMENTARY_ON);
    KeymapKey  key_x(0, 5, 0, KC_X);
    KeymapKey  key_momentary_off(0, 4, 1, QK_SWAP_HANDS_MOMENTARY_OFF);
    KeymapKey  key_y(0, 5, 1, KC_Y);
    set_keymap({key_z, key_a, key_momentary_on, key_x, key_momentary_off, key_y});

    // tap all keys without swapping
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Y));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z, key_x, key_y);
    VERIFY_AND_CLEAR(driver);

    // turn on swap hands while held
    key_momentary_on.press();
    run_one_scan_loop();
    EXPECT_TRUE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands by releasing momentary on key
    key_momentary_on.release();
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);
    EXPECT_FALSE(is_swap_hands_on());

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_z, key_a, key_x);
    VERIFY_AND_CLEAR(driver);

    // manually turn on swap hands
    swap_hands_on();
    EXPECT_TRUE(is_swap_hands_on());

    // turn off swap hands while held, which is now on the key_y position
    key_y.press();
    run_one_scan_loop();
    EXPECT_FALSE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_z, key_a, key_x);
    VERIFY_AND_CLEAR(driver);

    // turn on swap hands by releasing momentary off key again
    key_y.release();
    run_one_scan_loop();
    EXPECT_TRUE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // manually turn off swap hands again
    swap_hands_off();
    EXPECT_FALSE(is_swap_hands_on());
}

TEST_F(SwapHands, toggle) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_a(0, 9, 0, KC_A);
    KeymapKey  key_z(0, 0, 0, KC_Z);
    KeymapKey  key_swap_hands_toggle(0, 4, 0, QK_SWAP_HANDS_TOGGLE);
    KeymapKey  key_x(0, 5, 0, KC_X);
    set_keymap({key_a, key_z, key_swap_hands_toggle, key_x});

    // tap all keys without swapping
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z, key_x);
    VERIFY_AND_CLEAR(driver);

    // turn on swap hands
    tap_keys(key_swap_hands_toggle);
    EXPECT_TRUE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z, key_swap_hands_toggle);
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands, the toggle is now on the position of our x key
    tap_keys(key_x);
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);
    EXPECT_FALSE(is_swap_hands_on());

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z, key_x);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SwapHands, tap_toggle) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_a(0, 9, 0, KC_A);
    KeymapKey  key_z(0, 0, 0, KC_Z);
    KeymapKey  key_swap_hands_tap_toggle(0, 4, 0, QK_SWAP_HANDS_TAP_TOGGLE);
    KeymapKey  key_x(0, 5, 0, KC_X);
    set_keymap({key_z, key_a, key_swap_hands_tap_toggle, key_x});

    // tap all keys without swapping
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z, key_x);
    VERIFY_AND_CLEAR(driver);

    // Case 1: turn on swap hands by holding the key
    key_swap_hands_tap_toggle.press();
    idle_for(TAPPING_TERM + 1);
    EXPECT_TRUE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    EXPECT_TRUE(is_swap_hands_on());
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands by releasing the key again
    key_swap_hands_tap_toggle.release();
    run_one_scan_loop();
    EXPECT_FALSE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // Case 2: turn on swap hands by holding the key and interrupt it by
    // tapping it on the swapped layout
    key_swap_hands_tap_toggle.press();
    idle_for(TAPPING_TERM + 1);
    EXPECT_TRUE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys with swapping and tap the tap toggle key, which is on key_x
    // position
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_NO_REPORT(driver);
    tap_keys(key_a, key_z, key_x);
    EXPECT_TRUE(is_swap_hands_on());
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands by releasing the hold key again
    key_swap_hands_tap_toggle.release();
    run_one_scan_loop();
    EXPECT_FALSE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_z, key_a, key_x);
    VERIFY_AND_CLEAR(driver);

    // Case 3: turn on swap hands by tapping the key repeatedly
    for (int i = 0; i < TAPPING_TOGGLE; i++) {
        tap_key(key_swap_hands_tap_toggle);
        if (i < (TAPPING_TOGGLE - 1)) {
            EXPECT_FALSE(is_swap_hands_on());
        }
    }
    EXPECT_TRUE(is_swap_hands_on());

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    // key_x is our toggle key, thus doesn't produce a report but we don't tap
    // it here as we want to explicitly test the deactivation tapping sequence
    // later
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // toggle hand swapping off
    for (int i = 0; i < TAPPING_TOGGLE; i++) {
        tap_key(key_x);
        if (i < (TAPPING_TOGGLE - 1)) {
            EXPECT_TRUE(is_swap_hands_on());
        }
    }
    EXPECT_FALSE(is_swap_hands_on());

    // tap all keys without swapping
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z, key_x);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SwapHands, oneshot) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_a(0, 9, 0, KC_A);
    KeymapKey  key_z(0, 0, 0, KC_Z);
    KeymapKey  key_swap_hands_oneshot(0, 4, 0, QK_SWAP_HANDS_ONE_SHOT);
    KeymapKey  key_x(0, 5, 0, KC_X);
    set_keymap({key_a, key_z, key_swap_hands_oneshot, key_x});

    // tap all keys without swapping
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z, key_x);
    VERIFY_AND_CLEAR(driver);

    // turn on swap hands for "oneshot"
    tap_keys(key_swap_hands_oneshot);
    EXPECT_TRUE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys with only the first beeing swapped
    EXPECT_REPORT(driver, (KC_Z)); // swapped
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z)); // non-swapped
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a);
    EXPECT_FALSE(is_swap_hands_on());
    tap_keys(key_z, key_x);
    VERIFY_AND_CLEAR(driver);

    // turn on swap hands while holding the oneshot key
    key_swap_hands_oneshot.press();
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);
    EXPECT_TRUE(is_swap_hands_on());

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands by releasing the oneshot key
    key_swap_hands_oneshot.release();
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);
    EXPECT_FALSE(is_swap_hands_on());

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z, key_x);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SwapHands, tapping) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_a(0, 9, 0, KC_A);
    KeymapKey  key_z(0, 0, 0, KC_Z);
    KeymapKey  key_swap_hands_tapping(0, 4, 0, SH_T(KC_Y));
    KeymapKey  key_x(0, 5, 0, KC_X);
    set_keymap({key_z, key_a, key_swap_hands_tapping, key_x});

    // tap all keys without swapping
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Y));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_a, key_z, key_x, key_swap_hands_tapping);
    VERIFY_AND_CLEAR(driver);
    EXPECT_FALSE(is_swap_hands_on());

    // turn on swap hands while held
    key_swap_hands_tapping.press();
    idle_for(TAPPING_TERM + 1);
    EXPECT_TRUE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    // BUG: if key_x aka. key_swap_hands_tapping is tapped here swap hands is
    // stuck forever
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands
    EXPECT_TRUE(is_swap_hands_on());
    key_swap_hands_tapping.release();
    run_one_scan_loop();
    EXPECT_FALSE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Y));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_z, key_a, key_x, key_swap_hands_tapping);
    VERIFY_AND_CLEAR(driver);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SH_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

// see https://github.com/qmk/qmk_firmware/issues/2522
TEST_F(SwapHands, bug_2522) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_a(0, 9, 0, KC_A);
    KeymapKey  key_z(0, 0, 0, KC_Z);
    KeymapKey  key_swap_hands_tapping(0, 4, 0, SH_T(KC_SPC));
    KeymapKey  key_x(0, 5, 0, KC_X);
    set_keymap({key_z, key_a, key_swap_hands_tapping, key_x});

    // turn on swap hands while held
    key_swap_hands_tapping.press();
    run_one_scan_loop();
    EXPECT_TRUE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys with swapping
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    // BUG: if key_x aka. key_swap_hands_tapping is tapped here swap hands is
    // stuck forever
    tap_keys(key_a, key_z);
    VERIFY_AND_CLEAR(driver);

    // turn off swap hands
    EXPECT_TRUE(is_swap_hands_on());
    key_swap_hands_tapping.release();
    run_one_scan_loop();
    EXPECT_FALSE(is_swap_hands_on());
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);

    // tap all keys without swapping again
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_Y));
    EXPECT_EMPTY_REPORT(driver);
    tap_keys(key_z, key_a, key_x, key_swap_hands_tapping);
    VERIFY_AND_CLEAR(driver);
}
