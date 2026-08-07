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

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class Tapping : public TestFixture {};

TEST_F(Tapping, TapA_SHFT_T_KeyReportsKey) {
    TestDriver driver;
    InSequence s;
    auto       key_shift_hold_p_tap = KeymapKey(0, 7, 0, SFT_T(KC_P));

    set_keymap({key_shift_hold_p_tap});

    key_shift_hold_p_tap.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();

    key_shift_hold_p_tap.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(Tapping, HoldA_SHFT_T_KeyReportsShift) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 7, 0, SFT_T(KC_P));

    set_keymap({mod_tap_hold_key});

    mod_tap_hold_key.press();
    EXPECT_REPORT(driver, (KC_LSFT));

    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);

    mod_tap_hold_key.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(Tapping, ANewTapWithinTappingTermIsBuggy) {
    // See issue #1478 for more information
    TestDriver driver;
    InSequence s;
    auto       key_shift_hold_p_tap = KeymapKey(0, 7, 0, SFT_T(KC_P));

    set_keymap({key_shift_hold_p_tap});

    // Tapping keys does nothing on press
    key_shift_hold_p_tap.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();

    key_shift_hold_p_tap.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    key_shift_hold_p_tap.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();

    key_shift_hold_p_tap.release();
    EXPECT_EMPTY_REPORT(driver);
    idle_for(TAPPING_TERM + 1);

    key_shift_hold_p_tap.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();
    key_shift_hold_p_tap.release();

    EXPECT_EMPTY_REPORT(driver);
    idle_for(TAPPING_TERM + 1);

    key_shift_hold_p_tap.press();
    // Shouldn't be called here really
    EXPECT_REPORT(driver, (KC_LSFT));
    idle_for(TAPPING_TERM);

    EXPECT_EMPTY_REPORT(driver);
    key_shift_hold_p_tap.release();
    run_one_scan_loop();
}
