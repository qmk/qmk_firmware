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

using testing::InSequence;

// KEYBOARD_SHARED_EP counterpart of tests/progressive_keyboard_reports: with a
// shared endpoint, report_keyboard_t carries a report_id which host_keyboard_send()
// stamps into the struct it is handed. These tests pin the 6KRO progressive path
// against that interaction — the internal comparison cache must never absorb the
// stamp, or a mods-only change double-sends on the first report after boot. Both
// tests must hold in --gtest_filter isolation, where no earlier case has stamped
// the report globals.

class ProgressiveKeyboardReportsSharedEp : public TestFixture {};

// A change that only alters the modifier byte collapses to a single report, even
// as the very first report emitted after boot.
TEST_F(ProgressiveKeyboardReportsSharedEp, ModsOnlyChangeSendsSingleReport) {
    TestDriver driver;

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT)).Times(1);

    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}

// On press, a single logical change that adds both a modifier and a key must be
// split so the modifier reaches the host first.
TEST_F(ProgressiveKeyboardReportsSharedEp, ModifierIsReportedBeforeKeyOnPress) {
    TestDriver driver;
    InSequence s;

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_A));

    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::add_key(KC_A);
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}
