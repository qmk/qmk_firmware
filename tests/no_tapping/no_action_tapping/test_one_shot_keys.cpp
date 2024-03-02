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

#include "action_util.h"
#include "keyboard_report_util.hpp"
#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class OneShot : public TestFixture {};

TEST_F(OneShot, OSMWithoutAdditionalKeypressDoesNothing) {
    TestDriver driver;
    auto       osm_key = KeymapKey(0, 0, 0, OSM(MOD_LSFT), KC_LSFT);

    set_keymap({osm_key});

    /* Press and release OSM key*/
    EXPECT_NO_REPORT(driver);
    osm_key.press();
    EXPECT_REPORT(driver, (osm_key.report_code));
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);
    osm_key.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSL_No_ReportPress) {
    TestDriver driver;
    auto       osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    auto       empty_key   = KeymapKey{0, 1, 0, KC_NO};
    auto       regular_key = KeymapKey{1, 1, 0, KC_A};

    set_keymap({osl_key, empty_key, regular_key});

    /* Press OSL key */
    EXPECT_NO_REPORT(driver);
    osl_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release OSL key */
    EXPECT_NO_REPORT(driver);
    osl_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Press regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release regular key */
    EXPECT_NO_REPORT(driver);
    regular_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(OneShot, OSL_ReportPress) {
    TestDriver driver;
    auto       osl_key     = KeymapKey{0, 0, 0, OSL(1)};
    auto       empty_key   = KeymapKey{0, 1, 0, KC_NO};
    auto       regular_key = KeymapKey{1, 1, 0, KC_A};

    set_keymap({osl_key, empty_key, regular_key});

    /* Press OSL key */
    osl_key.press();
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);

    /* Press regular key */
    regular_key.press();
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);

    /* Release regular key */
    regular_key.release();
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);

    /* Release OSL key */
    osl_key.release();
    run_one_scan_loop();
    EXPECT_NO_REPORT(driver);
    VERIFY_AND_CLEAR(driver);
}
