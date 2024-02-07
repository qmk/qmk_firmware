// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycodes.h"
#include "test_common.hpp"

using testing::_;

class LayerLock : public TestFixture {};

TEST_F(LayerLock, LayerLockMomentaryTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, MO(1));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

    /* Press Lower. */
    EXPECT_NO_REPORT(driver);
    key_layer.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key_ll);
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    key_layer.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(LayerLock, LayerLockLayerTapTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, LT(1, KC_B));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

    /* Press Lower. */
    EXPECT_NO_REPORT(driver);
    key_layer.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key_ll);
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(LayerLock, LayerLockOneshotTapTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, OSL(1));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

    /* Press Lower. */
    EXPECT_NO_REPORT(driver);
    tap_key(key_layer);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key_ll);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(LayerLock, LayerLockOneshotHoldTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, OSL(1));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

    /* Press Lower. */
    EXPECT_NO_REPORT(driver);
    key_layer.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key_ll);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    key_layer.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);
}


TEST_F(LayerLock, LayerLockTimeoutTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, MO(1));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

    /* Press Lower. */
    EXPECT_NO_REPORT(driver);
    key_layer.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key_ll);
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    key_layer.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    idle_for(LAYER_LOCK_IDLE_TIMEOUT);
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);
}
