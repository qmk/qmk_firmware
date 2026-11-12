// Copyright 2026 Dave Thompson (@dave-thompson)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycodes.h"
#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class ComboRefLayer : public TestFixture {};

// The combo is pressed on layer 1 (matched via reference layer 0), then
// layer 1 is released before the combo keys. The combo keys' releases must
// still be matched, or the combo's output is never released.
TEST_F(ComboRefLayer, release_after_reference_layer_turned_off) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_mo(0, 0, 0, MO(1));
    KeymapKey  key_a(0, 1, 0, KC_A);
    KeymapKey  key_b(0, 2, 0, KC_B);
    set_keymap({key_mo, key_a, key_b, KeymapKey(1, 0, 0, KC_TRNS), KeymapKey(1, 1, 0, KC_1), KeymapKey(1, 2, 0, KC_2)});

    key_mo.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_X));
    key_a.press();
    run_one_scan_loop();
    key_b.press();
    run_one_scan_loop();
    idle_for(COMBO_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    key_mo.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    key_a.release();
    run_one_scan_loop();
    key_b.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Keys that are transparent on a self-referencing layer resolve to the
// layer below. With no layer change, the release must be matched exactly as
// the press was, so the combo's output is released.
TEST_F(ComboRefLayer, transparent_keys_on_self_referencing_layer) {
    TestDriver driver;
    InSequence s;
    KeymapKey  key_a(0, 1, 0, KC_A);
    KeymapKey  key_b(0, 2, 0, KC_B);
    set_keymap({key_a, key_b, KeymapKey(1, 1, 0, KC_1), KeymapKey(1, 2, 0, KC_2), KeymapKey(2, 1, 0, KC_TRNS), KeymapKey(2, 2, 0, KC_TRNS)});

    layer_on(1);
    layer_on(2);

    EXPECT_REPORT(driver, (KC_Y));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_b});
    VERIFY_AND_CLEAR(driver);

    layer_clear();
}
