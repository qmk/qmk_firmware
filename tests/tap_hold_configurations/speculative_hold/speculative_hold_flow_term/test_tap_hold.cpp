// Copyright 2026 Google LLC
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
#include <utility>

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

class SpeculativeHoldFlowTerm : public TestFixture {};

TEST_F(SpeculativeHoldFlowTerm, within_flow_term_one_modtap) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 1, 0, KC_SPC);
    auto       mod_tap_key = KeymapKey(0, 2, 0, RSFT_T(KC_B));
    set_keymap({regular_key, mod_tap_key});

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_SPC));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), 0); // Don't speculate.
    EXPECT_EQ(get_mods(), 0);

    EXPECT_REPORT(driver, (KC_RSFT));
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), 0);
    EXPECT_EQ(get_mods(), MOD_BIT_RSHIFT);

    // Release mod-tap key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldFlowTerm, within_flow_term_two_modtaps) {
    TestDriver driver;
    InSequence s;
    auto       regular_key  = KeymapKey(0, 0, 0, KC_A);
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_B));
    auto       mod_tap_key2 = KeymapKey(0, 2, 0, CTL_T(KC_C));

    set_keymap({regular_key, mod_tap_key1, mod_tap_key2});

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap key 1 quickly after regular key. The mod-tap should settle
    // immediately as tapped, sending `KC_B`.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), 0); // Don't speculate.

    // Press mod-tap key 2 quickly.
    EXPECT_NO_REPORT(driver);
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), 0); // Don't speculate.

    // Hold for longer than the tapping term.
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_LCTL));
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap keys.
    EXPECT_REPORT(driver, (KC_LCTL));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldFlowTerm, after_flow_term_one_modtap) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 1, 0, KC_SPC);
    auto       mod_tap_key = KeymapKey(0, 2, 0, RSFT_T(KC_B));
    set_keymap({regular_key, mod_tap_key});

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_SPC));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    idle_for(SPECULATIVE_HOLD_FLOW_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap key.
    EXPECT_REPORT(driver, (KC_RSFT));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), MOD_BIT_RSHIFT);
    EXPECT_EQ(get_mods(), 0);

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), 0);
    EXPECT_EQ(get_mods(), MOD_BIT_RSHIFT);

    // Release mod-tap key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldFlowTerm, after_flow_term_two_modtaps) {
    TestDriver driver;
    InSequence s;
    auto       regular_key  = KeymapKey(0, 1, 0, KC_SPC);
    auto       mod_tap_key1 = KeymapKey(0, 2, 0, RSFT_T(KC_B));
    auto       mod_tap_key2 = KeymapKey(0, 3, 0, RCTL_T(KC_C));
    set_keymap({regular_key, mod_tap_key1, mod_tap_key2});

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_SPC));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    idle_for(SPECULATIVE_HOLD_FLOW_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap key 1.
    EXPECT_REPORT(driver, (KC_RSFT));
    mod_tap_key1.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), MOD_BIT_RSHIFT);
    EXPECT_EQ(get_mods(), 0);

    // Press mod-tap key 2.
    EXPECT_REPORT(driver, (KC_RSFT, KC_RCTL));
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), MOD_BIT_RSHIFT | MOD_BIT_RCTRL);
    EXPECT_EQ(get_mods(), 0);

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), 0);
    EXPECT_EQ(get_mods(), MOD_BIT_RSHIFT | MOD_BIT_RCTRL);

    // Release mod-tap keys.
    EXPECT_REPORT(driver, (KC_RCTL));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

} // namespace
