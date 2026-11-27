// Copyright 2024-2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class ChordalHoldHoldOnOtherKeyPress : public TestFixture {};

TEST_F(ChordalHoldHoldOnOtherKeyPress, chord_with_mod_tap_settled_as_hold) {
    TestDriver driver;
    InSequence s;
    // Mod-tap key on the left hand.
    auto mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    // Regular key on the right hand.
    auto regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_A));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, chord_nested_press_settled_as_hold) {
    TestDriver driver;
    InSequence s;
    // Mod-tap key on the left hand.
    auto mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    // Regular key on the right hand.
    auto regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_A));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, chord_rolled_press_settled_as_hold) {
    TestDriver driver;
    InSequence s;
    // Mod-tap key on the left hand.
    auto mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    // Regular key on the right hand.
    auto regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_A));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap key.
    EXPECT_REPORT(driver, (KC_A));
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, non_chord_with_mod_tap_settled_as_tap) {
    TestDriver driver;
    InSequence s;
    // Mod-tap key and regular key both on the left hand.
    auto mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_REPORT(driver, (KC_P));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, tap_mod_tap_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_key});

    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    idle_for(TAPPING_TERM - 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, hold_mod_tap_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_key});

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_key.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, two_mod_taps_same_hand_hold_til_timeout) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, MATRIX_COLS - 2, 0, RCTL_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, MATRIX_COLS - 1, 0, RSFT_T(KC_B));

    set_keymap({mod_tap_key1, mod_tap_key2});

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Continue holding til the tapping term.
    EXPECT_REPORT(driver, (KC_RIGHT_CTRL));
    EXPECT_REPORT(driver, (KC_RIGHT_CTRL, KC_RIGHT_SHIFT));
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap keys.
    EXPECT_REPORT(driver, (KC_RIGHT_SHIFT));
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, two_mod_taps_nested_press_opposite_hands) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, MATRIX_COLS - 1, 0, RSFT_T(KC_B));

    set_keymap({mod_tap_key1, mod_tap_key2});

    // Press first mod-tap key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press second mod-tap key.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release second mod-tap key.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release first mod-tap key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, two_mod_taps_nested_press_same_hand) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, 2, 0, RSFT_T(KC_B));

    set_keymap({mod_tap_key1, mod_tap_key2});

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap keys.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key2.release();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, three_mod_taps_same_hand_streak_roll) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, 2, 0, CTL_T(KC_B));
    auto       mod_tap_key3 = KeymapKey(0, 3, 0, RSFT_T(KC_C));

    set_keymap({mod_tap_key1, mod_tap_key2, mod_tap_key3});

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys 1, 2, 3.
    //
    // NOTE: The correct order of events should be
    // EXPECT_REPORT(driver, (KC_A));
    // EXPECT_REPORT(driver, (KC_A, KC_B));
    // EXPECT_REPORT(driver, (KC_A, KC_B, KC_C));
    // EXPECT_REPORT(driver, (KC_B, KC_C));
    // EXPECT_REPORT(driver, (KC_C));
    // EXPECT_EMPTY_REPORT(driver);
    //
    // However, due to a workaround for https://github.com/tmk/tmk_keyboard/issues/60,
    // the events are processed out of order, with the first two keys released
    // before pressing KC_C.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_C));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, three_mod_taps_same_hand_streak_orders) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, 2, 0, CTL_T(KC_B));
    auto       mod_tap_key3 = KeymapKey(0, 3, 0, RSFT_T(KC_C));

    set_keymap({mod_tap_key1, mod_tap_key2, mod_tap_key3});

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    // Press mod-tap keys.
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key3.press();
    run_one_scan_loop();
    // Release keys 3, 2, 1.
    mod_tap_key3.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    idle_for(TAPPING_TERM);
    // Press mod-tap keys.
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key3.press();
    run_one_scan_loop();
    // Release keys 3, 1, 2.
    mod_tap_key3.release();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // NOTE: The correct order of events should be
    // EXPECT_REPORT(driver, (KC_A));
    // EXPECT_REPORT(driver, (KC_A, KC_B));
    // EXPECT_REPORT(driver, (KC_A, KC_B, KC_C));
    // EXPECT_REPORT(driver, (KC_A, KC_C));
    // EXPECT_REPORT(driver, (KC_A));
    // EXPECT_EMPTY_REPORT(driver);
    //
    // However, due to a workaround for https://github.com/tmk/tmk_keyboard/issues/60,
    // the events are processed out of order, with the first two keys released
    // before pressing KC_C.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_C));
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    idle_for(TAPPING_TERM);
    // Press mod-tap keys.
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key3.press();
    run_one_scan_loop();
    // Release keys 2, 3, 1.
    mod_tap_key2.release();
    run_one_scan_loop();
    mod_tap_key3.release();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, three_mod_taps_two_left_one_right) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, 2, 0, CTL_T(KC_B));
    auto       mod_tap_key3 = KeymapKey(0, MATRIX_COLS - 1, 0, RSFT_T(KC_C));

    set_keymap({mod_tap_key1, mod_tap_key2, mod_tap_key3});

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release key 3.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release key 2, then key 1.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key2.release();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release key 3.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release key 1, then key 2.
    EXPECT_REPORT(driver, (KC_LEFT_CTRL));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, three_mod_taps_one_held_two_tapped) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, MATRIX_COLS - 2, 0, CTL_T(KC_B));
    auto       mod_tap_key3 = KeymapKey(0, MATRIX_COLS - 1, 0, RSFT_T(KC_C));

    set_keymap({mod_tap_key1, mod_tap_key2, mod_tap_key3});

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys 3, 2, 1.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key3.press();
    run_one_scan_loop();
    mod_tap_key3.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    mod_tap_key1.press();
    run_one_scan_loop();

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys 3, 1, 2.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key3.press();
    run_one_scan_loop();
    mod_tap_key3.release();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, tap_regular_key_while_layer_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_hold_key = KeymapKey(0, 1, 0, LT(1, KC_P));
    auto       regular_key        = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);
    auto       no_key             = KeymapKey(1, 1, 0, XXXXXXX);
    auto       layer_key          = KeymapKey(1, MATRIX_COLS - 1, 0, KC_B);

    set_keymap({layer_tap_hold_key, regular_key, no_key, layer_key});

    // Press layer-tap-hold key.
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_REPORT(driver, (KC_B));
    regular_key.press();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 2);
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 2);
    VERIFY_AND_CLEAR(driver);

    // Release layer-tap-hold key.
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.release();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 0);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, long_distinct_taps_of_layer_tap_key_and_regular_key) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_hold_key = KeymapKey(0, 1, 0, LT(1, KC_P));
    auto       regular_key        = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);
    auto       layer_key          = KeymapKey(0, MATRIX_COLS - 1, 0, KC_B);

    set_keymap({layer_tap_hold_key, regular_key});

    // Press layer-tap-hold key.
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Idle for tapping term of layer tap hold key.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    EXPECT_EQ(layer_state, 2);
    VERIFY_AND_CLEAR(driver);

    // Release layer-tap-hold key.
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.release();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 0);
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_REPORT(driver, (KC_A));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, nested_tap_of_layer_0_layer_tap_keys) {
    TestDriver driver;
    InSequence s;
    // The keys are layer-taps on layer 0 but regular keys on layer 1.
    auto first_layer_tap_key  = KeymapKey(0, 1, 0, LT(1, KC_A));
    auto second_layer_tap_key = KeymapKey(0, MATRIX_COLS - 1, 0, LT(1, KC_P));
    auto first_key_on_layer   = KeymapKey(1, 1, 0, KC_B);
    auto second_key_on_layer  = KeymapKey(1, MATRIX_COLS - 1, 0, KC_Q);

    set_keymap({first_layer_tap_key, second_layer_tap_key, first_key_on_layer, second_key_on_layer});

    // Press first layer-tap key.
    EXPECT_NO_REPORT(driver);
    first_layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press second layer-tap key.
    EXPECT_REPORT(driver, (KC_Q));
    second_layer_tap_key.press();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 2);
    VERIFY_AND_CLEAR(driver);

    // Release second layer-tap key.
    EXPECT_EMPTY_REPORT(driver);
    second_layer_tap_key.release();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 2);
    VERIFY_AND_CLEAR(driver);

    // Release first layer-tap key.
    EXPECT_NO_REPORT(driver);
    first_layer_tap_key.release();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 0);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, lt_mt_one_regular_key) {
    TestDriver driver;
    InSequence s;
    auto       lt_key      = KeymapKey(0, 1, 0, LT(1, KC_A));
    auto       mt_key0     = KeymapKey(0, 2, 0, SFT_T(KC_B));
    auto       mt_key1     = KeymapKey(1, 2, 0, CTL_T(KC_C));
    auto       regular_key = KeymapKey(1, MATRIX_COLS - 1, 0, KC_X);
    auto       no_key0     = KeymapKey(0, MATRIX_COLS - 1, 0, XXXXXXX);
    auto       no_key1     = KeymapKey(1, 1, 0, XXXXXXX);

    set_keymap({lt_key, mt_key0, mt_key1, regular_key, no_key0, no_key1});

    // Press LT, MT.
    EXPECT_NO_REPORT(driver);
    lt_key.press();
    run_one_scan_loop();
    mt_key1.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_REPORT(driver, (KC_LCTL));
    EXPECT_REPORT(driver, (KC_LCTL, KC_X));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release the regular key.
    EXPECT_REPORT(driver, (KC_LCTL));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release MT key.
    EXPECT_EMPTY_REPORT(driver);
    mt_key1.release();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), 0);
    VERIFY_AND_CLEAR(driver);

    // Release LT key.
    lt_key.release();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 0);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, nested_tap_of_layer_tap_keys) {
    TestDriver driver;
    InSequence s;
    // The keys are layer-taps on all layers.
    auto first_key_layer_0  = KeymapKey(0, 1, 0, LT(1, KC_A));
    auto second_key_layer_0 = KeymapKey(0, MATRIX_COLS - 1, 0, LT(1, KC_P));
    auto first_key_layer_1  = KeymapKey(1, 1, 0, LT(2, KC_B));
    auto second_key_layer_1 = KeymapKey(1, MATRIX_COLS - 1, 0, LT(2, KC_Q));
    auto first_key_layer_2  = KeymapKey(2, 1, 0, KC_TRNS);
    auto second_key_layer_2 = KeymapKey(2, MATRIX_COLS - 1, 0, KC_TRNS);

    set_keymap({first_key_layer_0, second_key_layer_0, first_key_layer_1, second_key_layer_1, first_key_layer_2, second_key_layer_2});

    // Press first layer-tap key.
    EXPECT_NO_REPORT(driver);
    first_key_layer_0.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press second layer-tap key.
    EXPECT_NO_REPORT(driver);
    second_key_layer_0.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release second layer-tap key.
    EXPECT_REPORT(driver, (KC_Q));
    EXPECT_EMPTY_REPORT(driver);
    second_key_layer_0.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release first layer-tap key.
    EXPECT_NO_REPORT(driver);
    first_key_layer_0.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, roll_layer_tap_key_with_regular_key) {
    TestDriver driver;
    InSequence s;

    auto layer_tap_hold_key = KeymapKey(0, 1, 0, LT(1, KC_P));
    auto regular_key        = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);
    auto layer_key          = KeymapKey(1, MATRIX_COLS - 1, 0, KC_B);

    set_keymap({layer_tap_hold_key, regular_key, layer_key});

    // Press layer-tap-hold key.
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_REPORT(driver, (KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release layer-tap-hold key.
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// When a held mod-tap key is released while another mod-tap key is undecided,
// its release is retained in `waiting_buffer`. If an opposite-hand mod-tap
// press then settles the undecided key as held under HOLD_ON_OTHER_KEY_PRESS,
// the retained release at the head of `waiting_buffer` must be processed as a
// release rather than promoted as the next `tapping_key` and dropped:
//   1. LSFT_T(KC_F) down (L), 201 ms -> held Left Shift
//   2. RCTL_T(KC_K) down (R), 10 ms  -> undecided tapping_key
//   3. LSFT_T(KC_F) up (L), 10 ms    -> retained in waiting_buffer
//   4. LALT_T(KC_S) down (L)         -> settles RCTL_T(KC_K) as held Right Ctrl,
//                                       releases Left Shift, and promotes LALT_T(KC_S)
//   5. 10 ms, LALT_T(KC_S) up        -> taps 's' with Right Ctrl held
//   6. RCTL_T(KC_K) up               -> releases Right Ctrl
TEST_F(ChordalHoldHoldOnOtherKeyPress, retained_mt_hold_release) {
    TestDriver driver;
    InSequence s;
    auto       mt_f = KeymapKey(0, 3, 0, LSFT_T(KC_F)); // Left hand.
    auto       mt_s = KeymapKey(0, 2, 0, LALT_T(KC_S)); // Left hand.
    auto       mt_k = KeymapKey(0, 7, 0, RCTL_T(KC_K)); // Right hand.
    set_keymap({mt_f, mt_s, mt_k});

    EXPECT_REPORT(driver, (KC_LSFT));
    mt_f.press(); // Hold LSFT_T(KC_F) past the tapping term.
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mt_k.press();
    idle_for(10);
    // Since mt_k is unsettled, this LSFT_T(KC_F) release is retained.
    mt_f.release();
    idle_for(10);
    VERIFY_AND_CLEAR(driver);

    // Press LALT_T(KC_S) (L). Now, RCTL_T(KC_K) settles as held. LSFT_T(KC_F)'s
    // retained release unregisters Left Shift on the same scan.
    EXPECT_REPORT(driver, (KC_LSFT, KC_RCTL));
    EXPECT_REPORT(driver, (KC_RCTL));
    mt_s.press();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), MOD_BIT_RCTRL);
    VERIFY_AND_CLEAR(driver);

    // Release LALT_T(KC_S) within its tapping term -> sends Ctrl+S.
    idle_for(10);
    EXPECT_REPORT(driver, (KC_RCTL, KC_S));
    EXPECT_REPORT(driver, (KC_RCTL));
    mt_s.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mt_k.release();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), 0);
    VERIFY_AND_CLEAR(driver);
}

// Similar to the previous test, but with a retained layer-tap release:
//   1. LT(1, KC_D) down (L), 201 ms -> Layer 1 active
//   2. RCTL_T(KC_K) down (R), 10 ms -> undecided tapping_key
//   3. LT(1, KC_D) up (L), 10 ms    -> retained in waiting_buffer
//   4. KC_F down (L), KC_F up       -> settles RCTL_T(KC_K) as Right Ctrl,
//                                      turns Layer 1 off, and taps 'f' on Layer 0
//   5. RCTL_T(KC_K) up              -> releases Right Ctrl
TEST_F(ChordalHoldHoldOnOtherKeyPress, retained_lt_hold_release) {
    TestDriver driver;
    InSequence s;
    auto       lt_d    = KeymapKey(0, 2, 0, LT(1, KC_D));  // Left hand.
    auto       key_f_0 = KeymapKey(0, 3, 0, KC_F);         // Left hand, Layer 0.
    auto       key_f_1 = KeymapKey(1, 3, 0, KC_X);         // Left hand, Layer 1.
    auto       mt_k    = KeymapKey(0, 7, 0, RCTL_T(KC_K)); // Right hand.
    auto       trns_d  = KeymapKey(1, 2, 0, KC_TRNS);
    auto       trns_k  = KeymapKey(1, 7, 0, KC_TRNS);
    set_keymap({lt_d, key_f_0, key_f_1, mt_k, trns_d, trns_k});

    EXPECT_NO_REPORT(driver);
    lt_d.press(); // Hold LT(1, KC_D) past the tapping term.
    idle_for(TAPPING_TERM + 1);
    EXPECT_EQ(layer_state, 1 << 1);
    VERIFY_AND_CLEAR(driver);

    // Press RCTL_T(KC_K) (R), then release LT(1, KC_D) (retained).
    EXPECT_NO_REPORT(driver);
    mt_k.press();
    idle_for(10);
    lt_d.release();
    idle_for(10);
    EXPECT_EQ(layer_state, 1 << 1);
    VERIFY_AND_CLEAR(driver);

    // Press and release KC_F (L). RCTL_T(KC_K) settles as Right Ctrl, and
    // LT(1, KC_D) release turns Layer 1 off, and KC_F is decoded on Layer 0.
    EXPECT_REPORT(driver, (KC_RCTL));
    EXPECT_REPORT(driver, (KC_RCTL, KC_F));
    key_f_0.press();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 0);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_RCTL));
    key_f_0.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mt_k.release();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), 0);
    EXPECT_EQ(layer_state, 0);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldHoldOnOtherKeyPress, two_mod_tap_keys_stuttered_press) {
    TestDriver driver;
    InSequence s;

    auto mod_tap_key1 = KeymapKey(0, 1, 0, LSFT_T(KC_A));
    auto mod_tap_key2 = KeymapKey(0, 2, 0, LCTL_T(KC_B));

    set_keymap({mod_tap_key1, mod_tap_key2});

    // Hold first mod-tap key until the tapping term.
    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key1.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Press the second mod-tap key, then quickly release and press the first.
    EXPECT_NO_REPORT(driver);
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_REPORT(driver, (KC_B, KC_A));
    mod_tap_key1.press();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), 0); // Verify that Shift was released.
    VERIFY_AND_CLEAR(driver);

    // Release both keys.
    EXPECT_REPORT(driver, (KC_A));
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
