/* Copyright 2024 leep-frog
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
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_keymap_key.hpp"
#include "housekeeping_keyboard.h"

using testing::_;
using testing::InSequence;

class Housekeeping : public TestFixture {};

TEST_F(Housekeeping, Works) {
    TestDriver driver;
    InSequence s;
    auto       key_a = KeymapKey{0, 1, 0, KC_A};
    auto       key_h = KeymapKey{0, 2, 0, KC_H};

    set_keymap({key_a, key_h});

    // Key that doesn't affect housekeeping
    key_a.press();
    EXPECT_REPORT(driver, (KC_A));
    run_one_scan_loop();
    key_a.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // Key that does affect housekeeping
    key_h.press();
    EXPECT_REPORT(driver, (KC_H));
    run_one_scan_loop();
    key_h.release();
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_I));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}
