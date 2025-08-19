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

class ComboEvents : public TestFixture {};

TEST_F(ComboEvents, combo_action) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 1, KC_A);
    KeymapKey  key_b(0, 0, 2, KC_B);
    set_keymap({key_a, key_b});

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver).Times(2);
    tap_combo({key_a, key_b});
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboEvents, combo_release) {
    TestDriver driver;
    KeymapKey  key_x(0, 0, 1, KC_X);
    KeymapKey  key_y(0, 0, 2, KC_Y);
    set_keymap({key_x, key_y});

    EXPECT_REPORT(driver, (KC_1)).Times(3);
    EXPECT_REPORT(driver, (KC_1, KC_2));
    EXPECT_REPORT(driver, (KC_1, KC_3));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_x, key_y});
    VERIFY_AND_CLEAR(driver);


    // Combo deactivates early when y is released
    EXPECT_REPORT(driver, (KC_1)).Times(2);
    EXPECT_REPORT(driver, (KC_1, KC_3));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_y, key_x});
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboEvents, combo_should_trigger) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 1, KC_A);
    KeymapKey  key_b(0, 0, 2, KC_B);
    set_keymap({key_a, key_b});

    combo_override = true;
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_b});
    VERIFY_AND_CLEAR(driver);
    combo_override = false;
}
