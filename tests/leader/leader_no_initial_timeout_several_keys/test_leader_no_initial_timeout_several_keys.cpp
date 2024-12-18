// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_keymap_key.hpp"

using testing::_;

class Leader : public TestFixture {};

TEST_F(Leader, does_not_timeout_until_numkeypress_keys_pressed) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_a      = KeymapKey(0, 1, 0, KC_A);
    auto key_b      = KeymapKey(0, 2, 0, KC_B);

    set_keymap({key_leader, key_a, key_b});

    EXPECT_EQ(leader_sequence_active(), false);

    EXPECT_NO_REPORT(driver);
    tap_key(key_leader);

    EXPECT_EQ(leader_sequence_active(), true);

    idle_for(1000);

    EXPECT_EQ(leader_sequence_active(), true);
    EXPECT_EQ(leader_sequence_timed_out(), false);

    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);

    idle_for(1000);

    EXPECT_EQ(leader_sequence_active(), true);
    EXPECT_EQ(leader_sequence_timed_out(), false);

    tap_key(key_b);

    idle_for(300);

    EXPECT_EQ(leader_sequence_active(), false);
    EXPECT_EQ(leader_sequence_timed_out(), true);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
}
