// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycode.h"
#include "test_common.hpp"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::InSequence;

class AutoCorrect : public TestFixture {
   public:
    void SetUp() override {
        autocorrect_enable();
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
TEST_F(AutoCorrect, OnOffToggle) {
    TestDriver driver;

    EXPECT_EQ(autocorrect_is_enabled(), true);

    autocorrect_disable();
    EXPECT_EQ(autocorrect_is_enabled(), false);
    autocorrect_disable();
    EXPECT_EQ(autocorrect_is_enabled(), false);

    autocorrect_enable();
    EXPECT_EQ(autocorrect_is_enabled(), true);
    autocorrect_enable();
    EXPECT_EQ(autocorrect_is_enabled(), true);

    autocorrect_toggle();
    EXPECT_EQ(autocorrect_is_enabled(), false);
    autocorrect_toggle();
    EXPECT_EQ(autocorrect_is_enabled(), true);

    VERIFY_AND_CLEAR(driver);
}

// Test that typing "fales" autocorrects to "false"
TEST_F(AutoCorrect, fales_to_false_autocorrection) {
    TestDriver driver;
    auto       key_f = KeymapKey(0, 0, 0, KC_F);
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_l = KeymapKey(0, 2, 0, KC_L);
    auto       key_e = KeymapKey(0, 3, 0, KC_E);
    auto       key_s = KeymapKey(0, 4, 0, KC_S);

    set_keymap({key_f, key_a, key_l, key_e, key_s});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(AnyNumber());
    { // Expect the following reports in this order.
        InSequence s;
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_F)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_L)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_BACKSPACE)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_S)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)));
    }

    TapKeys(key_f, key_a, key_l, key_e, key_s);

    VERIFY_AND_CLEAR(driver);
}

// Test that typing "fales" doesn't autocorrect if disabled
TEST_F(AutoCorrect, fales_disabled_autocorrect) {
    TestDriver driver;
    auto       key_f = KeymapKey(0, 0, 0, KC_F);
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_l = KeymapKey(0, 2, 0, KC_L);
    auto       key_e = KeymapKey(0, 3, 0, KC_E);
    auto       key_s = KeymapKey(0, 4, 0, KC_S);

    set_keymap({key_f, key_a, key_l, key_e, key_s});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(AnyNumber());
    { // Expect the following reports in this order.
        InSequence s;
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_F)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_L)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_S)));
    }

    autocorrect_disable();
    TapKeys(key_f, key_a, key_l, key_e, key_s);
    autocorrect_enable();

    VERIFY_AND_CLEAR(driver);
}

// Test that typing "falsify" doesn't autocorrect if disabled
TEST_F(AutoCorrect, falsify_should_not_autocorrect) {
    TestDriver driver;
    auto       key_f = KeymapKey(0, 0, 0, KC_F);
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_l = KeymapKey(0, 2, 0, KC_L);
    auto       key_s = KeymapKey(0, 3, 0, KC_S);
    auto       key_i = KeymapKey(0, 4, 0, KC_I);
    auto       key_y = KeymapKey(0, 5, 0, KC_Y);

    set_keymap({key_f, key_a, key_l, key_s, key_i, key_y});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(AnyNumber());
    { // Expect the following reports in this order.
        InSequence s;
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_F)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_L)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_S)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_I)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_F)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_Y)));
    }

    TapKeys(key_f, key_a, key_l, key_s, key_i, key_f, key_y);

    VERIFY_AND_CLEAR(driver);
}

// Test that  typing "ture" autocorrect to "true"
TEST_F(AutoCorrect, ture_to_true_autocorrect) {
    TestDriver driver;
    auto       key_t_code = KeymapKey(0, 0, 0, KC_T);
    auto       key_r      = KeymapKey(0, 1, 0, KC_R);
    auto       key_u      = KeymapKey(0, 2, 0, KC_U);
    auto       key_e      = KeymapKey(0, 3, 0, KC_E);
    auto       key_space  = KeymapKey(0, 4, 0, KC_SPACE);

    set_keymap({key_t_code, key_r, key_u, key_e, key_space});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(AnyNumber());
    { // Expect the following reports in this order.
        InSequence s;
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_SPACE)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_T)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_U)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_R)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_BACKSPACE))).Times(2);
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_R)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_U)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)));
    }

    TapKeys(key_space, key_t_code, key_u, key_r, key_e);

    VERIFY_AND_CLEAR(driver);
}

// Test that  typing "overture" does not autocorrect
TEST_F(AutoCorrect, overture_should_not_autocorrect) {
    TestDriver driver;
    auto       key_t_code = KeymapKey(0, 0, 0, KC_T);
    auto       key_r      = KeymapKey(0, 1, 0, KC_R);
    auto       key_u      = KeymapKey(0, 2, 0, KC_U);
    auto       key_e      = KeymapKey(0, 3, 0, KC_E);
    auto       key_o      = KeymapKey(0, 4, 0, KC_O);
    auto       key_v      = KeymapKey(0, 5, 0, KC_V);

    set_keymap({key_t_code, key_r, key_u, key_e, key_o, key_v});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(AnyNumber());
    { // Expect the following reports in this order.
        InSequence s;
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_O)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_V)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_R)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_T)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_U)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_R)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)));
    }

    TapKeys(key_o, key_v, key_e, key_r, key_t_code, key_u, key_r, key_e);

    VERIFY_AND_CLEAR(driver);
}
