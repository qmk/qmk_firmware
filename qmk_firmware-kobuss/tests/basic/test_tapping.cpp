/* Copyright 2017 Fred Sundvik
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

#include "test_common.hpp"
#include "action_tapping.h"

using testing::_;
using testing::InSequence;

class Tapping : public TestFixture {};

TEST_F(Tapping, TapA_SHFT_T_KeyReportsKey) {
    TestDriver driver;
    InSequence s;

    press_key(7, 0);
    // Tapping keys does nothing on press
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    run_one_scan_loop();
    release_key(7, 0);
    // First we get the key press
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    // Then the release
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    run_one_scan_loop();
}

TEST_F(Tapping, HoldA_SHFT_T_KeyReportsShift) {
    TestDriver driver;
    InSequence s;

    press_key(7, 0);
    // Tapping keys does nothing on press
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    idle_for(TAPPING_TERM);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)));
    run_one_scan_loop();
}

TEST_F(Tapping, ANewTapWithinTappingTermIsBuggy) {
    // See issue #1478 for more information
    TestDriver driver;
    InSequence s;

    press_key(7, 0);
    // Tapping keys does nothing on press
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    run_one_scan_loop();
    release_key(7, 0);
    // First we get the key press
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    // Then the release
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    run_one_scan_loop();

    // This sends KC_P, even if it should do nothing
    press_key(7, 0);
    // This test should not succed if everything works correctly
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    run_one_scan_loop();
    release_key(7, 0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    idle_for(TAPPING_TERM + 1);

    // On the other hand, nothing is sent if we are outside the tapping term
    press_key(7, 0);
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    run_one_scan_loop();
    release_key(7, 0);

    // First we get the key press
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    // Then the release
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    idle_for(TAPPING_TERM + 1);

    // Now we are geting into strange territory, as the hold registers too early here
    // But the stranges part is:
    // If TAPPING_TERM + 1 above is changed to TAPPING_TERM or TAPPING_TERM + 2 it doesn't
    press_key(7, 0);
    // Shouldn't be called here really
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(1);
    idle_for(TAPPING_TERM);
}
