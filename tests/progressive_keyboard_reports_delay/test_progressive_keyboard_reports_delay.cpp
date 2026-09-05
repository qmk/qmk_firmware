/* Copyright 2026 QMK
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

#include "action_util.h"
#include "keyboard_report_util.hpp"
#include "test_common.hpp"
#include "timer.h"

using testing::_;
using testing::AnyNumber;
using testing::InSequence;
using testing::InvokeWithoutArgs;

// Delay counterpart of tests/progressive_keyboard_reports. The test platform's
// wait_ms() advances the emulated timer deterministically, so the delay between
// sub-reports is observable as an exact timestamp difference at the driver mock.

class ProgressiveKeyboardReportsDelay : public TestFixture {};

// A split press must still emit modifier-then-key, with PROGRESSIVE_REPORT_DELAY
// milliseconds elapsing between the sub-report and the final report.
TEST_F(ProgressiveKeyboardReportsDelay, DelayIsInsertedBetweenSubReports) {
    TestDriver driver;
    InSequence s;

    uint32_t first_time  = 0;
    uint32_t second_time = 0;
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT)).WillOnce(InvokeWithoutArgs([&]() { first_time = timer_read32(); }));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_A)).WillOnce(InvokeWithoutArgs([&]() { second_time = timer_read32(); }));

    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::add_key(KC_A);
    send_keyboard_report();

    EXPECT_EQ(second_time - first_time, PROGRESSIVE_REPORT_DELAY);
    VERIFY_AND_CLEAR(driver);
}

// A split release must likewise separate the key-release sub-report from the
// modifier release by PROGRESSIVE_REPORT_DELAY milliseconds.
TEST_F(ProgressiveKeyboardReportsDelay, DelayIsInsertedBetweenReleaseSubReports) {
    TestDriver driver;

    /* Establish the held state: Shift + A. */
    EXPECT_ANY_REPORT(driver).Times(AnyNumber());
    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::add_key(KC_A);
    send_keyboard_report();
    VERIFY_AND_CLEAR(driver);

    InSequence s;

    uint32_t first_time  = 0;
    uint32_t second_time = 0;
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT)).WillOnce(InvokeWithoutArgs([&]() { first_time = timer_read32(); }));
    EXPECT_EMPTY_REPORT(driver).WillOnce(InvokeWithoutArgs([&]() { second_time = timer_read32(); }));

    ::del_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::del_key(KC_A);
    send_keyboard_report();

    EXPECT_EQ(second_time - first_time, PROGRESSIVE_REPORT_DELAY);
    /* The mods sub-report is the last report of this change; nothing follows it, so no trailing
       delay may stall the caller after it is sent. */
    EXPECT_EQ(timer_read32(), second_time);
    VERIFY_AND_CLEAR(driver);
}

// A mods-only change goes out as a single report with no sub-report before or
// after it, so the whole send must complete without any delay stalling the caller.
TEST_F(ProgressiveKeyboardReportsDelay, ModsOnlyChangeInsertsNoDelay) {
    TestDriver driver;

    uint32_t start = timer_read32();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT)).Times(1);

    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    send_keyboard_report();

    EXPECT_EQ(timer_read32() - start, 0u);
    VERIFY_AND_CLEAR(driver);
}

// An unsplit change — a plain key press with no modifier change — must not
// insert any delay before its single report.
TEST_F(ProgressiveKeyboardReportsDelay, UnsplitReportInsertsNoDelay) {
    TestDriver driver;

    uint32_t start = timer_read32();
    EXPECT_REPORT(driver, (KC_A)).Times(1);

    ::add_key(KC_A);
    send_keyboard_report();

    EXPECT_EQ(timer_read32() - start, 0u);
    VERIFY_AND_CLEAR(driver);
}
