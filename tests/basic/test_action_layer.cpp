/* Copyright 2017 Colin T.A. Gray
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
using testing::Return;

class ActionLayer : public TestFixture {};

// TEST_F(ActionLayer, LayerStateDBG) {
//     layer_state_set(0);
// }

// TEST_F(ActionLayer, LayerStateSet) {
//     layer_state_set(0);
//     EXPECT_EQ(layer_state, 0);
//     layer_state_set(0b001100);
//     EXPECT_EQ(layer_state, 0b001100);
// }

// TEST_F(ActionLayer, LayerStateIs) {
//     layer_state_set(0);
//     EXPECT_EQ(layer_state_is(0), true);
//     EXPECT_EQ(layer_state_is(1), true);
//     layer_state_set(1);
//     EXPECT_EQ(layer_state_is(0), true);
//     EXPECT_EQ(layer_state_is(1), true);
//     layer_state_set(2);
//     EXPECT_EQ(layer_state_is(0), false);
//     EXPECT_EQ(layer_state_is(1), false);
//     EXPECT_EQ(layer_state_is(2), true);
// }

TEST_F(ActionLayer, LayerStateCmp) {
    uint32_t prev_layer;

    prev_layer = 0;
    EXPECT_EQ(layer_state_cmp(prev_layer, 0), true);
    EXPECT_EQ(layer_state_cmp(prev_layer, 1), false);

    prev_layer = 1;
    EXPECT_EQ(layer_state_cmp(prev_layer, 0), true);
    EXPECT_EQ(layer_state_cmp(prev_layer, 1), false);

    prev_layer = 2;
    EXPECT_EQ(layer_state_cmp(prev_layer, 0), false);
    EXPECT_EQ(layer_state_cmp(prev_layer, 1), true);
    EXPECT_EQ(layer_state_cmp(prev_layer, 2), false);
}

// TEST_F(ActionLayer, LayerClear) {
//     layer_clear();
//     EXPECT_EQ(layer_state, 0);
// }

// TEST_F(ActionLayer, LayerMove) {
//     layer_move(0);
//     EXPECT_EQ(layer_state, 1);
//     layer_move(3);
//     EXPECT_EQ(layer_state, 0b1000);
// }

// TEST_F(ActionLayer, LayerOn) {
//     layer_clear();
//     layer_on(1);
//     layer_on(3);
//     layer_on(3);
//     EXPECT_EQ(layer_state, 0b1010);
// }

// TEST_F(ActionLayer, LayerOff) {
//     layer_clear();
//     layer_on(1);
//     layer_on(3);
//     layer_off(3);
//     layer_off(2);
//     EXPECT_EQ(layer_state, 0b1000);
// }
