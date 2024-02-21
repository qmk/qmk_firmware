// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_keymap_key.hpp"

using testing::_;

class Unicode : public TestFixture {};

TEST_F(Unicode, sends_bmp_unicode_sequence) {
    TestDriver driver;

    set_unicode_input_mode(UNICODE_MODE_LINUX);

    EXPECT_UNICODE(driver, 0x03A8); // Ψ
    register_unicode(0x03A8);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Unicode, sends_smp_unicode_sequence) {
    TestDriver driver;

    set_unicode_input_mode(UNICODE_MODE_LINUX);

    EXPECT_UNICODE(driver, 0x1F9D9); // 🧙
    register_unicode(0x1F9D9);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Unicode, sends_surrogate_pair_for_macos) {
    TestDriver driver;

    set_unicode_input_mode(UNICODE_MODE_MACOS);

    // EXPECT_UNICODE() assumes Linux input mode
    {
        testing::InSequence s;

        // Alt+D83EDDD9 🧙
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_D, KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_8, KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_3, KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_E, KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_D, KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_D, KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_D, KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_9, KC_LEFT_ALT));
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_EMPTY_REPORT(driver);
    }

    register_unicode(0x1F9D9);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Unicode, sends_unicode_string) {
    TestDriver driver;

    set_unicode_input_mode(UNICODE_MODE_LINUX);

    {
        testing::InSequence s;

        EXPECT_UNICODE(driver, 0xFF31);
        EXPECT_UNICODE(driver, 0xFF2D);
        EXPECT_UNICODE(driver, 0xFF2B);
        EXPECT_UNICODE(driver, 0xFF01);
    }
    send_unicode_string("ＱＭＫ！");

    VERIFY_AND_CLEAR(driver);
}
