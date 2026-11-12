/* Copyright 2021 Stefan Kerkmann
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
using testing::AtMost;
using testing::InSequence;

class DefaultTapHold : public TestFixture {};

TEST_F(DefaultTapHold, tap_regular_key_while_mod_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Idle for tapping term of mod tap hold key. */
    idle_for(TAPPING_TERM - 3);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(DefaultTapHold, tap_a_mod_tap_key_while_another_mod_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       first_mod_tap_hold_key  = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       second_mod_tap_hold_key = KeymapKey(0, 2, 0, RSFT_T(KC_A));

    set_keymap({first_mod_tap_hold_key, second_mod_tap_hold_key});

    /* Press first mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    first_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press second tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release second tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release first mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    first_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(DefaultTapHold, tap_regular_key_while_layer_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       layer_tap_hold_key = KeymapKey(0, 1, 0, LT(1, KC_P));
    auto       regular_key        = KeymapKey(0, 2, 0, KC_A);
    auto       layer_key          = KeymapKey(1, 2, 0, KC_B);

    set_keymap({layer_tap_hold_key, regular_key, layer_key});

    /* Press layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release layer-tap-hold key */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_REPORT(driver, (KC_P, KC_A));
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(DefaultTapHold, tap_mod_tap_hold_key_two_times) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_hold_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press mod-tap-hold key again. */
    EXPECT_REPORT(driver, (KC_P));
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(DefaultTapHold, tap_mod_tap_hold_key_twice_and_hold_on_second_time) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_hold_key});

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press mod-tap-hold key again. */
    EXPECT_REPORT(driver, (KC_P));
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(DefaultTapHold, tap_and_hold_mod_tap_hold_key) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));

    set_keymap({mod_tap_hold_key});

    /* Press mod-tap-hold key. */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Release of a modifier-only key is retained while a mod-tap is unsettled. In
// "KC_MEH down, LCTL_T(KC_A) down, KC_MEH up, LCTL_T(KC_A) up", nothing is sent
// when KC_MEH is released; the tap of LCTL_T(KC_A) is typed with Meh still held
// (Ctrl+Shift+Alt+A).
TEST_F(DefaultTapHold, modifier_release_is_retained_while_mt_is_unsettled) {
    TestDriver driver;
    InSequence s;
    auto       meh_key     = KeymapKey(0, 4, 3, KC_MEH);
    auto       mod_tap_key = KeymapKey(0, 0, 1, LCTL_T(KC_A));
    set_keymap({meh_key, mod_tap_key});

    EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_LALT));
    meh_key.press();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), MOD_BIT_LCTRL | MOD_BIT_LSHIFT | MOD_BIT_LALT);
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    idle_for(10);
    meh_key.release();
    idle_for(10);
    // Meh is retained even though KC_MEH was released.
    EXPECT_EQ(get_mods(), MOD_BIT_LCTRL | MOD_BIT_LSHIFT | MOD_BIT_LALT);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_LCTL, KC_LSFT, KC_LALT, KC_A));
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), 0);
    VERIFY_AND_CLEAR(driver);
}

// Release of a (non-modifier) key is forwarded while a mod-tap is unsettled. In
// "S(KC_1) down, LCTL_T(KC_A) down, S(KC_1) up, LCTL_T(KC_A) up", the "!" is
// released as soon as its key is, so it cannot auto-repeat on the host, and the
// mod-tap key is tapped afterwards.
TEST_F(DefaultTapHold, key_release_is_forwarded_while_mt_is_unsettled) {
    TestDriver driver;
    InSequence s;
    auto       shifted_key = KeymapKey(0, 1, 0, S(KC_1));
    auto       mod_tap_key = KeymapKey(0, 0, 1, LCTL_T(KC_A));
    set_keymap({shifted_key, mod_tap_key});

    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_1));
    shifted_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    idle_for(10);
    VERIFY_AND_CLEAR(driver);

    // shifted_key release is sent immediately.
    EXPECT_REPORT(driver, (KC_LSFT)).Times(AtMost(1));
    EXPECT_EMPTY_REPORT(driver);
    shifted_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    idle_for(10);
    mod_tap_key.release();
    run_one_scan_loop();
    EXPECT_EQ(get_mods(), 0);
    VERIFY_AND_CLEAR(driver);
}
