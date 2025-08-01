// Copyright 2025 Google LLC
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

extern "C" bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
    return true;
}

class SpeculativeHoldRetroTappingTest : public TestFixture {};

TEST_F(SpeculativeHoldRetroTappingTest, roll_regular_to_lgui_mod) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       regular_key = KeymapKey(0, 2, 0, KC_B);

    set_keymap({mod_tap_key, regular_key});

    EXPECT_REPORT(driver, (KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B, KC_LGUI));
    mod_tap_key.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LGUI));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Neutralizer invoked by Speculative Hold.
    EXPECT_REPORT(driver, (KC_LGUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LGUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldRetroTappingTest, regular_to_mod_under_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, LSFT_T(KC_A));
    auto       regular_key = KeymapKey(0, 2, 0, KC_B);

    set_keymap({mod_tap_key, regular_key});

    EXPECT_REPORT(driver, (KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B, KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldRetroTappingTest, mod_under_tap_term_to_regular) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       regular_key = KeymapKey(0, 2, 0, KC_B);

    set_keymap({mod_tap_key, regular_key});

    EXPECT_REPORT(driver, (KC_LGUI));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Neutralizer invoked by Speculative Hold.
    EXPECT_REPORT(driver, (KC_LGUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LGUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_B, KC_P));
    EXPECT_REPORT(driver, (KC_B));
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldRetroTappingTest, mod_over_tap_term_to_regular) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, LSFT_T(KC_A));
    auto       regular_key = KeymapKey(0, 2, 0, KC_B);

    set_keymap({mod_tap_key, regular_key});

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_B));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_B));
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldRetroTappingTest, mod_under_tap_term_to_mod_under_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_lgui = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_lsft = KeymapKey(0, 2, 0, LSFT_T(KC_A));

    set_keymap({mod_tap_lgui, mod_tap_lsft});

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_lsft.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    mod_tap_lgui.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_lsft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_lgui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldRetroTappingTest, mod_over_tap_term_to_mod_under_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_lgui = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_lsft = KeymapKey(0, 2, 0, LSFT_T(KC_A));

    set_keymap({mod_tap_lgui, mod_tap_lsft});

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_lsft.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    mod_tap_lgui.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mod_tap_lsft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_P));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_lgui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldRetroTappingTest, mod_under_tap_term_to_mod_over_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_lgui = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_lsft = KeymapKey(0, 2, 0, LSFT_T(KC_A));

    set_keymap({mod_tap_lgui, mod_tap_lsft});

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_lsft.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    mod_tap_lgui.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LGUI));
    mod_tap_lsft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Neutralizer invoked by Retro Tapping.
    EXPECT_REPORT(driver, (KC_LGUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LGUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_P, KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_lgui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldRetroTappingTest, mod_under_tap_term_to_mod_over_tap_term_offset) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_lgui = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_lsft = KeymapKey(0, 2, 0, LSFT_T(KC_A));

    set_keymap({mod_tap_lgui, mod_tap_lsft});

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_lsft.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    mod_tap_lgui.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_lsft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LGUI));
    // Neutralizer invoked by Retro Tapping.
    EXPECT_REPORT(driver, (KC_LGUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LGUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    idle_for(TAPPING_TERM);
    mod_tap_lgui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldRetroTappingTest, mod_over_tap_term_to_mod_over_tap_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_lgui = KeymapKey(0, 1, 0, LGUI_T(KC_P));
    auto       mod_tap_lsft = KeymapKey(0, 2, 0, LSFT_T(KC_A));

    set_keymap({mod_tap_lgui, mod_tap_lsft});

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_lsft.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    mod_tap_lgui.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LGUI));
    mod_tap_lsft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Neutralizer invoked by Retro Tapping.
    EXPECT_REPORT(driver, (KC_LGUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LGUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_P, KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_lgui.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldRetroTappingTest, mod_to_mod_to_mod) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_lalt = KeymapKey(0, 1, 0, LALT_T(KC_R));
    auto       mod_tap_lsft = KeymapKey(0, 2, 0, SFT_T(KC_A));
    auto       mod_tap_lctl = KeymapKey(0, 3, 0, LCTL_T(KC_C));

    set_keymap({mod_tap_lalt, mod_tap_lsft, mod_tap_lctl});

    EXPECT_REPORT(driver, (KC_LALT));
    mod_tap_lalt.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_LALT));
    mod_tap_lsft.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_lalt.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT));
    mod_tap_lctl.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_lsft.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_C, KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_lctl.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
