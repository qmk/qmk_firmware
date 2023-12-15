// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_keymap_key.hpp"

using testing::_;

const uint32_t PROGMEM unicode_map[] = {
    0x03A8, // Ψ
    0x2318  // ⌘
};

class UnicodeMap : public TestFixture {};

TEST_F(UnicodeMap, sends_unicodemap_code_point_from_keycode) {
    TestDriver driver;

    auto key_um = KeymapKey(0, 0, 0, UM(0));

    set_keymap({key_um});

    EXPECT_UNICODE(driver, 0x03A8);
    tap_key(key_um);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(UnicodeMap, sends_unicodemap_pair_from_keycode) {
    TestDriver driver;

    auto key_shift = KeymapKey(0, 0, 0, KC_LEFT_SHIFT);
    auto key_up    = KeymapKey(0, 1, 0, UP(0, 1));

    set_keymap({key_shift, key_up});

    EXPECT_UNICODE(driver, 0x03A8);
    tap_key(key_up);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    key_shift.press();
    run_one_scan_loop();

    EXPECT_UNICODE(driver, 0x2318);
    tap_key(key_up);

    EXPECT_NO_REPORT(driver);
    key_shift.release();
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}
