/* Copyright 2022 Isaac Elenbaas
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    return true;
}

using testing::_;
using testing::AnyNumber;
using testing::AnyOf;
using testing::InSequence;

class RetroShiftDefaultTapHold : public TestFixture {};

TEST_F(RetroShiftDefaultTapHold, tap_mod_tap_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 0, 0, CTL_T(KC_A));

    set_keymap({mod_tap_hold_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, hold_mod_tap_key_under_retro_shift) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 0, 0, CTL_T(KC_A));

    set_keymap({mod_tap_hold_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    idle_for(AUTO_SHIFT_TIMEOUT);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, hold_mod_tap_key_over_retro_shift) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 0, 0, CTL_T(KC_A));

    set_keymap({mod_tap_hold_key});

    /* Press mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_hold_key.press();
    run_one_scan_loop();
    idle_for(RETRO_SHIFT);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, tap_regular_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       regular_key      = KeymapKey(0, 1, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LCTL))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LCTL, KC_A));
    EXPECT_REPORT(driver, (KC_LCTL));
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, tap_mod_tap_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key    = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, 1, 0, ALT_T(KC_A));

    set_keymap({mod_tap_hold_key, mod_tap_regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod-tap-regular key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-regular key. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LCTL))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LCTL, KC_A));
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, tap_regular_key_while_mod_tap_key_is_held_over_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       regular_key      = KeymapKey(0, 1, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LCTL))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LCTL, KC_A));
    EXPECT_REPORT(driver, (KC_LCTL));
    regular_key.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, tap_mod_tap_key_while_mod_tap_key_is_held_over_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key    = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, 1, 0, ALT_T(KC_A));

    set_keymap({mod_tap_hold_key, mod_tap_regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod-tap-regular key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-regular key. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LCTL))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LCTL, KC_A));
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_regular_key.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, hold_regular_key_while_mod_tap_key_is_held_over_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       regular_key      = KeymapKey(0, 1, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    idle_for(AUTO_SHIFT_TIMEOUT);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key. */
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(KC_LCTL, KC_LSFT),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LCTL))))
        .Times(AnyNumber());
    // clang-format on
    EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_A));
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(KC_LCTL, KC_LSFT),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    EXPECT_REPORT(driver, (KC_LCTL));
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, hold_mod_tap_key_while_mod_tap_key_is_held_over_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key    = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, 1, 0, ALT_T(KC_A));

    set_keymap({mod_tap_hold_key, mod_tap_regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod-tap-regular key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_regular_key.press();
    run_one_scan_loop();
    idle_for(AUTO_SHIFT_TIMEOUT);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-regular key. */
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(KC_LCTL, KC_LSFT),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LCTL))))
        .Times(AnyNumber());
    // clang-format on
    EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_A));
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(KC_LCTL, KC_LSFT),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_regular_key.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, roll_tap_regular_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       regular_key      = KeymapKey(0, 1, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key. */
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, roll_tap_mod_tap_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key    = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, 1, 0, ALT_T(KC_A));

    set_keymap({mod_tap_hold_key, mod_tap_regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod-tap-regular key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-regular key. */
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, roll_hold_regular_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       regular_key      = KeymapKey(0, 1, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    idle_for(AUTO_SHIFT_TIMEOUT);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(RetroShiftDefaultTapHold, roll_hold_mod_tap_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key    = KeymapKey(0, 0, 0, CTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, 1, 0, ALT_T(KC_A));

    set_keymap({mod_tap_hold_key, mod_tap_regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod-tap-regular key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-regular key. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_EMPTY_REPORT(driver);
    idle_for(AUTO_SHIFT_TIMEOUT);
    mod_tap_regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}
