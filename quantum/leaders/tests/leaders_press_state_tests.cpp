/* Copyright 2017 Alex Olkhovskiy
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
#include <cstdarg>
#include "quantum_keycodes.h"
extern "C" {
#include "leaders/press_state.h"
}
class Pressstate : public testing::Test {

public:
  keypos_t keys[20];
  Pressstate() {
    init_press_state();
    for (int8_t i = 0; i < 20; i++) {
      keys[i] = (keypos_t) {
        .col = i,
        .row = i
      };
    }
  }
  virtual ~Pressstate() {
  }

};

TEST_F(Pressstate, init_press_state_works ) {
  ASSERT_EQ(press_state_get(), 0UL );
}

TEST_F(Pressstate, press_state_basic_put_remove_works ) {
  press_state_put((press_t) {.key=keys[0],  .keycode=42, .ignore=true, .sentinels=0x0000 });
  ASSERT_EQ(press_state_get(), 1UL );
  press_state_remove_by_idx(find_press(keys[1]));
  ASSERT_EQ(press_state_get(), 1UL );
  press_state_remove_by_idx(find_press(keys[0]));
  ASSERT_EQ(press_state_get(), 0UL );
}

TEST_F(Pressstate, remove_press_in_the_middle ) {
  ASSERT_EQ(press_state_get(), 0UL );
  press_state_put((press_t) {.key=keys[0],  .keycode=43, .ignore=true, .sentinels=0x0000 });
  press_state_put((press_t) {.key=keys[1],  .keycode=42, .ignore=true, .sentinels=0x0000 });
  press_state_put((press_t) {.key=keys[2],  .keycode=45, .ignore=true, .sentinels=0x0000 });
  press_state_put((press_t) {.key=keys[3],  .keycode=46, .ignore=true, .sentinels=0x0000 });
  press_state_remove_by_idx(find_press(keys[1]));
  ASSERT_EQ(press_state_get(), 0b0000000000001101);
  press_state_remove_by_idx(find_press(keys[9]));
  ASSERT_EQ(press_state_get(), 0b0000000000001101);
}

TEST_F(Pressstate, biton16_test1 ) {
  ASSERT_EQ(biton16(0b000), 0 );
  ASSERT_EQ(biton16(0b001), 0 );
  ASSERT_EQ(biton16(0b011), 1 );
  ASSERT_EQ(biton16(0b101), 2 );
  ASSERT_EQ(biton16(0b100), 2 );
  ASSERT_EQ(biton16(0b1100), 3 );
}
