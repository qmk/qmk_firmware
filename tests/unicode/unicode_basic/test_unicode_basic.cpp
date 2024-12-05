// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_keymap_key.hpp"

using testing::_;

class UnicodeBasic : public TestFixture {};

TEST_F(UnicodeBasic, sends_unicode_sequence) {
    TestDriver driver;

    set_unicode_input_mode(UNICODE_MODE_LINUX);

    auto key_uc = KeymapKey(0, 0, 0, UC(0x03A8)); // Ψ

    set_keymap({key_uc});

    EXPECT_UNICODE(driver, 0x03A8);
    tap_key(key_uc);

    VERIFY_AND_CLEAR(driver);
}
