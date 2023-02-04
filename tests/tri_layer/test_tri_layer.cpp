// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test_common.hpp"


using testing::_;
using testing::InSequence;

class ActionLayer : public TestFixture {};

TEST_F(ActionLayer, TriLayerStateTest) {
    TestDriver driver;
    KeymapKey  lower_layer_key  = KeymapKey{0, 0, 0, QK_TRI_LAYER_LOWER};
    KeymapKey  raise_layer_key  = KeymapKey{0, 1, 0, QK_TRI_LAYER_RAISE};

    set_keymap({raise_layer_key, lower_layer_key, \
        KeymapKey{1, 0, 0, KC_TRNS}, KeymapKey{1, 1, 0, KC_TRNS}, \
        KeymapKey{2, 0, 0, KC_TRNS}, KeymapKey{2, 1, 0, KC_TRNS}, \
        KeymapKey{3, 0, 0, KC_TRNS}, KeymapKey{3, 1, 0, KC_TRNS}, \
        });

    /* Press Lower. */
    EXPECT_NO_REPORT(driver);
    lower_layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_raise_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);

    /* Release Lower. */
    EXPECT_NO_REPORT(driver);
    lower_layer_key.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_raise_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);

    /* Press Raise. */
    EXPECT_NO_REPORT(driver);
    raise_layer_key.press();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_TRUE(layer_state_is(get_tri_layer_raise_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);

    /* Release Raise. */
    EXPECT_NO_REPORT(driver);
    raise_layer_key.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_raise_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);


    /* Press Lower, then raise, and release raise and then lower. */
    EXPECT_NO_REPORT(driver);
    lower_layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_raise_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));

    raise_layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_TRUE(layer_state_is(get_tri_layer_raise_layer()));
    EXPECT_TRUE(layer_state_is(get_tri_layer_adjust_layer()));

    raise_layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_raise_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));

    lower_layer_key.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(get_tri_layer_lower_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_raise_layer()));
    EXPECT_FALSE(layer_state_is(get_tri_layer_adjust_layer()));
    VERIFY_AND_CLEAR(driver);

}
