// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_keymap_key.hpp"

using testing::_;

class Leader : public TestFixture {};

TEST_F(Leader, triggers_one_key_sequence) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_a      = KeymapKey(0, 1, 0, KC_A);

    set_keymap({key_leader, key_a});

    EXPECT_EQ(leader_sequence_active(), false);

    EXPECT_NO_REPORT(driver);
    tap_key(key_leader);

    EXPECT_EQ(leader_sequence_active(), true);

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);

    EXPECT_EQ(leader_sequence_timed_out(), false);

    idle_for(300);

    EXPECT_EQ(leader_sequence_active(), false);
    EXPECT_EQ(leader_sequence_timed_out(), true);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
}

TEST_F(Leader, triggers_two_key_sequence) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_a      = KeymapKey(0, 1, 0, KC_A);
    auto key_b      = KeymapKey(0, 2, 0, KC_B);

    set_keymap({key_leader, key_a, key_b});

    EXPECT_EQ(leader_sequence_active(), false);

    EXPECT_NO_REPORT(driver);
    tap_key(key_leader);

    EXPECT_EQ(leader_sequence_active(), true);

    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
    tap_key(key_b);

    EXPECT_EQ(leader_sequence_timed_out(), false);

    idle_for(300);

    EXPECT_EQ(leader_sequence_active(), false);
    EXPECT_EQ(leader_sequence_timed_out(), true);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
}

TEST_F(Leader, triggers_three_key_sequence) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_a      = KeymapKey(0, 1, 0, KC_A);
    auto key_b      = KeymapKey(0, 2, 0, KC_B);
    auto key_c      = KeymapKey(0, 3, 0, KC_C);

    set_keymap({key_leader, key_a, key_b, key_c});

    EXPECT_EQ(leader_sequence_active(), false);

    EXPECT_NO_REPORT(driver);
    tap_key(key_leader);

    EXPECT_EQ(leader_sequence_active(), true);

    EXPECT_REPORT(driver, (KC_3));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
    tap_key(key_b);
    tap_key(key_c);

    EXPECT_EQ(leader_sequence_timed_out(), false);

    idle_for(300);

    EXPECT_EQ(leader_sequence_active(), false);
    EXPECT_EQ(leader_sequence_timed_out(), true);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
}

TEST_F(Leader, triggers_four_key_sequence) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_a      = KeymapKey(0, 1, 0, KC_A);
    auto key_b      = KeymapKey(0, 2, 0, KC_B);
    auto key_c      = KeymapKey(0, 3, 0, KC_C);
    auto key_d      = KeymapKey(0, 4, 0, KC_D);

    set_keymap({key_leader, key_a, key_b, key_c, key_d});

    EXPECT_EQ(leader_sequence_active(), false);

    EXPECT_NO_REPORT(driver);
    tap_key(key_leader);

    EXPECT_EQ(leader_sequence_active(), true);

    EXPECT_REPORT(driver, (KC_4));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
    tap_key(key_b);
    tap_key(key_c);
    tap_key(key_d);

    EXPECT_EQ(leader_sequence_timed_out(), false);

    idle_for(300);

    EXPECT_EQ(leader_sequence_active(), false);
    EXPECT_EQ(leader_sequence_timed_out(), true);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
}

TEST_F(Leader, triggers_five_key_sequence) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_a      = KeymapKey(0, 1, 0, KC_A);
    auto key_b      = KeymapKey(0, 2, 0, KC_B);
    auto key_c      = KeymapKey(0, 3, 0, KC_C);
    auto key_d      = KeymapKey(0, 4, 0, KC_D);
    auto key_e      = KeymapKey(0, 5, 0, KC_E);

    set_keymap({key_leader, key_a, key_b, key_c, key_d, key_e});

    EXPECT_EQ(leader_sequence_active(), false);

    EXPECT_NO_REPORT(driver);
    tap_key(key_leader);

    EXPECT_EQ(leader_sequence_active(), true);

    EXPECT_REPORT(driver, (KC_5));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
    tap_key(key_b);
    tap_key(key_c);
    tap_key(key_d);
    tap_key(key_e);

    EXPECT_EQ(leader_sequence_timed_out(), false);

    idle_for(300);

    EXPECT_EQ(leader_sequence_active(), false);
    EXPECT_EQ(leader_sequence_timed_out(), true);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_a);
}

TEST_F(Leader, extracts_mod_tap_keycode) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_mt     = KeymapKey(0, 1, 0, LSFT_T(KC_A));

    set_keymap({key_leader, key_mt});

    tap_key(key_leader);

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_mt);

    EXPECT_EQ(leader_sequence_one_key(KC_A), true);

    idle_for(300);
}

TEST_F(Leader, extracts_layer_tap_keycode) {
    TestDriver driver;

    auto key_leader = KeymapKey(0, 0, 0, QK_LEADER);
    auto key_lt     = KeymapKey(0, 1, 0, LT(1, KC_A));

    set_keymap({key_leader, key_lt});

    tap_key(key_leader);

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_lt);

    EXPECT_EQ(leader_sequence_one_key(KC_A), true);

    idle_for(300);
}
