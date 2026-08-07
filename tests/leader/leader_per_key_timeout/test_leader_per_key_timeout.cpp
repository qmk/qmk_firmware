// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_keymap_key.hpp"

using testing::_;

class Leader : public TestFixture {};

TEST_F(Leader, does_not_timeout_during_sequence) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_a      = KeymapKey(0, 1, 0, KC_A);
    auto key_b      = KeymapKey(0, 2, 0, KC_B);
    auto key_c      = KeymapKey(0, 3, 0, KC_C);

    set_keymap({key_leader, key_a, key_b, key_c});

    tap_key(key_leader);

    EXPECT_NO_REPORT(driver);
    tap_key(key_a);

    idle_for(150);

    EXPECT_NO_REPORT(driver);
    tap_key(key_b);

    idle_for(150);

    EXPECT_REPORT(driver, (KC_3));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_c);

    idle_for(300);
}
