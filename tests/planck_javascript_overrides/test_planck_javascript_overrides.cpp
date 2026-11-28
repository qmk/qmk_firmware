// Copyright 2026 Nick Getka (@NickGetka)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test_common.hpp"

using testing::_;
using testing::AnyNumber;

class PlanckJavascriptOverrides : public TestFixture {};

TEST_F(PlanckJavascriptOverrides, LowerBracketUsesOpeningAndClosingSymbols) {
    TestDriver driver;
    KeymapKey shift(0, 0, 0, KC_LSFT);
    KeymapKey bracket(1, 1, 0, KC_LBRC);
    set_keymap({shift, bracket});
    layer_on(1);

    EXPECT_REPORT(driver, (KC_LBRC));
    bracket.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    bracket.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT));
    shift.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_RBRC));
    bracket.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(AnyNumber());
    bracket.release();
    shift.release();
    run_one_scan_loop();
    layer_off(1);
}

TEST_F(PlanckJavascriptOverrides, CommaOverrideIsRestrictedToLowerAndRaise) {
    TestDriver driver;
    KeymapKey shift(0, 0, 0, KC_RSFT);
    KeymapKey base_comma(0, 1, 0, KC_COMM);
    KeymapKey lower_comma(1, 1, 0, KC_COMM);
    KeymapKey raise_comma(2, 1, 0, KC_COMM);
    set_keymap({shift, base_comma, lower_comma, raise_comma});

    EXPECT_REPORT(driver, (KC_RSFT));
    shift.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_RSFT, KC_COMM));
    base_comma.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_RSFT));
    base_comma.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    for (auto key : {lower_comma, raise_comma}) {
        layer_on(key.layer);
        EXPECT_CALL(driver, send_keyboard_mock(_)).Times(AnyNumber());
        EXPECT_REPORT(driver, (KC_DOT));
        key.press();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        EXPECT_CALL(driver, send_keyboard_mock(_)).Times(AnyNumber());
        key.release();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);
        layer_off(key.layer);
    }

    EXPECT_EMPTY_REPORT(driver);
    shift.release();
    run_one_scan_loop();
}
