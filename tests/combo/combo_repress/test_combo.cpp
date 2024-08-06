// Copyright 2024 @Filios92
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "quantum.h"
#include "keycode.h"
#include "test_common.h"
#include "test_driver.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class ComboRepress : public TestFixture {};

TEST_F(ComboRepress, combo_repress_tapped) {
    TestDriver driver;
    KeymapKey  key_f(0, 0, 0, KC_F);
    KeymapKey  key_g(0, 0, 1, KC_G);
    set_keymap({key_f, key_g});

    EXPECT_REPORT(driver, (KC_LEFT_ALT)).Times(2);
    EXPECT_REPORT(driver, (KC_TAB, KC_LEFT_ALT));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_f, key_g}, 20);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboRepress, combo_repress_held_released_one_key_and_repressed) {
    TestDriver driver;
    KeymapKey  key_f(0, 0, 0, KC_F);
    KeymapKey  key_g(0, 0, 1, KC_G);
    KeymapKey  key_h(0, 0, 2, KC_H);
    KeymapKey  key_j(0, 0, 3, KC_J);
    set_keymap({key_f, key_g, key_h, key_j});

    /* Press combo F+G */
    EXPECT_REPORT(driver, (KC_LEFT_ALT)).Times(2);
    EXPECT_REPORT(driver, (KC_TAB, KC_LEFT_ALT));
    key_f.press();
    run_one_scan_loop();
    key_g.press();
    run_one_scan_loop();
    idle_for(COMBO_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* Release G */
    EXPECT_NO_REPORT(driver);
    key_g.release();
    idle_for(80);
    VERIFY_AND_CLEAR(driver);

    /* Tap G */
    EXPECT_REPORT(driver, (KC_TAB, KC_LEFT_ALT));
    EXPECT_REPORT(driver, (KC_LEFT_ALT));
    tap_key(key_g, TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* Tap G, but hold for longer */
    EXPECT_REPORT(driver, (KC_TAB, KC_LEFT_ALT));
    EXPECT_REPORT(driver, (KC_LEFT_ALT));
    tap_key(key_g, TAPPING_TERM * 2);
    VERIFY_AND_CLEAR(driver);

    idle_for(500);

    /* Tap other combo while holding F */
    EXPECT_REPORT(driver, (KC_ESCAPE, KC_LEFT_ALT));
    EXPECT_REPORT(driver, (KC_LEFT_ALT));
    tap_combo({key_h, key_j}, TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* G press and hold */
    EXPECT_REPORT(driver, (KC_TAB, KC_LEFT_ALT));
    EXPECT_REPORT(driver, (KC_LEFT_ALT));
    key_g.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* F release and tap */
    EXPECT_REPORT(driver, (KC_LEFT_ALT, KC_LEFT_SHIFT)).Times(2);
    EXPECT_REPORT(driver, (KC_TAB, KC_LEFT_ALT, KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_ALT));
    key_f.release();
    run_one_scan_loop();
    tap_key(key_f);
    VERIFY_AND_CLEAR(driver);

    /* Release G */
    EXPECT_EMPTY_REPORT(driver);
    key_g.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboRepress, combo_repress_normal_combo) {
    TestDriver driver;
    KeymapKey  key_f(0, 0, 0, KC_F);
    KeymapKey  key_g(0, 0, 1, KC_G);
    KeymapKey  key_h(0, 0, 2, KC_H);
    KeymapKey  key_j(0, 0, 3, KC_J);
    set_keymap({key_f, key_g, key_h, key_j});

    /* Press combo H+J */
    EXPECT_REPORT(driver, (KC_ESCAPE));
    key_h.press();
    run_one_scan_loop();
    key_j.press();
    run_one_scan_loop();
    idle_for(COMBO_TERM + 10);
    VERIFY_AND_CLEAR(driver);

    /* Release H */
    EXPECT_NO_REPORT(driver);
    key_h.release();
    idle_for(80);
    VERIFY_AND_CLEAR(driver);

    /* Tap H */
    EXPECT_REPORT(driver, (KC_H, KC_ESCAPE));
    EXPECT_REPORT(driver, (KC_ESCAPE));
    tap_key(key_h);
    VERIFY_AND_CLEAR(driver);

    /* Tap H, but hold for longer */
    EXPECT_REPORT(driver, (KC_H, KC_ESCAPE));
    EXPECT_REPORT(driver, (KC_ESCAPE));
    tap_key(key_h, TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    idle_for(500);

    /* Tap other combo while holding K */
    EXPECT_REPORT(driver, (KC_ESCAPE, KC_LEFT_ALT)).Times(2);
    EXPECT_REPORT(driver, (KC_ESCAPE, KC_TAB, KC_LEFT_ALT));
    EXPECT_REPORT(driver, (KC_ESCAPE));
    tap_combo({key_f, key_g}, TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* H press and hold */
    EXPECT_REPORT(driver, (KC_H, KC_ESCAPE));
    key_h.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* J release and tap */
    EXPECT_REPORT(driver, (KC_H));
    key_j.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    /* Release G */
    EXPECT_EMPTY_REPORT(driver);
    key_h.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
