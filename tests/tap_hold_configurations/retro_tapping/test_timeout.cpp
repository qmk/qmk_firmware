/* Copyright 2024 John Rigoni
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include "keycodes.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class RetroTapTimeout : public TestFixture {};

TEST_F(RetroTapTimeout, retro_tap_timeout_left_shift) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_hold_key});

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.press();
    idle_for(RETRO_TAPPING_TIMEOUT);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapTimeout, retro_tap_timeout_left_mod) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, LGUI_T(KC_P));

    set_keymap({mod_tap_hold_key});

    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    EXPECT_REPORT(driver, (KC_LGUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.press();
    idle_for(RETRO_TAPPING_TIMEOUT);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
