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
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    osm_key.press();
    run_one_scan_loop();
    osm_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* OSM are added when an actual report is send */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(osm_key.report_code)));
    send_keyboard_report();
    testing::Mock::VerifyAndClearExpectations(&driver);

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
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    osm_key.press();
    run_one_scan_loop();
    osm_key.release();
    idle_for(ONESHOT_TIMEOUT);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(regular_key.report_code))).Times(1);
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

#endif

TEST_P(OneShotParametrizedTestFixture, OSMWithAdditionalKeypress) {
    TestDriver driver;
    KeymapKey  osm_key     = GetParam().first;
    KeymapKey  regular_key = GetParam().second;

    set_keymap({osm_key, regular_key});

    /* Press and release OSM */
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    osm_key.press();
    run_one_scan_loop();
    osm_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(osm_key.report_code, regular_key.report_code))).Times(1);
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_P(OneShotParametrizedTestFixture, OSMAsRegularModifierWithAdditionalKeypress) {
    TestDriver          driver;
    testing::InSequence s;

    KeymapKey osm_key     = GetParam().first;
    KeymapKey regular_key = GetParam().second;

    set_keymap({osm_key, regular_key});

    /* Press OSM */
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    osm_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key */
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key */
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release OSM */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(regular_key.report_code, osm_key.report_code))).Times(1);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(1);
    osm_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
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

TEST_F(OneShot, OSLWithAdditionalKeypress) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  regular_key = KeymapKey{1, 1, 0, KC_A};

    set_keymap({osl_key, regular_key});

    /* Press OSL key */
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    osl_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release OSL key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(2);
    osl_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(regular_key.report_code))).Times(2);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    regular_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key */
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    regular_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}
