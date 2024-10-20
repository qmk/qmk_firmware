// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"
#include "mouse_report_util.hpp"
#include "test_common.hpp"
#include "test_pointing_device_driver.h"

using testing::_;

struct SimpleReport {
    int16_t x;
    int16_t y;
    int16_t h;
    int16_t v;
};

class Pointing : public TestFixture {};
class PointingInvertXYParametrizedTestFixture : public ::testing::WithParamInterface<std::pair<SimpleReport, SimpleReport>>, public Pointing {};

TEST_P(PointingInvertXYParametrizedTestFixture, PointingMouseKeysViaPointingDriver) {
    TestDriver   driver;
    SimpleReport input        = GetParam().first;
    SimpleReport expectations = GetParam().second;

    set_x(input.x);
    set_y(input.y);
    set_h(input.h);
    set_v(input.v);

    EXPECT_MOUSE_REPORT(driver, (expectations.x, expectations.y, expectations.h, expectations.v, 0));
    run_one_scan_loop();

    // EXPECT_EMPTY_MOUSE_REPORT(driver);
    clear_movement();
    run_one_scan_loop();

    EXPECT_NO_MOUSE_REPORT(driver);
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}
// clang-format off
INSTANTIATE_TEST_CASE_P(
    PointingInvertXYTests,
    PointingInvertXYParametrizedTestFixture,
    ::testing::Values(
        //                      Input                       Expected
        std::make_pair(SimpleReport{ 33, 0, 0, 0}, SimpleReport{ -33, 0, 0, 0}),
        std::make_pair(SimpleReport{  0, -127, 0, 0}, SimpleReport{ 0, 127, 0, 0}),
        std::make_pair(SimpleReport{  10, -20, 0, 0}, SimpleReport{ -10, 20, 0, 0})
        ));
// clang-format on
