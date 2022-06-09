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

#include "keycode.h"
#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class KeyPress : public TestFixture {};

TEST_F(KeyPress, SendKeyboardIsNotCalledWhenNoKeyIsPressed) {
    TestDriver driver;
    EXPECT_NO_REPORT(driver);
    keyboard_task();
}

TEST_F(KeyPress, CorrectKeyIsReportedWhenPressed) {
    TestDriver driver;
    auto       key = KeymapKey(0, 0, 0, KC_A);

    set_keymap({key});

    key.press();
    EXPECT_REPORT(driver, (key.report_code));
    keyboard_task();

    key.release();
    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

TEST_F(KeyPress, ANonMappedKeyDoesNothing) {
    TestDriver driver;
    auto       key = KeymapKey(0, 0, 0, KC_NO);

    set_keymap({key});

    key.press();
    EXPECT_NO_REPORT(driver);
    keyboard_task();
    keyboard_task();
}

TEST_F(KeyPress, CorrectKeysAreReportedWhenTwoKeysArePressed) {
    TestDriver driver;
    auto       key_b = KeymapKey(0, 0, 0, KC_B);
    auto       key_c = KeymapKey(0, 1, 1, KC_C);

    set_keymap({key_b, key_c});

    key_b.press();
    key_c.press();
    // Note that QMK only processes one key at a time
    // See issue #1476 for more information
    EXPECT_REPORT(driver, (key_b.report_code));
    keyboard_task();

    EXPECT_REPORT(driver, (key_b.report_code, key_c.report_code));
    keyboard_task();

    key_b.release();
    key_c.release();
    // Note that the first key released is the first one in the matrix order
    EXPECT_REPORT(driver, (key_c.report_code));
    keyboard_task();

    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

TEST_F(KeyPress, LeftShiftIsReportedCorrectly) {
    TestDriver driver;
    auto       key_a    = KeymapKey(0, 0, 0, KC_A);
    auto       key_lsft = KeymapKey(0, 3, 0, KC_LEFT_SHIFT);

    set_keymap({key_a, key_lsft});

    key_lsft.press();
    key_a.press();

    // Unfortunately modifiers are also processed in the wrong order
    // See issue #1476 for more information
    EXPECT_REPORT(driver, (key_a.report_code));
    keyboard_task();
    EXPECT_REPORT(driver, (key_a.report_code, key_lsft.report_code));
    keyboard_task();

    key_a.release();
    EXPECT_REPORT(driver, (key_lsft.report_code));
    keyboard_task();

    key_lsft.release();
    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

TEST_F(KeyPress, PressLeftShiftAndControl) {
    TestDriver driver;
    auto       key_lsft  = KeymapKey(0, 3, 0, KC_LEFT_SHIFT);
    auto       key_lctrl = KeymapKey(0, 5, 0, KC_LEFT_CTRL);

    set_keymap({key_lctrl, key_lsft});

    key_lsft.press();
    key_lctrl.press();

    // Unfortunately modifiers are also processed in the wrong order
    // See issue #1476 for more information
    EXPECT_REPORT(driver, (key_lsft.report_code));
    keyboard_task();

    EXPECT_REPORT(driver, (key_lsft.report_code, key_lctrl.report_code));
    keyboard_task();

    key_lsft.release();
    key_lctrl.release();

    EXPECT_REPORT(driver, (key_lctrl.report_code));
    keyboard_task();

    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

TEST_F(KeyPress, LeftAndRightShiftCanBePressedAtTheSameTime) {
    TestDriver driver;
    auto       key_lsft = KeymapKey(0, 3, 0, KC_LEFT_SHIFT);
    auto       key_rsft = KeymapKey(0, 4, 0, KC_RIGHT_SHIFT);

    set_keymap({key_rsft, key_lsft});

    key_lsft.press();
    key_rsft.press();
    // Unfortunately modifiers are also processed in the wrong order
    // See issue #1476 for more information
    EXPECT_REPORT(driver, (key_lsft.report_code));
    keyboard_task();

    EXPECT_REPORT(driver, (key_lsft.report_code, key_rsft.report_code));
    keyboard_task();

    key_lsft.release();
    key_rsft.release();

    EXPECT_REPORT(driver, (key_rsft.report_code));
    keyboard_task();

    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

TEST_F(KeyPress, RightShiftLeftControlAndCharWithTheSameKey) {
    TestDriver driver;
    auto       combo_key = KeymapKey(0, 0, 0, RSFT(LCTL(KC_O)));

    set_keymap({combo_key});

    // BUG: The press is split into two reports
    // BUG: It reports RSFT instead of LSFT
    // See issue #524 for more information
    // The underlying cause is that we use only one bit to represent the right hand
    // modifiers.
    combo_key.press();
    EXPECT_REPORT(driver, (KC_RIGHT_SHIFT, KC_RIGHT_CTRL));
    EXPECT_REPORT(driver, (KC_RIGHT_SHIFT, KC_RIGHT_CTRL, KC_O));
    keyboard_task();

    combo_key.release();
    EXPECT_REPORT(driver, (KC_RIGHT_SHIFT, KC_RIGHT_CTRL));
    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

TEST_F(KeyPress, PressPlusEqualReleaseBeforePress) {
    TestDriver driver;
    InSequence s;
    auto       key_plus = KeymapKey(0, 1, 1, KC_PLUS);
    auto       key_eql  = KeymapKey(0, 0, 1, KC_EQUAL);

    set_keymap({key_plus, key_eql});

    key_plus.press();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_EQUAL));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_plus.release();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_eql.press();
    EXPECT_REPORT(driver, (key_eql.report_code));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_eql.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(KeyPress, PressPlusEqualDontReleaseBeforePress) {
    TestDriver driver;
    InSequence s;
    auto       key_plus = KeymapKey(0, 1, 1, KC_PLUS);
    auto       key_eql  = KeymapKey(0, 0, 1, KC_EQUAL);

    set_keymap({key_plus, key_eql});

    key_plus.press();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_EQUAL));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_eql.press();
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_EQUAL));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_plus.release();
    // BUG: Should really still return KC_EQUAL, but this is fine too
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_eql.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(KeyPress, PressEqualPlusReleaseBeforePress) {
    TestDriver driver;
    InSequence s;
    auto       key_plus = KeymapKey(0, 1, 1, KC_PLUS);
    auto       key_eql  = KeymapKey(0, 0, 1, KC_EQUAL);

    set_keymap({key_plus, key_eql});

    key_eql.press();
    EXPECT_REPORT(driver, (KC_EQUAL));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_eql.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_plus.press();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_EQUAL));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_plus.release();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(KeyPress, PressEqualPlusDontReleaseBeforePress) {
    TestDriver driver;
    InSequence s;
    auto       key_plus = KeymapKey(0, 1, 1, KC_PLUS);
    auto       key_eql  = KeymapKey(0, 0, 1, KC_EQUAL);

    set_keymap({key_plus, key_eql});

    key_eql.press();
    EXPECT_REPORT(driver, (KC_EQUAL));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_plus.press();
    // BUG: The sequence is a bit strange, but it works, the end result is that
    // KC_PLUS is sent
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_EQUAL));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_EQUAL));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_eql.release();
    // I guess it's fine to still report shift here
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    key_plus.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}
