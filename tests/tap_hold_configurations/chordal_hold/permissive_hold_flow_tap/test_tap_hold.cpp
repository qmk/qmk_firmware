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

class ChordalHoldPermissiveHoldFlowTap : public TestFixture {};

TEST_F(ChordalHoldPermissiveHoldFlowTap, chordal_hold_handedness) {
    EXPECT_EQ(chordal_hold_handedness({.col = 0, .row = 0}), 'L');
    EXPECT_EQ(chordal_hold_handedness({.col = MATRIX_COLS - 1, .row = 0}), 'R');
    EXPECT_EQ(chordal_hold_handedness({.col = 0, .row = 2}), '*');
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, get_chordal_hold_default) {
    auto make_record = [](uint8_t row, uint8_t col, keyevent_type_t type = KEY_EVENT) {
        return keyrecord_t{
            .event =
                {
                    .key     = {.col = col, .row = row},
                    .type    = type,
                    .pressed = true,
                },
        };
    };
    // Create two records on the left hand.
    keyrecord_t record_l0 = make_record(0, 0);
    keyrecord_t record_l1 = make_record(1, 0);
    // Create a record on the right hand.
    keyrecord_t record_r = make_record(0, MATRIX_COLS - 1);

    // Function should return true when records are on opposite hands.
    EXPECT_TRUE(get_chordal_hold_default(&record_l0, &record_r));
    EXPECT_TRUE(get_chordal_hold_default(&record_r, &record_l0));
    // ... and false when on the same hand.
    EXPECT_FALSE(get_chordal_hold_default(&record_l0, &record_l1));
    EXPECT_FALSE(get_chordal_hold_default(&record_l1, &record_l0));
    // But (2, 0) has handedness '*', for which true is returned for chords
    // with either hand.
    keyrecord_t record_l2 = make_record(2, 0);
    EXPECT_TRUE(get_chordal_hold_default(&record_l2, &record_l0));
    EXPECT_TRUE(get_chordal_hold_default(&record_l2, &record_r));

    // Create a record resulting from a combo.
    keyrecord_t record_combo = make_record(0, 0, COMBO_EVENT);
    // Function returns true in all cases.
    EXPECT_TRUE(get_chordal_hold_default(&record_l0, &record_combo));
    EXPECT_TRUE(get_chordal_hold_default(&record_r, &record_combo));
    EXPECT_TRUE(get_chordal_hold_default(&record_combo, &record_l0));
    EXPECT_TRUE(get_chordal_hold_default(&record_combo, &record_r));
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, chord_nested_press_settled_as_hold) {
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

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_A));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, chord_rolled_press_settled_as_tap) {
    TestDriver driver;
    InSequence s;
    // Mod-tap key on the left hand.
    auto mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    // Regular key on the right hand.
    auto regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap key and regular key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap key.
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
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

TEST_F(ChordalHoldPermissiveHoldFlowTap, non_chord_with_mod_tap_settled_as_tap) {
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

TEST_F(ChordalHoldPermissiveHoldFlowTap, tap_mod_tap_key) {
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

TEST_F(ChordalHoldPermissiveHoldFlowTap, hold_mod_tap_key) {
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

TEST_F(ChordalHoldPermissiveHoldFlowTap, two_mod_taps_same_hand_hold_til_timeout) {
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

TEST_F(ChordalHoldPermissiveHoldFlowTap, two_mod_taps_nested_press_opposite_hands) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, MATRIX_COLS - 1, 0, RSFT_T(KC_B));

    set_keymap({mod_tap_key1, mod_tap_key2});

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap keys.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, two_mod_taps_nested_press_same_hand) {
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
    mod_tap_key2.release();
    run_one_scan_loop();

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, three_mod_taps_same_hand_streak_roll) {
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
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_C));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, three_mod_taps_same_hand_streak_orders) {
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

    // Release keys 3, 2, 1.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys 3, 1, 2.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B));
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys 2, 3, 1.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_A, KC_C));
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key2.release();
    run_one_scan_loop();
    mod_tap_key3.release();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, three_mod_taps_opposite_hands_roll) {
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
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys 1, 2, 3.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_C));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, three_mod_taps_two_left_one_right) {
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
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release key 3.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release key 2, then key 1.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release key 3.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_CTRL));
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release key 1, then key 2.
    EXPECT_REPORT(driver, (KC_LEFT_CTRL));
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, three_mod_taps_one_held_two_tapped) {
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
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys 3, 2, 1.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key3.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys 3, 1, 2.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    mod_tap_key3.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B));
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, two_mod_taps_one_regular_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, MATRIX_COLS - 2, 0, CTL_T(KC_B));
    auto       regular_key  = KeymapKey(0, MATRIX_COLS - 1, 0, KC_C);

    set_keymap({mod_tap_key1, mod_tap_key2, regular_key});

    // Press keys.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_C));
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    run_one_scan_loop();
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release keys.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B, KC_C));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B));
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, tap_regular_key_while_layer_tap_key_is_held) {
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
    // Press regular key.
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_REPORT(driver, (KC_B));
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

TEST_F(ChordalHoldPermissiveHoldFlowTap, nested_tap_of_layer_0_layer_tap_keys) {
    TestDriver driver;
    InSequence s;
    // The keys are layer-taps on layer 2 but regular keys on layer 1.
    auto first_layer_tap_key  = KeymapKey(0, 1, 0, LT(1, KC_A));
    auto second_layer_tap_key = KeymapKey(0, MATRIX_COLS - 1, 0, LT(1, KC_P));
    auto first_key_on_layer   = KeymapKey(1, 1, 0, KC_B);
    auto second_key_on_layer  = KeymapKey(1, MATRIX_COLS - 1, 0, KC_Q);

    set_keymap({first_layer_tap_key, second_layer_tap_key, first_key_on_layer, second_key_on_layer});

    // Press first layer-tap key.
    EXPECT_NO_REPORT(driver);
    first_layer_tap_key.press();
    run_one_scan_loop();
    // Press second layer-tap key.
    second_layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release second layer-tap key.
    EXPECT_REPORT(driver, (KC_Q));
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

TEST_F(ChordalHoldPermissiveHoldFlowTap, lt_mt_one_regular_key) {
    TestDriver driver;
    InSequence s;
    auto       lt_key      = KeymapKey(0, 1, 0, LT(1, KC_A));
    auto       mt_key0     = KeymapKey(0, 2, 0, SFT_T(KC_B));
    auto       mt_key1     = KeymapKey(1, 2, 0, CTL_T(KC_C));
    auto       regular_key = KeymapKey(1, MATRIX_COLS - 1, 0, KC_X);
    auto       no_key0     = KeymapKey(0, MATRIX_COLS - 1, 0, XXXXXXX);
    auto       no_key1     = KeymapKey(1, 1, 0, XXXXXXX);

    set_keymap({lt_key, mt_key0, mt_key1, regular_key, no_key0, no_key1});

    // Press LT, MT, and regular key.
    EXPECT_NO_REPORT(driver);
    lt_key.press();
    run_one_scan_loop();
    mt_key1.press();
    run_one_scan_loop();
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release the regular key.
    EXPECT_REPORT(driver, (KC_LCTL));
    EXPECT_REPORT(driver, (KC_LCTL, KC_X));
    EXPECT_REPORT(driver, (KC_LCTL));
    regular_key.release();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), MOD_BIT_LCTRL);
    EXPECT_EQ(layer_state, 2);
    VERIFY_AND_CLEAR(driver);

    // Release MT key.
    EXPECT_EMPTY_REPORT(driver);
    mt_key1.release();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), 0);
    VERIFY_AND_CLEAR(driver);

    // Release LT key.
    EXPECT_NO_REPORT(driver);
    lt_key.release();
    run_one_scan_loop();
    EXPECT_EQ(layer_state, 0);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, nested_tap_of_layer_tap_keys) {
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

TEST_F(ChordalHoldPermissiveHoldFlowTap, roll_layer_tap_key_with_regular_key) {
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
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release layer-tap-hold key.
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_A));
    layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldPermissiveHoldFlowTap, two_mod_tap_keys_stuttered_press) {
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
