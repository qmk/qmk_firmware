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

extern "C" {
enum unicode_names {
    ENDASH,
    EMDASH,
    DELTA_LOWERCASE,
    DELTA_UPPERCASE,
};

const uint32_t unicode_map[] PROGMEM = {
    [ENDASH]          = 0x2013,
    [EMDASH]          = 0x2014,
    [DELTA_LOWERCASE] = 0x03b4,
    [DELTA_UPPERCASE] = 0x0394,
};

#define U_DASH XP(ENDASH, EMDASH)
#define U_DELTA XP(DELTA_LOWERCASE, DELTA_UPPERCASE)

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case U_DELTA:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case U_DASH:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
} // extern "C"

class CapsWord : public TestFixture {
   public:
    void SetUp() override {
        caps_word_off();
    }
};

// Tests that typing U_DELTA while Caps Word is on sends the uppercase Delta.
TEST_F(CapsWord, ShiftedUnicodeMapKey) {
    TestDriver driver;
    KeymapKey  key_delta(0, 0, 0, U_DELTA);
    KeymapKey  key_spc(0, 1, 0, KC_SPC);
    set_keymap({key_delta, key_spc});

    // Allow any number of reports with no keys or only KC_LSFT and KC_LCTL.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LCTL, KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    { // Expect: "Uppercase Delta, space, lowercase delta".
        InSequence s;
        EXPECT_UNICODE(driver, unicode_map[DELTA_UPPERCASE]);
        EXPECT_REPORT(driver, (KC_SPC));
        EXPECT_UNICODE(driver, unicode_map[DELTA_LOWERCASE]);
    }

    // Turn on Caps Word and tap "delta, space, delta".
    caps_word_on();
    tap_keys(key_delta, key_spc, key_delta);

    EXPECT_EQ(is_caps_word_on(), false);
    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests typing U_ENDASH while Caps Word is on.
TEST_F(CapsWord, UnshiftedUnicodeMapKey) {
    TestDriver driver;
    KeymapKey  key_dash(0, 0, 0, U_DASH);
    set_keymap({key_dash});

    // Allow any number of reports with no keys or only KC_LSFT and KC_LCTL.
    // clang-format off
    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT),
                KeyboardReport(KC_LCTL, KC_LSFT))))
        .Times(AnyNumber());
    // clang-format on
    EXPECT_UNICODE(driver, unicode_map[ENDASH]);

    // Turn on Caps Word and tap U_DASH key.
    caps_word_on();
    tap_key(key_dash);

    EXPECT_EQ(is_caps_word_on(), true);
    testing::Mock::VerifyAndClearExpectations(&driver);
}
