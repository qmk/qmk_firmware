// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2023 @filterpaper
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "quantum.h"
#include "keycode.h"
#include "test_common.h"
#include "test_driver.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class Combo : public TestFixture {};

TEST_F(Combo, combo_modtest_tapped) {
    TestDriver driver;
    KeymapKey  key_y(0, 0, 1, KC_Y);
    KeymapKey  key_u(0, 0, 2, KC_U);
    set_keymap({key_y, key_u});

    EXPECT_REPORT(driver, (KC_SPACE));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_y, key_u});
    VERIFY_AND_CLEAR(driver);
}

TEST_F(Combo, combo_modtest_held_longer_than_tapping_term) {
    TestDriver driver;
    KeymapKey  key_y(0, 0, 1, KC_Y);
    KeymapKey  key_u(0, 0, 2, KC_U);
    set_keymap({key_y, key_u});

    EXPECT_REPORT(driver, (KC_RIGHT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_y, key_u}, TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(Combo, combo_osmshift_tapped) {
    TestDriver driver;
    KeymapKey  key_z(0, 0, 1, KC_Z);
    KeymapKey  key_x(0, 0, 2, KC_X);
    KeymapKey  key_i(0, 0, 3, KC_I);
    set_keymap({key_z, key_x, key_i});

    EXPECT_NO_REPORT(driver);
    tap_combo({key_z, key_x});
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_I, KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_i);
    VERIFY_AND_CLEAR(driver);
}
