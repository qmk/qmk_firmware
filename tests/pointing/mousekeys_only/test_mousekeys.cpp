// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"
#include "mouse_report_util.hpp"
#include "test_common.hpp"
#include "test_pointing_device_driver.h"

using testing::_;

struct MouseKeyExpectations {
    int16_t  x;
    int16_t  y;
    int16_t  h;
    int16_t  v;
    uint16_t button_mask;
};

class Pointing : public TestFixture {};
class PointingKeycodesParametrizedTestFixture : public ::testing::WithParamInterface<std::pair<KeymapKey, MouseKeyExpectations>>, public Pointing {};

TEST_P(PointingKeycodesParametrizedTestFixture, PointingMouseKeysViaPointingDriver) {
    TestDriver           driver;
    KeymapKey            mouse_key    = GetParam().first;
    MouseKeyExpectations expectations = GetParam().second;

    set_keymap({mouse_key});

    EXPECT_MOUSE_REPORT(driver, (expectations.x, expectations.y, expectations.h, expectations.v, expectations.button_mask));
    mouse_key.press();
    run_one_scan_loop();

    EXPECT_EMPTY_MOUSE_REPORT(driver);
    mouse_key.release();
    run_one_scan_loop();

    EXPECT_NO_MOUSE_REPORT(driver);
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}
// clang-format off
INSTANTIATE_TEST_CASE_P(
    PointingMouseKeysOnlyTests,
    PointingKeycodesParametrizedTestFixture,
    ::testing::Values(
        //                                Key               ,                           X, Y, H, V, Buttons Mask
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_1},     MouseKeyExpectations{ 0, 0, 0, 0, 1}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_2},     MouseKeyExpectations{ 0, 0, 0, 0, 2}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_3},     MouseKeyExpectations{ 0, 0, 0, 0, 4}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_4},     MouseKeyExpectations{ 0, 0, 0, 0, 8}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_5},     MouseKeyExpectations{ 0, 0, 0, 0, 16}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_6},     MouseKeyExpectations{ 0, 0, 0, 0, 32}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_7},     MouseKeyExpectations{ 0, 0, 0, 0, 64}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_8},     MouseKeyExpectations{ 0, 0, 0, 0, 128}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_CURSOR_UP},    MouseKeyExpectations{ 0,-8, 0, 0, 0}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_CURSOR_DOWN},  MouseKeyExpectations{ 0, 8, 0, 0, 0}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_CURSOR_LEFT},  MouseKeyExpectations{-8, 0, 0, 0, 0}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_CURSOR_RIGHT}, MouseKeyExpectations{ 8, 0, 0, 0, 0}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_WHEEL_UP},     MouseKeyExpectations{ 0, 0, 0, 1, 0}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_WHEEL_DOWN},   MouseKeyExpectations{ 0, 0, 0,-1, 0}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_WHEEL_LEFT},   MouseKeyExpectations{ 0, 0,-1, 0, 0}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_WHEEL_RIGHT},  MouseKeyExpectations{ 0, 0, 1, 0, 0})
        ));
// clang-format on
