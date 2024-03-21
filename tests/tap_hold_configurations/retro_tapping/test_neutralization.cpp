/* Copyright 2023 Vladislav Kucheriavykh
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
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class RetroTapNeutralization : public TestFixture {};

TEST_F(RetroTapNeutralization, neutralize_retro_tapped_left_gui_mod_tap) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 7, 0, LGUI_T(KC_P));

    set_keymap({mod_tap_hold_key});

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LGUI));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (DUMMY_MOD_NEUTRALIZER_KEYCODE, KC_LGUI));
    EXPECT_REPORT(driver, (KC_LGUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapNeutralization, do_not_neutralize_retro_tapped_left_shift_mod_tap) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 7, 0, LSFT_T(KC_P));

    set_keymap({mod_tap_hold_key});

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapNeutralization, do_not_neutralize_retro_tapped_right_gui_mod_tap) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 7, 0, RGUI_T(KC_P));

    set_keymap({mod_tap_hold_key});

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_RGUI));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapNeutralization, do_not_neutralize_retro_tapped_left_gui_shift_mod_tap) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 7, 0, MT(MOD_LGUI | MOD_LSFT, KC_P));

    set_keymap({mod_tap_hold_key});

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapNeutralization, do_not_neutralize_roll_of_regular_and_mod_tap_keys) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Idle for tapping term of mod tap hold key. */
    idle_for(TAPPING_TERM - 3);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapNeutralization, do_not_neutralize_tap_regular_key_while_mod_tap_is_held) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press and hold mod-tap key. */
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_REPORT(driver, (KC_A, KC_LEFT_GUI));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Idle for tapping term of mod tap hold key. */
    idle_for(TAPPING_TERM - 3);
    VERIFY_AND_CLEAR(driver);
}
