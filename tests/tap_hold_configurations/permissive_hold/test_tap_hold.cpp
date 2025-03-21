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
