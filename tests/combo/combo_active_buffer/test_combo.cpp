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

class ComboBuffer : public TestFixture {};

TEST_F(ComboBuffer, combo_active_buffer_overflow) {
    TestDriver driver;
    KeymapKey  key_a(0, 0, 0, KC_A);
    KeymapKey  key_b(0, 1, 0, KC_B);
    KeymapKey  key_c(0, 2, 0, KC_C);
    KeymapKey  key_d(0, 3, 0, KC_D);
    KeymapKey  key_e(0, 4, 0, KC_E);
    KeymapKey  key_f(0, 5, 0, KC_F);
    set_keymap({key_a, key_b, key_c, key_d, key_e, key_f});

    EXPECT_REPORT(driver, (KC_1));
    EXPECT_REPORT(driver, (KC_1, KC_2));
    EXPECT_REPORT(driver, (KC_2));
    EXPECT_REPORT(driver, (KC_2, KC_3));
    EXPECT_REPORT(driver, (KC_3));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_a, key_b, key_c, key_d, key_e, key_f});
    VERIFY_AND_CLEAR(driver);
}
