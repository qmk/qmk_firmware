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

#include <functional>

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::AnyNumber;
using testing::InSequence;

namespace {

bool process_record_user_default(uint16_t keycode, keyrecord_t *record) {
    return true;
}

// Indirection so that process_record_user() can be
// replaced with other functions in the test cases below.
std::function<bool(uint16_t, keyrecord_t *)> process_record_user_fun = process_record_user_default;

extern "C" bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_user_fun(keycode, record);
}

class SpeculativeHoldDefault : public TestFixture {
   public:
    void SetUp() override {
        process_record_user_fun = process_record_user_default;
    }
};

TEST_F(SpeculativeHoldDefault, get_speculative_hold) {
    keyrecord_t record = {};

    // With the default definition of get_speculative_hold(), Speculative Hold
    // is enabled for Ctrl and Shift.
    EXPECT_TRUE(get_speculative_hold(MT(MOD_LCTL, KC_NO), &record));
    EXPECT_TRUE(get_speculative_hold(MT(MOD_LSFT, KC_NO), &record));
    EXPECT_TRUE(get_speculative_hold(MT(MOD_LCTL | MOD_LSFT, KC_NO), &record));
    EXPECT_TRUE(get_speculative_hold(MT(MOD_RCTL, KC_NO), &record));
    EXPECT_TRUE(get_speculative_hold(MT(MOD_RSFT, KC_NO), &record));
    EXPECT_TRUE(get_speculative_hold(MT(MOD_RCTL | MOD_RSFT, KC_NO), &record));

    EXPECT_FALSE(get_speculative_hold(MT(MOD_LALT, KC_NO), &record));
    EXPECT_FALSE(get_speculative_hold(MT(MOD_LGUI, KC_NO), &record));
    EXPECT_FALSE(get_speculative_hold(MT(MOD_RALT, KC_NO), &record));
    EXPECT_FALSE(get_speculative_hold(MT(MOD_RGUI, KC_NO), &record));
    EXPECT_FALSE(get_speculative_hold(MT(MOD_MEH, KC_NO), &record));
    EXPECT_FALSE(get_speculative_hold(MT(MOD_HYPR, KC_NO), &record));
}

TEST_F(SpeculativeHoldDefault, tap_mod_tap) {
    TestDriver driver;
    InSequence s;
    static int process_record_user_calls = 0;
    auto       mod_tap_key               = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_key});

    process_record_user_fun = [](uint16_t keycode, keyrecord_t *record) {
        ++process_record_user_calls;
        return true;
    };

    // Press mod-tap-hold key. Mod is held speculatively.
    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    idle_for(10);
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), MOD_BIT_LSHIFT);
    // Speculative mod holds and releases are made directly, bypassing regular
    // event processing. No calls have been made yet to process_record_user().
    EXPECT_EQ(process_record_user_calls, 0);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver); // Speculative mod canceled.
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    // All mods are released.
    EXPECT_EQ(get_speculative_mods(), 0);
    EXPECT_EQ(get_mods(), 0);
    // Two calls have now been made, for pressing and releasing KC_P.
    EXPECT_EQ(process_record_user_calls, 2);

    // Idle for tapping term of mod tap hold key.
    idle_for(TAPPING_TERM - 10);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldDefault, key_overrides) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, LSFT_T(KC_A));
    auto       esc_key     = KeymapKey(0, 3, 0, KC_ESC);

    set_keymap({mod_tap_key, esc_key});

    // Press mod-tap Shift key.
    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press Esc key.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_HOME));
    esc_key.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Release Esc key.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT));
    esc_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap Shift key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldDefault, tap_regular_key_while_mod_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Tap regular key.
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Idle for tapping term of mod tap hold key.
    idle_for(TAPPING_TERM - 3);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldDefault, tap_mod_tap_key_two_times) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap-hold key again.
    EXPECT_REPORT(driver, (KC_P));
    mod_tap_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldDefault, tap_mod_tap_key_twice_and_hold_on_second_time) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap-hold key again.
    EXPECT_REPORT(driver, (KC_P));
    mod_tap_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldDefault, tap_and_hold_mod_tap_key) {
    TestDriver driver;
    InSequence s;
    static int process_record_user_calls = 0;
    auto       mod_tap_key               = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_key});

    process_record_user_fun = [](uint16_t keycode, keyrecord_t *record) {
        ++process_record_user_calls;
        return true;
    };

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    idle_for(TAPPING_TERM - 1);
    EXPECT_EQ(get_speculative_mods(), MOD_BIT_LSHIFT);
    EXPECT_EQ(get_mods(), 0);
    // Speculative mod holds and releases are made directly, bypassing regular
    // event processing. No calls have been made yet to process_record_user().
    EXPECT_EQ(process_record_user_calls, 0);
    idle_for(2);
    // Now that the key has settled, one call has been made for the hold event.
    EXPECT_EQ(process_record_user_calls, 1);
    EXPECT_EQ(get_speculative_mods(), 0);
    EXPECT_EQ(get_mods(), MOD_BIT_LSHIFT);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    EXPECT_EQ(process_record_user_calls, 2);
    VERIFY_AND_CLEAR(driver);
}

// Test with layer tap and speculative mod tap keys on the same layer,
// rolling from LT to MT key:
// "LT down, MT down, (wait out tapping term), LT up, MT up."
TEST_F(SpeculativeHoldDefault, lt_mt_same_layer_roll) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       mod_tap_key   = KeymapKey(0, 1, 0, SFT_T(KC_B));
    auto       regular_key   = KeymapKey(1, 1, 0, KC_C);

    set_keymap({layer_tap_key, mod_tap_key, regular_key});

    // Press layer tap key.
    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap key, after flow tap term but within tapping term. The
    // speculative mod activates.
    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Wait for the layer tap key to settle.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_C));
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release keys.
    EXPECT_EMPTY_REPORT(driver);
    layer_tap_key.release();
    run_one_scan_loop();
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    // All mods are released.
    EXPECT_EQ(get_mods() | get_speculative_mods(), 0);
}

// Test with layer tap and speculative mod tap keys on the same layer, trying a
// nested press:
// "LT down, MT down, (wait out tapping term), MT up, LT up."
TEST_F(SpeculativeHoldDefault, lt_mt_same_layer_nested_press) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       mod_tap_key   = KeymapKey(0, 1, 0, SFT_T(KC_B));
    auto       regular_key   = KeymapKey(1, 1, 0, KC_C);

    set_keymap({layer_tap_key, mod_tap_key, regular_key});

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_C));
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release keys: MT first, LT second.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    layer_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    // All mods are released.
    EXPECT_EQ(get_mods() | get_speculative_mods(), 0);
}

// Test with layer tap and speculative mod tap keys on the same layer, trying a
// nested press with the MT first:
// "MT down, LT down, (wait out tapping term), LT up, MT up."
TEST_F(SpeculativeHoldDefault, mt_lt_same_layer_nested_press) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       mod_tap_key   = KeymapKey(0, 1, 0, SFT_T(KC_B));
    auto       regular_key   = KeymapKey(1, 1, 0, KC_C);

    set_keymap({layer_tap_key, mod_tap_key, regular_key});

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    layer_tap_key.release();
    run_one_scan_loop();
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    // All mods are released.
    EXPECT_EQ(get_mods() | get_speculative_mods(), 0);
}

// Test with a speculative mod tap key reached by a layer tap key, rolling from
// LT to MT key:
// "LT down, MT down, (wait out tapping term), LT up, MT up."
TEST_F(SpeculativeHoldDefault, lt_mt_different_layer_roll) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key   = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       regular_key     = KeymapKey(0, 1, 0, KC_B);
    auto       placeholder_key = KeymapKey(1, 0, 0, KC_NO);
    auto       mod_tap_key     = KeymapKey(1, 1, 0, SFT_T(KC_C));

    set_keymap({layer_tap_key, regular_key, placeholder_key, mod_tap_key});

    // Press layer tap key.
    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    run_one_scan_loop();
    // Press mod tap key.
    mod_tap_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release keys.
    EXPECT_REPORT(driver, (KC_LSFT));
    layer_tap_key.release();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    // All mods are released.
    EXPECT_EQ(get_mods() | get_speculative_mods(), 0);
}

// Test with a speculative mod tap key reached by a layer tap key, slowly
// rolling from LT to MT key:
// "LT down, (wait), MT down, (wait), LT up, MT up."
TEST_F(SpeculativeHoldDefault, lt_mt_different_layer_slow_roll) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key   = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       regular_key     = KeymapKey(0, 1, 0, KC_B);
    auto       placeholder_key = KeymapKey(1, 0, 0, KC_NO);
    auto       mod_tap_key     = KeymapKey(1, 1, 0, SFT_T(KC_C));

    set_keymap({layer_tap_key, regular_key, placeholder_key, mod_tap_key});

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    idle_for(TAPPING_TERM + 1);

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_B));
    EXPECT_EMPTY_REPORT(driver);
    layer_tap_key.release();
    run_one_scan_loop();
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    // All mods are released.
    EXPECT_EQ(get_mods() | get_speculative_mods(), 0);
}

// Test with a speculative mod tap key reached by a layer tap key, trying a
// nested press:
// "LT down, MT down, (wait out tapping term), MT up, LT up."
TEST_F(SpeculativeHoldDefault, lt_mt_different_layer_nested_press) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key   = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       regular_key     = KeymapKey(0, 1, 0, KC_B);
    auto       placeholder_key = KeymapKey(1, 0, 0, KC_NO);
    auto       mod_tap_key     = KeymapKey(1, 1, 0, SFT_T(KC_C));

    set_keymap({layer_tap_key, regular_key, placeholder_key, mod_tap_key});

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    run_one_scan_loop();
    mod_tap_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release keys.
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    layer_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    // All mods are released.
    EXPECT_EQ(get_mods() | get_speculative_mods(), 0);
}

// Test with a speculative mod tap key reached by a layer tap key, trying a
// slow nested press:
// "LT down, (wait), MT down, MT up, LT up."
TEST_F(SpeculativeHoldDefault, lt_mt_different_layer_slow_nested_press) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key   = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       regular_key     = KeymapKey(0, 1, 0, KC_B);
    auto       placeholder_key = KeymapKey(1, 0, 0, KC_NO);
    auto       mod_tap_key     = KeymapKey(1, 1, 0, SFT_T(KC_C));

    set_keymap({layer_tap_key, regular_key, placeholder_key, mod_tap_key});

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    idle_for(TAPPING_TERM + 1);

    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_C));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    layer_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    // All mods are released.
    EXPECT_EQ(get_mods() | get_speculative_mods(), 0);
}

} // namespace
