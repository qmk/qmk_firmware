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
using testing::AnyNumber;
using testing::InSequence;

class FlowTapTest : public TestFixture {};

TEST_F(FlowTapTest, short_flow_tap_settled_as_tapped) {
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
    EXPECT_REPORT(driver, (KC_B));
    mod_tap_key1.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap key 2 quickly.
    EXPECT_REPORT(driver, (KC_B, KC_C));
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Hold for longer than the tapping term.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap keys.
    EXPECT_REPORT(driver, (KC_C));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(FlowTapTest, long_flow_tap_settled_as_held) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 0, 0, KC_A);
    auto       mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_B));

    set_keymap({regular_key, mod_tap_key});

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    idle_for(FLOW_TAP_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Hold for the tapping term.
    EXPECT_REPORT(driver, (KC_LSFT));
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(FlowTapTest, holding_multiple_mod_taps) {
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

    EXPECT_NO_REPORT(driver);
    idle_for(FLOW_TAP_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap keys.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    mod_tap_key2.press();
    idle_for(TAPPING_TERM - 5); // Hold almost until tapping term.
    VERIFY_AND_CLEAR(driver);

    // Press regular key.
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_LCTL));
    EXPECT_REPORT(driver, (KC_LSFT, KC_LCTL, KC_A));
    regular_key.press();
    idle_for(10);
    VERIFY_AND_CLEAR(driver);

    // Release keys.
    EXPECT_REPORT(driver, (KC_LSFT, KC_LCTL));
    EXPECT_REPORT(driver, (KC_LCTL));
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(FlowTapTest, layer_tap_key) {
    TestDriver driver;
    InSequence s;
    auto       regular_key   = KeymapKey(0, 0, 0, KC_A);
    auto       layer_tap_key = KeymapKey(0, 1, 0, LT(1, KC_B));
    auto       regular_key2  = KeymapKey(1, 0, 0, KC_C);

    set_keymap({regular_key, layer_tap_key, regular_key2});

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Press layer-tap key, quickly after the regular key.
    EXPECT_REPORT(driver, (KC_B));
    layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Release layer-tap key.
    EXPECT_EMPTY_REPORT(driver);
    layer_tap_key.release();
    run_one_scan_loop();

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    idle_for(FLOW_TAP_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Press layer-tap key, slowly after the regular key.
    EXPECT_NO_REPORT(driver);
    layer_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    EXPECT_EQ(layer_state, 1 << 1);
    VERIFY_AND_CLEAR(driver);

    // Tap regular key2.
    EXPECT_REPORT(driver, (KC_C));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Release layer-tap key.
    EXPECT_NO_REPORT(driver);
    layer_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(FlowTapTest, combo_key) {
    TestDriver driver;
    InSequence s;
    auto       regular_key   = KeymapKey(0, 0, 0, KC_A);
    auto       mod_tap_key   = KeymapKey(0, 1, 0, SFT_T(KC_X));
    auto       layer_tap_key = KeymapKey(0, 2, 0, LT(1, KC_Y));

    set_keymap({regular_key, mod_tap_key, layer_tap_key});

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Press combo keys quickly after regular key.
    EXPECT_REPORT(driver, (KC_Z));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({mod_tap_key, layer_tap_key});
    VERIFY_AND_CLEAR(driver);

    // Press mod-tap key quickly.
    EXPECT_REPORT(driver, (KC_X));
    mod_tap_key.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(FlowTapTest, oneshot_mod_key) {
    TestDriver driver;
    InSequence s;
    auto       regular_key = KeymapKey(0, 0, 0, KC_A);
    auto       osm_key     = KeymapKey(0, 1, 0, OSM(MOD_LSFT));

    set_keymap({regular_key, osm_key});

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Tap OSM, tap regular key.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(osm_key);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Nested press of OSM and regular keys.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    EXPECT_EMPTY_REPORT(driver);
    osm_key.press();
    run_one_scan_loop();
    tap_key(regular_key);
    osm_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(FlowTapTest, quick_tap) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_A));

    set_keymap({mod_tap_key});

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_key(mod_tap_key);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
