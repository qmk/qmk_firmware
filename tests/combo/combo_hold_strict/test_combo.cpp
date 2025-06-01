// Copyright 2024 @Filios92
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gmock/gmock.h"
#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.h"
#include "test_common.hpp"
#include "test_driver.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class ComboHoldStrict : public TestFixture {};

TEST_F(ComboHoldStrict, combo_hold_strict_held_full_term) {
    TestDriver driver;
    KeymapKey  key_h(0, 0, 0, KC_H);
    KeymapKey  key_j(0, 0, 1, KC_J);
    set_keymap({key_h, key_j});

    EXPECT_REPORT(driver, (KC_LCTL));
    key_h.press();
    run_one_scan_loop();
    key_j.press();
    run_one_scan_loop();
    idle_for(COMBO_HOLD_TERM);
    combo_task();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboHoldStrict, combo_hold_strict_tap_other_key_before_term) {
    TestDriver driver;
    KeymapKey  key_h(0, 0, 0, KC_H);
    KeymapKey  key_j(0, 0, 1, KC_J);
    KeymapKey  key_f(0, 0, 2, KC_F);
    set_keymap({key_h, key_j, key_f});

    EXPECT_REPORT(driver, (KC_H));
    EXPECT_REPORT(driver, (KC_H, KC_J));
    EXPECT_REPORT(driver, (KC_H, KC_J, KC_F));
    key_h.press();
    run_one_scan_loop();
    key_j.press();
    run_one_scan_loop();
    idle_for(COMBO_HOLD_TERM / 2);
    combo_task();
    key_f.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboHoldStrict, combo_hold_strict_tap_other_key_after_term) {
    TestDriver driver;
    KeymapKey  key_h(0, 0, 0, KC_H);
    KeymapKey  key_j(0, 0, 1, KC_J);
    KeymapKey  key_f(0, 0, 2, KC_F);
    set_keymap({key_h, key_j, key_f});

    EXPECT_REPORT(driver, (KC_LCTL));
    EXPECT_REPORT(driver, (KC_LCTL, KC_F));
    key_h.press();
    run_one_scan_loop();
    key_j.press();
    run_one_scan_loop();
    idle_for(COMBO_HOLD_TERM);
    combo_task();
    key_f.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
