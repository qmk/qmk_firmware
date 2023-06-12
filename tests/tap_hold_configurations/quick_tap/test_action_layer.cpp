/* Copyright 2021 Stefan Kerkmann
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

#include "keyboard_report_util.hpp"
#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class ActionLayer : public TestFixture {};

TEST_F(ActionLayer, LayerTapToggleWithToggleWithKeypress) {
    TestDriver driver;
    KeymapKey  layer_key = KeymapKey{0, 0, 0, TT(1)};

    /* These keys must have the same position in the matrix, only the layer is different. */
    KeymapKey regular_key = KeymapKey{0, 1, 0, KC_A};
    set_keymap({layer_key, regular_key, KeymapKey{1, 1, 0, KC_B}});

    /* Tap TT five times . */
    /* TODO: Tapping Force Hold breaks TT */
    EXPECT_NO_REPORT(driver);

    layer_key.press();
    run_one_scan_loop();
    layer_key.release();
    run_one_scan_loop();
    expect_layer_state(0);

    idle_for(QUICK_TAP_TERM + 10);

    layer_key.press();
    run_one_scan_loop();
    layer_key.release();
    run_one_scan_loop();
    expect_layer_state(0);

    layer_key.press();
    run_one_scan_loop();
    layer_key.release();
    run_one_scan_loop();
    expect_layer_state(0);

    layer_key.press();
    run_one_scan_loop();
    layer_key.release();
    run_one_scan_loop();
    expect_layer_state(0);

    layer_key.press();
    run_one_scan_loop();
    layer_key.release();
    run_one_scan_loop();
    expect_layer_state(0);

    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_A)).Times(1);
    regular_key.press();
    run_one_scan_loop();
    expect_layer_state(0);
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver).Times(1);
    regular_key.release();
    run_one_scan_loop();
    expect_layer_state(0);
    VERIFY_AND_CLEAR(driver);
}
