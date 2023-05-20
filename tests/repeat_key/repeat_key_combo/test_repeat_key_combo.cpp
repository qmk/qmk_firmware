// Copyright 2023 Google LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using ::testing::AnyNumber;
using ::testing::InSequence;

namespace {

class RepeatKey : public TestFixture {};

// Tests repeating a combo, KC_X + KC_Y = KC_Q, by typing
// "X, Repeat, Repeat, {X Y}, Repeat, Repeat". This produces "xxxqqq".
TEST_F(RepeatKey, Combo) {
    TestDriver driver;
    KeymapKey  key_x(0, 0, 0, KC_X);
    KeymapKey  key_y(0, 1, 0, KC_Y);
    KeymapKey  key_repeat(0, 2, 0, QK_REP);
    set_keymap({key_x, key_y, key_repeat});

    // Allow any number of empty reports.
    EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
    {
        InSequence seq;
        EXPECT_REPORT(driver, (KC_X));
        EXPECT_REPORT(driver, (KC_X));
        EXPECT_REPORT(driver, (KC_X));
        EXPECT_REPORT(driver, (KC_Q));
        EXPECT_REPORT(driver, (KC_Q));
        EXPECT_REPORT(driver, (KC_Q));
    }

    tap_keys(key_x, key_repeat, key_repeat);
    tap_combo({key_x, key_y});

    EXPECT_KEYCODE_EQ(get_last_keycode(), KC_Q);

    tap_keys(key_repeat, key_repeat);

    testing::Mock::VerifyAndClearExpectations(&driver);
}

} // namespace
