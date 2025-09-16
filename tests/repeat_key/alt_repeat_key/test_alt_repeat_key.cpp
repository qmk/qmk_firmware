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
using ::testing::InSequence;

namespace {

bool process_record_user_default(uint16_t keycode, keyrecord_t* record) {
    return true;
}

bool remember_last_key_user_default(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    return true;
}

uint16_t get_alt_repeat_key_keycode_user_default(uint16_t keycode, uint8_t mods) {
    return KC_TRNS;
}

// Indirections so that process_record_user() can be replaced with other
// functions in the test cases below.
std::function<bool(uint16_t, keyrecord_t*)>           process_record_user_fun             = process_record_user_default;
std::function<bool(uint16_t, keyrecord_t*, uint8_t*)> remember_last_key_user_fun          = remember_last_key_user_default;
std::function<uint16_t(uint16_t, uint8_t)>            get_alt_repeat_key_keycode_user_fun = get_alt_repeat_key_keycode_user_default;

extern "C" bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    return process_record_user_fun(keycode, record);
}

extern "C" bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    return remember_last_key_user_fun(keycode, record, remembered_mods);
}

extern "C" uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    return get_alt_repeat_key_keycode_user_fun(keycode, mods);
}

class AltRepeatKey : public TestFixture {
   public:
    bool process_record_user_was_called_;

    void SetUp() override {
        process_record_user_fun             = process_record_user_default;
        remember_last_key_user_fun          = remember_last_key_user_default;
        get_alt_repeat_key_keycode_user_fun = get_alt_repeat_key_keycode_user_default;
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

TEST_F(AltRepeatKey, AlternateBasic) {
    TestDriver driver;
    KeymapKey  key_bspc(0, 0, 0, KC_BSPC);
    KeymapKey  key_pgdn(0, 1, 0, KC_PGDN);
    KeymapKey  key_pgup(0, 2, 0, KC_PGUP);
    KeymapKey  key_repeat(0, 4, 0, QK_REP);
    KeymapKey  key_alt_repeat(0, 5, 0, QK_AREP);
    set_keymap({key_bspc, key_pgdn, key_pgup, key_repeat, key_alt_repeat});

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    {
        InSequence seq;
        EXPECT_REPORT(driver, (KC_BSPC));
        EXPECT_REPORT(driver, (KC_DEL));
        EXPECT_REPORT(driver, (KC_DEL));
        EXPECT_REPORT(driver, (KC_BSPC));
        EXPECT_REPORT(driver, (KC_DEL));
        EXPECT_REPORT(driver, (KC_PGDN));
        EXPECT_REPORT(driver, (KC_PGUP));
        EXPECT_REPORT(driver, (KC_PGUP));
        EXPECT_REPORT(driver, (KC_PGDN));
    }

    tap_key(key_bspc);

    for (int n = 1; n <= 2; ++n) { // Tap the Alternate Repeat Key twice.
        ExpectProcessRecordUserCalledWith(true, KC_DEL, -n);
        key_alt_repeat.press(); // Press the Alternate Repeat Key.
        run_one_scan_loop();
        EXPECT_TRUE(process_record_user_was_called_);

        // Expect the corresponding release event.
        ExpectProcessRecordUserCalledWith(false, KC_DEL, -n);
        key_alt_repeat.release(); // Release the Repeat Key.
        run_one_scan_loop();
        EXPECT_TRUE(process_record_user_was_called_);
    }

    process_record_user_fun = process_record_user_default;
    tap_keys(key_repeat, key_alt_repeat);
    tap_keys(key_pgdn, key_alt_repeat);
    tap_keys(key_pgup, key_alt_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

struct TestParamsAlternateKeyCodes {
    uint16_t keycode;
    uint8_t  mods;
    uint16_t expected_alt_keycode;
};

// Tests `get_alt_repeat_key_keycode()` for various keycodes.
TEST_F(AltRepeatKey, GetAltRepeatKeyKeycode) {
    for (const auto& params : std::vector<TestParamsAlternateKeyCodes>({
             // clang-format off
          // Each line tests one call to `get_alt_repeat_key_keycode()`:
          // {keycode, mods, expected_alt_keycode}.
          // Arrows.
          {KC_LEFT, 0, KC_RGHT},
          {KC_RGHT, 0, KC_LEFT},
          {KC_LEFT, MOD_BIT(KC_LSFT), LSFT(KC_RGHT)},
          {KC_LEFT, MOD_BIT(KC_RSFT), RSFT(KC_RGHT)},
          {KC_LEFT, MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT), C(S(KC_RGHT))},
          {KC_LEFT, MOD_BIT(KC_LGUI), LGUI(KC_RGHT)},
          {C(KC_LEFT), MOD_BIT(KC_LSFT), C(S(KC_RGHT))},
          {KC_UP, 0, KC_DOWN},
          // Navigation keys.
          {KC_PGUP, 0, KC_PGDN},
          {KC_HOME, 0, KC_END },
          // Media keys.
          {KC_WBAK, 0, KC_WFWD},
          {KC_MNXT, 0, KC_MPRV},
          {KC_MRWD, 0, KC_MFFD},
          {KC_VOLU, 0, KC_VOLD},
          {KC_BRIU, 0, KC_BRID},
          // Emacs navigation.
          {KC_N, MOD_BIT(KC_LCTL), C(KC_P)},
          {KC_B, MOD_BIT(KC_LCTL), LCTL(KC_F)},
          {KC_B, MOD_BIT(KC_RCTL), RCTL(KC_F)},
          {KC_B, MOD_BIT(KC_LALT), LALT(KC_F)},
          {KC_F, MOD_BIT(KC_LCTL), C(KC_B)},
          {KC_A, MOD_BIT(KC_LCTL), C(KC_E)},
          {KC_D, MOD_BIT(KC_LCTL), C(KC_U)},
          // Vim navigation.
          {KC_J, 0, KC_K},
          {KC_K, 0, KC_J},
          {KC_H, 0, KC_L},
          {KC_B, 0, KC_W},
          {KC_W, 0, KC_B},
          {KC_E, 0, KC_B},
          {KC_B, MOD_BIT(KC_LSFT), S(KC_W)},
          {KC_W, MOD_BIT(KC_LSFT), S(KC_B)},
          {KC_E, MOD_BIT(KC_LSFT), S(KC_B)},
          {KC_O, MOD_BIT(KC_LCTL), C(KC_I)},
          {KC_I, MOD_BIT(KC_LCTL), C(KC_O)},
          // Other.
          {KC_DEL, 0, KC_BSPC},
          {KC_LBRC, 0, KC_RBRC},
          {KC_LCBR, 0, KC_RCBR},
          // Some keys where the last key is a tap-hold key.
          {LSFT_T(KC_F), MOD_BIT(KC_RCTL), RCTL(KC_B)},
          {LT(1, KC_A), MOD_BIT(KC_RGUI), RGUI(KC_E)},
          {RALT_T(KC_J), 0, KC_K},
          // Some keys where no alternate is defined.
          {KC_A, 0, KC_NO},
          {KC_F1, 0, KC_NO},
          {QK_LEAD, 0, KC_NO},
          {MO(1), 0, KC_NO},
             // clang-format on
         })) {
        SCOPED_TRACE(std::string("Input keycode: ") + get_keycode_string(params.keycode));
        set_last_keycode(params.keycode);
        set_last_mods(params.mods);

        const uint16_t actual = get_alt_repeat_key_keycode();

        EXPECT_KEYCODE_EQ(get_alt_repeat_key_keycode(), params.expected_alt_keycode);
    }
}

// Test adding to and overriding the above through the
// `get_alt_repeat_key_keycode_user()` callback.
TEST_F(AltRepeatKey, GetAltRepeatKeyKeycodeUser) {
    get_alt_repeat_key_keycode_user_fun = [](uint16_t keycode, uint8_t mods) -> uint16_t {
        bool shifted = (mods & MOD_MASK_SHIFT);
        switch (keycode) {
            case KC_LEFT:
                return KC_ENT;
            case MO(1):
                return TG(1);
            case KC_TAB: // Tab <-> Shift + Tab example.
                if (shifted) {
                    return KC_TAB;
                } else {
                    return S(KC_TAB);
                }
        }

        // Ctrl + Y <-> Ctrl + Z example.
        if ((mods & MOD_MASK_CTRL)) {
            switch (keycode) {
                case KC_Y:
                    return C(KC_Z);
                case KC_Z:
                    return C(KC_Y);
            }
        }

        return KC_NO;
    };

    set_last_keycode(KC_LEFT);
    EXPECT_KEYCODE_EQ(get_alt_repeat_key_keycode(), KC_ENT);

    set_last_keycode(MO(1));
    EXPECT_KEYCODE_EQ(get_alt_repeat_key_keycode(), TG(1));

    set_last_keycode(KC_TAB);
    EXPECT_KEYCODE_EQ(get_alt_repeat_key_keycode(), S(KC_TAB));

    set_last_keycode(KC_TAB);
    set_last_mods(MOD_BIT(KC_LSFT));
    EXPECT_KEYCODE_EQ(get_alt_repeat_key_keycode(), KC_TAB);

    set_last_keycode(KC_Z);
    set_last_mods(MOD_BIT(KC_LCTL));
    EXPECT_KEYCODE_EQ(get_alt_repeat_key_keycode(), C(KC_Y));

    set_last_keycode(KC_Y);
    set_last_mods(MOD_BIT(KC_LCTL));
    EXPECT_KEYCODE_EQ(get_alt_repeat_key_keycode(), C(KC_Z));
}

// Tests rolling from a key to Alternate Repeat.
TEST_F(AltRepeatKey, RollingToAltRepeat) {
    TestDriver driver;
    KeymapKey  key_left(0, 0, 0, KC_LEFT);
    KeymapKey  key_alt_repeat(0, 1, 0, QK_AREP);
    set_keymap({key_left, key_alt_repeat});

    {
        InSequence seq;
        EXPECT_REPORT(driver, (KC_LEFT));
        EXPECT_REPORT(driver, (KC_LEFT, KC_RGHT));
        EXPECT_REPORT(driver, (KC_RGHT));
        EXPECT_EMPTY_REPORT(driver);
        EXPECT_REPORT(driver, (KC_RGHT));
        EXPECT_EMPTY_REPORT(driver);
    }

    // Perform a rolled press from Left to Alternate Repeat.

    ExpectProcessRecordUserCalledWith(true, KC_LEFT, 0);
    key_left.press();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(true, KC_RGHT, -1);
    key_alt_repeat.press(); // Press the Alternate Repeat Key.
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(false, KC_LEFT, 0);
    key_left.release();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(false, KC_RGHT, -1);
    key_alt_repeat.release(); // Release the Alternate Repeat Key.
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    process_record_user_fun = process_record_user_default;
    tap_key(key_alt_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests rolling from Alternate Repeat to another key.
TEST_F(AltRepeatKey, RollingFromAltRepeat) {
    TestDriver driver;
    KeymapKey  key_left(0, 0, 0, KC_LEFT);
    KeymapKey  key_up(0, 1, 0, KC_UP);
    KeymapKey  key_alt_repeat(0, 2, 0, QK_AREP);
    set_keymap({key_left, key_up, key_alt_repeat});

    {
        InSequence seq;
        EXPECT_REPORT(driver, (KC_LEFT));
        EXPECT_EMPTY_REPORT(driver);
        EXPECT_REPORT(driver, (KC_RGHT));
        EXPECT_REPORT(driver, (KC_RGHT, KC_UP));
        EXPECT_REPORT(driver, (KC_UP));
        EXPECT_EMPTY_REPORT(driver);
        EXPECT_REPORT(driver, (KC_DOWN));
        EXPECT_EMPTY_REPORT(driver);
    }

    tap_key(key_left);

    // Perform a rolled press from Alternate Repeat to Up.

    ExpectProcessRecordUserCalledWith(true, KC_RGHT, -1);
    key_alt_repeat.press(); // Press the Alternate Repeat Key.
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(true, KC_UP, 0);
    key_up.press();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_UP);

    ExpectProcessRecordUserCalledWith(false, KC_RGHT, -1);
    key_alt_repeat.release(); // Release the Alternate Repeat Key.
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    ExpectProcessRecordUserCalledWith(false, KC_UP, 0);
    key_up.release();
    run_one_scan_loop();
    EXPECT_TRUE(process_record_user_was_called_);

    process_record_user_fun = process_record_user_default;
    tap_key(key_alt_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests using the Alternate Repeat Key on a macro that doesn't have an
// alternate keycode defined.
TEST_F(AltRepeatKey, AlternateUnsupportedMacro) {
    TestDriver driver;
    KeymapKey  key_foo(0, 0, 0, QK_USER_0);
    KeymapKey  key_alt_repeat(0, 1, 0, QK_AREP);
    set_keymap({key_foo, key_alt_repeat});

    process_record_user_fun = [=](uint16_t keycode, keyrecord_t* record) {
        process_record_user_was_called_ = true;
        switch (keycode) {
            case QK_USER_0:
                if (record->event.pressed) {
                    SEND_STRING("foo");
                }
                break;
        }
        return true;
    };

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    ExpectString(driver, "foofoo");

    process_record_user_was_called_ = false;
    tap_key(key_foo);

    EXPECT_TRUE(process_record_user_was_called_);
    EXPECT_KEYCODE_EQ(get_last_keycode(), QK_USER_0);
    EXPECT_KEYCODE_EQ(get_alt_repeat_key_keycode(), KC_NO);

    process_record_user_was_called_ = false;
    key_alt_repeat.press(); // Press Alternate Repeat.
    run_one_scan_loop();

    EXPECT_FALSE(process_record_user_was_called_);

    process_record_user_was_called_ = false;
    key_alt_repeat.release(); // Release Alternate Repeat.
    run_one_scan_loop();

    EXPECT_FALSE(process_record_user_was_called_);

    process_record_user_was_called_ = false;
    tap_key(key_foo);

    EXPECT_TRUE(process_record_user_was_called_);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests a macro with custom alternate behavior.
TEST_F(AltRepeatKey, MacroCustomAlternate) {
    TestDriver driver;
    KeymapKey  key_foo(0, 0, 0, QK_USER_0);
    KeymapKey  key_alt_repeat(0, 1, 0, QK_AREP);
    set_keymap({key_foo, key_alt_repeat});

    get_alt_repeat_key_keycode_user_fun = [](uint16_t keycode, uint8_t mods) -> uint16_t {
        switch (keycode) {
            case QK_USER_0:
                return QK_USER_0; // QK_USER_0 handles its own alternate.
            default:
                return KC_NO; // No key by default.
        }
    };
    process_record_user_fun = [=](uint16_t keycode, keyrecord_t* record) {
        process_record_user_was_called_ = true;
        switch (keycode) {
            case QK_USER_0:
                if (record->event.pressed) {
                    if (get_repeat_key_count() >= 0) {
                        SEND_STRING("foo");
                    } else { // Key is being alternate repeated.
                        SEND_STRING("bar");
                    }
                }
                break;
        }
        return true;
    };

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    ExpectString(driver, "foobarbar");

    tap_keys(key_foo, key_alt_repeat, key_alt_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests the Additional "Alternate" keys example from the documentation page.
TEST_F(AltRepeatKey, AdditionalAlternateKeysExample) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_w(0, 1, 0, KC_W);
    KeymapKey  key_altrep2(0, 2, 0, QK_USER_0);
    KeymapKey  key_altrep3(0, 3, 0, QK_USER_1);
    set_keymap({key_a, key_w, key_altrep2, key_altrep3});

    remember_last_key_user_fun = [](uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
        switch (keycode) {
            case QK_USER_0:
            case QK_USER_1:
                return false; // Ignore ALTREP keys.
        }
        return true; // Other keys can be repeated.
    };
    process_record_user_fun = [=](uint16_t keycode, keyrecord_t* record) {
        switch (keycode) {
            case QK_USER_0:
                if (record->event.pressed) {
                    const uint16_t last_key = get_last_keycode();
                    switch (last_key) {
                        case KC_A:
                            SEND_STRING(/*a*/ "tion");
                            break;
                        case KC_W:
                            SEND_STRING(/*w*/ "hich");
                            break;
                    }
                }
                return false;
            case QK_USER_1:
                if (record->event.pressed) {
                    const uint16_t last_key = get_last_keycode();
                    switch (last_key) {
                        case KC_A:
                            SEND_STRING(/*a*/ "bout");
                            break;
                        case KC_W:
                            SEND_STRING(/*w*/ "ould");
                            break;
                    }
                }
                return false;
        }
        return true;
    };

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    ExpectString(driver, "ationwhichaboutwould");

    tap_keys(key_a, key_altrep2, key_w, key_altrep2);
    tap_keys(key_a, key_altrep3, key_w, key_altrep3);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

} // namespace
