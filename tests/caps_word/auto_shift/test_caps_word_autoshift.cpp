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

class CapsWord : public TestFixture {
   public:
    void SetUp() override {
        caps_word_off();
    }
};

// Tests that with Auto Shift, letter keys are shifted by Caps Word
// regardless of whether they are released before AUTO_SHIFT_TIMEOUT.
TEST_F(CapsWord, AutoShiftKeys) {
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
    { // Expect: "A, A, space, a".
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_SPC));
        EXPECT_REPORT(driver, (KC_A));
    }

    // Turn on Caps Word and type "A (quick tap), A (long press), space, A".
    caps_word_on();

    tap_key(key_a);                         // Tap A quickly.
    tap_key(key_a, AUTO_SHIFT_TIMEOUT + 1); // Long press A.
    tap_key(key_spc);
    tap_key(key_a);

    testing::Mock::VerifyAndClearExpectations(&driver);
}
