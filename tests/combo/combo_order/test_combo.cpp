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

TEST_F(ComboConflicts, combo_requires_order) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_c(0, 2, 0, KC_C);
    set_keymap({key_a, key_b, key_c});

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, B, C in that order; release C, B, A
    // triggers ABC combo in order
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
    key_a.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    // Press C, A, B in that order; release B, A, C
    // triggers CAB combo in order
    run_one_scan_loop();
    key_c.press();
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    key_c.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A)).Times(2);
    EXPECT_REPORT(driver, (KC_A, KC_C)).Times(2);
    EXPECT_REPORT(driver, (KC_A, KC_C, KC_B));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, C, B; release B, C, A
    // does not trigger any combo
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_c.press();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    key_c.release();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboConflicts, combo_doesnt_require_order) {
    TestDriver driver;
    KeymapKey  key_x(0, 0, 0, KC_X);
    KeymapKey  key_y(0, 1, 0, KC_Y);
    KeymapKey  key_z(0, 2, 0, KC_Z);
    set_keymap({key_x, key_y, key_z});

    EXPECT_REPORT(driver, (KC_3));
    EXPECT_EMPTY_REPORT(driver);
    // Press X, Y, Z in that order; release Z, Y, X
    // triggers XYZ combo
    run_one_scan_loop();
    key_x.press();
    run_one_scan_loop();
    key_y.press();
    run_one_scan_loop();
    key_z.press();
    run_one_scan_loop();
    key_z.release();
    run_one_scan_loop();
    key_y.release();
    run_one_scan_loop();
    key_x.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);


    EXPECT_REPORT(driver, (KC_3));
    EXPECT_EMPTY_REPORT(driver);
    // Press Y, X, Z in that order; release Z, X, Y
    // triggers XYZ combo
    run_one_scan_loop();
    key_y.press();
    run_one_scan_loop();
    key_x.press();
    run_one_scan_loop();
    key_z.press();
    run_one_scan_loop();
    key_z.release();
    run_one_scan_loop();
    key_x.release();
    run_one_scan_loop();
    key_y.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
