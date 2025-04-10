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

    /* Press and release OSM2 */
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

TEST_F(OneShot, OSLWithMoAndAdditionalKeypress) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  mo_key      = KeymapKey{1, 1, 0, MO(2)};
    KeymapKey  regular_key = KeymapKey{2, 1, 1, KC_A};

    set_keymap({osl_key, mo_key, regular_key});

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

    /* Press MO */
    EXPECT_NO_REPORT(driver);
    mo_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(2));
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (regular_key.report_code)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(2));
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release MO */
    EXPECT_NO_REPORT(driver);
    mo_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));
    VERIFY_AND_CLEAR(driver);
}

class OneShotLayerParametrizedTestFixture : public ::testing::WithParamInterface<uint16_t>, public OneShot {};

TEST_P(OneShotLayerParametrizedTestFixture, OSLWithActionAndAdditionalKeypress) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  action_key  = KeymapKey{1, 1, 0, GetParam()};
    KeymapKey  regular_key = KeymapKey{2, 1, 1, KC_A};

    set_keymap({osl_key, action_key, regular_key});

    /* Tap OSL key */
    EXPECT_NO_REPORT(driver);
    tap_key(osl_key);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Tag Action key */
    EXPECT_NO_REPORT(driver);
    tap_key(action_key);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(2));
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (regular_key.report_code)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(2));
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

INSTANTIATE_TEST_CASE_P(OneShotLayerTests, OneShotLayerParametrizedTestFixture, ::testing::Values(TG(2), TO(2)));

TEST_F(OneShot, OSLWithDFAndAdditionalKeypress) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  df_key      = KeymapKey{1, 1, 0, DF(2)};
    KeymapKey  regular_key = KeymapKey{2, 1, 1, KC_A};

    set_keymap({osl_key, df_key, regular_key});

    layer_state_t default_layer_state_bak = default_layer_state;

    /* Tap OSL key */
    EXPECT_NO_REPORT(driver);
    tap_key(osl_key);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    /* Press DF key */
    EXPECT_NO_REPORT(driver);
    df_key.press();
    run_one_scan_loop();
    EXPECT_EQ(default_layer_state, 0b001);

    VERIFY_AND_CLEAR(driver);

    /* Release DF key */
    EXPECT_NO_REPORT(driver);
    df_key.release();
    run_one_scan_loop();
    EXPECT_EQ(default_layer_state, 0b100);
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

    default_layer_state = default_layer_state_bak;
}

TEST_F(OneShot, OSLChainingTwoOSLsAndAdditionalKeypress) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl1_key    = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  osl2_key    = KeymapKey{1, 1, 0, OSL(2)};
    KeymapKey  regular_key = KeymapKey{2, 1, 1, KC_A};

    set_keymap({osl1_key, osl2_key, regular_key});

    /* Press and release first OSL key */
    EXPECT_NO_REPORT(driver);
    osl1_key.press();
    run_one_scan_loop();
    osl1_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    /* Press and release second OSL */
    EXPECT_NO_REPORT(driver);
    osl2_key.press();
    run_one_scan_loop();
    osl2_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(2));
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
    EXPECT_TRUE(layer_state_is(0));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSLWithShortLT) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  lt_key  = KeymapKey(1, 1, 0, LT(2, KC_A));

    set_keymap({osl_key, lt_key});

    /* Tap OSL key */
    EXPECT_NO_REPORT(driver);
    tap_key(osl_key);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    /* Tap LT key. */
    EXPECT_REPORT(driver, (lt_key.report_code)).Times(1);
    EXPECT_EMPTY_REPORT(driver);
    tap_key(lt_key);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSLWithLongLTAndRegularKey) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  lt_key      = KeymapKey(1, 1, 0, LT(2, KC_A));
    KeymapKey  regular_key = KeymapKey(2, 1, 1, KC_B);

    set_keymap({osl_key, lt_key, regular_key});

    /* Tap OSL key */
    EXPECT_NO_REPORT(driver);
    tap_key(osl_key);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    /* Press LT key. */
    EXPECT_NO_REPORT(driver);
    lt_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Idle for tapping term of mod tap hold key. */
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);
    EXPECT_TRUE(layer_state_is(2));

    /* Press regular key. */
    EXPECT_REPORT(driver, (regular_key.report_code)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSLWithShortModTapKeyAndRegularKey) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key          = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  mod_tap_hold_key = KeymapKey(1, 1, 0, SFT_T(KC_P));
    KeymapKey  regular_key      = KeymapKey(0, 2, 0, KC_A);

    set_keymap({osl_key, mod_tap_hold_key, regular_key});

    /* Tap OSL key */
    EXPECT_NO_REPORT(driver);
    tap_key(osl_key);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

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

    /* Press regular key. */
    EXPECT_REPORT(driver, (regular_key.report_code));
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSLWithLongModTapKeyAndRegularKey) {
    TestDriver driver;
    InSequence s;
    KeymapKey  osl_key          = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  mod_tap_hold_key = KeymapKey(1, 1, 0, SFT_T(KC_P));
    KeymapKey  regular_key      = KeymapKey(1, 2, 0, KC_A);

    set_keymap({osl_key, mod_tap_hold_key, regular_key});

    /* Tap OSL key */
    EXPECT_NO_REPORT(driver);
    tap_key(osl_key);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    /* Press mod-tap-hold key. */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Idle for tapping term of mod tap hold key. */
    EXPECT_REPORT(driver, (KC_LSFT));
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* Release mod-tap-hold key. */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key. */
    EXPECT_REPORT(driver, (regular_key.report_code)).Times(1);
    EXPECT_EMPTY_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key. */
    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}