// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"
#include "mouse_report_util.hpp"
#include "test_common.hpp"
#include "test_pointing_device_driver.h"
#include "mousekey.h"

using testing::_;

class Pointing : public TestFixture {};
class PointingButtonsViaMousekeysParametrized : public ::testing::WithParamInterface<std::pair<KeymapKey, uint8_t>>, public Pointing {};

TEST_F(Pointing, NoMovementOnInitFailure) {
    TestDriver driver;

    pointing_device_set_status(POINTING_DEVICE_STATUS_INIT_FAILED);
    pd_set_x(-50);
    pd_set_y(100);
    EXPECT_NO_MOUSE_REPORT(driver);
    run_one_scan_loop();

    pointing_device_set_status(POINTING_DEVICE_STATUS_SUCCESS);
    EXPECT_MOUSE_REPORT(driver, (-50, 100, 0, 0, 0));
    run_one_scan_loop();

    pd_clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, SendMouseIsNotCalledWithNoInput) {
    TestDriver driver;
    EXPECT_NO_MOUSE_REPORT(driver);
    run_one_scan_loop();
}

TEST_F(Pointing, Xnegative) {
    TestDriver driver;

    pd_set_x(-10);
    EXPECT_MOUSE_REPORT(driver, (-10, 0, 0, 0, 0));
    run_one_scan_loop();

    pd_clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, Xpositive) {
    TestDriver driver;

    pd_set_x(10);
    EXPECT_MOUSE_REPORT(driver, (10, 0, 0, 0, 0));
    run_one_scan_loop();

    pd_clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, Ynegative) {
    TestDriver driver;

    pd_set_y(-20);
    EXPECT_MOUSE_REPORT(driver, (0, -20, 0, 0, 0));
    run_one_scan_loop();

    pd_clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, Ypositive) {
    TestDriver driver;

    pd_set_y(20);
    EXPECT_MOUSE_REPORT(driver, (0, 20, 0, 0, 0));
    run_one_scan_loop();

    pd_clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, XandY) {
    TestDriver driver;

    pd_set_x(-50);
    pd_set_y(100);
    EXPECT_MOUSE_REPORT(driver, (-50, 100, 0, 0, 0));
    run_one_scan_loop();

    pd_clear_movement();
    // EXPECT_EMPTY_MOUSE_REPORT(driver);
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, CorrectButtonIsReportedWhenPressed) {
    TestDriver driver;

    EXPECT_MOUSE_REPORT(driver, (0, 0, 0, 0, 1));
    pd_press_button(POINTING_DEVICE_BUTTON1);
    run_one_scan_loop();

    EXPECT_EMPTY_MOUSE_REPORT(driver);
    pd_release_button(POINTING_DEVICE_BUTTON1);
    run_one_scan_loop();

    EXPECT_NO_MOUSE_REPORT(driver);
    run_one_scan_loop();

    pd_clear_all_buttons();
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

TEST_F(Pointing, CorrectButtonIsReportedWhenKeyPressed) {
    TestDriver driver;
    auto       key = KeymapKey(0, 0, 0, QK_MOUSE_BUTTON_1);
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

TEST_P(PointingButtonsViaMousekeysParametrized, MouseKeysViaPointingDriver) {
    TestDriver driver;
    KeymapKey  mouse_key   = GetParam().first;
    uint8_t    button_mask = GetParam().second;

    set_keymap({mouse_key});

    EXPECT_MOUSE_REPORT(driver, (0, 0, 0, 0, button_mask));
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
    ButtonsOneToEight,
    PointingButtonsViaMousekeysParametrized,
    ::testing::Values(
        //                                Key               , Buttons Mask
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_1}, 1),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_2}, 2),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_3}, 4),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_4}, 8),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_5}, 16),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_6}, 32),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_7}, 64),
        std::make_pair(KeymapKey{0, 0, 0, QK_MOUSE_BUTTON_8}, 128)
        ));
// clang-format on
