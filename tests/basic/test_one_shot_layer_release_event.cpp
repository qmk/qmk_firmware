/* Copyright 2026 QMK
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

#include <functional>

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

namespace {

bool process_record_user_default(uint16_t keycode, keyrecord_t* record) {
    return true;
}

// Indirection so that process_record_user() can be replaced per test case.
std::function<bool(uint16_t, keyrecord_t*)> process_record_user_fun = process_record_user_default;

} // namespace

extern "C" bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    return process_record_user_fun(keycode, record);
}

class OneShotLayerReleaseEvent : public TestFixture {
   public:
    void SetUp() override {
        process_record_user_fun = process_record_user_default;
    }
};

// Regression test for https://github.com/qmk/qmk_firmware/issues/26309
//
// When a regular (non-modifier) key press clears an active one-shot layer,
// process_record_user() must see exactly one press event followed by
// exactly one release event for that key: one for the physical press, and
// one for the physical release. It must NOT be reported as released while
// the key is still physically held down, and it must NOT be reported as
// released a second time when it is actually released.
TEST_F(OneShotLayerReleaseEvent, RegularKeyClearingOslIsNotReleasedTwice) {
    TestDriver driver;
    KeymapKey  osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    KeymapKey  regular_key = KeymapKey{1, 1, 0, KC_A};

    set_keymap({osl_key, regular_key});

    int press_count         = 0;
    int release_count       = 0;
    process_record_user_fun = [&](uint16_t keycode, keyrecord_t* record) {
        if (keycode == regular_key.code) {
            if (record->event.pressed) {
                press_count++;
            } else {
                release_count++;
            }
        }
        return true;
    };

    /* Tap the OSL key to arm the one-shot layer. */
    tap_key(osl_key);

    /* Press the regular key: this is the very key press that clears the
     * armed one-shot layer. */
    regular_key.press();
    run_one_scan_loop();

    /* The key is still physically held down at this point. It must have
     * been reported to process_record_user() as pressed exactly once, and
     * must NOT already have been reported as released. */
    EXPECT_EQ(press_count, 1);
    EXPECT_EQ(release_count, 0);

    /* Now physically release the key. */
    regular_key.release();
    run_one_scan_loop();

    /* The key must now have been reported as released exactly once (not
     * twice, as happened before this bug was fixed). */
    EXPECT_EQ(press_count, 1);
    EXPECT_EQ(release_count, 1);
}
