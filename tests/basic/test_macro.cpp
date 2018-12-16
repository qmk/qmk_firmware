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
#include "time.h"

using testing::InSequence;
using testing::InvokeWithoutArgs;

class Macro : public TestFixture {};

#define AT_TIME(t) WillOnce(InvokeWithoutArgs([current_time]() {EXPECT_EQ(timer_elapsed32(current_time), t);}))

TEST_F(Macro, PlayASimpleMacro) {
    TestDriver driver;
    InSequence s;
    press_key(8, 0);
    uint32_t current_time = timer_read32();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT, KC_H)))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)))
        .AT_TIME(0);
    // The macro system could actually skip these empty keyboard reports
    // it should be enough to just send a report with the next key down
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_L)))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_L)))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_O)))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_SPACE)))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)))
        .AT_TIME(100);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT, KC_W)))
        .AT_TIME(100);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)))
        .AT_TIME(100);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(100);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_O)))
    // BUG: The timer should not really have advanced 10 ms here
    // See issue #1477
        .AT_TIME(110);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
    // BUG: The timer should not advance on both keydown and key-up
    // See issue #1477
        .AT_TIME(120);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_R)))
        .AT_TIME(130);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(140);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_L)))
        .AT_TIME(150);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(160);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_D)))
        .AT_TIME(170);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(180);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)))
        .AT_TIME(190);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT, KC_1)))
        .AT_TIME(200);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT)))
        .AT_TIME(210);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()))
        .AT_TIME(220);
    run_one_scan_loop();
}