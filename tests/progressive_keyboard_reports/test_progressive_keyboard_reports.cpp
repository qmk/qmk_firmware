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

using testing::_;
using testing::AnyNumber;
using testing::InSequence;

// These tests drive the QMK core report builders directly (add_mods/add_key/... then a single
// send_keyboard_report()) so that a modifier and a key change land in one report transition,
// which is what exercises the progressive reporting. The calls are qualified with `::` because the
// test body is a TestFixture member, and TestFixture::add_key(KeymapKey) would otherwise shadow
// the global core function ::add_key(uint8_t). The mod helpers have no such collision, but are
// qualified too for symmetry and to make clear these are core functions, not fixture helpers.

class ProgressiveKeyboardReports : public TestFixture {};

// On press, a single logical change that adds both a modifier and a key must be
// split so the modifier reaches the host first, guaranteeing the key is shifted.
TEST_F(ProgressiveKeyboardReports, ModifierIsReportedBeforeKeyOnPress) {
    TestDriver driver;
    InSequence s;

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_A));

    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::add_key(KC_A);
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}

// On release, the same change in reverse must clear the key while the modifier
// is still held, then clear the modifier, so the key never registers unshifted.
TEST_F(ProgressiveKeyboardReports, KeyIsReleasedBeforeModifierOnRelease) {
    TestDriver driver;

    /* Establish the held state: Shift + A. */
    EXPECT_ANY_REPORT(driver).Times(AnyNumber());
    ::add_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::add_key(KC_A);
    send_keyboard_report();
    VERIFY_AND_CLEAR(driver);

    InSequence s;

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);

    ::del_mods(MOD_BIT(KC_LEFT_SHIFT));
    ::del_key(KC_A);
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}

// With no modifier change, a plain key press still collapses to a single report.
TEST_F(ProgressiveKeyboardReports, PlainKeyPressSendsSingleReport) {
    TestDriver driver;

    EXPECT_REPORT(driver, (KC_A)).Times(1);

    ::add_key(KC_A);
    send_keyboard_report();

    VERIFY_AND_CLEAR(driver);
}
