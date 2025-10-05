// Copyright 2025 @johnwilmes
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.h"
#include "test_common.hpp"
#include "test_driver.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

extern bool combo_override;

class ComboFlags : public TestFixture {};

TEST_F(ComboFlags, combo_long) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_c(0, 2, 0, KC_C);
    KeymapKey  key_d(0, 3, 0, KC_D);
    KeymapKey  key_e(0, 4, 0, KC_E);
    KeymapKey  key_f(0, 5, 0, KC_F);
    KeymapKey  key_g(0, 0, 1, KC_G);
    KeymapKey  key_h(0, 1, 1, KC_H);
    KeymapKey  key_i(0, 2, 1, KC_I);
    KeymapKey  key_j(0, 3, 1, KC_J);
    KeymapKey  key_k(0, 4, 1, KC_K);
    KeymapKey  key_l(0, 5, 1, KC_L);
    KeymapKey  key_m(0, 0, 2, KC_M);
    KeymapKey  key_n(0, 1, 2, KC_N);
    KeymapKey  key_o(0, 2, 2, KC_O);
    KeymapKey  key_p(0, 3, 2, KC_P);
    KeymapKey  key_q(0, 4, 2, KC_Q);
    KeymapKey  key_r(0, 5, 2, KC_R);
    set_keymap({key_a, key_b, key_c, key_d, key_e, key_f, key_g, key_h, key_i, key_j, key_k, key_l, key_m, key_n, key_o, key_p, key_q, key_r});

    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_b, key_c, key_d, key_e, key_f, key_g, key_h, key_i, key_j, key_k, key_l, key_m, key_n, key_o, key_p, key_q, key_r}, 300);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(ComboFlags, combo_flags) {
    TestDriver driver;
    KeymapKey  key_a0(0, 0, 0, KC_A);
    KeymapKey  key_b0(0, 1, 0, KC_B);
    KeymapKey  key_c0(0, 2, 0, KC_C);
    KeymapKey  key_d0(0, 3, 0, KC_D);
    KeymapKey  key_d1(1, 0, 0, KC_D);
    KeymapKey  key_a1(1, 1, 0, KC_A);
    KeymapKey  key_b1(1, 2, 0, KC_B);
    KeymapKey  key_c1(1, 3, 0, KC_C);
    set_keymap({key_a0, key_b0, key_c0, key_d0, key_a1, key_b1, key_c1, key_d1});

    // in order, proper layer, held -> fires
    EXPECT_REPORT(driver, (KC_LEFT_CTRL));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a0, key_d0}, 300);
    VERIFY_AND_CLEAR(driver);

    // out of order, proper layer, held -> no fire
    EXPECT_REPORT(driver, (KC_D));
    EXPECT_REPORT(driver, (KC_D, KC_A));
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_d0, key_a0}, 300);
    VERIFY_AND_CLEAR(driver);

    // in order, proper layer, tapped -> no fire
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_D));
    EXPECT_REPORT(driver, (KC_D));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a0, key_d0}, 1);
    VERIFY_AND_CLEAR(driver);

    // in order, wrong layer, held -> no fire
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_REPORT(driver, (KC_A, KC_D));
    EXPECT_REPORT(driver, (KC_D));
    EXPECT_EMPTY_REPORT(driver);
    layer_on(1);
    tap_combo({key_a1, key_d1}, 300);
    layer_off(1);
    VERIFY_AND_CLEAR(driver);

    // in order, layer 1 on, keys for layer 0, held -> fires
    EXPECT_REPORT(driver, (KC_LEFT_CTRL));
    EXPECT_EMPTY_REPORT(driver);
    layer_on(1);
    tap_combo({key_a0, key_d0}, 300);
    layer_off(1);
    VERIFY_AND_CLEAR(driver);
}
