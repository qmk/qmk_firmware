/* Copyright 2021 Stefan Kerkmann
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

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class AutoShift : public TestFixture {};

TEST_F(AutoShift, key_release_before_timeout) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({regular_key});

    /* Press regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(AutoShift, key_release_after_timeout) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({regular_key});

    /* Press regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    idle_for(AUTO_SHIFT_TIMEOUT);
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Roll a regular key KC_F into a tap-hold key. KC_F's release is processed
// right away, although the tap-hold key is still unsettled, so that Auto Shift
// evaluates the key when it is actually released.
//
// This test prevents KC_F from falsely auto-shifting due to queuing its release
// after the mod-tap settles, by which point the Auto Shift timeout has elapsed.
TEST_F(AutoShift, key_release_while_mt_is_unsettled_is_not_shifted) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 1, 0, KC_F);
    auto       mod_tap_key = KeymapKey(0, 2, 0, RSFT_T(KC_J));
    set_keymap({regular_key, mod_tap_key});

    EXPECT_NO_REPORT(driver);
    regular_key.press();
    idle_for(60);
    mod_tap_key.press();
    idle_for(60);
    VERIFY_AND_CLEAR(driver);

    // Release regular_key before AUTO_SHIFT_TIMEOUT, while the mod-tap key is
    // unsettled. Release is processed right away, the key is tapped unshifted.
    EXPECT_REPORT(driver, (KC_F));
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    idle_for(AUTO_SHIFT_TIMEOUT - 60);
    VERIFY_AND_CLEAR(driver);

    // Release the mod-tap key (which is tapped).
    EXPECT_REPORT(driver, (KC_J));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), 0);
    VERIFY_AND_CLEAR(driver);
}

// Same as above, but holding the regular key past the Auto Shift timeout.
TEST_F(AutoShift, held_past_timeout_while_mt_is_unsettled_is_shifted) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 1, 0, KC_F);
    auto       mod_tap_key = KeymapKey(0, 2, 0, RSFT_T(KC_J));
    set_keymap({regular_key, mod_tap_key});

    EXPECT_NO_REPORT(driver);
    regular_key.press();
    idle_for(60);
    mod_tap_key.press();
    idle_for(AUTO_SHIFT_TIMEOUT - 60 - 1);
    VERIFY_AND_CLEAR(driver);

    // regular_key is held past timeout, so it is shifted.
    EXPECT_REPORT(driver, (KC_LSFT, KC_F));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    idle_for(10);
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_J));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), 0);
    VERIFY_AND_CLEAR(driver);
}
