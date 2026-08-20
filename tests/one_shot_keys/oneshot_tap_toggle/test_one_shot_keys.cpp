// Copyright 2026 NapOli1084 (@NapOli1084)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "action_util.h"
#include "keyboard_report_util.hpp"
#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class OneShot : public TestFixture {
   protected:
    TestDriver driver;
};

class OneShotParametrizedTestFixture : public ::testing::WithParamInterface<std::pair<KeymapKey, KeymapKey>>, public OneShot {
   protected:
    void setup_lock_osm_and_verify(KeymapKey& osm_key, KeymapKey& regular_key) {
        set_keymap({osm_key, regular_key});

        /* Lock OSM by tapping it ONESHOT_TAP_TOGGLE times */
        EXPECT_REPORT(driver, (osm_key.report_code)).Times(1);
        for (int i = 0; i < ONESHOT_TAP_TOGGLE; ++i) {
            tap_key(osm_key);
        }
        VERIFY_AND_CLEAR(driver);

        /* Press regular key */
        EXPECT_REPORT(driver, (osm_key.report_code, regular_key.report_code)).Times(1);
        regular_key.press();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        /* Release regular key */
        EXPECT_REPORT(driver, (osm_key.report_code)).Times(1);
        regular_key.release();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        /* Tap regular key again; mod should still be reported */
        EXPECT_REPORT(driver, (osm_key.report_code, regular_key.report_code)).Times(1);
        EXPECT_REPORT(driver, (osm_key.report_code)).Times(1);
        tap_key(regular_key);
        VERIFY_AND_CLEAR(driver);
    }

    void tap_regular_key_no_mod(KeymapKey& regular_key) {
        /* Tap regular key; confirm no mod */
        EXPECT_REPORT(driver, (regular_key.report_code)).Times(1);
        EXPECT_EMPTY_REPORT(driver);
        tap_key(regular_key);
        VERIFY_AND_CLEAR(driver);
    }
};

TEST_P(OneShotParametrizedTestFixture, OSMLockAndUnlockOnTap) {
    KeymapKey osm_key     = GetParam().first;
    KeymapKey regular_key = GetParam().second;

    setup_lock_osm_and_verify(osm_key, regular_key);

    /* Unlock OSM by tapping it */
    EXPECT_EMPTY_REPORT(driver);
    tap_key(osm_key);
    VERIFY_AND_CLEAR(driver);

    tap_regular_key_no_mod(regular_key);
}

TEST_P(OneShotParametrizedTestFixture, OSMLockAndUnlockOnHold) {
    KeymapKey osm_key     = GetParam().first;
    KeymapKey regular_key = GetParam().second;

    setup_lock_osm_and_verify(osm_key, regular_key);

    /* Unlock OSM by holding it */
    EXPECT_NO_REPORT(driver);
    osm_key.press();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    /* Release OSM */
    EXPECT_EMPTY_REPORT(driver);
    osm_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    tap_regular_key_no_mod(regular_key);
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
