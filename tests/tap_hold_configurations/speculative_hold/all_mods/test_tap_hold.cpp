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

// Gets the unpacked 8-bit mods corresponding to a given mod-tap keycode.
uint8_t unpack_mod_tap_mods(uint16_t keycode) {
    const uint8_t mods5 = QK_MOD_TAP_GET_MODS(keycode);
    return (mods5 & 0x10) != 0 ? (mods5 << 4) : mods5;
}

bool get_speculative_hold_all_mods(uint16_t keycode, keyrecord_t *record) {
    return true; // Enable Speculative Hold for all mod-tap keys.
}

// Indirection so that get_speculative_hold() can be
// replaced with other functions in the test cases below.
std::function<bool(uint16_t, keyrecord_t *)> get_speculative_hold_fun = get_speculative_hold_all_mods;

extern "C" bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
    return get_speculative_hold_fun(keycode, record);
}

class SpeculativeHoldAllMods : public TestFixture {
   public:
    void SetUp() override {
        get_speculative_hold_fun = get_speculative_hold_all_mods;
    }
};

TEST_F(SpeculativeHoldAllMods, tap_mod_tap_neutralized) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, GUI_T(KC_P));

    set_keymap({mod_tap_key});

    // Press mod-tap-hold key. Mod is held speculatively.
    EXPECT_REPORT(driver, (KC_LGUI));
    mod_tap_key.press();
    idle_for(10);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key. Speculative mod is neutralized and canceled.
    EXPECT_REPORT(driver, (KC_LGUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LGUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Idle for tapping term of mod tap hold key.
    idle_for(TAPPING_TERM - 10);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldAllMods, hold_two_mod_taps) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, LCTL_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, 2, 0, RALT_T(KC_B));

    set_keymap({mod_tap_key1, mod_tap_key2});

    // Press first mod-tap key.
    EXPECT_REPORT(driver, (KC_LCTL));
    mod_tap_key1.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), MOD_BIT_LCTRL);

    // Press second mod-tap key.
    EXPECT_REPORT(driver, (KC_LCTL, KC_RALT));
    mod_tap_key2.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), MOD_BIT_LCTRL | MOD_BIT_RALT);

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);
    EXPECT_EQ(get_speculative_mods(), 0);
    EXPECT_EQ(get_mods(), MOD_BIT_LCTRL | MOD_BIT_RALT);

    // Release first mod-tap key.
    EXPECT_REPORT(driver, (KC_RALT));
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release second mod-tap key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldAllMods, two_mod_taps_same_mods) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, GUI_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, 2, 0, GUI_T(KC_B));

    set_keymap({mod_tap_key1, mod_tap_key2});

    // Press first mod-tap key.
    EXPECT_REPORT(driver, (KC_LGUI));
    mod_tap_key1.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Tap second mod-tap key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key2.press();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release first mod-tap key.
    EXPECT_REPORT(driver, (KC_LGUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LGUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_B));
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldAllMods, respects_get_speculative_hold_callback) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 0, 0, LSFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, 1, 0, LSFT_T(KC_B));
    auto       mod_tap_key3 = KeymapKey(0, 2, 0, LCTL_T(KC_C));
    auto       mod_tap_key4 = KeymapKey(0, 3, 0, LCTL_T(KC_D));
    auto       mod_tap_key5 = KeymapKey(0, 4, 0, RSFT_T(KC_E));
    auto       mod_tap_key6 = KeymapKey(0, 5, 0, RSFT_T(KC_F));

    set_keymap({mod_tap_key1, mod_tap_key2, mod_tap_key3, mod_tap_key4, mod_tap_key5, mod_tap_key6});

    // Enable Speculative Hold selectively for some of the keys.
    get_speculative_hold_fun = [](uint16_t keycode, keyrecord_t *record) {
        switch (keycode) {
            case LSFT_T(KC_B):
            case LCTL_T(KC_D):
            case RSFT_T(KC_F):
                return true;
        }
        return false;
    };

    for (KeymapKey *mod_tap_key : {&mod_tap_key2, &mod_tap_key4, &mod_tap_key6}) {
        SCOPED_TRACE(std::string("mod_tap_key = ") + mod_tap_key->name);
        const uint8_t mods = unpack_mod_tap_mods(mod_tap_key->code);

        // Long press and release mod_tap_key.
        // For these keys where Speculative Hold is enabled, then the mod should
        // activate immediately on keydown.
        EXPECT_REPORT(driver, (KC_LCTL + biton(mods)));
        mod_tap_key->press();
        run_one_scan_loop();
        EXPECT_EQ(get_speculative_mods(), mods);
        EXPECT_EQ(get_mods(), 0);
        VERIFY_AND_CLEAR(driver);

        EXPECT_NO_REPORT(driver);
        idle_for(TAPPING_TERM + 1);
        EXPECT_EQ(get_speculative_mods(), 0);
        EXPECT_EQ(get_mods(), mods);
        VERIFY_AND_CLEAR(driver);

        EXPECT_EMPTY_REPORT(driver);
        mod_tap_key->release();
        idle_for(TAPPING_TERM + 1);
        EXPECT_EQ(get_speculative_mods(), 0);
        EXPECT_EQ(get_mods(), 0);
        VERIFY_AND_CLEAR(driver);
    }

    for (KeymapKey *mod_tap_key : {&mod_tap_key1, &mod_tap_key3, &mod_tap_key5}) {
        SCOPED_TRACE(std::string("mod_tap_key = ") + mod_tap_key->name);
        const uint8_t mods = unpack_mod_tap_mods(mod_tap_key->code);

        // Long press and release mod_tap_key.
        // For these keys where Speculative Hold is disabled, the mod should
        // activate when the key has settled after the tapping term.
        EXPECT_NO_REPORT(driver);
        mod_tap_key->press();
        run_one_scan_loop();
        EXPECT_EQ(get_speculative_mods(), 0);
        EXPECT_EQ(get_mods(), 0);
        VERIFY_AND_CLEAR(driver);

        EXPECT_REPORT(driver, (KC_LCTL + biton(mods)));
        idle_for(TAPPING_TERM + 1);
        EXPECT_EQ(get_speculative_mods(), 0);
        EXPECT_EQ(get_mods(), mods);
        VERIFY_AND_CLEAR(driver);

        EXPECT_EMPTY_REPORT(driver);
        mod_tap_key->release();
        idle_for(TAPPING_TERM + 1);
        EXPECT_EQ(get_speculative_mods(), 0);
        EXPECT_EQ(get_mods(), 0);
        VERIFY_AND_CLEAR(driver);
    }
}

TEST_F(SpeculativeHoldAllMods, respects_magic_mod_config) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, CTL_T(KC_P));

    set_keymap({mod_tap_key});

    keymap_config.swap_lctl_lgui = true;

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LGUI));
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LGUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    EXPECT_REPORT(driver, (KC_LGUI));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    keymap_config.swap_lctl_lgui = false;

    // Press mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LCTL));
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
}

TEST_F(SpeculativeHoldAllMods, tap_a_mod_tap_key_while_another_mod_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       first_mod_tap_key  = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       second_mod_tap_key = KeymapKey(0, 2, 0, RSFT_T(KC_A));

    set_keymap({first_mod_tap_key, second_mod_tap_key});

    // Press first mod-tap-hold key.
    EXPECT_REPORT(driver, (KC_LSFT));
    first_mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press second tap-hold key.
    EXPECT_REPORT(driver, (KC_LSFT, KC_RSFT));
    second_mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release second tap-hold key.
    EXPECT_NO_REPORT(driver);
    second_mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release first mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    first_mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(SpeculativeHoldAllMods, tap_mod_tap_key_two_times) {
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

} // namespace
