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
using testing::InSequence;
class PermissiveHold : public TestFixture {};

TEST_F(PermissiveHold, tap_regular_key_while_mod_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_hold_key = KeymapKey(0, 1, 0, SFT_T(KC_P));
    auto       regular_key      = KeymapKey(0, 2, 0, KC_A);

    set_keymap({mod_tap_hold_key, regular_key});

    /* Press mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, regular_key.report_code));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(PermissiveHold, tap_a_mod_tap_key_while_another_mod_tap_key_is_held) {
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

    /* Press second mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release second mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, second_mod_tap_hold_key.report_code));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    second_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release first mod-tap-hold key */
    EXPECT_EMPTY_REPORT(driver);
    first_mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(PermissiveHold, tap_regular_key_while_layer_tap_key_is_held) {
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
    EXPECT_REPORT(driver, (layer_key.report_code));
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release layer-tap-hold key */
    EXPECT_NO_REPORT(driver);
    layer_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(PermissiveHold, repress_while_release_is_waiting_keeps_layer_of_first_press) {
    TestDriver driver;
    InSequence s;
    auto       mod_tap_key_1  = KeymapKey(0, 1, 0, RCTL_T(KC_E));
    auto       regular_key    = KeymapKey(0, 2, 0, KC_C);
    auto       layer_tap_key  = KeymapKey(0, 3, 0, LT(1, KC_F));
    auto       mod_tap_key_2  = KeymapKey(0, 4, 0, LSFT_T(KC_B));
    auto       other_key      = KeymapKey(0, 5, 0, KC_G);
    auto       regular_key_l1 = KeymapKey(1, 2, 0, KC_5);
    auto       other_key_l1   = KeymapKey(1, 5, 0, KC_7);

    set_keymap({mod_tap_key_1, regular_key, layer_tap_key, mod_tap_key_2, other_key, regular_key_l1, other_key_l1, KeymapKey(1, 1, 0, KC_TRNS), KeymapKey(1, 3, 0, KC_TRNS), KeymapKey(1, 4, 0, KC_TRNS)});

    /* Press mod-tap key 1, regular key, layer-tap key, mod-tap key 2 and other key */
    EXPECT_NO_REPORT(driver);
    mod_tap_key_1.press();
    run_one_scan_loop();
    regular_key.press();
    run_one_scan_loop();
    layer_tap_key.press();
    run_one_scan_loop();
    mod_tap_key_2.press();
    run_one_scan_loop();
    other_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key: mod-tap key 1 is held (permissive hold), regular key is pressed on layer 0 */
    EXPECT_REPORT(driver, (KC_RCTL));
    EXPECT_REPORT(driver, (KC_RCTL, KC_C));
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release other key: layer-tap key is held (layer 1 on); the release of the regular key still waits behind mod-tap key 2 */
    EXPECT_NO_REPORT(driver);
    other_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key again, now on layer 1 */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap key 2 (tap): the waiting release of the regular key must release KC_C */
    EXPECT_REPORT(driver, (KC_RCTL, KC_C, KC_B));
    EXPECT_REPORT(driver, (KC_RCTL, KC_C, KC_B, KC_7));
    EXPECT_REPORT(driver, (KC_RCTL, KC_B, KC_7));
    EXPECT_REPORT(driver, (KC_RCTL, KC_B));
    EXPECT_REPORT(driver, (KC_RCTL, KC_B, KC_5));
    EXPECT_REPORT(driver, (KC_RCTL, KC_5));
    mod_tap_key_2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key, mod-tap key 1 and layer-tap key */
    EXPECT_REPORT(driver, (KC_RCTL));
    regular_key.release();
    run_one_scan_loop();
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key_1.release();
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);
    layer_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
