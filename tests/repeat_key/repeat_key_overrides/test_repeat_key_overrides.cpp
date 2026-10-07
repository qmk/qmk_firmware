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

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using ::testing::AnyNumber;
using ::testing::Matcher;

namespace {

bool process_record_user_default(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool remember_last_key_user_default(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    return true;
}

std::function<bool(uint16_t, keyrecord_t *)>            process_record_user_fun    = process_record_user_default;
std::function<bool(uint16_t, keyrecord_t *, uint8_t *)> remember_last_key_user_fun = remember_last_key_user_default;

extern "C" bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_user_fun(keycode, record);
}

extern "C" bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    return remember_last_key_user_fun(keycode, record, remembered_mods);
}

class RepeatKeyOverrides : public TestFixture {
   public:
    bool process_record_user_was_called_;

    void SetUp() override {
        reset_repeat_key_state();
        process_record_user_fun    = process_record_user_default;
        remember_last_key_user_fun = remember_last_key_user_default;
    }

    void ExpectProcessRecordUserCalledWith(bool expected_press, uint16_t expected_keycode, int8_t expected_repeat_key_count) {
        process_record_user_was_called_ = false;
        process_record_user_fun         = [=](uint16_t keycode, keyrecord_t *record) {
            EXPECT_EQ(record->event.pressed, expected_press);
            EXPECT_KEYCODE_EQ(keycode, expected_keycode);
            EXPECT_EQ(get_repeat_key_count(), expected_repeat_key_count);
            process_record_user_was_called_ = true;
            return true;
        };
    }
};

// Tests that pressing Left Alt + / triggers override to backslash \,
// and tapping Repeat Key subsequently outputs \ again.
TEST_F(RepeatKeyOverrides, AltSlashOverride) {
    TestDriver                   driver;
    Matcher<report_keyboard_t &> empty_or_lalt = AnyOf(KeyboardReport(), KeyboardReport(KC_LALT));
    KeymapKey                    key_lalt(0, 0, 0, KC_LALT);
    KeymapKey                    key_slsh(0, 1, 0, KC_SLSH);
    KeymapKey                    key_repeat(0, 2, 0, QK_REP);
    set_keymap({key_lalt, key_slsh, key_repeat});

    // Hold Left Alt
    EXPECT_REPORT(driver, (KC_LALT));
    key_lalt.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press / (triggers override -> backslash \, Left Alt suppressed)
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_BSLS));
    key_slsh.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release / (Left Alt still held, so Left Alt is sent again)
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LALT));
    key_slsh.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release Left Alt
    EXPECT_EMPTY_REPORT(driver);
    key_lalt.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Tap Repeat Key (sends \, since weak Left Alt + / triggers override)
    EXPECT_CALL(driver, send_keyboard_mock(empty_or_lalt)).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_BSLS));
    ExpectProcessRecordUserCalledWith(true, KC_SLSH, 1);
    key_repeat.press();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);
    VERIFY_AND_CLEAR(driver);

    EXPECT_CALL(driver, send_keyboard_mock(empty_or_lalt)).Times(AnyNumber());
    ExpectProcessRecordUserCalledWith(false, KC_SLSH, 1);
    key_repeat.release();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);
    VERIFY_AND_CLEAR(driver);
}

// Tests that pressing Left Alt + Left Shift + / triggers override to |,
// and tapping Repeat Key subsequently outputs | again.
TEST_F(RepeatKeyOverrides, AltShiftSlashOverride) {
    TestDriver                   driver;
    Matcher<report_keyboard_t &> lsft_and_or_lalt = AnyOf(KeyboardReport(KC_LSFT), KeyboardReport(KC_LSFT, KC_LALT));
    KeymapKey                    key_lalt(0, 0, 0, KC_LALT);
    KeymapKey                    key_lshift(0, 1, 0, KC_LSFT);
    KeymapKey                    key_slsh(0, 2, 0, KC_SLSH);
    KeymapKey                    key_repeat(0, 3, 0, QK_REP);
    set_keymap({key_lalt, key_lshift, key_slsh, key_repeat});

    // Hold Left Alt
    EXPECT_REPORT(driver, (KC_LALT));
    key_lalt.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Hold Left Shift
    EXPECT_REPORT(driver, (KC_LALT, KC_LSFT));
    key_lshift.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press / (triggers override -> Shift + \, Alt suppressed, Shift remains)
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_BSLS));
    key_slsh.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release /
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT))).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LALT, KC_LSFT));
    key_slsh.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release Left Shift
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LALT));
    key_lshift.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release Left Alt
    EXPECT_EMPTY_REPORT(driver);
    key_lalt.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Tap Repeat Key (sends | -> Shift + \)
    EXPECT_CALL(driver, send_keyboard_mock(lsft_and_or_lalt)).Times(AnyNumber());
    EXPECT_REPORT(driver, (KC_LSFT, KC_BSLS));
    ExpectProcessRecordUserCalledWith(true, KC_SLSH, 1);
    key_repeat.press();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);
    VERIFY_AND_CLEAR(driver);

    EXPECT_CALL(driver, send_keyboard_mock(lsft_and_or_lalt)).Times(AnyNumber());
    EXPECT_EMPTY_REPORT(driver);
    ExpectProcessRecordUserCalledWith(false, KC_SLSH, 1);
    key_repeat.release();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);
    VERIFY_AND_CLEAR(driver);
}

} // namespace
