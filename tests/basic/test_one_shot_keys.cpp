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

#include "action_util.h"
#include "keyboard_report_util.hpp"
#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class OneShot : public TestFixture {};
class OneShotParametrizedTestFixture : public ::testing::WithParamInterface<std::pair<KeymapKey, KeymapKey>>, public OneShot {};

TEST_F(OneShot, OSMWithoutAdditionalKeypressDoesNothing) {
    TestDriver driver;
    auto       osm_key = KeymapKey(0, 0, 0, OSM(MOD_LSFT), KC_LSFT);

    set_keymap({osm_key});

    /* Press and release OSM key*/
    EXPECT_NO_REPORT(driver);
    tap_key(osm_key);
    VERIFY_AND_CLEAR(driver);

    /* OSM are added when an actual report is send */
    EXPECT_REPORT(driver, (osm_key.report_code));
    send_keyboard_report();
    VERIFY_AND_CLEAR(driver);

    /* Make unit-test pass */
    clear_oneshot_mods();
}

#if defined(ONESHOT_TIMEOUT)

TEST_P(OneShotParametrizedTestFixture, OSMExpiredDoesNothing) {
    TestDriver driver;
    KeymapKey  osm_key     = GetParam().first;
    KeymapKey  regular_key = GetParam().second;

    set_keymap({osm_key, regular_key});

    /* Press and release OSM */
    EXPECT_NO_REPORT(driver);
    osm_key.press();
    run_one_scan_loop();
    osm_key.release();
    idle_for(ONESHOT_TIMEOUT);
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (regular_key.report_code)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

#endif

TEST_P(OneShotParametrizedTestFixture, OSMWithAdditionalKeypress) {
    TestDriver driver;
    KeymapKey  osm_key     = GetParam().first;
    KeymapKey  regular_key = GetParam().second;

    set_keymap({osm_key, regular_key});

    /* Press and release OSM */
    EXPECT_NO_REPORT(driver);
    tap_key(osm_key);
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (osm_key.report_code, regular_key.report_code)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_P(OneShotParametrizedTestFixture, OSMAsRegularModifierWithAdditionalKeypress) {
    TestDriver          driver;
    testing::InSequence s;

    KeymapKey osm_key     = GetParam().first;
    KeymapKey regular_key = GetParam().second;

    set_keymap({osm_key, regular_key});

    /* Press OSM */
    EXPECT_NO_REPORT(driver);
    osm_key.press();
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

    /* Release OSM */
    EXPECT_REPORT(driver, (regular_key.report_code, osm_key.report_code)).Times(1);
    EXPECT_EMPTY_REPORT(driver);
    osm_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// clang-format off

INSTANTIATE_TEST_CASE_P(
    OneShotModifierTests,
    OneShotParametrizedTestFixture,
    ::testing::Values(
        /* first is osm key, second is regular key. */
        std::make_pair(KeymapKey{0, 0, 0, OSM(MOD_LSFT), KC_LSFT}, KeymapKey{0, 1, 1, KC_A}),
        std::make_pair(KeymapKey{0, 0, 0, OSM(MOD_LCTL), KC_LCTL}, KeymapKey{0, 1, 1, KC_A}),
        std::make_pair(KeymapKey{0, 0, 0, OSM(MOD_LALT), KC_LALT}, KeymapKey{0, 1, 1, KC_A}),
        std::make_pair(KeymapKey{0, 0, 0, OSM(MOD_LGUI), KC_LGUI}, KeymapKey{0, 1, 1, KC_A}),
        std::make_pair(KeymapKey{0, 0, 0, OSM(MOD_RCTL), KC_RCTL}, KeymapKey{0, 1, 1, KC_A}),
        std::make_pair(KeymapKey{0, 0, 0, OSM(MOD_RSFT), KC_RSFT}, KeymapKey{0, 1, 1, KC_A}),
        std::make_pair(KeymapKey{0, 0, 0, OSM(MOD_RALT), KC_RALT}, KeymapKey{0, 1, 1, KC_A}),
        std::make_pair(KeymapKey{0, 0, 0, OSM(MOD_RGUI), KC_RGUI}, KeymapKey{0, 1, 1, KC_A})
        ));
// clang-format on

TEST_F(OneShot, OSMChainingTwoOSMs) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osm_key1    = KeymapKey{0, 0, 0, OSM(MOD_LSFT), KC_LSFT};
    KeymapKey  osm_key2    = KeymapKey{0, 0, 1, OSM(MOD_LCTL), KC_LCTL};
    KeymapKey  regular_key = KeymapKey{0, 1, 0, KC_A};

    set_keymap({osm_key1, osm_key2, regular_key});

    /* Press and release OSM1 */
    EXPECT_NO_REPORT(driver);
    tap_key(osm_key1);
    VERIFY_AND_CLEAR(driver);

    /* Press and relesea OSM2 */
    EXPECT_NO_REPORT(driver);
    tap_key(osm_key2);
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (osm_key1.report_code, osm_key2.report_code, regular_key.report_code)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSMDoubleTapNotLockingOSMs) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osm_key1    = KeymapKey{0, 0, 0, OSM(MOD_LSFT), KC_LSFT};
    KeymapKey  osm_key2    = KeymapKey{0, 0, 1, OSM(MOD_LCTL), KC_LCTL};
    KeymapKey  regular_key = KeymapKey{0, 1, 0, KC_A};

    set_keymap({osm_key1, osm_key2, regular_key});

    /* Press and release OSM1 */
    EXPECT_NO_REPORT(driver);
    tap_key(osm_key1);
    VERIFY_AND_CLEAR(driver);

    /* Press and release OSM2 twice */
    EXPECT_NO_REPORT(driver);
    tap_key(osm_key2);
    tap_key(osm_key2);
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (osm_key1.report_code, osm_key2.report_code, regular_key.report_code)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (regular_key.report_code)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSMHoldNotLockingOSMs) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osm_key1    = KeymapKey{0, 0, 0, OSM(MOD_LSFT), KC_LSFT};
    KeymapKey  osm_key2    = KeymapKey{0, 0, 1, OSM(MOD_LCTL), KC_LCTL};
    KeymapKey  regular_key = KeymapKey{0, 1, 0, KC_A};

    set_keymap({osm_key1, osm_key2, regular_key});

    /* Press and release OSM1 */
    EXPECT_NO_REPORT(driver);
    tap_key(osm_key1);
    VERIFY_AND_CLEAR(driver);

    /* Press and hold OSM2 */
    EXPECT_REPORT(driver, (osm_key1.report_code, osm_key2.report_code)).Times(1);
    osm_key2.press();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    /* Press and release regular key */
    EXPECT_REPORT(driver, (osm_key1.report_code, osm_key2.report_code, regular_key.report_code)).Times(1);
    EXPECT_REPORT(driver, (osm_key2.report_code)).Times(1);
    tap_key(regular_key);
    VERIFY_AND_CLEAR(driver);

    /* Release OSM2 */
    EXPECT_EMPTY_REPORT(driver);
    osm_key2.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (regular_key.report_code)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSLWithAdditionalKeypress) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  regular_key = KeymapKey{1, 1, 0, KC_A};

    set_keymap({osl_key, regular_key});

    /* Press OSL key */
    EXPECT_NO_REPORT(driver);
    osl_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release OSL key */
    EXPECT_NO_REPORT(driver);
    osl_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (regular_key.report_code)).Times(1);
    EXPECT_EMPTY_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSLWithOsmAndAdditionalKeypress) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  osm_key     = KeymapKey{1, 1, 0, OSM(MOD_LSFT), KC_LSFT};
    KeymapKey  regular_key = KeymapKey{1, 1, 1, KC_A};

    set_keymap({osl_key, osm_key, regular_key});

    /* Press OSL key */
    EXPECT_NO_REPORT(driver);
    osl_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release OSL key */
    EXPECT_NO_REPORT(driver);
    osl_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    /* Press and release OSM */
    EXPECT_NO_REPORT(driver);
    tap_key(osm_key);
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (osm_key.report_code, regular_key.report_code)).Times(1);
    EXPECT_EMPTY_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
