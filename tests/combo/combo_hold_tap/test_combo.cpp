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

class ComboConflicts : public TestFixture {};

TEST_F(ComboConflicts, combo_hold) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 1, KC_A);
    KeymapKey  key_b(0, 0, 2, KC_B);
    set_keymap({key_a, key_b});

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_b}, COMBO_HOLD_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_b}, COMBO_HOLD_TERM - 1);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboConflicts, combo_tap) {
    TestDriver driver;
    KeymapKey  key_x(0, 0, 1, KC_X);
    KeymapKey  key_y(0, 0, 2, KC_Y);
    set_keymap({key_x, key_y});

    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_x, key_y}, COMBO_HOLD_TERM - 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_X));
    EXPECT_REPORT(driver, (KC_X, KC_Y));
    EXPECT_REPORT(driver, (KC_Y));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_x, key_y}, COMBO_HOLD_TERM + 1);
    VERIFY_AND_CLEAR(driver);
}
