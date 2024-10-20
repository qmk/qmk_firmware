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
// test auto shift and space cadet interaction
// press shift, press key, release shift, release key
// the right interaction is we only get the shifted key
// the wrong interaction is we get a bracket and a shifted key
TEST_F(AutoShift, auto_shift_with_space_cadet) {
    TestDriver driver;
    InSequence s;
    auto       left_shift = KeymapKey(0, 0, 0, SC_LSPO);
    auto       key_a      = KeymapKey(0, 1, 0, KC_A);

    set_keymap({left_shift, key_a});

    /* Press regular key */
    EXPECT_NO_REPORT(driver);
    left_shift.press();
    key_a.press();
    left_shift.release();
    key_a.release();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
