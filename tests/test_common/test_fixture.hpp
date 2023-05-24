/* Copyright 2017 Fred Sundvik
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

#pragma once

#include <cstdint>
#include <unordered_map>
#include <optional>
#include "gtest/gtest.h"
#include "keyboard.h"
#include "test_keymap_key.hpp"

class TestFixture : public testing::Test {
   public:
    static TestFixture* m_this;

    TestFixture();
    ~TestFixture();
    static void SetUpTestCase();
    static void TearDownTestCase();

    void set_keymap(std::initializer_list<KeymapKey> keycodes);
    void add_key(const KeymapKey key);

    const KeymapKey* find_key(const layer_t layer_t, const keypos_t position) const;
    void             get_keycode(const layer_t layer, const keypos_t position, uint16_t* result) const;

    /**
     * @brief Taps `key` with `delay_ms` delay between press and release.
     */
    void tap_key(KeymapKey key, unsigned delay_ms = 1);

    /**
     * @brief Taps multiple KeymapKey keys in order, e.g. `tap_keys(key_a, key_b)`.
     */
    template <typename... Ts>
    void tap_keys(Ts... keys) {
        for (KeymapKey key : {keys...}) {
            tap_key(key);
        }
    }

    void run_one_scan_loop();
    void idle_for(unsigned ms);

    void expect_layer_state(layer_t layer) const;

   protected:
    void                   print_test_log() const;
    std::vector<KeymapKey> keymap;
};
