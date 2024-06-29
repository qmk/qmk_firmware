/* Copyright 2024 Mercury Wilberforce
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
class PermissiveHold : public TestFixture {};

TEST_F(PermissiveHold, tap_regular_key_while_mod_tap_key_and_another_mod_tap_key_are_held) {
    TestDriver driver;
    InSequence s;
    auto       first_mod_tap_hold_key  = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       second_mod_tap_hold_key = KeymapKey(0, 2, 0, CTL_T(KC_Q));
    auto       regular_key             = KeymapKey(0, 3, 0, KC_A);

    set_keymap({first_mod_tap_hold_key, second_mod_tap_hold_key, regular_key});

    /* Press first mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    first_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press second mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL, regular_key.report_code));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release second mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    second_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release first mod-tap-hold key */
    EXPECT_EMPTY_REPORT(driver);
    first_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(PermissiveHold, tap_a_mod_tap_key_while_two_other_mod_tap_keys_are_held) {
    TestDriver driver;
    InSequence s;
    auto       first_mod_tap_hold_key  = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       second_mod_tap_hold_key = KeymapKey(0, 2, 0, CTL_T(KC_A));
    auto       third_mod_tap_hold_key  = KeymapKey(0, 3, 0, RSFT_T(KC_Q));

    set_keymap({first_mod_tap_hold_key, second_mod_tap_hold_key, third_mod_tap_hold_key});

    /* Press first mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    first_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press second mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press third mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    third_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release third mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL, third_mod_tap_hold_key.report_code));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    third_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release second mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    second_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release first mod-tap-hold key */
    EXPECT_EMPTY_REPORT(driver);
    first_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(PermissiveHold, tap_regular_key_while_layer_and_another_layer_tap_key_are_held) {
    TestDriver driver;
    InSequence s;
    auto       first_layer_tap_hold_key  = KeymapKey(0, 1, 0, LT(1, KC_P));
    auto       regular_1_key             = KeymapKey(0, 2, 0, KC_A);
    auto       regular_2_key             = KeymapKey(0, 3, 0, KC_G);
    auto       second_layer_tap_hold_key = KeymapKey(1, 3, 0, LT(2, KC_X));
    auto       first_layer_1_key         = KeymapKey(1, 2, 0, KC_B);
    auto       first_layer_2_key         = KeymapKey(1, 1, 0, KC_Z);
    auto       second_layer_1_key        = KeymapKey(2, 2, 0, KC_Y);
    auto       second_layer_2_key        = KeymapKey(2, 1, 0, KC_V);

    set_keymap({first_layer_tap_hold_key, second_layer_tap_hold_key, regular_1_key, first_layer_1_key, second_layer_1_key, regular_2_key, first_layer_2_key, second_layer_2_key});

    /* Press first layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    first_layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press second layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_NO_REPORT(driver);
    regular_1_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_REPORT(driver, (second_layer_1_key.report_code));
    EXPECT_EMPTY_REPORT(driver);
    regular_1_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release second layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release first layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    first_layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
