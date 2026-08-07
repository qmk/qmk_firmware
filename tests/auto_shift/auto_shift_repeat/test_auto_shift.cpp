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

using testing::_;
using testing::AnyNumber;
using testing::InSequence;

class AutoShiftRepeat : public TestFixture {};

TEST_F(AutoShiftRepeat, tap_regular_key_cancelling_another_key_hold) {
    TestDriver driver;
    InSequence s;
    auto       repeat_key  = KeymapKey(0, 1, 0, KC_P);
    auto       regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({repeat_key, regular_key});

    /* Press repeat key. */
    EXPECT_NO_REPORT(driver);
    repeat_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(testing::AnyNumber());
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(testing::AnyNumber());
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(testing::AnyNumber());
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(testing::AnyNumber());
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release repeat key. */
    EXPECT_NO_REPORT(driver);
    repeat_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(AutoShiftRepeat, tap_regular_key_while_another_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       repeat_key  = KeymapKey(0, 1, 0, KC_P);
    auto       regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({repeat_key, regular_key});

    /* Press repeat key. */
    EXPECT_NO_REPORT(driver);
    repeat_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Idle for auto-repeat to kick in. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_P));
    idle_for(AUTO_SHIFT_TIMEOUT);
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key. */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key. */
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release repeat key. */
    EXPECT_EMPTY_REPORT(driver);
    repeat_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}
