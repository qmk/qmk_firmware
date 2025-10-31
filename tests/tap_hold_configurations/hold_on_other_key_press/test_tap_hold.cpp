/* Copyright 2022 Vladislav Kucheriavykh
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

class HoldOnOtherKeyPress : public TestFixture {};

TEST_F(HoldOnOtherKeyPress, short_distinct_taps_of_mod_tap_key_and_regular_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_REPORT(driver, (KC_A));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(HoldOnOtherKeyPress, long_distinct_taps_of_mod_tap_key_and_regular_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Idle for tapping term of mod tap hold key. */
    EXPECT_REPORT(driver, (KC_LSFT));
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_REPORT(driver, (KC_A));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(HoldOnOtherKeyPress, short_distinct_taps_of_layer_tap_key_and_regular_key) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       regular_key        = KeymapKey(0, 2, 0, KC_A);
    auto       layer_key          = KeymapKey(0, 2, 0, KC_B);

    set_keymap({layer_tap_hold_key, regular_key});

    /* Press layer-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release layer-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_REPORT(driver, (KC_A));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(HoldOnOtherKeyPress, long_distinct_taps_of_layer_tap_key_and_regular_key) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_hold_key = KeymapKey(0, 1, 0, LT(1, KC_P));
    auto       regular_key        = KeymapKey(0, 2, 0, KC_A);
    auto       layer_key          = KeymapKey(0, 2, 0, KC_B);

    set_keymap({layer_tap_hold_key, regular_key});

    /* Press layer-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Idle for tapping term of layer tap hold key. */
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* Release layer-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_REPORT(driver, (KC_A));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(HoldOnOtherKeyPress, tap_regular_key_while_mod_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_A, KC_LSFT));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_REPORT(driver, (KC_LSFT));
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

TEST_F(HoldOnOtherKeyPress, tap_a_mod_tap_key_while_another_mod_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       first_mod_tap_hold_key  = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       second_mod_tap_hold_key = KeymapKey(0, 2, 0, RSFT_T(KC_A));

    set_keymap({first_mod_tap_hold_key, second_mod_tap_hold_key});

    /* Press first mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    first_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press second tap-hold key */
    EXPECT_REPORT(driver, (KC_LSFT));
    second_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release second tap-hold key */
    EXPECT_REPORT(driver, (KC_A, KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT));
    second_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release first mod-tap-hold key */
    EXPECT_EMPTY_REPORT(driver);
    first_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(HoldOnOtherKeyPress, tap_regular_key_while_layer_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_hold_key = KeymapKey(0, 1, 0, LT(1, KC_P));
    auto       regular_key        = KeymapKey(0, 2, 0, KC_A);
    auto       layer_key          = KeymapKey(1, 2, 0, KC_B);

    set_keymap({layer_tap_hold_key, regular_key, layer_key});

    /* Press layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(HoldOnOtherKeyPress, nested_tap_of_layer_0_layer_tap_keys) {
    TestDriver driver;
    InSequence s;
    /* The keys are layer-taps on layer 0 but regular keys on layer 1 */
    auto first_layer_tap_key  = KeymapKey(0, 1, 0, LT(1, KC_A));
    auto second_layer_tap_key = KeymapKey(0, 2, 0, LT(1, KC_P));
    auto first_key_on_layer   = KeymapKey(1, 1, 0, KC_B);
    auto second_key_on_layer  = KeymapKey(1, 2, 0, KC_Q);

    set_keymap({first_layer_tap_key, second_layer_tap_key, first_key_on_layer, second_key_on_layer});

    /* Press first layer-tap key */
    EXPECT_NO_REPORT(driver);
    first_layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press second layer-tap key */
    EXPECT_REPORT(driver, (KC_Q));
    second_layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release second layer-tap key */
    EXPECT_EMPTY_REPORT(driver);
    second_layer_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release first layer-tap key */
    EXPECT_NO_REPORT(driver);
    first_layer_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(HoldOnOtherKeyPress, nested_tap_of_layer_tap_keys) {
    TestDriver driver;
    InSequence s;
    /* The keys are layer-taps on all layers */
    auto first_key_layer_0  = KeymapKey(0, 1, 0, LT(1, KC_A));
    auto second_key_layer_0 = KeymapKey(0, 2, 0, LT(1, KC_P));
    auto first_key_layer_1  = KeymapKey(1, 1, 0, LT(2, KC_B));
    auto second_key_layer_1 = KeymapKey(1, 2, 0, LT(2, KC_Q));
    auto first_key_layer_2  = KeymapKey(2, 1, 0, KC_TRNS);
    auto second_key_layer_2 = KeymapKey(2, 2, 0, KC_TRNS);

    set_keymap({first_key_layer_0, second_key_layer_0, first_key_layer_1, second_key_layer_1, first_key_layer_2, second_key_layer_2});

    /* Press first layer-tap key */
    EXPECT_NO_REPORT(driver);
    first_key_layer_0.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press second layer-tap key */
    EXPECT_NO_REPORT(driver);
    second_key_layer_0.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release second layer-tap key */
    EXPECT_REPORT(driver, (KC_Q));
    EXPECT_EMPTY_REPORT(driver);
    second_key_layer_0.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release first layer-tap key */
    EXPECT_NO_REPORT(driver);
    first_key_layer_0.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(HoldOnOtherKeyPress, roll_mod_tap_key_with_regular_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_A, KC_LSFT));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_A));
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(HoldOnOtherKeyPress, roll_layer_tap_key_with_regular_key) {
    TestDriver driver;
    InSequence s;

    auto layer_tap_hold_key = KeymapKey(0, 1, 0, LT(1, KC_P));
    auto regular_key        = KeymapKey(0, 2, 0, KC_A);
    auto layer_key          = KeymapKey(1, 2, 0, KC_B);

    set_keymap({layer_tap_hold_key, regular_key, layer_key});

    /* Press layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
