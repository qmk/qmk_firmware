// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2023 @filterpaper
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "quantum.h"
#include "keycode.h"
#include "test_common.h"
#include "test_driver.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

extern "C" {
enum combos { modtest, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

uint16_t const modtest_combo[] PROGMEM = {KC_Y, KC_U, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [modtest] = COMBO(modtest_combo, RSFT_T(KC_SPACE))
};
// clang-format on
}

using testing::_;
using testing::InSequence;

class Combo : public TestFixture {};

TEST_F(Combo, combo_tapped) {
    TestDriver driver;
    KeymapKey  key_y(0, 0, 1, KC_Y);
    KeymapKey  key_u(0, 0, 2, KC_U);
    set_keymap({key_y, key_u});

    EXPECT_REPORT(driver, (KC_SPACE));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_y, key_u});
    VERIFY_AND_CLEAR(driver);
}

TEST_F(Combo, combo_held_longer_than_tapping_term) {
    TestDriver driver;
    KeymapKey  key_y(0, 0, 1, KC_Y);
    KeymapKey  key_u(0, 0, 2, KC_U);
    set_keymap({key_y, key_u});

    EXPECT_REPORT(driver, (KC_RIGHT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);
    tap_combo({key_y, key_u}, TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);
}
