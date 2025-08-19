// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2023 @filterpaper
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.h"
#include "test_driver.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class Combo : public TestFixture {};

TEST_F(Combo, combo_basic) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    set_keymap({key_a, key_b});

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_EMPTY_REPORT(driver);
    // Press key A, wait for less than COMBO_TERM, then press key B
    run_one_scan_loop(); // Ensure that combo timer is > 0
    key_a.press();
    idle_for(COMBO_TERM-1);
    key_b.press();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(Combo, combo_too_slow) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    set_keymap({key_a, key_b});

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    // Press key A, wait for more than COMBO_TERM, then press key B
    run_one_scan_loop(); // Ensure that combo timer is > 0
    key_a.press();
    idle_for(COMBO_TERM + 1);
    key_b.press();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(Combo, combo_release_interrupt) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_c(0, 2, 0, KC_C);
    KeymapKey  key_d(0, 3, 0, KC_D);
    set_keymap({key_a, key_c, key_d});

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_2));
    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, C, D in that order; release A after C
    // Should still trigger combo for C+D
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_c.press();
    run_one_scan_loop();
    key_a.release();
    run_one_scan_loop();
    key_d.press();
    run_one_scan_loop();
    key_c.release();
    run_one_scan_loop();
    key_d.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(Combo, combo_disjoint) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_c(0, 2, 0, KC_C);
    KeymapKey  key_d(0, 3, 0, KC_D);
    set_keymap({key_a, key_b, key_c, key_d});

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_REPORT(driver, (KC_1, KC_2));
    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, B, C, D in that order; trigger combos for A+B and C+D
    tap_combo({key_a, key_b, key_c, key_d});
    VERIFY_AND_CLEAR(driver);
}

TEST_F(Combo, combo_noncontiguous) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_c(0, 2, 0, KC_C);
    KeymapKey  key_d(0, 3, 0, KC_D);
    set_keymap({key_a, key_b, key_c, key_d});

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_C));
    EXPECT_REPORT(driver, (KC_A, KC_C, KC_B));
    EXPECT_REPORT(driver, (KC_A, KC_C, KC_B, KC_D));
    EXPECT_REPORT(driver, (KC_C, KC_B, KC_D));
    EXPECT_REPORT(driver, (KC_B, KC_D));
    EXPECT_REPORT(driver, (KC_D));
    EXPECT_EMPTY_REPORT(driver);
    // Press A, C, B, D in that order; don't trigger any combos
    tap_combo({key_a, key_c, key_b, key_d});
    VERIFY_AND_CLEAR(driver);
}

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

TEST_F(Combo, combo_single_key_twice) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 1, KC_A);
    set_keymap({key_a});

    EXPECT_REPORT(driver, (KC_B));
    tap_combo({key_a});
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a});
    VERIFY_AND_CLEAR(driver);
}
