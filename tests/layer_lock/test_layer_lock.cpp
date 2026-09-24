// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycodes.h"
#include "test_common.hpp"

using testing::_;

class LayerLock : public TestFixture {};

TEST_F(LayerLock, LayerLockState) {
    TestDriver driver;
    KeymapKey  key_a = KeymapKey(0, 0, 0, KC_A);
    KeymapKey  key_b = KeymapKey(1, 0, 0, KC_B);
    KeymapKey  key_c = KeymapKey(2, 0, 0, KC_C);
    KeymapKey  key_d = KeymapKey(3, 0, 0, KC_C);

    set_keymap({key_a, key_b, key_c, key_d});

    EXPECT_FALSE(is_layer_locked(1));
    EXPECT_FALSE(is_layer_locked(2));
    EXPECT_FALSE(is_layer_locked(3));

    layer_lock_invert(1); // Layer 1: unlocked -> locked
    layer_lock_on(2);     // Layer 2: unlocked -> locked
    layer_lock_off(3);    // Layer 3: stays unlocked

    // Layers 1 and 2 are now on.
    EXPECT_TRUE(layer_state_is(1));
    EXPECT_TRUE(layer_state_is(2));
    // Layers 1 and 2 are now locked.
    EXPECT_TRUE(is_layer_locked(1));
    EXPECT_TRUE(is_layer_locked(2));
    EXPECT_FALSE(is_layer_locked(3));

    layer_lock_invert(1); // Layer 1: locked -> unlocked
    layer_lock_on(2);     // Layer 2: stays locked
    layer_lock_on(3);     // Layer 3: unlocked -> locked

    EXPECT_FALSE(layer_state_is(1));
    EXPECT_TRUE(layer_state_is(2));
    EXPECT_TRUE(layer_state_is(3));
    EXPECT_FALSE(is_layer_locked(1));
    EXPECT_TRUE(is_layer_locked(2));
    EXPECT_TRUE(is_layer_locked(3));

    layer_lock_invert(1); // Layer 1: unlocked -> locked
    layer_lock_off(2);    // Layer 2: locked -> unlocked

    EXPECT_TRUE(layer_state_is(1));
    EXPECT_FALSE(layer_state_is(2));
    EXPECT_TRUE(layer_state_is(3));
    EXPECT_TRUE(is_layer_locked(1));
    EXPECT_FALSE(is_layer_locked(2));
    EXPECT_TRUE(is_layer_locked(3));

    layer_lock_all_off(); // Layers 1 and 3: locked -> unlocked

    EXPECT_FALSE(layer_state_is(1));
    EXPECT_FALSE(layer_state_is(2));
    EXPECT_FALSE(layer_state_is(3));
    EXPECT_FALSE(is_layer_locked(1));
    EXPECT_FALSE(is_layer_locked(2));
    EXPECT_FALSE(is_layer_locked(3));
}

TEST_F(LayerLock, LayerLockMomentaryTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, MO(1));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

    EXPECT_NO_REPORT(driver);
    key_layer.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    EXPECT_FALSE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key_ll);
    EXPECT_TRUE(layer_state_is(1));
    EXPECT_TRUE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    key_layer.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    EXPECT_TRUE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);

    // Pressing Layer Lock again unlocks the lock.
    EXPECT_NO_REPORT(driver);
    key_ll.press();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(1));
    EXPECT_FALSE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(LayerLock, LayerLockLayerTapTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, LT(1, KC_B));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

    EXPECT_NO_REPORT(driver);
    key_layer.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key_ll);
    EXPECT_TRUE(layer_state_is(1));
    EXPECT_TRUE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);

    // Pressing Layer Lock again unlocks the lock.
    EXPECT_NO_REPORT(driver);
    key_ll.press();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(1));
    EXPECT_FALSE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(LayerLock, LayerLockOneshotTapTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, OSL(1));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

    EXPECT_NO_REPORT(driver);
    tap_key(key_layer);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key_ll);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    EXPECT_TRUE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);

    // Pressing Layer Lock again unlocks the lock.
    EXPECT_NO_REPORT(driver);
    key_ll.press();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(1));
    EXPECT_FALSE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(LayerLock, LayerLockOneshotHoldTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, OSL(1));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

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
    EXPECT_TRUE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);

    // Pressing Layer Lock again unlocks the lock.
    EXPECT_NO_REPORT(driver);
    key_ll.press();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(1));
    EXPECT_FALSE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(LayerLock, LayerLockTimeoutTest) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, MO(1));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_trns  = KeymapKey(1, 0, 0, KC_TRNS);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_trns, key_ll});

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
    EXPECT_TRUE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    idle_for(LAYER_LOCK_IDLE_TIMEOUT);
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(1));
    EXPECT_FALSE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(LayerLock, ToKeyOverridesLayerLock) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, MO(1));
    KeymapKey  key_to0   = KeymapKey(1, 0, 0, TO(0));
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_to0, key_ll});

    EXPECT_NO_REPORT(driver);
    layer_lock_on(1);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    EXPECT_TRUE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key_to0); // TO(0) overrides Layer Lock and unlocks layer 1.
    EXPECT_FALSE(layer_state_is(1));
    EXPECT_FALSE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);
}

TEST_F(LayerLock, LayerClearOverridesLayerLock) {
    TestDriver driver;
    KeymapKey  key_layer = KeymapKey(0, 0, 0, MO(1));
    KeymapKey  key_a     = KeymapKey(0, 1, 0, KC_A);
    KeymapKey  key_ll    = KeymapKey(1, 1, 0, QK_LAYER_LOCK);

    set_keymap({key_layer, key_a, key_ll});

    EXPECT_NO_REPORT(driver);
    layer_lock_on(1);
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    EXPECT_TRUE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A));
    layer_clear(); // layer_clear() overrides Layer Lock and unlocks layer 1.
    key_a.press();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(1));
    EXPECT_FALSE(is_layer_locked(1));
    VERIFY_AND_CLEAR(driver);
}
