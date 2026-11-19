// Copyright 2026 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycode.h"
#include "test_common.hpp"

using testing::_;
using testing::AnyNumber;
using testing::InSequence;

class NkroBootCompat : public TestFixture {};

TEST_F(NkroBootCompat, SingleKeyIsReportedInBothViewsThenCleared) {
    TestDriver driver;
    auto       key_a = KeymapKey(0, 0, 0, KC_A);
    set_keymap({key_a});

    key_a.press();
    EXPECT_REPORT(driver, (KC_A)).Times(1);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_a.release();
    EXPECT_EMPTY_REPORT(driver).Times(1);
    run_one_scan_loop();
}

TEST_F(NkroBootCompat, SixKeysAppearInBothViews) {
    TestDriver driver;
    auto       key_a = KeymapKey(0, 0, 0, KC_A);
    auto       key_b = KeymapKey(0, 1, 0, KC_B);
    auto       key_c = KeymapKey(0, 2, 0, KC_C);
    auto       key_d = KeymapKey(0, 3, 0, KC_D);
    auto       key_e = KeymapKey(0, 4, 0, KC_E);
    auto       key_f = KeymapKey(0, 5, 0, KC_F);
    set_keymap({key_a, key_b, key_c, key_d, key_e, key_f});

    key_a.press();
    key_b.press();
    key_c.press();
    key_d.press();
    key_e.press();
    key_f.press();
    EXPECT_ANY_REPORT(driver).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_A, KC_B, KC_C, KC_D, KC_E, KC_F)).Times(1);
    run_one_scan_loop();
}

TEST_F(NkroBootCompat, SeventhKeyIsOnlyInTheBitfield) {
    TestDriver driver;
    auto       key_a = KeymapKey(0, 0, 0, KC_A);
    auto       key_b = KeymapKey(0, 1, 0, KC_B);
    auto       key_c = KeymapKey(0, 2, 0, KC_C);
    auto       key_d = KeymapKey(0, 3, 0, KC_D);
    auto       key_e = KeymapKey(0, 4, 0, KC_E);
    auto       key_f = KeymapKey(0, 5, 0, KC_F);
    auto       key_g = KeymapKey(0, 6, 0, KC_G);
    set_keymap({key_a, key_b, key_c, key_d, key_e, key_f, key_g});

    key_a.press();
    key_b.press();
    key_c.press();
    key_d.press();
    key_e.press();
    key_f.press();
    EXPECT_ANY_REPORT(driver).Times(AnyNumber());
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_g.press();
    EXPECT_CALL(driver, send_keyboard_nkro_mock(KeyboardNkroReportViews({KC_A, KC_B, KC_C, KC_D, KC_E, KC_F}, {KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G}))).Times(1);
    run_one_scan_loop();
}

TEST_F(NkroBootCompat, BootViewIsNotBackfilledWhenOneOfSixIsReleased) {
    TestDriver driver;
    auto       key_a = KeymapKey(0, 0, 0, KC_A);
    auto       key_b = KeymapKey(0, 1, 0, KC_B);
    auto       key_c = KeymapKey(0, 2, 0, KC_C);
    auto       key_d = KeymapKey(0, 3, 0, KC_D);
    auto       key_e = KeymapKey(0, 4, 0, KC_E);
    auto       key_f = KeymapKey(0, 5, 0, KC_F);
    auto       key_g = KeymapKey(0, 6, 0, KC_G);
    set_keymap({key_a, key_b, key_c, key_d, key_e, key_f, key_g});

    key_a.press();
    key_b.press();
    key_c.press();
    key_d.press();
    key_e.press();
    key_f.press();
    key_g.press();
    EXPECT_ANY_REPORT(driver).Times(AnyNumber());
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_a.release();
    EXPECT_CALL(driver, send_keyboard_nkro_mock(KeyboardNkroReportViews({KC_B, KC_C, KC_D, KC_E, KC_F}, {KC_B, KC_C, KC_D, KC_E, KC_F, KC_G}))).Times(1);
    run_one_scan_loop();
}

TEST_F(NkroBootCompat, ReleasingAllKeysClearsBothViews) {
    TestDriver driver;
    auto       key_a = KeymapKey(0, 0, 0, KC_A);
    auto       key_b = KeymapKey(0, 1, 0, KC_B);
    set_keymap({key_a, key_b});

    key_a.press();
    key_b.press();
    EXPECT_ANY_REPORT(driver).Times(AnyNumber());
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_a.release();
    key_b.release();
    {
        InSequence seq;
        EXPECT_REPORT(driver, (KC_B)).Times(1);
        EXPECT_EMPTY_REPORT(driver).Times(1);
        run_one_scan_loop();
    }
}

TEST_F(NkroBootCompat, ModifierOnlyPressSendsOneReport) {
    TestDriver driver;
    auto       key_lsft = KeymapKey(0, 0, 0, KC_LSFT);
    set_keymap({key_lsft});

    key_lsft.press();
    EXPECT_REPORT(driver, (KC_LSFT)).Times(1);
    run_one_scan_loop();
}

TEST_F(NkroBootCompat, UnchangedStateSendsNothing) {
    TestDriver driver;
    auto       key_a = KeymapKey(0, 0, 0, KC_A);
    set_keymap({key_a});

    key_a.press();
    EXPECT_REPORT(driver, (KC_A)).Times(1);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    run_one_scan_loop();
}

TEST_F(NkroBootCompat, NkroToggleDoesNotChangeReports) {
    TestDriver driver;
    auto       key_togg = KeymapKey(0, 0, 0, NK_TOGG);
    auto       key_a    = KeymapKey(0, 1, 0, KC_A);
    set_keymap({key_togg, key_a});

    EXPECT_NO_REPORT(driver);
    tap_key(key_togg);
    VERIFY_AND_CLEAR(driver);

    key_a.press();
    EXPECT_REPORT(driver, (KC_A)).Times(1);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_a.release();
    EXPECT_EMPTY_REPORT(driver).Times(1);
    run_one_scan_loop();
}
