/* Copyright 2025 Garretonzo
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

#include "gtest/gtest.h"

extern "C" {
#include "quantum/action_layer.h"
#include "quantum/action.h"
#include "quantum/dynamic_keymap.h"
#include "quantum/quantum_keycodes.h"
#include "quantum/keymap_common.h"
#include "keycode_cache_mock.h"
}

// Mock variables for testing
extern "C" {
    // These need to be defined for the tests to compile
    bool disable_action_cache = false;
}

class KeycodeCacheTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // Reset any global state before each test
        disable_action_cache = false;
        
        // Initialize test key position
        test_key.row = 0;
        test_key.col = 0;
        
        // Initialize test keycodes
        initial_keycode = KC_A;
        changed_keycode = KC_B;
        
        // Set initial keymap
        dynamic_keymap_set_keycode(0, test_key.row, test_key.col, initial_keycode);
    }

    void TearDown() override {
        // Clean up after each test
        disable_action_cache = false;
    }

    keypos_t test_key;
    uint16_t initial_keycode;
    uint16_t changed_keycode;
};

#ifdef KEYCODE_CACHE_ENABLE

TEST_F(KeycodeCacheTest, TestKeycodeMatchOnPressAndRelease) {
    // Test that store_or_get_action works with keycode cache enabled
    // The keycode when pressed should match the keycode when released
    
    // Press the key
    action_t press_action = store_or_get_action(true, test_key);
    
    // Release the key
    action_t release_action = store_or_get_action(false, test_key);
    
    // Both actions should be for the same keycode
    EXPECT_EQ(press_action.code, release_action.code);
    EXPECT_EQ(press_action.code, action_for_keycode(initial_keycode).code);
}

TEST_F(KeycodeCacheTest, TestCacheLimitExceeded) {
    // Test that when keycode cache limit is exceeded, 
    // it falls back to default functionality
    
    // Fill the cache to the limit
    keypos_t keys[KEYCODE_CACHE_LIMIT + 1];
    for (int i = 0; i <= KEYCODE_CACHE_LIMIT; i++) {
        keys[i].row = i / MATRIX_COLS;
        keys[i].col = i % MATRIX_COLS;
        dynamic_keymap_set_keycode(0, keys[i].row, keys[i].col, KC_A + i);
        
        // Press each key
        store_or_get_action(true, keys[i]);
    }
    
    // The last key should not be cached (exceeds limit)
    // Change its keycode
    uint16_t new_keycode = KC_Z;
    dynamic_keymap_set_keycode(0, keys[KEYCODE_CACHE_LIMIT].row, keys[KEYCODE_CACHE_LIMIT].col, new_keycode);
    
    // Release the last key - should get the NEW keycode (not cached)
    action_t release_action = store_or_get_action(false, keys[KEYCODE_CACHE_LIMIT]);
    EXPECT_EQ(release_action.code, action_for_keycode(new_keycode).code);
    
    // Clean up - release all other keys
    for (int i = 0; i < KEYCODE_CACHE_LIMIT; i++) {
        store_or_get_action(false, keys[i]);
    }
}

TEST_F(KeycodeCacheTest, TestDynamicKeymapChangeWithCache) {
    // Test with keycode cache: a key is pressed, during the press
    // dynamic_keymap_set_keycode remaps the key to a different key,
    // then when released, the released key should match the initial key
    
    // Press the key (should cache initial_keycode)
    action_t press_action = store_or_get_action(true, test_key);
    EXPECT_EQ(press_action.code, action_for_keycode(initial_keycode).code);
    
    // While key is pressed, change the keymap
    dynamic_keymap_set_keycode(0, test_key.row, test_key.col, changed_keycode);
    
    // Release the key - should get the ORIGINAL cached keycode
    action_t release_action = store_or_get_action(false, test_key);
    EXPECT_EQ(release_action.code, action_for_keycode(initial_keycode).code);
    EXPECT_NE(release_action.code, action_for_keycode(changed_keycode).code);
}

#endif // KEYCODE_CACHE_ENABLE

TEST_F(KeycodeCacheTest, TestDynamicKeymapChangeWithoutCache) {
    // Test without keycode cache: a key is pressed, during the press
    // dynamic_keymap_set_keycode remaps the key to a different key,
    // then when released, the released key should match the NEW key
    
    // Disable cache for this test
    disable_action_cache = true;
    
    // Press the key
    action_t press_action = store_or_get_action(true, test_key);
    EXPECT_EQ(press_action.code, action_for_keycode(initial_keycode).code);
    
    // While key is pressed, change the keymap
    dynamic_keymap_set_keycode(0, test_key.row, test_key.col, changed_keycode);
    
    // Release the key - should get the NEW keycode (no cache)
    action_t release_action = store_or_get_action(false, test_key);
    EXPECT_EQ(release_action.code, action_for_keycode(changed_keycode).code);
    EXPECT_NE(release_action.code, action_for_keycode(initial_keycode).code);
}

#ifdef KEYCODE_CACHE_ENABLE

TEST_F(KeycodeCacheTest, TestCacheUpdateExistingKey) {
    // Test that pressing the same key twice updates the cache entry
    // rather than creating a duplicate
    
    // Press the key
    store_or_get_action(true, test_key);
    
    // Change the keymap
    dynamic_keymap_set_keycode(0, test_key.row, test_key.col, changed_keycode);
    
    // Press the same key again (should update existing cache entry)
    action_t second_press_action = store_or_get_action(true, test_key);
    EXPECT_EQ(second_press_action.code, action_for_keycode(changed_keycode).code);
    
    // Release should get the updated keycode
    action_t release_action = store_or_get_action(false, test_key);
    EXPECT_EQ(release_action.code, action_for_keycode(changed_keycode).code);
}

TEST_F(KeycodeCacheTest, TestCacheRemovalOnRelease) {
    // Test that releasing a key removes it from the cache
    
    // Press and release a key
    store_or_get_action(true, test_key);
    store_or_get_action(false, test_key);
    
    // Change the keymap
    dynamic_keymap_set_keycode(0, test_key.row, test_key.col, changed_keycode);
    
    // Press the key again - should use new keycode (not cached)
    action_t press_action = store_or_get_action(true, test_key);
    EXPECT_EQ(press_action.code, action_for_keycode(changed_keycode).code);
    
    // Clean up
    store_or_get_action(false, test_key);
}

TEST_F(KeycodeCacheTest, TestMultipleKeysInCache) {
    // Test that multiple keys can be cached simultaneously
    
    keypos_t key1 = {0, 0};
    keypos_t key2 = {0, 1};
    uint16_t keycode1 = KC_A;
    uint16_t keycode2 = KC_B;
    
    // Set up keymaps
    dynamic_keymap_set_keycode(0, key1.row, key1.col, keycode1);
    dynamic_keymap_set_keycode(0, key2.row, key2.col, keycode2);
    
    // Press both keys
    action_t press1 = store_or_get_action(true, key1);
    action_t press2 = store_or_get_action(true, key2);
    
    EXPECT_EQ(press1.code, action_for_keycode(keycode1).code);
    EXPECT_EQ(press2.code, action_for_keycode(keycode2).code);
    
    // Change both keymaps
    dynamic_keymap_set_keycode(0, key1.row, key1.col, KC_X);
    dynamic_keymap_set_keycode(0, key2.row, key2.col, KC_Y);
    
    // Release both keys - should get original keycodes
    action_t release1 = store_or_get_action(false, key1);
    action_t release2 = store_or_get_action(false, key2);
    
    EXPECT_EQ(release1.code, action_for_keycode(keycode1).code);
    EXPECT_EQ(release2.code, action_for_keycode(keycode2).code);
}

#endif // KEYCODE_CACHE_ENABLE
