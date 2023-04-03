// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class TriLayer : public TestFixture {};

TEST_F(TriLayer, TriLayerLowerTest) {
    TestDriver driver;
    KeymapKey  lower_layer_key = KeymapKey{0, 0, 0, QK_TRI_LAYER_LOWER};

    set_keymap({lower_layer_key, KeymapKey{1, 0, 0, KC_TRNS}});

    /* Press Lower. */
    EXPECT_NO_REPORT(driver);
    lower_layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_upper_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);

    /* Release Lower. */
    EXPECT_NO_REPORT(driver);
    lower_layer_key.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_upper_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(TriLayer, TriLayerUpperTest) {
    TestDriver driver;
    KeymapKey  upper_layer_key = KeymapKey{0, 0, 0, QK_TRI_LAYER_UPPER};

    set_keymap({upper_layer_key, KeymapKey{2, 0, 0, KC_TRNS}});

    /* Press Raise. */
    EXPECT_NO_REPORT(driver);
    upper_layer_key.press();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_TRUE(layer_state_is(get_tri_layer_upper_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);

    /* Release Raise. */
    EXPECT_NO_REPORT(driver);
    upper_layer_key.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_upper_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(TriLayer, TriLayerAdjustTest) {
    TestDriver driver;
    KeymapKey  lower_layer_key = KeymapKey{0, 0, 0, QK_TRI_LAYER_LOWER};
    KeymapKey  upper_layer_key = KeymapKey{0, 1, 0, QK_TRI_LAYER_UPPER};

    set_keymap({
        upper_layer_key,
        lower_layer_key,
        KeymapKey{1, 0, 0, KC_TRNS},
        KeymapKey{1, 1, 0, KC_TRNS},
        KeymapKey{2, 0, 0, KC_TRNS},
        KeymapKey{2, 1, 0, KC_TRNS},
        KeymapKey{3, 0, 0, KC_TRNS},
        KeymapKey{3, 1, 0, KC_TRNS},
    });

    /* Press Lower, then upper, and release upper and then lower. */
    EXPECT_NO_REPORT(driver);
    lower_layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_upper_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));

    upper_layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_TRUE(layer_state_is(get_tri_layer_upper_layer()));
    EXPECT_TRUE(layer_state_is(get_tri_layer_adjust_layer()));

    lower_layer_key.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_TRUE(layer_state_is(get_tri_layer_upper_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));

    upper_layer_key.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_upper_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);
}
