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

#include "gtest/gtest.h"
#include "keyboard_report_util.hpp"
#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class ActionLayer : public TestFixture {};

TEST_F(ActionLayer, LayerStateDBG) {
    TestDriver driver;

    layer_state_set(0);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerStateSet) {
    TestDriver driver;

    layer_state_set(0);
    EXPECT_EQ(layer_state, 0);
    layer_state_set(0b001100);
    EXPECT_EQ(layer_state, 0b001100);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerStateIs) {
    TestDriver driver;

    layer_state_set(0);
    EXPECT_EQ(layer_state_is(0), true);
    EXPECT_EQ(layer_state_is(1), false);
    layer_state_set(1);
    EXPECT_EQ(layer_state_is(0), true);
    EXPECT_EQ(layer_state_is(1), false);
    layer_state_set(2);
    EXPECT_EQ(layer_state_is(0), false);
    EXPECT_EQ(layer_state_is(1), true);
    EXPECT_EQ(layer_state_is(2), false);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerStateCmp) {
    TestDriver driver;
    uint32_t   prev_layer;

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

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerClear) {
    TestDriver driver;

    layer_clear();
    EXPECT_EQ(layer_state, 0);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerMove) {
    TestDriver driver;

    layer_move(0);
    EXPECT_EQ(layer_state, 1);
    layer_move(3);
    EXPECT_EQ(layer_state, 0b1000);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerOn) {
    TestDriver driver;

    layer_clear();
    layer_on(1);
    layer_on(3);
    layer_on(3);
    EXPECT_EQ(layer_state, 0b1010);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerOff) {
    TestDriver driver;

    layer_clear();
    layer_on(1);
    layer_on(3);
    layer_off(3);
    layer_off(2);
    EXPECT_EQ(layer_state, 0b0010);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, MomentaryLayerDoesNothing) {
    TestDriver driver;
    KeymapKey  layer_key = KeymapKey{0, 0, 0, MO(1)};

    set_keymap({layer_key});

    /* Press and release MO, nothing should happen. */
    EXPECT_NO_REPORT(driver);
    layer_key.press();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_NO_REPORT(driver);
    layer_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, MomentaryLayerWithKeypress) {
    TestDriver driver;
    KeymapKey  layer_key = KeymapKey{0, 0, 0, MO(1)};

    /* These keys must have the same position in the matrix, only the layer is different. */
    KeymapKey regular_key = KeymapKey{0, 1, 0, KC_A};
    set_keymap({layer_key, regular_key, KeymapKey{1, 1, 0, KC_B}});

    /* Press MO. */
    EXPECT_NO_REPORT(driver);
    layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press key on layer 1 */
    EXPECT_REPORT(driver, (KC_B)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release key on layer 1 */
    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release MO */
    EXPECT_NO_REPORT(driver);
    layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, ToggleLayerDoesNothing) {
    GTEST_SKIP() << "TODO: Toggle layer does not activate the expected layer on key press but on release.";

    TestDriver driver;
    KeymapKey  layer_key = KeymapKey{0, 0, 0, TG(1)};

    set_keymap({layer_key});

    /* Press TG. Layer state should not change as it's applied on release. */
    EXPECT_NO_REPORT(driver);
    layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release TG. */
    EXPECT_NO_REPORT(driver);
    layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, ToggleLayerUpAndDown) {
    GTEST_SKIP() << "TODO: Toggle layer does not activate the expected layer on key press but on release.";

    TestDriver driver;
    KeymapKey  toggle_layer_1_on_layer_0 = KeymapKey{0, 0, 0, TG(1)};
    KeymapKey  toggle_layer_0_on_layer_1 = KeymapKey{1, 1, 0, TG(0)};

    set_keymap({toggle_layer_1_on_layer_0, toggle_layer_0_on_layer_1});

    /* Toggle Layer 1. */
    EXPECT_NO_REPORT(driver);
    toggle_layer_1_on_layer_0.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_NO_REPORT(driver);
    toggle_layer_1_on_layer_0.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Toggle Layer 0. */
    EXPECT_NO_REPORT(driver);
    toggle_layer_0_on_layer_1.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_NO_REPORT(driver);
    toggle_layer_0_on_layer_1.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerTapToggleDoesNothing) {
    GTEST_SKIP() << "TODO: Tap toggle layer does not activate the expected layer on key press.";

    TestDriver driver;
    KeymapKey  layer_key = KeymapKey{0, 0, 0, TT(1)};

    set_keymap({layer_key});

    /* Press and release TT. */
    EXPECT_NO_REPORT(driver);
    layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_NO_REPORT(driver);
    layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerTapToggleWithKeypress) {
    GTEST_SKIP() << "TODO: Tap toggle layer does not activate the expected layer on key press.";

    TestDriver driver;
    KeymapKey  layer_key = KeymapKey{0, 0, 0, TT(1)};

    /* These keys must have the same position in the matrix, only the layer is different. */
    KeymapKey regular_key = KeymapKey{0, 1, 0, KC_A};
    set_keymap({layer_key, regular_key, KeymapKey{1, 1, 0, KC_B}});

    /* Press TT. */
    EXPECT_NO_REPORT(driver);
    layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_REPORT(driver, (KC_B)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_NO_REPORT(driver);
    layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerTapToggleWithToggleWithKeypress) {
    GTEST_SKIP() << "TODO: Tap toggle layer does not activate the expected layer on key press.";

    TestDriver driver;
    KeymapKey  layer_key = KeymapKey{0, 0, 0, TT(1)};

    /* These keys must have the same position in the matrix, only the layer is different. */
    KeymapKey regular_key = KeymapKey{0, 1, 0, KC_A};
    set_keymap({layer_key, regular_key, KeymapKey{1, 1, 0, KC_B}});

    /* Tap TT five times . */
    EXPECT_NO_REPORT(driver);

    layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));

    layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));

    layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));

    layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));

    layer_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    layer_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));

    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_REPORT(driver, (KC_B)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    EXPECT_EMPTY_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(ActionLayer, LayerTapReleasedBeforeKeypressReleaseWithModifiers) {
    TestDriver driver;
    InSequence s;

    KeymapKey layer_0_key_0 = KeymapKey{0, 0, 0, LT(1, KC_T)};
    KeymapKey layer_1_key_1 = KeymapKey{1, 1, 0, RALT(KC_9)};

    set_keymap({layer_0_key_0, layer_1_key_1});

    /* Press layer tap and wait for tapping term to switch to layer 1 */
    EXPECT_NO_REPORT(driver);
    layer_0_key_0.press();
    idle_for(TAPPING_TERM);
    EXPECT_TRUE(layer_state_is(0));
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press key with layer 1 mapping, result basically expected
     * altough more reports are send then necessary. */
    EXPECT_REPORT(driver, (KC_RALT)).Times(1);
    EXPECT_REPORT(driver, (KC_RALT, KC_9)).Times(1);
    layer_1_key_1.press();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(1));
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release layer tap key, no report is send because key is still held. */
    EXPECT_NO_REPORT(driver);
    layer_0_key_0.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Unregister keycode and modifier. */
    EXPECT_REPORT(driver, (KC_RALT)).Times(1);
    EXPECT_EMPTY_REPORT(driver);
    layer_1_key_1.release();
    run_one_scan_loop();
    EXPECT_TRUE(layer_state_is(0));
    testing::Mock::VerifyAndClearExpectations(&driver);
}
