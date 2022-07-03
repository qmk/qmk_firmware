/* Copyright 2022 Jouke Witteveen
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
#include "examples.h"

using testing::_;
using testing::InSequence;

class TapDance : public TestFixture {};

TEST_F(TapDance, DoubleTap) {
    TestDriver driver;
    InSequence s;
    auto       key_esc_caps = KeymapKey{0, 1, 0, TD(TD_ESC_CAPS)};

    set_keymap({key_esc_caps});

    /* The tap dance key does nothing on the first press */
    key_esc_caps.press();
    run_one_scan_loop();
    key_esc_caps.release();
    EXPECT_NO_REPORT(driver);

    /* We get the key press and the release on timeout */
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_ESC));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Double tap gets us the second key */
    tap_key(key_esc_caps);
    EXPECT_NO_REPORT(driver);
    key_esc_caps.press();
    EXPECT_REPORT(driver, (KC_CAPS));
    run_one_scan_loop();
    key_esc_caps.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(TapDance, DoubleTapWithMod) {
    TestDriver driver;
    InSequence s;
    auto       key_esc_caps = KeymapKey{0, 1, 0, TD(TD_ESC_CAPS)};
    auto       key_shift    = KeymapKey{0, 2, 0, KC_LSFT};

    set_keymap({key_esc_caps, key_shift});

    /* The tap dance key does nothing on the first press */
    key_shift.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();
    key_esc_caps.press();
    run_one_scan_loop();

    key_esc_caps.release();
    key_shift.release();
    EXPECT_EMPTY_REPORT(driver);

    /* We get the key press and the release */
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_ESC));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Double tap gets us the second key */
    key_shift.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();
    tap_key(key_esc_caps);
    EXPECT_NO_REPORT(driver);
    key_shift.release();
    key_esc_caps.press();
    EXPECT_REPORT(driver, (KC_LSFT, KC_CAPS));
    run_one_scan_loop();
    key_esc_caps.release();
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(TapDance, DoubleTapInterrupted) {
    TestDriver driver;
    InSequence s;
    auto       key_esc_caps = KeymapKey{0, 1, 0, TD(TD_ESC_CAPS)};
    auto       regular_key  = KeymapKey(0, 2, 0, KC_A);

    set_keymap({key_esc_caps, regular_key});

    /* Interrupted double tap */
    tap_key(key_esc_caps);
    regular_key.press();
    /* Immediate tap of the first key */
    EXPECT_REPORT(driver, (KC_ESC));
    EXPECT_EMPTY_REPORT(driver);
    /* Followed by the interrupting key */
    EXPECT_REPORT(driver, (KC_A));
    run_one_scan_loop();
    regular_key.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Second tap after being interrupted acts as a single tap */
    key_esc_caps.press();
    run_one_scan_loop();
    key_esc_caps.release();
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_ESC));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(TapDance, DanceFn) {
    TestDriver driver;
    InSequence s;
    auto       key_egg = KeymapKey(0, 1, 0, TD(CT_EGG));

    set_keymap({key_egg});

    /* 99 taps do nothing */
    for (int i = 0; i < 99; i++) {
        run_one_scan_loop();
        key_egg.press();
        run_one_scan_loop();
        key_egg.release();
    }
    idle_for(TAPPING_TERM);
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    /* 100 taps trigger the action */
    for (int i = 0; i < 100; i++) {
        run_one_scan_loop();
        key_egg.press();
        run_one_scan_loop();
        key_egg.release();
    }
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_C));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* 250 taps act the same as 100 taps */
    /* Taps are counted in an uint8_t, so the count overflows after 255 taps */
    for (int i = 0; i < 250; i++) {
        run_one_scan_loop();
        key_egg.press();
        run_one_scan_loop();
        key_egg.release();
    }
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_C));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(TapDance, DanceFnAdvanced) {
    TestDriver driver;
    InSequence s;
    auto       key_flsh = KeymapKey(0, 1, 0, TD(CT_FLSH));

    set_keymap({key_flsh});

    /* Three taps don't trigger a reset */
    EXPECT_REPORT(driver, (KC_3));
    EXPECT_REPORT(driver, (KC_3, KC_2));
    EXPECT_REPORT(driver, (KC_3, KC_2, KC_1));
    for (int i = 0; i < 3; i++) {
        run_one_scan_loop();
        key_flsh.press();
        run_one_scan_loop();
        key_flsh.release();
    }
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_3, KC_2));
    EXPECT_REPORT(driver, (KC_3));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Four taps trigger a reset */
    EXPECT_REPORT(driver, (KC_3));
    EXPECT_REPORT(driver, (KC_3, KC_2));
    EXPECT_REPORT(driver, (KC_3, KC_2, KC_1));
    EXPECT_REPORT(driver, (KC_2, KC_1));
    EXPECT_REPORT(driver, (KC_1));
    EXPECT_EMPTY_REPORT(driver);
    for (int i = 0; i < 4; i++) {
        run_one_scan_loop();
        key_flsh.press();
        run_one_scan_loop();
        key_flsh.release();
    }
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_R));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(TapDance, TapHold) {
    TestDriver driver;
    InSequence s;
    auto       key_cln = KeymapKey{0, 1, 0, TD(CT_CLN)};

    set_keymap({key_cln});

    /* Short taps fire on release */
    key_cln.press();
    run_one_scan_loop();
    key_cln.release();
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_SCLN));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Holds immediate following a tap apply to the tap key */
    key_cln.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_SCLN));
    idle_for(TAPPING_TERM * 2);
    key_cln.release();
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Holds trigger the hold key */
    key_cln.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    EXPECT_REPORT(driver, (KC_SCLN));
    run_one_scan_loop();
    key_cln.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(TapDance, QuadFunction) {
    TestDriver driver;
    InSequence s;
    auto       key_quad    = KeymapKey{0, 1, 0, TD(X_CTL)};
    auto       regular_key = KeymapKey(0, 2, 0, KC_A);

    set_keymap({key_quad, regular_key});

    /* Single tap */
    key_quad.press();
    run_one_scan_loop();
    key_quad.release();
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Single hold */
    key_quad.press();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_LCTL));
    run_one_scan_loop();
    key_quad.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Double tap */
    tap_key(key_quad);
    key_quad.press();
    run_one_scan_loop();
    key_quad.release();
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_ESC));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Double tap and hold */
    tap_key(key_quad);
    key_quad.press();
    run_one_scan_loop();
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (KC_LALT));
    run_one_scan_loop();
    key_quad.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    /* Double single tap */
    tap_key(key_quad);
    tap_key(key_quad);
    regular_key.press();
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_X));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_A));
    run_one_scan_loop();
    regular_key.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}
