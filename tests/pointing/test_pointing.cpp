// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"
#include "mouse_report_util.hpp"
#include "test_common.hpp"
#include "test_pointing_device_driver.h"
#include "mousekey.h"

using testing::_;

struct MouseKeyExpectations {
    int16_t  x;
    int16_t  y;
    int16_t  h;
    int16_t  v;
    uint16_t button_mask;
};

class Pointing : public TestFixture {};
class PointingKeycodeButtonsParametrizedTestFixture : public ::testing::WithParamInterface<std::pair<KeymapKey, MouseKeyExpectations>>, public Pointing {};

TEST_F(Pointing, SendMouseIsNotCalledWithNoInput) {
    TestDriver driver;
    EXPECT_NO_MOUSE_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(Pointing, Xnegative) {
    TestDriver driver;

    set_x(-10);
    EXPECT_MOUSE_REPORT(driver, (-10, 0, 0, 0, 0));
    run_one_scan_loop();

    clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);  // This should probably generate an empty report.
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, Xpositive) {
    TestDriver driver;

    set_x(10);
    EXPECT_MOUSE_REPORT(driver, (10, 0, 0, 0, 0));
    run_one_scan_loop();

    clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);  // This should probably generate an empty report.
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, Ynegative) {
    TestDriver driver;

    set_y(-20);
    EXPECT_MOUSE_REPORT(driver, (0, -20, 0, 0, 0));
    run_one_scan_loop();

    clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);  // This should probably generate an empty report.
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, Ypositive) {
    TestDriver driver;

    set_y(20);
    EXPECT_MOUSE_REPORT(driver, (0, 20, 0, 0, 0));
    run_one_scan_loop();

    clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);  // This should probably generate an empty report.
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, XandY) {
    TestDriver driver;

    set_x(-50);
    set_y(100);
    EXPECT_MOUSE_REPORT(driver, (-50, 100, 0, 0, 0));
    run_one_scan_loop();

    clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);  // This should probably generate an empty report.
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, CorrectButtonIsReportedWhenPressed) {
    TestDriver driver;

    EXPECT_MOUSE_REPORT(driver, (0, 0, 0, 0, 1));
    press_button(POINTING_DEVICE_BUTTON1);
    run_one_scan_loop();

    EXPECT_EMPTY_MOUSE_REPORT(driver);
    release_button(POINTING_DEVICE_BUTTON1);
    run_one_scan_loop();

    EXPECT_NO_MOUSE_REPORT(driver);
    run_one_scan_loop();

    clear_all_buttons();
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, CorrectButtonIsReportedWhenKeyPressed) {
    TestDriver driver;
    auto       key = KeymapKey(0, 0, 0, KC_MS_BTN1);
    set_keymap({key});

    EXPECT_MOUSE_REPORT(driver, (0, 0, 0, 0, 1));
    key.press();
    run_one_scan_loop();

    EXPECT_EMPTY_MOUSE_REPORT(driver);
    key.release();
    run_one_scan_loop();

    EXPECT_NO_MOUSE_REPORT(driver);
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_P(PointingKeycodeButtonsParametrizedTestFixture, PointingMouseKeysViaPointingDriver) {
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
    PointingMouseKeysTests,
    PointingKeycodeButtonsParametrizedTestFixture,
    ::testing::Values(
        //                                Key               ,  X, Y, H, V, Buttons Mask
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_1}, MouseKeyExpectations{0, 0, 0, 0, 1}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_2}, MouseKeyExpectations{0, 0, 0, 0, 2}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_3}, MouseKeyExpectations{0, 0, 0, 0, 4}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_4}, MouseKeyExpectations{0, 0, 0, 0, 8}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_5}, MouseKeyExpectations{0, 0, 0, 0, 16}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_6}, MouseKeyExpectations{0, 0, 0, 0, 32}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_7}, MouseKeyExpectations{0, 0, 0, 0, 64}),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_8}, MouseKeyExpectations{0, 0, 0, 0, 128})
        ));
// clang-format on
