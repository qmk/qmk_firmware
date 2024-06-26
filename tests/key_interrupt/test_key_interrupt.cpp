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
TEST_F(KeyInterrupt, a_d_key_interrupt) {
    TestDriver driver;
    auto       key_a = KeymapKey(0, 0, 0, KC_A);
    auto       key_d = KeymapKey(0, 1, 0, KC_D);

    set_keymap({key_a, key_d});

    /* Press A key */
    EXPECT_NO_REPORT(driver);
    key_a.press();
    run_one_scan_loop();
    EXPECT_REPORT(driver, (KC_A));

    /* Press D key */
    key_d.press();
    run_one_scan_loop();
    EXPECT_REPORT(driver, (KC_D));
    VERIFY_AND_CLEAR(driver);
}
