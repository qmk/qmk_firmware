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

class SequenceTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    momentary_sentinels = 0x0000;
    oneshot_sentinel = true;
    keyseq_index = 0;
  }
};

TEST_F(SequenceTest, reset_momentary_with_oneshot_test1 ) {
  keyseq_push(KC_A);
  keyseq_push(KC_A);
  keyseq_push(KC_A);
  ASSERT_EQ(keyseq_index, 3);
  keyseq_reset_momentary(3);
  ASSERT_EQ(keyseq_index, 3);
  keyseq_reset_momentary(1);
  ASSERT_EQ(keyseq_index, 3);
  keyseq_reset_momentary(2);
  ASSERT_EQ(keyseq_index, 3);
  keyseq_reset_oneshot();
  ASSERT_EQ(keyseq_index, 0);
}

TEST_F(SequenceTest, reset_momentary_no_oneshot_test1 ) {
  ASSERT_EQ(momentary_sentinels, 0);
  ASSERT_EQ(oneshot_sentinel, true);
  ASSERT_EQ(keyseq_index, 0);
  keyseq_push(KC_A);
  ASSERT_EQ(keyseq_index, 1);
  ASSERT_EQ(momentary_sentinels, 0b1);
  keyseq_push(KC_A);
  keyseq_push(KC_A);
  ASSERT_EQ(keyseq_index, 3);
  keyseq_reset_oneshot();
  ASSERT_EQ(keyseq_index, 3);
  keyseq_reset_momentary(3);
  ASSERT_EQ(keyseq_index, 2);
  keyseq_reset_momentary(1);
  ASSERT_EQ(keyseq_index, 2);
  keyseq_reset_momentary(2);
  ASSERT_EQ(keyseq_index, 0);
}
