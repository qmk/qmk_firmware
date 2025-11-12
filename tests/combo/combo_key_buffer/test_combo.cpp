// Copyright 2025 @johnwilmes
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.h"
#include "test_common.hpp"
#include "test_driver.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

extern bool combo_override;

class ComboKeyBuffer : public TestFixture {};

TEST_F(ComboKeyBuffer, combo_key_buffer) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_i(0, 2, 0, KC_I);
    KeymapKey  key_j(0, 3, 0, KC_J);
    KeymapKey  key_k(0, 4, 0, KC_K);
    KeymapKey  key_a2(0, 5, 0, KC_A);
    set_keymap({key_a, key_b, key_i, key_j, key_k, key_a2});

    EXPECT_REPORT(driver, (KC_1)).Times(2);
    EXPECT_REPORT(driver, (KC_1, KC_I));
    EXPECT_REPORT(driver, (KC_1, KC_I, KC_J));
    EXPECT_REPORT(driver, (KC_1, KC_J));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_i, key_j, key_b});
    VERIFY_AND_CLEAR(driver);

    // buffer overflow prevents combo from firing
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_I));
    EXPECT_REPORT(driver, (KC_A, KC_I, KC_J));
    EXPECT_REPORT(driver, (KC_A, KC_I, KC_J, KC_K));
    EXPECT_REPORT(driver, (KC_A, KC_I, KC_J, KC_K, KC_B));
    EXPECT_REPORT(driver, (KC_I, KC_J, KC_K, KC_B));
    EXPECT_REPORT(driver, (KC_J, KC_K, KC_B));
    EXPECT_REPORT(driver, (KC_K, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_i, key_j, key_k, key_b});
    VERIFY_AND_CLEAR(driver);

    // buffer overflow prevents combo from firing initially, fires with a second key press
    EXPECT_REPORT(driver, (KC_A)).Times(2);
    EXPECT_REPORT(driver, (KC_A, KC_I));
    EXPECT_REPORT(driver, (KC_A, KC_I, KC_J));
    EXPECT_REPORT(driver, (KC_A, KC_I, KC_J, KC_K));
    EXPECT_REPORT(driver, (KC_A, KC_I, KC_J, KC_K, KC_1));
    // the first KC_A release is consumed by the active combo even though it is a different position
    EXPECT_REPORT(driver, (KC_A, KC_J, KC_K, KC_1));
    EXPECT_REPORT(driver, (KC_A, KC_K, KC_1));
    EXPECT_REPORT(driver, (KC_A, KC_1));
    EXPECT_EMPTY_REPORT(driver);
    for (KeymapKey key : {key_a, key_i, key_j, key_k, key_b, key_a2}) {
        key.press();
        run_one_scan_loop();
    }
    for (KeymapKey key : {key_a, key_i, key_j, key_k, key_b, key_a2}) {
        key.release();
        run_one_scan_loop();
    }
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboKeyBuffer, combo_key_buffer_blocked) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_i(0, 2, 0, KC_I);
    KeymapKey  key_j(0, 3, 0, KC_J);
    KeymapKey  key_k(0, 4, 0, KC_K);
    KeymapKey  key_x(0, 5, 0, KC_X);
    set_keymap({key_a, key_b, key_i, key_j, key_k, key_x});

    // If the key buffer doesn't overflow, we wait for ABX to fire
    EXPECT_REPORT(driver, (KC_2)).Times(2);
    EXPECT_REPORT(driver, (KC_I, KC_2));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_b, key_i, key_x});
    VERIFY_AND_CLEAR(driver);

    // If the key buffer overflows, we just use AB
    EXPECT_REPORT(driver, (KC_1));
    EXPECT_REPORT(driver, (KC_1, KC_I));
    EXPECT_REPORT(driver, (KC_1, KC_I, KC_J));
    EXPECT_REPORT(driver, (KC_1, KC_I, KC_J, KC_K));
    EXPECT_REPORT(driver, (KC_1, KC_I, KC_J, KC_K, KC_X));
    EXPECT_REPORT(driver, (KC_I, KC_J, KC_K, KC_X));
    EXPECT_REPORT(driver, (KC_J, KC_K, KC_X));
    EXPECT_REPORT(driver, (KC_K, KC_X));
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_b, key_i, key_j, key_k, key_x});
    VERIFY_AND_CLEAR(driver);
}
