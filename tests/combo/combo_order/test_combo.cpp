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

class ComboOrder : public TestFixture {};

TEST_F(ComboOrder, combo_requires_order) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_c(0, 2, 0, KC_C);
    set_keymap({key_a, key_b, key_c});

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, B, C in that order
    // triggers ABC combo
    tap_combo({key_a, key_b, key_c});
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    // Press C, A, B in that order; release B, A, C
    // triggers CAB combo in order
    tap_combo({key_c, key_a, key_b});
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_C));
    EXPECT_REPORT(driver, (KC_A, KC_C, KC_B));
    EXPECT_REPORT(driver, (KC_C, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, C, B
    // does not trigger any combo
    tap_combo({key_a, key_c, key_b});
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboOrder, combo_doesnt_require_order) {
    TestDriver driver;
    KeymapKey  key_x(0, 0, 0, KC_X);
    KeymapKey  key_y(0, 1, 0, KC_Y);
    KeymapKey  key_z(0, 2, 0, KC_Z);
    set_keymap({key_x, key_y, key_z});

    EXPECT_REPORT(driver, (KC_3));
    EXPECT_EMPTY_REPORT(driver);
    // Press X, Y, Z in that order
    // triggers XYZ combo
    tap_combo({key_x, key_y, key_z});
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_3));
    EXPECT_EMPTY_REPORT(driver);
    // Press Y, X, Z in that order
    // triggers XYZ combo
    tap_combo({key_y, key_x, key_z});
    VERIFY_AND_CLEAR(driver);
}
