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

#include <functional>

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using ::testing::AnyNumber;
using ::testing::AnyOf;
using ::testing::InSequence;

#define FOO_MACRO SAFE_RANGE

namespace {

bool process_record_user_default(uint16_t keycode, keyrecord_t* record) {
    return true;
}

bool remember_last_key_user_default(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    return true;
}

// Indirection so that process_record_user() and remember_last_key_user()
// can be replaced with other functions in the test cases below.
std::function<bool(uint16_t, keyrecord_t*)>           process_record_user_fun    = process_record_user_default;
std::function<bool(uint16_t, keyrecord_t*, uint8_t*)> remember_last_key_user_fun = remember_last_key_user_default;

extern "C" bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    return process_record_user_fun(keycode, record);
}
extern "C" bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    return remember_last_key_user_fun(keycode, record, remembered_mods);
}

class RepeatKey : public TestFixture {
   public:
    bool process_record_user_was_called_;

    void SetUp() override {
        autoshift_disable();
        process_record_user_fun    = process_record_user_default;
        remember_last_key_user_fun = remember_last_key_user_default;
    }

    void ExpectProcessRecordUserCalledWith(bool expected_press, uint16_t expected_keycode, int8_t expected_repeat_key_count) {
        process_record_user_was_called_ = false;
        process_record_user_fun         = [=](uint16_t keycode, keyrecord_t* record) {
            EXPECT_EQ(record->event.pressed, expected_press);
            EXPECT_KEYCODE_EQ(keycode, expected_keycode);
            EXPECT_EQ(get_repeat_key_count(), expected_repeat_key_count);
            // Tests below use this to verify process_record_user() was called.
            process_record_user_was_called_ = true;
            return true;
        };
    }

    // Expects that the characters of `s` are sent.
    // NOTE: This implementation is limited to chars a-z, A-Z.
    void ExpectString(TestDriver& driver, const std::string& s) {
        InSequence seq;
        for (int c : s) {
            switch (c) {
                case 'a' ... 'z': { // Lowercase letter.
                    uint16_t keycode = c - ('a' - KC_A);
                    EXPECT_REPORT(driver, (keycode));
                } break;

                case 'A' ... 'Z': { // Capital letter = KC_LSFT + letter key.
                    uint16_t keycode = c - ('A' - KC_A);
                    EXPECT_REPORT(driver, (KC_LSFT, keycode));
                } break;
            }
        }
    }
};

// Tests that "A, Repeat, Repeat, B, Repeat" produces "aaabb".
TEST_F(RepeatKey, Basic) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_repeat(0, 2, 0, QK_REP);
    set_keymap({key_a, key_b, key_repeat});

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    ExpectString(driver, "aaabb");

    // When KC_A is pressed, process_record_user() should be called
    // with a press event with keycode == KC_A and repeat_key_count() == 0.
    ExpectProcessRecordUserCalledWith(true, KC_A, 0);
    key_a.press();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    // After pressing A, the keycode of the key to be repeated is KC_A.
    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_A);
    EXPECT_EQ(get_last_mods(), 0);

    // Expect the corresponding release event when A is released.
    ExpectProcessRecordUserCalledWith(false, KC_A, 0);
    key_a.release();
    run_one_scan_loop();

    for (int n = 1; n <= 2; ++n) { // Tap the Repeat Key twice.
        // When Repeat is pressed, process_record_user() should be called with a
        // press event with keycode == KC_A and repeat_key_count() == n.
        ExpectProcessRecordUserCalledWith(true, KC_A, n);
        key_repeat.press(); // Press the Repeat Key.
        run_one_scan_loop();
        EXPECT_TRUE(process_record_user_was_called_);

        // Expect the corresponding release event.
        ExpectProcessRecordUserCalledWith(false, KC_A, n);
        key_repeat.release(); // Release the Repeat Key.
        run_one_scan_loop();
        EXPECT_TRUE(process_record_user_was_called_);
    }

    process_record_user_fun = process_record_user_default;
    tap_key(key_b);
    // Then after tapping key_b, the keycode to be repeated becomes KC_B.
    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_B);

    tap_key(key_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests repeating a macro. The keycode FOO_MACRO sends "foo" when pressed. The
// test taps "FOO_MACRO, Repeat, Repeat", producing "foofoofoo".
TEST_F(RepeatKey, Macro) {
    TestDriver driver;
    KeymapKey  key_foo(0, 0, 0, FOO_MACRO);
    KeymapKey  key_repeat(0, 1, 0, QK_REP);
    set_keymap({key_foo, key_repeat});

    // Define process_record_user() to handle FOO_MACRO.
    process_record_user_fun = [](uint16_t keycode, keyrecord_t* record) {
        switch (keycode) {
            case FOO_MACRO:
                if (record->event.pressed) {
                    SEND_STRING("foo");
                }
                break;
        }
        return true;
    };

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    ExpectString(driver, "foofoofoo");

    tap_key(key_foo);

    EXPECT_KEYCODE_EQ(get_last_keycode(), FOO_MACRO);

    tap_keys(key_repeat, key_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests a macro with customized repeat behavior: "foo" is sent normally, "bar"
// on the first repeat, and "baz" on subsequent repeats. The test taps
// "FOO_MACRO, Repeat, Repeat, FOO_MACRO, Repeat", producing "foobarbazfoobar".
TEST_F(RepeatKey, MacroCustomRepeat) {
    TestDriver driver;
    KeymapKey  key_foo(0, 0, 0, FOO_MACRO);
    KeymapKey  key_repeat(0, 1, 0, QK_REP);
    set_keymap({key_foo, key_repeat});

    process_record_user_fun = [](uint16_t keycode, keyrecord_t* record) {
        switch (keycode) {
            case FOO_MACRO:
                if (record->event.pressed) {
                    switch (get_repeat_key_count()) {
                        case 0: // When pressed normally.
                            SEND_STRING("foo");
                            break;
                        case 1: // On first repeat.
                            SEND_STRING("bar");
                            break;
                        default: // On subsequent repeats.
                            SEND_STRING("baz");
                            break;
                    }
                }
                break;
        }
        return true;
    };

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    ExpectString(driver, "foobarbazfoobar");

    tap_key(key_foo);

    EXPECT_KEYCODE_EQ(get_last_keycode(), FOO_MACRO);

    tap_keys(key_repeat, key_repeat, key_foo, key_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests repeating keys on different layers. A 2-layer keymap is defined:
//   Layer 0:   QK_REP , MO(1)  , KC_A
//   Layer 1:   KC_TRNS, KC_TRNS, KC_B
// The test does the following, which should produce "bbbaaa":
// 1. Hold MO(1), switching to layer 1.
// 2. Tap KC_B on layer 1.
// 3. Release MO(1), switching back to layer 0.
// 4. Tap Repeat twice.
// 5. Tap KC_A on layer 0.
// 6. Hold MO(1), switching to layer 1.
// 7. Tap Repeat twice.
TEST_F(RepeatKey, AcrossLayers) {
    TestDriver driver;
    KeymapKey  key_repeat(0, 0, 0, QK_REP);
    KeymapKey  key_mo_1(0, 1, 0, MO(1));
    KeymapKey  regular_key(0, 2, 0, KC_A);
    set_keymap({// Layer 0.
                key_repeat, key_mo_1, regular_key,
                // Layer 1.
                KeymapKey{1, 0, 0, KC_TRNS}, KeymapKey{1, 1, 0, KC_TRNS}, KeymapKey{1, 2, 0, KC_B}});

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    ExpectString(driver, "bbbaaa");

    key_mo_1.press(); // Hold the MO(1) layer key.
    run_one_scan_loop();
    tap_key(regular_key); // Taps the KC_B key on layer 1.

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_B);

    key_mo_1.release(); // Release the layer key.
    run_one_scan_loop();
    tap_keys(key_repeat, key_repeat);
    tap_key(regular_key); // Taps the KC_A key on layer 0.

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_A);

    key_mo_1.press(); // Hold the layer key.
    run_one_scan_loop();
    tap_keys(key_repeat, key_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests "A(down), Repeat(down), A(up), Repeat(up), Repeat" produces "aaa".
TEST_F(RepeatKey, RollingToRepeat) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_repeat(0, 1, 0, QK_REP);
    set_keymap({key_a, key_repeat});

    {
        InSequence seq;
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_EMPTY_REPORT(driver);
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_EMPTY_REPORT(driver);
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_EMPTY_REPORT(driver);
    }

    // Perform a rolled press from A to Repeat.

    ExpectProcessRecordUserCalledWith(true, KC_A, 0);
    key_a.press();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(true, KC_A, 1);
    key_repeat.press(); // Press the Repeat Key.
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(false, KC_A, 0);
    key_a.release();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(false, KC_A, 1);
    key_repeat.release(); // Release the Repeat Key.
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    process_record_user_fun = process_record_user_default;
    tap_key(key_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests "A, Repeat(down), B(down), Repeat(up), B(up), Repeat" produces "aabb".
TEST_F(RepeatKey, RollingFromRepeat) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_repeat(0, 2, 0, QK_REP);
    set_keymap({key_a, key_b, key_repeat});

    {
        InSequence seq;
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_EMPTY_REPORT(driver);
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_REPORT(driver, (KC_A, KC_B));
        EXPECT_REPORT(driver, (KC_B));
        EXPECT_EMPTY_REPORT(driver);
        EXPECT_REPORT(driver, (KC_B));
        EXPECT_EMPTY_REPORT(driver);
    }

    tap_key(key_a);

    // Perform a rolled press from Repeat to B.

    ExpectProcessRecordUserCalledWith(true, KC_A, 1);
    key_repeat.press(); // Press the Repeat Key.
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(true, KC_B, 0);
    key_b.press();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_B);

    ExpectProcessRecordUserCalledWith(false, KC_A, 1);
    key_repeat.release(); // Release the Repeat Key.
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(false, KC_B, 0);
    key_b.release();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    process_record_user_fun = process_record_user_default;
    tap_key(key_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests Repeat Key with a modifier, types "AltGr+C, Repeat, Repeat, C".
TEST_F(RepeatKey, RecallMods) {
    TestDriver driver;
    KeymapKey  key_c(0, 0, 0, KC_C);
    KeymapKey  key_altgr(0, 1, 0, KC_RALT);
    KeymapKey  key_repeat(0, 2, 0, QK_REP);
    set_keymap({key_c, key_altgr, key_repeat});

    // Allow any number of reports with no keys or only KC_RALT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_RALT))))
        .Times(AnyNumber());
    // clang-format on

    { // Expect: "AltGr+C, AltGr+C, AltGr+C, C".
        InSequence seq;
        EXPECT_REPORT(driver, (KC_RALT, KC_C));
        EXPECT_REPORT(driver, (KC_RALT, KC_C));
        EXPECT_REPORT(driver, (KC_RALT, KC_C));
        EXPECT_REPORT(driver, (KC_C));
    }

    key_altgr.press();
    run_one_scan_loop();
    tap_key(key_c);
    key_altgr.release();
    run_one_scan_loop();

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_C);
    EXPECT_EQ(get_last_mods(), MOD_BIT(KC_RALT));

    tap_keys(key_repeat, key_repeat, key_c);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests that Repeat Key stacks mods, types
// "Ctrl+Left, Repeat, Shift+Repeat, Shift+Repeat, Repeat, Left".
TEST_F(RepeatKey, StackMods) {
    TestDriver driver;
    KeymapKey  key_left(0, 0, 0, KC_LEFT);
    KeymapKey  key_shift(0, 1, 0, KC_LSFT);
    KeymapKey  key_ctrl(0, 2, 0, KC_LCTL);
    KeymapKey  key_repeat(0, 3, 0, QK_REP);
    set_keymap({key_left, key_shift, key_ctrl, key_repeat});

    // Allow any number of reports with no keys or only mods.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LCTL),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LCTL, KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on

    { // Expect: "Ctrl+Left, Ctrl+Shift+Left".
        InSequence seq;
        EXPECT_REPORT(driver, (KC_LCTL, KC_LEFT));
        EXPECT_REPORT(driver, (KC_LCTL, KC_LEFT));
        EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_LEFT));
        EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_LEFT));
        EXPECT_REPORT(driver, (KC_LCTL, KC_LEFT));
        EXPECT_REPORT(driver, (KC_LEFT));
    }

    key_ctrl.press();
    run_one_scan_loop();
    tap_key(key_left);
    run_one_scan_loop();
    key_ctrl.release();
    run_one_scan_loop();

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_LEFT);
    EXPECT_EQ(get_last_mods(), MOD_BIT(KC_LCTL));

    tap_key(key_repeat);

    key_shift.press();
    run_one_scan_loop();
    tap_keys(key_repeat, key_repeat);
    key_shift.release();
    run_one_scan_loop();

    EXPECT_EQ(get_last_mods(), MOD_BIT(KC_LCTL));

    tap_keys(key_repeat, key_left);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Types: "S(KC_1), Repeat, Ctrl+Repeat, Ctrl+Repeat, Repeat, KC_2".
TEST_F(RepeatKey, ShiftedKeycode) {
    TestDriver driver;
    KeymapKey  key_exlm(0, 0, 0, S(KC_1));
    KeymapKey  key_2(0, 1, 0, KC_2);
    KeymapKey  key_ctrl(0, 2, 0, KC_LCTL);
    KeymapKey  key_repeat(0, 3, 0, QK_REP);
    set_keymap({key_exlm, key_2, key_ctrl, key_repeat});

    // Allow any number of reports with no keys or only mods.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LCTL),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LCTL, KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on

    { // Expect: "Shift+1, Shift+1, Ctrl+Shift+1, Ctrl+Shift+1, Shift+1, 2".
        InSequence seq;
        EXPECT_REPORT(driver, (KC_LSFT, KC_1));
        EXPECT_REPORT(driver, (KC_LSFT, KC_1));
        EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_1));
        EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_1));
        EXPECT_REPORT(driver, (KC_LSFT, KC_1));
        EXPECT_REPORT(driver, (KC_2));
    }

    tap_key(key_exlm);

    EXPECT_KEYCODE_EQ(get_last_keycode(), S(KC_1));

    tap_key(key_repeat);

    key_ctrl.press();
    run_one_scan_loop();
    tap_keys(key_repeat, key_repeat);
    key_ctrl.release();
    run_one_scan_loop();

    tap_keys(key_repeat, key_2);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests Repeat Key with a one-shot Shift, types
// "A, OSM(MOD_LSFT), Repeat, Repeat".
TEST_F(RepeatKey, WithOneShotShift) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_oneshot_shift(0, 1, 0, OSM(MOD_LSFT));
    KeymapKey  key_repeat(0, 2, 0, QK_REP);
    set_keymap({key_a, key_oneshot_shift, key_repeat});

    // Allow any number of reports with no keys or only KC_RALT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    ExpectString(driver, "aAa");

    tap_keys(key_a, key_oneshot_shift, key_repeat, key_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests Repeat Key with a mod-tap key, types
// "A, Repeat, Repeat, A(down), Repeat, Repeat, A(up), Repeat".
TEST_F(RepeatKey, ModTap) {
    TestDriver driver;
    KeymapKey  key_mt_a(0, 0, 0, LSFT_T(KC_A));
    KeymapKey  key_repeat(0, 1, 0, QK_REP);
    set_keymap({key_mt_a, key_repeat});

    // Allow any number of reports with no keys or only KC_LSFT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    ExpectString(driver, "aaaAAa");

    tap_key(key_mt_a);

    EXPECT_KEYCODE_EQ(get_last_keycode(), LSFT_T(KC_A));

    tap_keys(key_repeat, key_repeat);
    key_mt_a.press();
    run_one_scan_loop();
    tap_key(key_repeat, TAPPING_TERM + 1);
    tap_key(key_repeat);
    key_mt_a.release();
    run_one_scan_loop();
    tap_key(key_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests with Auto Shift. When repeating an autoshiftable key, it does not
// matter how long the original key was held, rather, quickly tapping vs.
// long-pressing the Repeat Key determines whether the shifted key is repeated.
//
// The test does the following, which should produce "aaABbB":
// 1. Tap KC_A quickly.
// 2. Tap Repeat Key quickly.
// 3. Long-press Repeat Key.
// 4. Long-press KC_B.
// 5. Tap Repeat Key quickly.
// 6. Long-press Repeat Key.
TEST_F(RepeatKey, AutoShift) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_repeat(0, 2, 0, QK_REP);
    set_keymap({key_a, key_b, key_repeat});

    autoshift_enable();

    // Allow any number of reports with no keys or only KC_LSFT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    ExpectString(driver, "aaABbB");

    tap_key(key_a); // Tap A quickly.

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_A);
    EXPECT_EQ(get_last_mods(), 0);

    tap_key(key_repeat);
    tap_key(key_repeat, AUTO_SHIFT_TIMEOUT + 1);

    tap_key(key_b, AUTO_SHIFT_TIMEOUT + 1); // Long press B.

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_B);
    EXPECT_EQ(get_last_mods(), 0);

    tap_key(key_repeat);
    tap_key(key_repeat, AUTO_SHIFT_TIMEOUT + 1);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Defines `remember_last_key_user()` to forget the Shift mod and types:
// "Ctrl+A, Repeat, Shift+A, Repeat, Shift+Repeat".
TEST_F(RepeatKey, FilterRememberedMods) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_ctrl(0, 1, 0, KC_LCTL);
    KeymapKey  key_shift(0, 2, 0, KC_LSFT);
    KeymapKey  key_repeat(0, 3, 0, QK_REP);
    set_keymap({key_a, key_ctrl, key_shift, key_repeat});

    remember_last_key_user_fun = [](uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
        *remembered_mods &= ~MOD_MASK_SHIFT;
        return true;
    };

    // Allow any number of reports with no keys or only mods.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LCTL),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LCTL, KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on

    { // Expect: "Ctrl+A, Ctrl+A, Shift+A, A, Shift+A".
        InSequence seq;
        EXPECT_REPORT(driver, (KC_LCTL, KC_A));
        EXPECT_REPORT(driver, (KC_LCTL, KC_A));
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    }

    key_ctrl.press();
    run_one_scan_loop();
    tap_key(key_a);

    EXPECT_EQ(get_last_mods(), MOD_BIT(KC_LCTL));

    key_ctrl.release();
    run_one_scan_loop();

    tap_key(key_repeat);
    key_shift.press();
    run_one_scan_loop();
    tap_key(key_a);

    EXPECT_EQ(get_last_mods(), 0); // Shift should be forgotten.

    key_shift.release();
    run_one_scan_loop();

    tap_key(key_repeat);

    key_shift.press();
    run_one_scan_loop();
    tap_key(key_repeat);
    key_shift.release();
    run_one_scan_loop();

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests set_last_keycode() and set_last_mods().
TEST_F(RepeatKey, SetRepeatKeyKeycode) {
    TestDriver driver;
    KeymapKey  key_repeat(0, 0, 0, QK_REP);
    set_keymap({key_repeat});

    // Allow any number of reports with no keys or only KC_LSFT.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    ExpectString(driver, "aaBB");

    set_last_keycode(KC_A);
    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_A);

    for (int n = 1; n <= 2; ++n) { // Tap the Repeat Key twice.
        // When Repeat is pressed, process_record_user() should be called with a
        // press event with keycode == KC_A and repeat_key_count() == n.
        ExpectProcessRecordUserCalledWith(true, KC_A, n);
        key_repeat.press(); // Press the Repeat Key.
        run_one_scan_loop();
        EXPECT_TRUE(process_record_user_was_called_);

        // Expect the corresponding release event.
        ExpectProcessRecordUserCalledWith(false, KC_A, n);
        key_repeat.release(); // Release the Repeat Key.
        run_one_scan_loop();
        EXPECT_TRUE(process_record_user_was_called_);
    }

    process_record_user_fun = process_record_user_default;
    set_last_keycode(KC_B);
    set_last_mods(MOD_BIT(KC_LSFT));

    tap_keys(key_repeat, key_repeat);

    set_last_keycode(KC_NO);
    tap_keys(key_repeat, key_repeat); // Has no effect.

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests the `repeat_key_invoke()` function.
TEST_F(RepeatKey, RepeatKeyInvoke) {
    TestDriver driver;
    KeymapKey  key_s(0, 0, 0, KC_S);
    set_keymap({key_s});

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    ExpectString(driver, "ss");

    tap_key(key_s);

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_S);

    // Calling repeat_key_invoke() should result in process_record_user()
    // getting a press event with keycode KC_S.
    ExpectProcessRecordUserCalledWith(true, KC_S, 1);
    keyevent_t event;
    event.key     = {0, 0};
    event.pressed = true;
    event.time    = timer_read();
    event.type    = KEY_EVENT;
    repeat_key_invoke(&event);
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    // Make the release event.
    ExpectProcessRecordUserCalledWith(false, KC_S, 1);
    event.pressed = false;
    event.time    = timer_read();
    repeat_key_invoke(&event);
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

} // namespace
