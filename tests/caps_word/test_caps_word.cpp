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

bool press_user_default(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

uint16_t passed_keycode;
bool     press_user_save_passed_keycode(uint16_t keycode) {
    passed_keycode = keycode;
    return true;
}

bool (*press_user_fun)(uint16_t) = press_user_default;

extern "C" {
bool caps_word_press_user(uint16_t keycode) {
    return press_user_fun(keycode);
}
} // extern "C"

class CapsWord : public TestFixture {
   public:
    void SetUp() override {
        caps_word_off();
        press_user_fun = press_user_default;
    }
};

// Tests caps_word_on(), _off(), and _toggle() functions.
TEST_F(CapsWord, OnOffToggleFuns) {
    TestDriver driver;

    EXPECT_EQ(is_caps_word_on(), false);

    caps_word_on();
    EXPECT_EQ(is_caps_word_on(), true);
    caps_word_on();
    EXPECT_EQ(is_caps_word_on(), true);

    caps_word_off();
    EXPECT_EQ(is_caps_word_on(), false);
    caps_word_off();
    EXPECT_EQ(is_caps_word_on(), false);

    caps_word_toggle();
    EXPECT_EQ(is_caps_word_on(), true);
    caps_word_toggle();
    EXPECT_EQ(is_caps_word_on(), false);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests the default `caps_word_press_user()` function.
TEST_F(CapsWord, DefaultCapsWordPressUserFun) {
    // Spot check some keycodes that continue Caps Word, with shift applied.
    for (uint16_t keycode : {KC_A, KC_B, KC_Z, KC_MINS}) {
        SCOPED_TRACE("keycode: " + testing::PrintToString(keycode));
        clear_weak_mods();
        EXPECT_TRUE(caps_word_press_user(keycode));
        EXPECT_EQ(get_weak_mods(), MOD_BIT(KC_LSFT));
    }

    // Some keycodes that continue Caps Word, without shifting.
    for (uint16_t keycode : {KC_1, KC_9, KC_0, KC_BSPC, KC_DEL}) {
        SCOPED_TRACE("keycode: " + testing::PrintToString(keycode));
        clear_weak_mods();
        EXPECT_TRUE(caps_word_press_user(keycode));
        EXPECT_EQ(get_weak_mods(), 0);
    }

    // Some keycodes that turn off Caps Word.
    for (uint16_t keycode : {KC_SPC, KC_DOT, KC_COMM, KC_TAB, KC_ESC, KC_ENT}) {
        SCOPED_TRACE("keycode: " + testing::PrintToString(keycode));
        EXPECT_FALSE(caps_word_press_user(keycode));
    }
}

// Tests that `CAPSWRD` key toggles Caps Word.
TEST_F(CapsWord, CapswrdKey) {
    TestDriver driver;
    KeymapKey  key_capswrd(0, 0, 0, CAPSWRD);
    set_keymap({key_capswrd});

    // No keyboard reports should be sent.
    EXPECT_NO_REPORT(driver);

    tap_key(key_capswrd); // Tap the CAPSWRD key.
    EXPECT_EQ(is_caps_word_on(), true);

    tap_key(key_capswrd); // Tap the CAPSWRD key again.
    EXPECT_EQ(is_caps_word_on(), false);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests that being idle for CAPS_WORD_IDLE_TIMEOUT turns off Caps Word.
TEST_F(CapsWord, IdleTimeout) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    set_keymap({key_a});

    // Allow any number of reports with no keys or only KC_LSFT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on

    // Expect "Shift+A".
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));

    // Turn on Caps Word and tap "A".
    caps_word_on();
    tap_key(key_a);

    testing::Mock::VerifyAndClearExpectations(&driver);

    idle_for(CAPS_WORD_IDLE_TIMEOUT);
    run_one_scan_loop();

    // Caps Word should be off and mods should be clear.
    EXPECT_EQ(is_caps_word_on(), false);
    EXPECT_EQ(get_mods() | get_weak_mods(), 0);

    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    // Expect unshifted "A".
    EXPECT_REPORT(driver, (KC_A));
    tap_key(key_a);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests that typing "A, 4, A, 4" produces "Shift+A, 4, Shift+A, 4".
TEST_F(CapsWord, ShiftsLettersButNotDigits) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_4(0, 1, 0, KC_4);
    set_keymap({key_a, key_4});

    // Allow any number of reports with no keys or only KC_LSFT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on

    { // Expect: "Shift+A, 4, Shift+A, 4".
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_4));
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_4));
    }

    // Turn on Caps Word and tap "A, 4, A, 4".
    caps_word_on();
    tap_keys(key_a, key_4, key_a, key_4);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests that typing "A, Space, A" produces "Shift+A, Space, A".
TEST_F(CapsWord, SpaceTurnsOffCapsWord) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_spc(0, 1, 0, KC_SPC);
    set_keymap({key_a, key_spc});

    // Allow any number of reports with no keys or only KC_LSFT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on

    { // Expect: "Shift+A, Space, A".
        InSequence seq;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_SPC));
        EXPECT_REPORT(driver, (KC_A));
    }

    // Turn on Caps Word and tap "A, Space, A".
    caps_word_on();
    tap_keys(key_a, key_spc, key_a);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests that typing "AltGr + A" produces "Shift + AltGr + A".
TEST_F(CapsWord, ShiftsAltGrSymbols) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_altgr(0, 1, 0, KC_RALT);
    set_keymap({key_a, key_altgr});

    // Allow any number of reports with no keys or only modifiers.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_RALT),
                KeyboardReport(KC_LSFT, KC_RALT))))
        .Times(AnyNumber());
    // Expect "Shift + AltGr + A".
    EXPECT_REPORT(driver, (KC_LSFT, KC_RALT, KC_A));
    // clang-format on

    // Turn on Caps Word and type "AltGr + A".
    caps_word_on();

    key_altgr.press();
    run_one_scan_loop();
    tap_key(key_a);
    run_one_scan_loop();
    key_altgr.release();

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests typing "AltGr + A" using a mod-tap key.
TEST_F(CapsWord, ShiftsModTapAltGrSymbols) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_altgr_t(0, 1, 0, RALT_T(KC_B));
    set_keymap({key_a, key_altgr_t});

    // Allow any number of reports with no keys or only modifiers.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_RALT),
                KeyboardReport(KC_LSFT, KC_RALT))))
        .Times(AnyNumber());
    // Expect "Shift + AltGr + A".
    EXPECT_REPORT(driver, (KC_LSFT, KC_RALT, KC_A));
    // clang-format on

    // Turn on Caps Word and type "AltGr + A".
    caps_word_on();

    key_altgr_t.press();
    idle_for(TAPPING_TERM + 1);
    tap_key(key_a);
    run_one_scan_loop();
    key_altgr_t.release();

    EXPECT_TRUE(is_caps_word_on());
    testing::Mock::VerifyAndClearExpectations(&driver);
}

struct CapsWordPressUserParams {
    std::string name;
    uint16_t    keycode;
    uint16_t    delay_ms;
    uint16_t    expected_passed_keycode;
    bool        continues_caps_word;

    static const std::string& GetName(const TestParamInfo<CapsWordPressUserParams>& info) {
        return info.param.name;
    }
};

class CapsWordPressUser : public ::testing::WithParamInterface<CapsWordPressUserParams>, public CapsWord {
    void SetUp() override {
        caps_word_on();
        passed_keycode = KC_NO;
        press_user_fun = press_user_save_passed_keycode;
    }
};

// Tests keycodes passed to caps_word_press_user() function for various keys.
TEST_P(CapsWordPressUser, KeyCode) {
    TestDriver driver;
    KeymapKey  key(0, 0, 0, GetParam().keycode);
    set_keymap({key});

    EXPECT_ANY_REPORT(driver).Times(AnyNumber());
    tap_key(key, GetParam().delay_ms);

    EXPECT_EQ(passed_keycode, GetParam().expected_passed_keycode);
    EXPECT_EQ(is_caps_word_on(), GetParam().continues_caps_word);
    clear_oneshot_mods();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

const uint16_t LT_1_KC_A = LT(1, KC_A);
// clang-format off
INSTANTIATE_TEST_CASE_P(
    PressUser,
    CapsWordPressUser,
    ::testing::Values(
        CapsWordPressUserParams{
            "KC_A", KC_A, 1, KC_A, true},
        CapsWordPressUserParams{
            "KC_HASH", KC_HASH, 1, KC_HASH, true},
        CapsWordPressUserParams{
            "KC_LSFT", KC_LSFT, 1, KC_LSFT, true},
        CapsWordPressUserParams{
            "KC_RSFT", KC_RSFT, 1, KC_RSFT, true},
        CapsWordPressUserParams{
            "LSFT_T_tapped", LSFT_T(KC_A), 1, KC_A, true},
        CapsWordPressUserParams{
            "LSFT_T_held", LSFT_T(KC_A), TAPPING_TERM + 1, KC_LSFT, true},
        CapsWordPressUserParams{
            "RSFT_T_held", RSFT_T(KC_A), TAPPING_TERM + 1, KC_RSFT, true},
        CapsWordPressUserParams{
            "RSA_T_held", RSA_T(KC_A), TAPPING_TERM + 1, RSFT(KC_RALT), true},
        // Holding a mod-tap other than Shift or AltGr stops Caps Word.
        CapsWordPressUserParams{
            "LCTL_T_held", LCTL_T(KC_A), TAPPING_TERM + 1, KC_NO, false},
        CapsWordPressUserParams{
            "LALT_T_held", LALT_T(KC_A), TAPPING_TERM + 1, KC_NO, false},
        CapsWordPressUserParams{
            "LGUI_T_held", LGUI_T(KC_A), TAPPING_TERM + 1, KC_NO, false},
        // Layer keys are ignored and continue Caps Word.
        CapsWordPressUserParams{
            "MO", MO(1), 1, KC_NO, true},
        CapsWordPressUserParams{
            "TO", TO(1), 1, KC_NO, true},
        CapsWordPressUserParams{
            "TG", TG(1), 1, KC_NO, true},
        CapsWordPressUserParams{
            "TT", TT(1), 1, KC_NO, true},
        CapsWordPressUserParams{
            "OSL", OSL(1), 1, KC_NO, true},
        CapsWordPressUserParams{
            "LT_held", LT_1_KC_A, TAPPING_TERM + 1, KC_NO, true},
        // AltGr keys are ignored and continue Caps Word.
        CapsWordPressUserParams{
            "KC_RALT", KC_RALT, 1, KC_NO, true},
        CapsWordPressUserParams{
            "OSM_MOD_RALT", OSM(MOD_RALT), 1, KC_NO, true},
        CapsWordPressUserParams{
            "RALT_T_held", RALT_T(KC_A), TAPPING_TERM + 1, KC_NO, true}
        ),
    CapsWordPressUserParams::GetName
    );
// clang-format on

struct CapsWordBothShiftsParams {
    std::string name;
    uint16_t    left_shift_keycode;
    uint16_t    right_shift_keycode;

    static const std::string& GetName(const TestParamInfo<CapsWordBothShiftsParams>& info) {
        return info.param.name;
    }
};

// Tests the BOTH_SHIFTS_TURNS_ON_CAPS_WORD method to turn on Caps Word.
class CapsWordBothShifts : public ::testing::WithParamInterface<CapsWordBothShiftsParams>, public CapsWord {};

// Pressing shifts as "Left down, Right down, Left up, Right up".
TEST_P(CapsWordBothShifts, PressLRLR) {
    TestDriver driver;
    KeymapKey  left_shift(0, 0, 0, GetParam().left_shift_keycode);
    KeymapKey  right_shift(0, 1, 0, GetParam().right_shift_keycode);
    set_keymap({left_shift, right_shift});

    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_RSFT),
                KeyboardReport(KC_LSFT, KC_RSFT))))
        .Times(AnyNumber());
    // clang-format on

    EXPECT_EQ(is_caps_word_on(), false);

    left_shift.press(); // Press both shifts.
    run_one_scan_loop();
    right_shift.press();

    // For mod-tap and Space Cadet keys, wait for the tapping term.
    if (left_shift.code == LSFT_T(KC_A) || left_shift.code == KC_LSPO) {
        idle_for(TAPPING_TERM);
    }

    run_one_scan_loop();
    left_shift.release(); // Release both.
    run_one_scan_loop();
    right_shift.release();
    run_one_scan_loop();

    EXPECT_EQ(is_caps_word_on(), true);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Pressing shifts as "Left down, Right down, Right up, Left up".
TEST_P(CapsWordBothShifts, PressLRRL) {
    TestDriver driver;
    KeymapKey  left_shift(0, 0, 0, GetParam().left_shift_keycode);
    KeymapKey  right_shift(0, 1, 0, GetParam().right_shift_keycode);
    set_keymap({left_shift, right_shift});

    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_RSFT),
                KeyboardReport(KC_LSFT, KC_RSFT))))
        .Times(AnyNumber());
    // clang-format on

    EXPECT_EQ(is_caps_word_on(), false);

    left_shift.press(); // Press both shifts.
    run_one_scan_loop();
    right_shift.press();

    if (left_shift.code == LSFT_T(KC_A) || left_shift.code == KC_LSPO) {
        idle_for(TAPPING_TERM);
    }
    run_one_scan_loop();

    right_shift.release(); // Release both.
    run_one_scan_loop();
    left_shift.release();
    run_one_scan_loop();

    EXPECT_EQ(is_caps_word_on(), true);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// clang-format off
INSTANTIATE_TEST_CASE_P(
    ShiftPairs,
    CapsWordBothShifts,
    ::testing::Values(
        CapsWordBothShiftsParams{
            "PlainShifts", KC_LSFT, KC_RSFT},
        CapsWordBothShiftsParams{
            "OneshotShifts", OSM(MOD_LSFT), OSM(MOD_RSFT)},
        CapsWordBothShiftsParams{
            "SpaceCadetShifts", KC_LSPO, KC_RSPC},
        CapsWordBothShiftsParams{
            "ModTapShifts", LSFT_T(KC_A), RSFT_T(KC_B)}
        ),
    CapsWordBothShiftsParams::GetName
    );
// clang-format on

struct CapsWordDoubleTapShiftParams {
    std::string name;
    uint16_t    left_shift_keycode;

    static const std::string& GetName(const TestParamInfo<CapsWordDoubleTapShiftParams>& info) {
        return info.param.name;
    }
};

// Tests the DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD method to turn on Caps Word.
class CapsWordDoubleTapShift : public ::testing::WithParamInterface<CapsWordDoubleTapShiftParams>, public CapsWord {};

// Tests that double tapping activates Caps Word.
TEST_P(CapsWordDoubleTapShift, Activation) {
    TestDriver driver;
    KeymapKey  left_shift(0, 0, 0, GetParam().left_shift_keycode);
    set_keymap({left_shift});

    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on

    EXPECT_EQ(is_caps_word_on(), false);

    // Tapping shift twice within the tapping term turns on Caps Word.
    tap_key(left_shift);
    idle_for(TAPPING_TERM - 10);
    tap_key(left_shift);

    EXPECT_EQ(is_caps_word_on(), true);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Double tap doesn't count if another key is pressed between the taps.
TEST_P(CapsWordDoubleTapShift, Interrupted) {
    TestDriver driver;
    KeymapKey  left_shift(0, 0, 0, GetParam().left_shift_keycode);
    KeymapKey  key_a(0, 1, 0, KC_A);
    set_keymap({left_shift, key_a});

    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LSFT, KC_A))))
        .Times(AnyNumber());
    // clang-format on

    left_shift.press();
    run_one_scan_loop();

    tap_key(key_a); // 'A' key interrupts the double tap.

    left_shift.release();
    run_one_scan_loop();

    idle_for(TAPPING_TERM - 10);
    tap_key(left_shift);

    EXPECT_EQ(is_caps_word_on(), false); // Caps Word is still off.
    clear_oneshot_mods();

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Double tap doesn't count if taps are more than tapping term apart.
TEST_P(CapsWordDoubleTapShift, SlowTaps) {
    TestDriver driver;
    KeymapKey  left_shift(0, 0, 0, GetParam().left_shift_keycode);
    set_keymap({left_shift});

    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on

    tap_key(left_shift);
    idle_for(TAPPING_TERM + 1);
    tap_key(left_shift);

    EXPECT_EQ(is_caps_word_on(), false); // Caps Word is still off.
    clear_oneshot_mods();

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// clang-format off
INSTANTIATE_TEST_CASE_P(
    Shifts,
    CapsWordDoubleTapShift,
    ::testing::Values(
        CapsWordDoubleTapShiftParams{"PlainShift", KC_LSFT},
        CapsWordDoubleTapShiftParams{"OneshotShift", OSM(MOD_LSFT)}
        ),
    CapsWordDoubleTapShiftParams::GetName
    );
// clang-format on

} // namespace
