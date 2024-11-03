/* Copyright 2022 Vladislav Kucheriavykh
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

extern "C" {
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R'},
    {'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R'},
    {'*', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R'},
    {'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R'},
};
} // extern "C"

class ChordalHoldAndPermissiveHold : public TestFixture {};

TEST_F(ChordalHoldAndPermissiveHold, chordal_hold_handedness) {
    EXPECT_EQ(chordal_hold_handedness_user({.col = 0, .row = 0}), 'L');
    EXPECT_EQ(chordal_hold_handedness_user({.col = MATRIX_COLS - 1, .row = 0}), 'R');
    EXPECT_EQ(chordal_hold_handedness_user({.col = 0, .row = 2}), '*');
}

TEST_F(ChordalHoldAndPermissiveHold, get_chordal_hold_default) {
    auto make_record = [](uint8_t row, uint8_t col, keyevent_type_t type = KEY_EVENT, uint16_t keycode = KC_NO) {
        return keyrecord_t{
            .event =
                {
                    .key     = {.col = col, .row = row},
                    .type    = type,
                    .pressed = true,
                },
            .keycode = keycode,
        };
    };
    // Create two records on the left hand.
    keyrecord_t record_l0 = make_record(0, 0);
    keyrecord_t record_l1 = make_record(1, 0);
    // Create a record on the right hand.
    keyrecord_t record_r = make_record(0, MATRIX_COLS - 1);

    // Function should return true when records are on opposite hands.
    EXPECT_TRUE(get_chordal_hold_default(&record_l0, &record_r));
    EXPECT_TRUE(get_chordal_hold_default(&record_r, &record_l0));
    // ... and false when on the same hand.
    EXPECT_FALSE(get_chordal_hold_default(&record_l0, &record_l1));
    EXPECT_FALSE(get_chordal_hold_default(&record_l1, &record_l0));
    // But (2, 0) has handedness '*', for which true is returned for chords
    // with either hand.
    keyrecord_t record_l2 = make_record(2, 0);
    EXPECT_TRUE(get_chordal_hold_default(&record_l2, &record_l0));
    EXPECT_TRUE(get_chordal_hold_default(&record_l2, &record_r));

    // Create a record resulting from a combo.
    keyrecord_t record_combo = make_record(0, 0, COMBO_EVENT, KC_X);
    // Function returns true in all cases.
    EXPECT_TRUE(get_chordal_hold_default(&record_l0, &record_combo));
    EXPECT_TRUE(get_chordal_hold_default(&record_r, &record_combo));
    EXPECT_TRUE(get_chordal_hold_default(&record_combo, &record_l0));
    EXPECT_TRUE(get_chordal_hold_default(&record_combo, &record_r));
}

TEST_F(ChordalHoldAndPermissiveHold, chord_nested_press_settled_as_hold) {
    TestDriver driver;
    InSequence s;
    // Mod-tap key on the left hand.
    auto mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    // Regular key on the right hand.
    auto regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_A));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldAndPermissiveHold, chord_rolled_press_settled_as_tap) {
    TestDriver driver;
    InSequence s;
    // Mod-tap key on the left hand.
    auto mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    // Regular key on the right hand.
    auto regular_key = KeymapKey(0, MATRIX_COLS - 1, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press regular key and release mod-tap key.
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_A));
    regular_key.press();
    run_one_scan_loop();
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release regular key.
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldAndPermissiveHold, non_chord_with_mod_tap_settled_as_tap) {
    TestDriver driver;
    InSequence s;
    // Mod-tap key and regular key both on the left hand.
    auto mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_key, regular_key});

    // Press mod-tap-hold key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Tap regular key.
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    tap_key(regular_key);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Release mod-tap-hold key.
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldAndPermissiveHold, tap_mod_tap_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_key});

    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    idle_for(TAPPING_TERM - 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldAndPermissiveHold, hold_mod_tap_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_key});

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_key.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ChordalHoldAndPermissiveHold, chordal_hold_ignores_multiple_mod_taps) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key1 = KeymapKey(0, 1, 0, SFT_T(KC_A));
    auto       mod_tap_key2 = KeymapKey(0, 2, 0, RSFT_T(KC_B));

    set_keymap({mod_tap_key1, mod_tap_key2});

    // Press mod-tap-hold key.
    EXPECT_NO_REPORT(driver);
    mod_tap_key1.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Press second mod-tap key.
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_RIGHT_SHIFT));
    mod_tap_key2.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    // Release keys.
    EXPECT_REPORT(driver, (KC_RIGHT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key1.release();
    run_one_scan_loop();
    mod_tap_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
