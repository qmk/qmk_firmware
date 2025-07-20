
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

class RetroTapping : public TestFixture {};

TEST_F(RetroTapping, tap_and_hold_mod_tap_hold_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_hold_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    /* TODO: Why is LSHIFT send at all? */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
