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
#include "quantum_keycodes.h"
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

enum tap_dance_codes {
    DANCE_0,
    DANCE_1,
};

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {}
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    const uint8_t mods = get_mods();
    process_caps_word_key(KC_W, mods, 0);
    register_code16(KC_W);
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    clear_weak_mods();
    unregister_code16(KC_W);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_finished, dance_0_reset),
    [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_finished, dance_1_reset),
};

// Tests that Tap Dance key codes do not disable Caps Word
TEST_F(CapsWord, TapDanceKeysPress) {
    TestDriver driver;
    KeymapKey key_a(0, 0, 0, KC_A);
    KeymapKey key_td0(0, 1, 0, TD(DANCE_0));
    set_keymap({key_a, key_td0});

    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    
    { // Expect: "A, A"
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    }

    // Turn on Caps Word and type "A", tap dance key, "A"
    caps_word_on();

    tap_key(key_a);
    tap_key(key_td0);
    tap_key(key_a);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

// Tests that a Tap Dance key can pick up the Caps Word state
// and be set to caps accordingly
TEST_F(CapsWord, TapDanceKeysCaps) {
    TestDriver driver;
    KeymapKey key_a(0, 0, 0, KC_A);
    KeymapKey key_td1(0, 1, 0, TD(DANCE_1));
    KeymapKey key_spc(0, 2, 0, KC_SPC);
    set_keymap({key_a, key_td1, key_spc});

    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(
                KeyboardReport(),
                KeyboardReport(KC_LSFT))))
        .Times(AnyNumber());
    
    { // Expect: "A, W, space, a, w, space"
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
        EXPECT_REPORT(driver, (KC_LSFT, KC_W));
        EXPECT_REPORT(driver, (KC_SPC));
        EXPECT_REPORT(driver, (KC_A));
        EXPECT_REPORT(driver, (KC_W));
        EXPECT_REPORT(driver, (KC_SPC));
    }

    // Turn on Caps Word and type "A", tap dance key, "A"
    caps_word_on();

    tap_key(key_a);
    tap_key(key_td1);
    tap_key(key_spc);
    tap_key(key_a);
    tap_key(key_td1);
    tap_key(key_spc);

    testing::Mock::VerifyAndClearExpectations(&driver);
}
