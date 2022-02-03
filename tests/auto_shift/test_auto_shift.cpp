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
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class AutoShift : public TestFixture {};

TEST_F(AutoShift, key_release_before_timeout) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({regular_key});

    /* Press regular key */
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(AutoShift, key_release_after_timeout) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({regular_key});

    /* Press regular key */
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    regular_key.press();
    idle_for(AUTO_SHIFT_TIMEOUT);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT, KC_A)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}