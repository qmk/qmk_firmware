// Copyright 2024 Google LLC
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

class ChordalHoldDefault : public TestFixture {};

TEST_F(ChordalHoldDefault, chord_nested_press_settled_as_tap) {
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
    // Tap regular key.
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap key.
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldDefault, chord_rolled_press_settled_as_tap) {
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

TEST_F(ChordalHoldDefault, non_chord_with_mod_tap_settled_as_tap) {
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

TEST_F(ChordalHoldDefault, tap_mod_tap_key) {
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

TEST_F(ChordalHoldDefault, hold_mod_tap_key) {
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

TEST_F(ChordalHoldDefault, two_mod_taps_same_hand_hold_til_timeout) {
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

TEST_F(ChordalHoldDefault, three_mod_taps_same_hand_streak_roll) {
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
}

TEST_F(ChordalHoldDefault, tap_regular_key_while_layer_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_hold_key = KeymapKey(0, 1, 0, LT(1, KC_P));
    auto       regular_key        = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);
    auto       layer_key          = KeymapKey(1, MATRIX_COLS - 1, 0, KC_B);

    set_keymap({layer_tap_hold_key, regular_key, layer_key});

    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.press(); // Press layer-tap-hold key.
    run_one_scan_loop();
    regular_key.press(); // Press regular key.
    run_one_scan_loop();
    regular_key.release(); // Release regular key.
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    layer_tap_hold_key.release(); // Release layer-tap-hold key.
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
