// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_keymap_key.hpp"

using testing::_;

// clang-format off
const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("qmk", 0x03A8) // Ψ
);
// clang-format on

class UnicodeUCIS : public TestFixture {};

TEST_F(UnicodeUCIS, matches_sequence) {
    TestDriver driver;

    auto key_q     = KeymapKey(0, 0, 0, KC_Q);
    auto key_m     = KeymapKey(0, 1, 0, KC_M);
    auto key_k     = KeymapKey(0, 2, 0, KC_K);
    auto key_enter = KeymapKey(0, 3, 0, KC_ENTER);

    set_keymap({key_q, key_m, key_k, key_enter});

    EXPECT_UNICODE(driver, 0x2328); // ⌨
    ucis_start();

    EXPECT_EQ(ucis_active(), true);
    EXPECT_EQ(ucis_count(), 0);

    EXPECT_REPORT(driver, (KC_Q));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_q);
    EXPECT_EQ(ucis_count(), 1);

    EXPECT_REPORT(driver, (KC_M));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_m);
    EXPECT_EQ(ucis_count(), 2);

    EXPECT_REPORT(driver, (KC_K));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_k);
    EXPECT_EQ(ucis_count(), 3);

    EXPECT_REPORT(driver, (KC_BACKSPACE)).Times(4);
    EXPECT_EMPTY_REPORT(driver).Times(4);
    EXPECT_UNICODE(driver, 0x03A8);
    tap_key(key_enter);

    EXPECT_EQ(ucis_active(), false);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(UnicodeUCIS, cancels_sequence) {
    TestDriver driver;

    auto key_q      = KeymapKey(0, 0, 0, KC_Q);
    auto key_m      = KeymapKey(0, 1, 0, KC_M);
    auto key_k      = KeymapKey(0, 2, 0, KC_K);
    auto key_escape = KeymapKey(0, 3, 0, KC_ESCAPE);

    set_keymap({key_q, key_m, key_k, key_escape});

    EXPECT_UNICODE(driver, 0x2328); // ⌨
    ucis_start();

    EXPECT_EQ(ucis_active(), true);
    EXPECT_EQ(ucis_count(), 0);

    EXPECT_REPORT(driver, (KC_Q));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_q);
    EXPECT_EQ(ucis_count(), 1);

    EXPECT_REPORT(driver, (KC_M));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_m);
    EXPECT_EQ(ucis_count(), 2);

    EXPECT_REPORT(driver, (KC_K));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_k);
    EXPECT_EQ(ucis_count(), 3);

    EXPECT_NO_REPORT(driver);
    tap_key(key_escape);

    EXPECT_EQ(ucis_active(), false);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(UnicodeUCIS, matches_sequence_with_corrected_typo) {
    TestDriver driver;

    auto key_q         = KeymapKey(0, 0, 0, KC_Q);
    auto key_m         = KeymapKey(0, 1, 0, KC_M);
    auto key_j         = KeymapKey(0, 2, 0, KC_J);
    auto key_k         = KeymapKey(0, 3, 0, KC_K);
    auto key_backspace = KeymapKey(0, 4, 0, KC_BACKSPACE);
    auto key_enter     = KeymapKey(0, 5, 0, KC_ENTER);

    set_keymap({key_q, key_m, key_j, key_k, key_backspace, key_enter});

    EXPECT_UNICODE(driver, 0x2328); // ⌨
    ucis_start();

    EXPECT_EQ(ucis_active(), true);
    EXPECT_EQ(ucis_count(), 0);

    EXPECT_REPORT(driver, (KC_Q));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_q);
    EXPECT_EQ(ucis_count(), 1);

    EXPECT_REPORT(driver, (KC_M));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_m);
    EXPECT_EQ(ucis_count(), 2);

    EXPECT_REPORT(driver, (KC_J));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_j);
    EXPECT_EQ(ucis_count(), 3);

    EXPECT_REPORT(driver, (KC_BACKSPACE));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_backspace);
    EXPECT_EQ(ucis_count(), 2);

    EXPECT_REPORT(driver, (KC_K));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_k);
    EXPECT_EQ(ucis_count(), 3);

    EXPECT_REPORT(driver, (KC_BACKSPACE)).Times(4);
    EXPECT_EMPTY_REPORT(driver).Times(4);
    EXPECT_UNICODE(driver, 0x03A8);
    tap_key(key_enter);

    EXPECT_EQ(ucis_active(), false);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(UnicodeUCIS, does_not_match_longer_sequence) {
    TestDriver driver;

    auto key_q     = KeymapKey(0, 0, 0, KC_Q);
    auto key_m     = KeymapKey(0, 1, 0, KC_M);
    auto key_k     = KeymapKey(0, 2, 0, KC_K);
    auto key_enter = KeymapKey(0, 3, 0, KC_ENTER);

    set_keymap({key_q, key_m, key_k, key_enter});

    EXPECT_UNICODE(driver, 0x2328); // ⌨
    ucis_start();

    EXPECT_EQ(ucis_active(), true);
    EXPECT_EQ(ucis_count(), 0);

    EXPECT_REPORT(driver, (KC_Q));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_q);
    EXPECT_EQ(ucis_count(), 1);

    EXPECT_REPORT(driver, (KC_M));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_m);
    EXPECT_EQ(ucis_count(), 2);

    EXPECT_REPORT(driver, (KC_K));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_k);
    EXPECT_EQ(ucis_count(), 3);

    EXPECT_REPORT(driver, (KC_K));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_k);
    EXPECT_EQ(ucis_count(), 4);

    EXPECT_NO_REPORT(driver);
    tap_key(key_enter);

    EXPECT_EQ(ucis_active(), false);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(UnicodeUCIS, does_not_match_shorter_sequence) {
    TestDriver driver;

    auto key_q     = KeymapKey(0, 0, 0, KC_Q);
    auto key_enter = KeymapKey(0, 1, 0, KC_ENTER);

    set_keymap({key_q, key_enter});

    EXPECT_UNICODE(driver, 0x2328); // ⌨
    ucis_start();

    EXPECT_EQ(ucis_active(), true);
    EXPECT_EQ(ucis_count(), 0);

    EXPECT_REPORT(driver, (KC_Q));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(key_q);
    EXPECT_EQ(ucis_count(), 1);

    EXPECT_NO_REPORT(driver);
    tap_key(key_enter);

    EXPECT_EQ(ucis_active(), false);

    VERIFY_AND_CLEAR(driver);
}
