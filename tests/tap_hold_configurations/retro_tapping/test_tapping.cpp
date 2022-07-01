/* Copyright 2021 Stefan Kerkmann
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
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class Tapping : public TestFixture {};

TEST_F(Tapping, HoldA_SHFT_T_KeyReportsShift) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 7, 0, SFT_T(KC_P));

    set_keymap({mod_tap_hold_key});

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(Tapping, ANewTapWithinTappingTermIsBuggy) {
    TestDriver driver;
    InSequence s;
    auto       key_shift_hold_p_tap = KeymapKey(0, 7, 0, SFT_T(KC_P));

    set_keymap({key_shift_hold_p_tap});

    /* Press mod_tap_hold key */
    EXPECT_NO_REPORT(driver);
    key_shift_hold_p_tap.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod_tap_hold key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    key_shift_hold_p_tap.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod_tap_hold key again */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    key_shift_hold_p_tap.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod_tap_hold key again */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    key_shift_hold_p_tap.release();
    idle_for(TAPPING_TERM + 1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod_tap_hold key again */
    EXPECT_NO_REPORT(driver);
    key_shift_hold_p_tap.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod_tap_hold key again */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    key_shift_hold_p_tap.release();
    idle_for(TAPPING_TERM + 1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod_tap_hold key again */
    EXPECT_NO_REPORT(driver);
    key_shift_hold_p_tap.press();
    idle_for(TAPPING_TERM);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod_tap_hold key again */
    /* TODO: Why is KC_LSFT send? */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    key_shift_hold_p_tap.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}
