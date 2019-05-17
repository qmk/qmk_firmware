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

#include "test_common.hpp"

using testing::_;
using testing::InSequence;

LEADERMANAGER_EXTERNS();

keypos_t key = (keypos_t) {
  .col = 0,
  .row = 0
};

keyevent_t press_event = keyevent_t {
  .key = key,
  .pressed = true
};

keyrecord_t pressed_record = (keyrecord_t) {
  .event = press_event
};

uint16_t* test_definitions[]  = {
  (uint16_t[]){3, KC_A, KC_B},
  (uint16_t[]){4, KC_B, KC_C, KC_D},
  (uint16_t[]){1}
};

class ProcessLeadersTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    leaders_init();
    keyseq_set_definitions(test_definitions);
  }
};

TEST_F(ProcessLeadersTest, process_leaders_basic_test) {
  process_leaders(KC_A, &pressed_record);
  ASSERT_EQ(keyseq_index, 0);
  ASSERT_EQ(momentary_sentinels, 0);
  ASSERT_EQ(oneshot_sentinel, true);
}


TEST_F(ProcessLeadersTest, process_leaders_basic_match_test1) {
  keyseq_index = 0;
  keyseq_push(KC_A);
  keyseq_reset_momentary(1);
  process_leaders(KC_A, &pressed_record);
  ASSERT_EQ(oneshot_sentinel, true);
  ASSERT_EQ(keyseq_index, 0);
}
