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
using testing::SaveArg;

// NKRO counterpart of tests/progressive_keyboard_reports: NKRO_DEFAULT_ON routes
// send_keyboard_report() through send_nkro_report(), exercising the bitmap
// intersection logic (last_report.bits[i] &= nkro_report->bits[i]) instead of the
// positional 6KRO key slots. PROGRESSIVE_REPORT_DELAY is also defined here so the
// delay insertion is covered on the NKRO path. See that suite for why the core
// calls are `::`-qualified.

class ProgressiveKeyboardReportsNkro : public TestFixture {};

// On press, a single logical change that adds both a modifier and a key must be
// split so the modifier reaches the host first, guaranteeing the key is shifted.
TEST_F(ProgressiveKeyboardReportsNkro, ModifierIsReportedBeforeKeyOnPress) {
    TestDriver driver;
    InSequence s;

    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT, KC_A));

    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::add_key(KC_A);
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}

// On release, the same change in reverse must clear the key while the modifier
// is still held, then clear the modifier, so the key never registers unshifted.
TEST_F(ProgressiveKeyboardReportsNkro, KeyIsReleasedBeforeModifierOnRelease) {
    TestDriver driver;

    /* Establish the held state: Shift + A. */
    EXPECT_ANY_NKRO_REPORT(driver).Times(AnyNumber());
    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::add_key(KC_A);
    send_keyboard_report();
    VERIFY_AND_CLEAR(driver);

    InSequence s;

    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_NKRO_REPORT(driver);

    ::del_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::del_key(KC_A);
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}

// With no modifier change, a plain key press still collapses to a single report.
TEST_F(ProgressiveKeyboardReportsNkro, PlainKeyPressSendsSingleReport) {
    TestDriver driver;

    EXPECT_NKRO_REPORT(driver, (KC_A)).Times(1);

    ::add_key(KC_A);
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}

// A change that only alters the modifier byte collapses to a single report: the
// mods sub-report already is the final state, so nothing further is sent.
TEST_F(ProgressiveKeyboardReportsNkro, ModsOnlyChangeSendsSingleReport) {
    TestDriver driver;

    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT)).Times(1);

    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}

// When a key swaps for another in the same scan as a mods change, the old key must
// be released before the new mods are applied: the host must never see the stale
// key together with the new modifier byte.
TEST_F(ProgressiveKeyboardReportsNkro, SwappedKeyIsReleasedBeforeModsApply) {
    TestDriver driver;

    /* Establish the held state: A. */
    EXPECT_ANY_NKRO_REPORT(driver).Times(AnyNumber());
    ::add_key(KC_A);
    send_keyboard_report();
    VERIFY_AND_CLEAR(driver);

    InSequence s;

    EXPECT_EMPTY_NKRO_REPORT(driver);
    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT, KC_B));

    ::del_key(KC_A);
    ::add_key(KC_B);
    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}

// A key that swaps for another within a single scan, with the modifiers unchanged,
// must not be split into a release sub-report — matching 6KRO's behaviour.
TEST_F(ProgressiveKeyboardReportsNkro, KeySwapSendsSingleReport) {
    TestDriver driver;

    /* Establish the held state: A. */
    EXPECT_ANY_NKRO_REPORT(driver).Times(AnyNumber());
    ::add_key(KC_A);
    send_keyboard_report();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NKRO_REPORT(driver, (KC_B)).Times(1);

    ::del_key(KC_A);
    ::add_key(KC_B);
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}

// Sub-reports are sent from a copy of the internal comparison cache; the host layer
// must still stamp every transmitted report with the NKRO report ID. The NkroReport
// matcher deliberately ignores report_id, so this is asserted explicitly here.
TEST_F(ProgressiveKeyboardReportsNkro, SubReportsCarryNkroReportId) {
    TestDriver driver;
    InSequence s;

    report_nkro_t sub_report{};
    report_nkro_t final_report{};
    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT)).WillOnce(SaveArg<0>(&sub_report));
    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT, KC_A)).WillOnce(SaveArg<0>(&final_report));

    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::add_key(KC_A);
    send_keyboard_report();

    EXPECT_EQ(sub_report.report_id, REPORT_ID_NKRO);
    EXPECT_EQ(final_report.report_id, REPORT_ID_NKRO);
    VERIFY_AND_CLEAR(driver);
}

// A split press must still emit modifier-then-key, with PROGRESSIVE_REPORT_DELAY
// milliseconds elapsing between the sub-report and the final report.
TEST_F(ProgressiveKeyboardReportsNkro, DelayIsInsertedBetweenSubReports) {
    TestDriver driver;
    InSequence s;

    uint32_t first_time  = 0;
    uint32_t second_time = 0;
    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT)).WillOnce(InvokeWithoutArgs([&]() { first_time = timer_read32(); }));
    EXPECT_NKRO_REPORT(driver, (KC_LEFT_SHIFT, KC_A)).WillOnce(InvokeWithoutArgs([&]() { second_time = timer_read32(); }));

    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::add_key(KC_A);
    send_keyboard_report();

    EXPECT_EQ(second_time - first_time, PROGRESSIVE_REPORT_DELAY);
    VERIFY_AND_CLEAR(driver);
}
