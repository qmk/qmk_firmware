// Copyright 2024 Harrison Chan (@xelus22)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycode.h"
#include "test_common.hpp"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::InSequence;

class KeyInterrupt : public TestFixture {
   public:
    void SetUp() override {
        key_interrupt_enable();
    }
    // Convenience function to tap `key`.
    void TapKey(KeymapKey key) {
        key.press();
        run_one_scan_loop();
        key.release();
        run_one_scan_loop();
    }

    // Taps in order each key in `keys`.
    template <typename... Ts>
    void TapKeys(Ts... keys) {
        for (KeymapKey key : {keys...}) {
            TapKey(key);
        }
    }
};

// Test that verifies enable/disable/toggling works
TEST_F(KeyInterrupt, OnOffToggle) {
    TestDriver driver;

    EXPECT_EQ(key_interrupt_is_enabled(), true);

    key_interrupt_disable();
    EXPECT_EQ(key_interrupt_is_enabled(), false);
    key_interrupt_disable();
    EXPECT_EQ(key_interrupt_is_enabled(), false);

    key_interrupt_enable();
    EXPECT_EQ(key_interrupt_is_enabled(), true);
    key_interrupt_enable();
    EXPECT_EQ(key_interrupt_is_enabled(), true);

    key_interrupt_toggle();
    EXPECT_EQ(key_interrupt_is_enabled(), false);
    key_interrupt_toggle();
    EXPECT_EQ(key_interrupt_is_enabled(), true);

    VERIFY_AND_CLEAR(driver);
}

// Test that holding A, and then pressing D, releases A and sends only D
TEST_F(KeyInterrupt, a_hold_d_key_interrupt) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_d(0, 1, 0, KC_D);

    set_keymap({key_a, key_d});

    /* Press A key */
    EXPECT_REPORT(driver, (KC_A));
    key_a.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press D key */
    EXPECT_REPORT(driver, (KC_D));
    key_d.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Test that holding D, and then pressing A, releases D and sends only A
TEST_F(KeyInterrupt, d_hold_a_key_interrupt) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_d(0, 1, 0, KC_D);

    set_keymap({key_a, key_d});

    /* Press A key */
    EXPECT_REPORT(driver, (KC_D));
    key_d.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press D key */
    EXPECT_REPORT(driver, (KC_A));
    key_a.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Test that holding W, holding A, and then pressing D, does NOT release W, but only releases A
TEST_F(KeyInterrupt, w_a_hold_d_key_interrupt) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_d(0, 1, 0, KC_D);
    KeymapKey  key_w(0, 2, 0, KC_W);

    set_keymap({key_a, key_d, key_w});

    /* Press W key */
    EXPECT_REPORT(driver, (KC_W));
    key_w.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press A key */
    EXPECT_REPORT(driver, (KC_A, KC_W));
    key_a.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press D key */
    EXPECT_REPORT(driver, (KC_D, KC_W));
    key_d.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Test that holding D and F, then press A, releases D and F, and sends only A
TEST_F(KeyInterrupt, d_f_hold_a_key_interrupt) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_d(0, 1, 0, KC_D);
    KeymapKey  key_f(0, 2, 0, KC_F);

    set_keymap({key_a, key_d, key_f});

    /* Press F key */
    EXPECT_REPORT(driver, (KC_F));
    key_f.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press D key */
    EXPECT_REPORT(driver, (KC_D, KC_F));
    key_d.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press A key */
    EXPECT_REPORT(driver, (KC_A));
    key_a.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// 2 Consecutive key interrupts, A, D, A, D
TEST_F(KeyInterrupt, d_and_a_consecutive_key_interrupt) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_d(0, 1, 0, KC_D);
    KeymapKey  key_f(0, 2, 0, KC_F);

    set_keymap({key_a, key_d, key_f});

    /* Press A key */
    EXPECT_REPORT(driver, (KC_A));
    key_a.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press D key */
    EXPECT_REPORT(driver, (KC_D));
    key_d.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_a.release();
    run_one_scan_loop();

    /* Press A key */
    EXPECT_REPORT(driver, (KC_A));
    key_a.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_d.release();
    run_one_scan_loop();

    /* Press D key */
    EXPECT_REPORT(driver, (KC_D));
    key_d.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
