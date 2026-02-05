// Copyright 2022 Isaac Elenbaas
// Copyright 2025 Google LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

extern "C" {
bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    return true;
}
} // extern "C"

using testing::_;
using testing::AnyNumber;
using testing::AnyOf;
using testing::InSequence;

class RetroShiftPermissiveHold : public TestFixture {};

TEST_F(RetroShiftPermissiveHold, tap_regular_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LCTL))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LCTL, KC_A));
    EXPECT_REPORT(driver, (KC_LCTL));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroShiftPermissiveHold, tap_mod_tap_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key         = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, LALT_T(KC_A));

    set_keymap({mod_tap_key, mod_tap_regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap-regular key.
    EXPECT_REPORT(driver, (KC_LCTL, KC_LALT));
    mod_tap_regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-regular key.
    EXPECT_REPORT(driver, (KC_LCTL));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LCTL))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LCTL, KC_A));
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroShiftPermissiveHold, tap_regular_key_while_mod_tap_key_is_held_over_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LCTL))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LCTL, KC_A));
    EXPECT_REPORT(driver, (KC_LCTL));
    regular_key.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroShiftPermissiveHold, tap_mod_tap_key_while_mod_tap_key_is_held_over_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key         = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, LALT_T(KC_A));

    set_keymap({mod_tap_key, mod_tap_regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap-regular key.
    EXPECT_REPORT(driver, (KC_LCTL, KC_LALT));
    mod_tap_regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-regular key.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LCTL))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LCTL, KC_A));
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_regular_key.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroShiftPermissiveHold, hold_regular_key_while_mod_tap_key_is_held_over_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    idle_for(AUTO_SHIFT_TIMEOUT);
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(KC_LCTL, KC_LSFT),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LCTL))))
        .Times(AnyNumber());
    // clang-format on
    EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_A));
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(KC_LCTL, KC_LSFT),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    EXPECT_REPORT(driver, (KC_LCTL));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroShiftPermissiveHold, hold_mod_tap_key_while_mod_tap_key_is_held_over_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key         = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, LALT_T(KC_A));

    set_keymap({mod_tap_key, mod_tap_regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap-regular key.
    EXPECT_REPORT(driver, (KC_LCTL, KC_LALT));
    mod_tap_regular_key.press();
    run_one_scan_loop();
    idle_for(AUTO_SHIFT_TIMEOUT);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-regular key.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(KC_LCTL, KC_LSFT),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LCTL))))
        .Times(AnyNumber());
    // clang-format on
    EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_A));
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(KC_LCTL, KC_LSFT),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_regular_key.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroShiftPermissiveHold, roll_tap_regular_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroShiftPermissiveHold, roll_tap_mod_tap_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key         = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, LALT_T(KC_A));

    set_keymap({mod_tap_key, mod_tap_regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap-regular key.
    EXPECT_REPORT(driver, (KC_LCTL, KC_LALT));
    mod_tap_regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-regular key.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroShiftPermissiveHold, roll_hold_regular_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    idle_for(AUTO_SHIFT_TIMEOUT);
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(RetroShiftPermissiveHold, roll_hold_mod_tap_key_while_mod_tap_key_is_held_under_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key         = KeymapKey(0, 0, 0, LCTL_T(KC_P));
    auto       mod_tap_regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, LALT_T(KC_A));

    set_keymap({mod_tap_key, mod_tap_regular_key});

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap-regular key.
    EXPECT_REPORT(driver, (KC_LCTL, KC_LALT));
    mod_tap_regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-regular key.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_EMPTY_REPORT(driver);
    idle_for(AUTO_SHIFT_TIMEOUT);
    mod_tap_regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Test with layer tap and speculative mod tap keys on the same layer, rolling
// from LT to MT key:
// "LT down, MT down, (wait out tapping term), LT up, MT up."
TEST_F(RetroShiftPermissiveHold, lt_mt_same_layer_roll) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       mod_tap_key   = KeymapKey(0, 1, 0, LCTL_T(KC_B));
    auto       regular_key   = KeymapKey(1, 1, 0, KC_C);

    set_keymap({layer_tap_key, mod_tap_key, regular_key});

    // Press layer tap key.
    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap key, after flow tap term but within tapping term. The
    // speculative mod activates.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Wait for the layer tap key to settle.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release keys.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_REPORT(driver, (KC_LSFT));
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

// Test with layer tap and speculative mod tap keys on the same layer, trying
// a nested press from LT to MT key:
// "LT down, MT down, (wait out tapping term), MT up, LT up."
TEST_F(RetroShiftPermissiveHold, lt_mt_same_layer_nested_press) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       mod_tap_key   = KeymapKey(0, 1, 0, LCTL_T(KC_B));
    auto       regular_key   = KeymapKey(1, 1, 0, KC_C);

    set_keymap({layer_tap_key, mod_tap_key, regular_key});

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release keys: MT first, LT second.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_LSFT, KC_C));
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

// Test with layer tap and speculative mod tap keys on the same layer, trying
// a nested press with the MT first:
// "MT down, LT down, (wait out tapping term), LT up, MT up."
TEST_F(RetroShiftPermissiveHold, mt_lt_same_layer_nested_press) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       mod_tap_key   = KeymapKey(0, 1, 0, LCTL_T(KC_B));
    auto       regular_key   = KeymapKey(1, 1, 0, KC_C);

    set_keymap({layer_tap_key, mod_tap_key, regular_key});

    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_A));
    EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT));
    EXPECT_REPORT(driver, (KC_LCTL));
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
TEST_F(RetroShiftPermissiveHold, lt_mt_different_layer_roll) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key   = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       regular_key     = KeymapKey(0, 1, 0, KC_B);
    auto       placeholder_key = KeymapKey(1, 0, 0, KC_NO);
    auto       mod_tap_key     = KeymapKey(1, 1, 0, LCTL_T(KC_C));

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
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    layer_tap_key.release();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_B));
    EXPECT_REPORT(driver, (KC_LSFT));
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
TEST_F(RetroShiftPermissiveHold, lt_mt_different_layer_slow_roll) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key   = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       regular_key     = KeymapKey(0, 1, 0, KC_B);
    auto       placeholder_key = KeymapKey(1, 0, 0, KC_NO);
    auto       mod_tap_key     = KeymapKey(1, 1, 0, LCTL_T(KC_C));

    set_keymap({layer_tap_key, regular_key, placeholder_key, mod_tap_key});

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    idle_for(TAPPING_TERM + 1);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_REPORT(driver, (KC_LSFT));
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

// Test with a speculative mod tap key reached by a layer tap key, try a nested
// press:
// "LT down, MT down, (wait out tapping term), MT up, LT up."
TEST_F(RetroShiftPermissiveHold, lt_mt_different_layer_nested_press) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key   = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       regular_key     = KeymapKey(0, 1, 0, KC_B);
    auto       placeholder_key = KeymapKey(1, 0, 0, KC_NO);
    auto       mod_tap_key     = KeymapKey(1, 1, 0, LCTL_T(KC_C));

    set_keymap({layer_tap_key, regular_key, placeholder_key, mod_tap_key});

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    run_one_scan_loop();
    mod_tap_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release keys.
    EXPECT_REPORT(driver, (KC_LSFT, KC_C));
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

// Test with a speculative mod tap key reached by a layer tap key, try a slow
// nested press:
// "LT down, (wait), MT down, MT up, LT up."
TEST_F(RetroShiftPermissiveHold, lt_mt_different_layer_slow_nested_press) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_key   = KeymapKey(0, 0, 0, LT(1, KC_A));
    auto       regular_key     = KeymapKey(0, 1, 0, KC_B);
    auto       placeholder_key = KeymapKey(1, 0, 0, KC_NO);
    auto       mod_tap_key     = KeymapKey(1, 1, 0, LCTL_T(KC_C));

    set_keymap({layer_tap_key, regular_key, placeholder_key, mod_tap_key});

    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    idle_for(TAPPING_TERM + 1);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

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
