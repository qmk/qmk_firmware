// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2023 @filterpaper
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

TEST_F(ComboConflicts, combo_irrelevant_press) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_x(0, 2, 0, KC_X);
    KeymapKey  key_y(0, 3, 0, KC_Y);
    KeymapKey  key_z(0, 4, 0, KC_Z);
    set_keymap({key_a, key_b, key_x, key_y, key_z});

    EXPECT_REPORT(driver, (KC_1)).Times(2);
    EXPECT_REPORT(driver, (KC_1, KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, Z, B in that order; release B, Z, A
    // Combo for A+B should be triggered since it does not require contiguity
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_z.press();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    key_z.release();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A)).Times(3);
    EXPECT_REPORT(driver, (KC_A, KC_Z));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, press and release Z, press B in that order; release B then A
    // Combo for A+B should not be triggered since there was a press+release of Z in between
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_z.press();
    run_one_scan_loop();
    key_z.release();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_X)).Times(2);
    EXPECT_REPORT(driver, (KC_X, KC_Z)).Times(2);
    EXPECT_REPORT(driver, (KC_X, KC_Z, KC_Y));
    EXPECT_EMPTY_REPORT(driver);
    // Press X, Z, Y in that order; release Y, Z, X
    // Combo for X+Y should not be triggered since it requires contiguity
    run_one_scan_loop();
    key_x.press();
    run_one_scan_loop();
    key_z.press();
    run_one_scan_loop();
    key_y.press();
    run_one_scan_loop();
    key_y.release();
    run_one_scan_loop();
    key_z.release();
    run_one_scan_loop();
    key_x.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboConflicts, combo_priority) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_x(0, 2, 0, KC_X);
    KeymapKey  key_y(0, 3, 0, KC_Y);
    set_keymap({key_a, key_b, key_x, key_y});

    EXPECT_REPORT(driver, (KC_4)).Times(2);
    EXPECT_REPORT(driver, (KC_4, KC_A));
    EXPECT_EMPTY_REPORT(driver);
    // Press X, A, B, Y in that order; release Y, B, A, X
    // Combo for X+B+Y should be triggered since it has higher priority (index)
    run_one_scan_loop();
    key_x.press();
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    key_y.press();
    run_one_scan_loop();
    key_y.release();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    key_x.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_4)).Times(2);
    EXPECT_REPORT(driver, (KC_4, KC_A));
    EXPECT_EMPTY_REPORT(driver);
    // Press X, Y, A, B in that order; release B, A, Y, X
    // Combo for X+B+Y should be triggered since it has higher priority (index)
    run_one_scan_loop();
    key_x.press();
    run_one_scan_loop();
    key_y.press();
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    key_y.release();
    run_one_scan_loop();
    key_x.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboConflicts, combo_priority_trigger) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_x(0, 2, 0, KC_X);
    KeymapKey  key_y(0, 3, 0, KC_Y);
    set_keymap({key_a, key_b, key_x, key_y});

    EXPECT_REPORT(driver, (KC_3)).Times(2);
    EXPECT_REPORT(driver, (KC_3, KC_B));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, X, B, Y in that order; release Y, B, X, A
    // Combo for X+A+Y should be triggered since it has earlier trigger
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_x.press();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    key_y.press();
    run_one_scan_loop();
    key_y.release();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    key_x.release();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboConflicts, combo_wait_for_preferred) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_x(0, 2, 0, KC_X);
    KeymapKey  key_y(0, 3, 0, KC_Y);
    KeymapKey  key_c(0, 4, 0, KC_C);
    set_keymap({key_a, key_b, key_x, key_y, key_c});

    EXPECT_REPORT(driver, (KC_4)).Times(2);
    EXPECT_REPORT(driver, (KC_4, KC_A));
    EXPECT_EMPTY_REPORT(driver);
    // Press X, A, Y, B in that order; release B, Y, A, X
    // Combo for X+B+Y should be triggered since it has higher priority (index), even though X+A+Y completed before it
    run_one_scan_loop();
    key_x.press();
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_y.press();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    key_y.release();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    key_x.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_6));
    EXPECT_EMPTY_REPORT(driver);
    // Press X, Y, A, B, C in that order; release C, B, A, Y, X
    // Combo for X+A+B+C+Y should be triggered sice it has higher priority than the others
    run_one_scan_loop();
    key_x.press();
    run_one_scan_loop();
    key_y.press();
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    key_c.press();
    run_one_scan_loop();
    key_c.release();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    key_y.release();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    key_x.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
