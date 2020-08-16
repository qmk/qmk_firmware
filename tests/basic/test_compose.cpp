/* Copyright 2020 Google LLC
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

using testing::_;
using testing::InSequence;
using testing::InvokeWithoutArgs;

class Compose : public TestFixture {};

TEST_F(Compose, PrintsStringWhenFinished) {
    TestDriver driver;
    InSequence s;
    press_key(9, 0); // COMPOSE
    // compose_start: 's'
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_S)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    run_one_scan_loop();
    
    press_key(0, 0); // KC_A
    // Nothing happens since compose mode eats this keypress.
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    run_one_scan_loop();
    
    press_key(1, 0); // KC_B
    
    // end_compose: 'v' for valid sequence
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_V)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    
    // compose macro: 'ccc'
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    
    run_one_scan_loop();
}

TEST_F(Compose, PrintsStringWhenFinishedWithDelay) {
    TestDriver driver;
    InSequence s;
    press_key(9, 0); // COMPOSE
    // compose_start: 's'
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_S)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    run_one_scan_loop();
    
    press_key(0, 0); // KC_A
    // Nothing happens since compose mode eats this keypress.
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    idle_for(20);
    
    press_key(1, 0); // KC_B
    
    // end_compose: 'v' for valid sequence
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_V)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    
    // compose macro: 'ccc'
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    
    run_one_scan_loop();
}

TEST_F(Compose, PrintsLastCharWhenSequenceFails) {
    TestDriver driver;
    InSequence s;
    press_key(9, 0); // COMPOSE
    // compose_start: 's'
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_S)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    run_one_scan_loop();
    
    press_key(0, 0); // KC_A
    // Nothing happens since compose mode eats this keypress.
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    run_one_scan_loop();
    
    press_key(0, 3); // KC_C: not a compose sequence!
    // end_compose: 'e' for invalid sequence
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    
    // press 'c' since the compose sequence failed.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
    
    run_one_scan_loop();
}
