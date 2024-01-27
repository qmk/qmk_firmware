// Copyright 2023 Google LLC
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
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AnyOf;
using ::testing::InSequence;
using ::testing::TestParamInfo;

namespace {

struct ShiftKeyParams {
    std::string name;
    uint16_t    keycode;
    uint16_t    report_shift_code;

    static const std::string& GetName(const TestParamInfo<ShiftKeyParams>& info) {
        return info.param.name;
    }
};

class CapsWordInvertOnShift : public ::testing::WithParamInterface<ShiftKeyParams>, public TestFixture {
    void SetUp() override {
        caps_word_off();
    }
};

// With Caps Word on, type "A, 4, Shift(A, 4, A), A, Shift(A), 4".
TEST_P(CapsWordInvertOnShift, ShiftWithinWord) {
    TestDriver driver;
    KeymapKey  key_shift(0, 0, 0, GetParam().keycode);
    KeymapKey  key_a(0, 1, 0, KC_A);
    KeymapKey  key_4(0, 2, 0, KC_4);
    set_keymap({key_shift, key_a, key_4});

    // Allow any number of reports with no keys or only KC_LSFT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on

    { // Expect: "A4a$aAa4"
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_4));
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_REPORT(driver, (KC_LSFT, KC_4));
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_REPORT(driver, (KC_4));
    }

    caps_word_on();
    tap_keys(key_a, key_4); // Type "A, 4".

    key_shift.press(); // Type "Shift(A, 4, A)".
    run_one_scan_loop();
    tap_keys(key_a, key_4, key_a);
    key_shift.release();
    run_one_scan_loop();

    tap_key(key_a); // Type "A".

    key_shift.press(); // Type "Shift(A)".
    run_one_scan_loop();
    tap_key(key_a);
    key_shift.release();
    run_one_scan_loop();

    tap_key(key_4); // Type "4".

    VERIFY_AND_CLEAR(driver);
}

TEST_P(CapsWordInvertOnShift, ShiftHeldAtWordEnd) {
    TestDriver driver;
    KeymapKey  key_shift(0, 0, 0, GetParam().keycode);
    KeymapKey  key_a(0, 1, 0, KC_A);
    KeymapKey  key_slsh(0, 2, 0, KC_SLSH);
    set_keymap({key_shift, key_a, key_slsh});

    // Allow any number of reports with no keys or only KC_LSFT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_RSFT))))
        .Times(AnyNumber());
    // clang-format on

    { // Expect: "Aa?A"
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_REPORT(driver, (GetParam().report_shift_code, KC_SLSH));
        EXPECT_REPORT(driver, (GetParam().report_shift_code, KC_A));
    }

    caps_word_on();
    tap_key(key_a);

    key_shift.press(); // Press Shift.
    run_one_scan_loop();

    EXPECT_EQ(get_mods(), 0);

    tap_key(key_a);
    tap_key(key_slsh); // Tap '/' key, which is word breaking, ending Caps Word.

    EXPECT_FALSE(is_caps_word_on());
    EXPECT_EQ(get_mods(), MOD_BIT(GetParam().report_shift_code));

    tap_key(key_a);
    key_shift.release(); // Release Shift.
    run_one_scan_loop();

    EXPECT_EQ(get_mods(), 0);
    VERIFY_AND_CLEAR(driver);
}

TEST_P(CapsWordInvertOnShift, TwoShiftsHeld) {
    TestDriver driver;
    KeymapKey  key_shift1(0, 0, 0, GetParam().keycode);
    KeymapKey  key_shift2(0, 1, 0, GetParam().report_shift_code);
    KeymapKey  key_a(0, 2, 0, KC_A);
    KeymapKey  key_slsh(0, 3, 0, KC_SLSH);
    set_keymap({key_shift1, key_shift2, key_a, key_slsh});

    // Allow any number of reports with no keys or only KC_LSFT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_RSFT))))
        .Times(AnyNumber());
    // clang-format on

    { // Expect: "Aa?a"
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_REPORT(driver, (GetParam().report_shift_code, KC_SLSH));
        EXPECT_REPORT(driver, (KC_A));
    }

    caps_word_on();
    tap_key(key_a);

    key_shift1.press(); // Press shift1.
    run_one_scan_loop();

    EXPECT_EQ(get_mods(), 0);

    tap_key(key_a);
    tap_key(key_slsh); // Tap '/' key, which is word breaking, ending Caps Word.

    EXPECT_FALSE(is_caps_word_on());
    EXPECT_EQ(get_mods(), MOD_BIT(GetParam().report_shift_code));

    key_shift2.press(); // Press shift2.
    run_one_scan_loop();

    EXPECT_EQ(get_mods(), MOD_BIT(GetParam().report_shift_code));

    key_shift1.release(); // Release shift1.
    run_one_scan_loop();

    EXPECT_EQ(get_mods(), 0);
    tap_key(key_a);

    key_shift2.release(); // Release shift2.
    run_one_scan_loop();

    EXPECT_EQ(get_mods(), 0);
    VERIFY_AND_CLEAR(driver);
}

// clang-format off
INSTANTIATE_TEST_CASE_P(
    Shifts,
    CapsWordInvertOnShift,
    ::testing::Values(
        ShiftKeyParams{"KC_LSFT", KC_LSFT, KC_LSFT},
        ShiftKeyParams{"KC_RSFT", KC_RSFT, KC_RSFT},
        ShiftKeyParams{"LSFT_T", LSFT_T(KC_A), KC_LSFT},
        ShiftKeyParams{"RSFT_T", RSFT_T(KC_A), KC_RSFT},
        ShiftKeyParams{"OSM_LSFT", OSM(MOD_LSFT), KC_LSFT},
        ShiftKeyParams{"OSM_RSFT", OSM(MOD_RSFT), KC_RSFT}
      ),
    ShiftKeyParams::GetName
    );
// clang-format on

} // namespace
