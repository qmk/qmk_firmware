/* Copyright 2018 Fred Sundvik
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

#if MAX_LAYER_BITS != 5
#error "Tese tests assume that the MAX_LAYER_BITS is equal to 5"
// If this is changed, change the constants below
#endif

#if MATRIX_COLS != 2 || MATRIX_ROWS !=2
#error "These tests assume that the second row starts after the second column"
#endif

namespace
{
  constexpr uint8_t max_layer_value = 0b11111;
  constexpr uint8_t min_layer_value = 0;
  constexpr uint8_t alternating_starting_with_1 = 0b10101;
  constexpr uint8_t alternating_starting_with_0 = 0b01010;


  uint8_t read_cache(uint8_t col, uint8_t row) {
    keypos_t key;
    key.col = col;
    key.row =  row;
    return read_source_layers_cache(key);
  }

  void write_cache(uint8_t col, uint8_t row, uint8_t value) {
    keypos_t key;
    key.col = col;
    key.row =  row;
    return update_source_layers_cache(key, value);
  }

  void fill_cache() {
    for (int i=0; i < MATRIX_ROWS; i++) {
      for (int j=0; j < MATRIX_COLS; j++) {
        write_cache(j, i, max_layer_value);
      }
    }
  }

  void clear_cache() {
    for (int i=0; i < MATRIX_ROWS; i++) {
      for (int j=0; j < MATRIX_COLS; j++) {
        write_cache(j, i, min_layer_value);
      }
    }
  }
}

class LayerCache : public testing::Test
{
public:
  LayerCache()
  {
    clear_cache();
  }
};

TEST_F(LayerCache, LayerCacheIsInitializedToZero) {
  for (int i=0; i < MATRIX_ROWS; i++) {
    for (int j=0; j < MATRIX_COLS; j++) {
      EXPECT_EQ(read_cache(j, i), min_layer_value);
    }
  }
}

TEST_F(LayerCache, FillAndClearCache) {
  fill_cache();
  clear_cache();
  for (int i=0; i < MATRIX_ROWS; i++) {
    for (int j=0; j < MATRIX_COLS; j++) {
      EXPECT_EQ(read_cache(j, i), min_layer_value);
    }
  }
}

TEST_F(LayerCache, WriteAndReadFirstPosMaximumValue) {
  write_cache(0, 0, max_layer_value);
  EXPECT_EQ(read_cache(0, 0), max_layer_value);
  // The second position should not be updated
  EXPECT_EQ(read_cache(1, 0), min_layer_value);
  EXPECT_EQ(read_cache(0, 1), min_layer_value);
}

TEST_F(LayerCache, WriteAndReadSecondPosMaximumValue) {
  write_cache(1, 0, max_layer_value);
  EXPECT_EQ(read_cache(1, 0), max_layer_value);
  // The surrounding positions should not be updated
  EXPECT_EQ(read_cache(0, 0), min_layer_value);
  EXPECT_EQ(read_cache(0, 1), min_layer_value);
}

TEST_F(LayerCache, WriteAndReadFirstPosAlternatingBitsStartingWith1) {
  write_cache(0, 0, alternating_starting_with_1);
  EXPECT_EQ(read_cache(0, 0), alternating_starting_with_1);
  // The second position should not be updated
  EXPECT_EQ(read_cache(1, 0), min_layer_value);
  EXPECT_EQ(read_cache(0, 1), min_layer_value);
}

TEST_F(LayerCache, WriteAndReadSecondPosAlternatingBitsStartingWith1) {
  write_cache(1, 0, alternating_starting_with_1);
  EXPECT_EQ(read_cache(1, 0), alternating_starting_with_1);
  // The surrounding positions should not be updated
  EXPECT_EQ(read_cache(0, 0), min_layer_value);
  EXPECT_EQ(read_cache(0, 1), min_layer_value);
}

TEST_F(LayerCache, WriteAndReadFirstPosAlternatingBitsStartingWith0) {
  write_cache(0, 0, alternating_starting_with_0);
  EXPECT_EQ(read_cache(0, 0), alternating_starting_with_0);
  // The second position should not be updated
  EXPECT_EQ(read_cache(1, 0), min_layer_value);
  EXPECT_EQ(read_cache(0, 1), min_layer_value);
}

TEST_F(LayerCache, WriteAndReadSecondPosAlternatingBitsStartingWith0) {
  write_cache(1, 0, alternating_starting_with_0);
  EXPECT_EQ(read_cache(1, 0), alternating_starting_with_0);
  // The surrounding positions should not be updated
  EXPECT_EQ(read_cache(0, 0), min_layer_value);
  EXPECT_EQ(read_cache(0, 1), min_layer_value);
}
