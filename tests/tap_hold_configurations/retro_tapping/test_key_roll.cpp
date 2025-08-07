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

class RetroTapKeyRoll : public TestFixture {};

TEST_F(RetroTapKeyRoll, regular_to_left_gui_mod_over_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_B);

    set_keymap({mod_tap_hold_key, regular_key});

    EXPECT_REPORT(driver, (KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B, KC_LEFT_GUI));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_GUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, regular_to_mod_over_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_B);

    set_keymap({mod_tap_hold_key, regular_key});

    EXPECT_REPORT(driver, (KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B, KC_LEFT_SHIFT));
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, regular_to_mod_under_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_B);

    set_keymap({mod_tap_hold_key, regular_key});

    EXPECT_REPORT(driver, (KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, mod_under_tap_term_to_regular) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_B);

    set_keymap({mod_tap_hold_key, regular_key});

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_B, KC_P));
    EXPECT_REPORT(driver, (KC_B));
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, mod_over_tap_term_to_regular) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_B);

    set_keymap({mod_tap_hold_key, regular_key});

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B));
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, mod_under_tap_term_to_mod_under_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_gui   = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_hold_lshft = KeymapKey(0, 2, 0, SFT_T(KC_A));

    set_keymap({mod_tap_hold_gui, mod_tap_hold_lshft});

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_lshft.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_gui.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_lshft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_gui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, mod_over_tap_term_to_mod_under_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_gui   = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_hold_lshft = KeymapKey(0, 2, 0, SFT_T(KC_A));

    set_keymap({mod_tap_hold_gui, mod_tap_hold_lshft});

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_hold_lshft.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_gui.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_lshft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_P));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_gui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, mod_under_tap_term_to_mod_over_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_gui   = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_hold_lshft = KeymapKey(0, 2, 0, SFT_T(KC_A));

    set_keymap({mod_tap_hold_gui, mod_tap_hold_lshft});

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_lshft.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_GUI));
    mod_tap_hold_gui.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    mod_tap_hold_lshft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_GUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_P, KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_gui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, mod_under_tap_term_to_mod_over_tap_term_offset) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_gui   = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_hold_lshft = KeymapKey(0, 2, 0, SFT_T(KC_A));

    set_keymap({mod_tap_hold_gui, mod_tap_hold_lshft});

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_lshft.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mod_tap_hold_gui.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_lshft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    EXPECT_REPORT(driver, (KC_LEFT_GUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    idle_for(TAPPING_TERM);
    mod_tap_hold_gui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, mod_over_tap_term_to_mod_over_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_gui   = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_hold_lshft = KeymapKey(0, 2, 0, SFT_T(KC_A));

    set_keymap({mod_tap_hold_gui, mod_tap_hold_lshft});

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_hold_lshft.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_GUI));
    mod_tap_hold_gui.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    mod_tap_hold_lshft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_GUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_P, KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_gui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroTapKeyRoll, mod_to_mod_to_mod) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_lalt  = KeymapKey(0, 1, 0, LALT_T(KC_R));
    auto       mod_tap_hold_lshft = KeymapKey(0, 2, 0, SFT_T(KC_A));
    auto       mod_tap_hold_lctrl = KeymapKey(0, 3, 0, LCTL_T(KC_C));

    set_keymap({mod_tap_hold_lalt, mod_tap_hold_lshft, mod_tap_hold_lctrl});

    EXPECT_REPORT(driver, (KC_LEFT_ALT));
    mod_tap_hold_lalt.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_ALT));
    mod_tap_hold_lshft.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_hold_lalt.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_CTRL, KC_LEFT_SHIFT));
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_lctrl.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_CTRL));
    mod_tap_hold_lshft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_C, KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_lctrl.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
