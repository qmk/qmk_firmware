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

// Gets the unpacked 8-bit mods corresponding to a given mod-tap keycode.
uint8_t unpack_mod_tap_mods(uint16_t keycode) {
    const uint8_t mods5 = QK_MOD_TAP_GET_MODS(keycode);
    return (mods5 & 0x10) != 0 ? (mods5 << 4) : mods5;
}

std::vector<uint8_t> mods_report(uint8_t mods) {
    std::vector<uint8_t> keycodes;
    if ((mods & MOD_BIT_LCTRL)) {
        keycodes.push_back(KC_LCTL);
    }
    if ((mods & MOD_BIT_LSHIFT)) {
        keycodes.push_back(KC_LSFT);
    }
    if ((mods & MOD_BIT_LALT)) {
        keycodes.push_back(KC_LALT);
    }
    if ((mods & MOD_BIT_LGUI)) {
        keycodes.push_back(KC_LGUI);
    }
    if ((mods & MOD_BIT_RCTRL)) {
        keycodes.push_back(KC_RCTL);
    }
    if ((mods & MOD_BIT_RSHIFT)) {
        keycodes.push_back(KC_RSFT);
    }
    if ((mods & MOD_BIT_RALT)) {
        keycodes.push_back(KC_RALT);
    }
    if ((mods & MOD_BIT_RGUI)) {
        keycodes.push_back(KC_RGUI);
    }
    return keycodes;
}

extern "C" bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
    return true; // Enable Speculative Hold for all mod-tap keys.
}

class SpeculativeHoldOneKey : public TestFixture {};

TEST_F(SpeculativeHoldOneKey, modtap_dont_speculate) {
    TestDriver driver;
    InSequence s;

    struct Params {
        uint8_t  initial_mods;
        uint16_t key;
    };
    for (Params params : std::vector<Params>({
             {MOD_BIT_LSHIFT, LALT_T(KC_1)},
             {MOD_BIT_RCTRL, LGUI_T(KC_1)},
             {MOD_BIT_LALT, LSFT_T(KC_1)},
             {MOD_BIT_RALT, RCTL_T(KC_1)},
             {MOD_MASK_SHIFT, RGUI_T(KC_1)},
         })) {
        std::string scope = "initial_mods=";
        scope += testing::PrintToString(params.initial_mods);
        scope += std::string(", key=") + get_keycode_string(params.key);
        SCOPED_TRACE(scope);

        const uint8_t initial_mods = params.initial_mods;
        auto          mod_tap_key  = KeymapKey(0, 1, 0, params.key);
        const uint8_t mod_tap_mods = unpack_mod_tap_mods(params.key);

        set_keymap({mod_tap_key});

        // Activate mods.
        set_mods(initial_mods);

        // Press mod-tap key.
        EXPECT_NO_REPORT(driver);
        mod_tap_key.press();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);
        EXPECT_EQ(get_mods(), initial_mods);
        EXPECT_EQ(get_speculative_mods(), 0);

        EXPECT_REPORT(driver, (mods_report(initial_mods | mod_tap_mods)));
        EXPECT_NO_REPORT(driver);
        idle_for(TAPPING_TERM + 1);
        VERIFY_AND_CLEAR(driver);
        EXPECT_EQ(get_speculative_mods(), 0);
        EXPECT_EQ(get_mods(), initial_mods | mod_tap_mods);

        // Release mod-tap key.
        EXPECT_REPORT(driver, (mods_report(initial_mods & ~mod_tap_mods)));
        mod_tap_key.release();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);
    }

    EXPECT_EMPTY_REPORT(driver);
    clear_mods();
    send_keyboard_report();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldOneKey, two_modtaps_dont_speculate_second_key) {
    TestDriver driver;
    InSequence s;

    for (auto keys : std::vector<std::pair<uint16_t, uint16_t>>({
             {LSFT_T(KC_A), LCTL_T(KC_1)},
             {RSFT_T(KC_A), RCTL_T(KC_1)},
             {LGUI_T(KC_A), LSFT_T(KC_1)},
             {RALT_T(KC_A), RSFT_T(KC_1)},
             {MEH_T(KC_A), LGUI_T(KC_1)},
             {RCS_T(KC_A), RSG_T(KC_1)},
             {LCS_T(KC_A), HYPR_T(KC_1)},
         })) {
        std::string scope = "keys = ";
        scope += get_keycode_string(keys.first);
        scope += std::string(", ") + get_keycode_string(keys.second);
        SCOPED_TRACE(scope);

        auto          mod_tap_key1 = KeymapKey(0, 1, 0, keys.first);
        auto          mod_tap_key2 = KeymapKey(0, 2, 0, keys.second);
        const uint8_t mods1        = unpack_mod_tap_mods(keys.first);
        const uint8_t mods2        = unpack_mod_tap_mods(keys.second);

        set_keymap({mod_tap_key1, mod_tap_key2});

        // Press first mod-tap key.
        EXPECT_REPORT(driver, (mods_report(mods1)));
        mod_tap_key1.press();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);
        EXPECT_EQ(get_speculative_mods(), mods1);

        // Press second mod-tap key.
        EXPECT_NO_REPORT(driver);
        mod_tap_key2.press();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);
        EXPECT_EQ(get_speculative_mods(), mods1);

        EXPECT_REPORT(driver, (mods_report(mods1 | mods2)));
        EXPECT_NO_REPORT(driver);
        idle_for(TAPPING_TERM + 1);
        VERIFY_AND_CLEAR(driver);
        EXPECT_EQ(get_speculative_mods(), 0);
        EXPECT_EQ(get_mods(), mods1 | mods2);

        // Release first mod-tap key.
        EXPECT_REPORT(driver, (mods_report(mods2 & ~mods1)));
        mod_tap_key1.release();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        // Release second mod-tap key.
        EXPECT_EMPTY_REPORT(driver);
        mod_tap_key2.release();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);
    }
}

} // namespace
