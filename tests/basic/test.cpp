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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "quantum.h"
#include "test_driver.h"
#include "test_matrix.h"
#include "keyboard_report_util.h"
#include "test_fixture.h"

using testing::_;
using testing::Return;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = {
	    {KC_A, KC_B},
	    {KC_C, KC_D}
	},
};

class KeyPress : public TestFixture {};

TEST_F(KeyPress, SendKeyboardIsNotCalledWhenNoKeyIsPressed) {
    TestDriver driver;
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    keyboard_task();
}

TEST_F(KeyPress, CorrectKeyIsReportedWhenPressed) {
    TestDriver driver;
    press_key(0, 0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
    keyboard_task();
}

TEST_F(KeyPress, CorrectKeysAreReportedWhenTwoKeysArePressed) {
    TestDriver driver;
    press_key(1, 0);
    press_key(0, 1);
    //Note that QMK only processes one key at a time
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_B)));
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_B, KC_C)));
    keyboard_task();
}
