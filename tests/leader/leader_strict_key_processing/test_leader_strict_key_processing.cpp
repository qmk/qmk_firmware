// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_keymap_key.hpp"

using testing::_;

class Leader : public TestFixture {};

TEST_F(Leader, does_not_extract_mod_tap_keycode) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_mt     = KeymapKey(0, 1, 0, LSFT_T(KC_A));

    set_keymap({key_leader, key_mt});

    tap_key(key_leader);

    EXPECT_NO_REPORT(driver);
    tap_key(key_mt);

    EXPECT_EQ(leader_sequence_one_key(KC_A), false);
    EXPECT_EQ(leader_sequence_one_key(LSFT_T(KC_A)), true);
}

TEST_F(Leader, does_not_extract_layer_tap_keycode) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_lt     = KeymapKey(0, 1, 0, LT(1, KC_A));

    set_keymap({key_leader, key_lt});

    tap_key(key_leader);

    EXPECT_NO_REPORT(driver);
    tap_key(key_lt);

    EXPECT_EQ(leader_sequence_one_key(KC_A), false);
    EXPECT_EQ(leader_sequence_one_key(LT(1, KC_A)), true);
}
