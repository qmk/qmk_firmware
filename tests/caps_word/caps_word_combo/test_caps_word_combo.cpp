// Copyright 2022 Google LLC
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

// Test Caps Word + Combos, with and without Auto Shift.

#include <algorithm>
#include <numeric>
#include <vector>

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

// Allow reports with no keys or only KC_LSFT.
// clang-format off
#define EXPECT_EMPTY_OR_LSFT(driver)              \
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf( \
            KeyboardReport(),                     \
            KeyboardReport(KC_LSFT))))
// clang-format on

using ::testing::AnyNumber;
using ::testing::AnyOf;
using ::testing::InSequence;
using ::testing::TestParamInfo;

extern "C" {
// Define some combos to use for the test, including overlapping combos and
// combos that chord tap-hold keys.
enum combo_events { AB_COMBO, BC_COMBO, AD_COMBO, DE_COMBO, FGHI_COMBO, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t ab_combo[] PROGMEM   = {KC_A, KC_B, COMBO_END};
const uint16_t bc_combo[] PROGMEM   = {KC_B, KC_C, COMBO_END};
const uint16_t ad_combo[] PROGMEM   = {KC_A, LCTL_T(KC_D), COMBO_END};
const uint16_t de_combo[] PROGMEM   = {LCTL_T(KC_D), LT(1, KC_E), COMBO_END};
const uint16_t fghi_combo[] PROGMEM = {KC_F, KC_G, KC_H, KC_I, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [AB_COMBO] = COMBO(ab_combo, KC_SPC),  // KC_A + KC_B = KC_SPC
    [BC_COMBO] = COMBO(bc_combo, KC_X),    // KC_B + KC_C = KC_X
    [AD_COMBO] = COMBO(ad_combo, KC_Y),    // KC_A + LCTL_T(KC_D) = KC_Y
    [DE_COMBO] = COMBO(de_combo, KC_Z),    // LCTL_T(KC_D) + LT(1, KC_E) = KC_Z
    [FGHI_COMBO] = COMBO(fghi_combo, KC_W) // KC_F + KC_G + KC_H + KC_I = KC_W
};
// clang-format on
} // extern "C"

namespace {

// To test combos thorougly, we test them with pressing the chord keys with
// a few different orders and timings.
struct TestParams {
    std::string name;
    bool        autoshift_on;

    static const std::string& GetName(const TestParamInfo<TestParams>& info) {
        return info.param.name;
    }
};

class CapsWord : public ::testing::WithParamInterface<TestParams>, public TestFixture {
   public:
    void SetUp() override {
        caps_word_off();
        if (GetParam().autoshift_on) {
            autoshift_enable();
        } else {
            autoshift_disable();
        }
    }
};

// Test pressing the keys in a combo with different orders and timings.
TEST_P(CapsWord, SingleCombo) {
    TestDriver driver;
    KeymapKey  key_b(0, 0, 1, KC_B);
    KeymapKey  key_c(0, 0, 2, KC_C);
    set_keymap({key_b, key_c});

    EXPECT_EMPTY_OR_LSFT(driver).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_X));

    caps_word_on();
    tap_combo({key_b, key_c});

    EXPECT_TRUE(is_caps_word_on());
    caps_word_off();

    VERIFY_AND_CLEAR(driver);
}

// Test a longer 4-key combo.
TEST_P(CapsWord, LongerCombo) {
    TestDriver driver;
    KeymapKey  key_f(0, 0, 0, KC_F);
    KeymapKey  key_g(0, 0, 1, KC_G);
    KeymapKey  key_h(0, 0, 2, KC_H);
    KeymapKey  key_i(0, 0, 3, KC_I);
    set_keymap({key_f, key_g, key_h, key_i});

    EXPECT_EMPTY_OR_LSFT(driver).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_W));

    caps_word_on();
    tap_combo({key_f, key_g, key_h, key_i});

    EXPECT_TRUE(is_caps_word_on());
    caps_word_off();

    VERIFY_AND_CLEAR(driver);
}

// Test with two overlapping combos on regular keys:
// KC_A + KC_B = KC_SPC,
// KC_B + KC_C = KC_X.
TEST_P(CapsWord, ComboRegularKeys) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 0, 1, KC_B);
    KeymapKey  key_c(0, 0, 2, KC_C);
    KeymapKey  key_1(0, 0, 3, KC_1);
    set_keymap({key_a, key_b, key_c, key_1});

    EXPECT_EMPTY_OR_LSFT(driver).Times(AnyNumber());
    { // Expect: "A, B, 1, X, 1, C, space, a".
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_LSFT, KC_B));
        EXPECT_REPORT(driver, (KC_1));
        EXPECT_REPORT(driver, (KC_LSFT, KC_X));
        EXPECT_REPORT(driver, (KC_1));
        EXPECT_REPORT(driver, (KC_LSFT, KC_C));
        EXPECT_REPORT(driver, (KC_SPC));
        EXPECT_REPORT(driver, (KC_A));
    }

    caps_word_on();
    tap_key(key_a);
    tap_key(key_b);
    tap_key(key_1);
    tap_combo({key_b, key_c}); // BC combo types "x".
    tap_key(key_1);
    tap_key(key_c);
    tap_combo({key_a, key_b}); // AB combo types space.
    tap_key(key_a);

    EXPECT_FALSE(is_caps_word_on());
    VERIFY_AND_CLEAR(driver);
}

// Test where combo chords involve tap-hold keys:
// KC_A + LCTL_T(KC_D) = KC_Y,
// LCTL_T(KC_D) + LT(1, KC_E) = KC_Z,
TEST_P(CapsWord, ComboModTapKey) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_modtap_d(0, 0, 1, LCTL_T(KC_D));
    KeymapKey  key_layertap_e(0, 0, 2, LT(1, KC_E));
    set_keymap({key_a, key_modtap_d, key_layertap_e});

    EXPECT_EMPTY_OR_LSFT(driver).Times(AnyNumber());
    { // Expect: "A, D, E, Y, Z".
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_LSFT, KC_D));
        EXPECT_REPORT(driver, (KC_LSFT, KC_E));
        EXPECT_REPORT(driver, (KC_LSFT, KC_Y));
        EXPECT_REPORT(driver, (KC_LSFT, KC_Z));
    }

    caps_word_on();
    tap_key(key_a);
    tap_key(key_modtap_d);
    tap_key(key_layertap_e);
    tap_combo({key_a, key_modtap_d});          // AD combo types "y".
    tap_combo({key_modtap_d, key_layertap_e}); // DE combo types "z".

    EXPECT_TRUE(is_caps_word_on());
    caps_word_off();

    VERIFY_AND_CLEAR(driver);
}

// clang-format off
INSTANTIATE_TEST_CASE_P(
    Combos,
    CapsWord,
    ::testing::Values(
        TestParams{"AutoshiftDisabled", false},
        TestParams{"AutoshiftEnabled", true}
        ),
    TestParams::GetName
    );
// clang-format on

} // namespace
