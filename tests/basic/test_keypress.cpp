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

using testing::_;
using testing::Return;

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
    release_key(0, 0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    keyboard_task();
}

TEST_F(KeyPress, CorrectKeysAreReportedWhenTwoKeysArePressed) {
    TestDriver driver;
    press_key(1, 0);
    press_key(0, 3);
    // Note that QMK only processes one key at a time
    // See issue #1476 for more information
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_B)));
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_B, KC_C)));
    keyboard_task();
    release_key(1, 0);
    release_key(0, 3);
    // Note that the first key released is the first one in the matrix order
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    keyboard_task();
}

TEST_F(KeyPress, ANonMappedKeyDoesNothing) {
    TestDriver driver;
    press_key(2, 0);
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    keyboard_task();
    keyboard_task();
}

TEST_F(KeyPress, LeftShiftIsReportedCorrectly) {
    TestDriver driver;
    press_key(3, 0);
    press_key(0, 0);
    // Unfortunately modifiers are also processed in the wrong order
    // See issue #1476 for more information
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A, KC_LSFT)));
    keyboard_task();
    release_key(0, 0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)));
    keyboard_task();
    release_key(3, 0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    keyboard_task();
}

TEST_F(KeyPress, PressLeftShiftAndControl) {
    TestDriver driver;
    press_key(3, 0);
    press_key(5, 0);
    // Unfortunately modifiers are also processed in the wrong order
    // See issue #1476 for more information
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)));
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT, KC_LCTRL)));
    keyboard_task();
}

TEST_F(KeyPress, LeftAndRightShiftCanBePressedAtTheSameTime) {
    TestDriver driver;
    press_key(3, 0);
    press_key(4, 0);
    // Unfortunately modifiers are also processed in the wrong order
    // See issue #1476 for more information
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)));
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT, KC_RSFT)));
    keyboard_task();
}

TEST_F(KeyPress, RightShiftLeftControlAndCharWithTheSameKey) {
    TestDriver driver;
    press_key(6, 0);
    // BUG: The press is split into two reports
    // BUG: It reports RSFT instead of LSFT
    // See issue #524 for more information
    // The underlying cause is that we use only one bit to represent the right hand
    // modifiers.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_RSFT, KC_RCTRL)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_RSFT, KC_RCTRL, KC_O)));
    keyboard_task();
    release_key(6, 0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_RSFT, KC_RCTRL)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    keyboard_task();
}