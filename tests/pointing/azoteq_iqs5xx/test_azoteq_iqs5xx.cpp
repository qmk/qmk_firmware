// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"

extern "C" {
#include "azoteq_iqs5xx.h"

void azoteq_iqs5xx_mock_reset(void);
void azoteq_iqs5xx_mock_set_base_data(azoteq_iqs5xx_base_data_t base_data);
}

class AzoteqIqs5xx : public testing::Test {
   protected:
    void SetUp() override {
        azoteq_iqs5xx_mock_reset();
    }
};

TEST_F(AzoteqIqs5xx, PreservesIncomingButtonsWhenReportingMovement) {
    azoteq_iqs5xx_base_data_t base_data = {0};
    base_data.number_of_fingers         = 1;
    base_data.x.l                       = 12;
    base_data.y.l                       = 34;
    azoteq_iqs5xx_mock_set_base_data(base_data);

    report_mouse_t input_report = {0};
    input_report.buttons        = (1 << POINTING_DEVICE_BUTTON1) | (1 << POINTING_DEVICE_BUTTON2);

    report_mouse_t report = azoteq_iqs5xx_get_report(input_report);

    EXPECT_EQ(report.x, 12);
    EXPECT_EQ(report.y, 34);
    EXPECT_EQ(report.h, 0);
    EXPECT_EQ(report.v, 0);
    EXPECT_EQ(report.buttons, input_report.buttons);
}

TEST_F(AzoteqIqs5xx, CombinesGestureButtonWithIncomingButtons) {
    azoteq_iqs5xx_base_data_t base_data       = {0};
    base_data.gesture_events_1.two_finger_tap = true;
    azoteq_iqs5xx_mock_set_base_data(base_data);

    report_mouse_t input_report = {0};
    input_report.buttons        = 1 << POINTING_DEVICE_BUTTON1;

    report_mouse_t report = azoteq_iqs5xx_get_report(input_report);

    EXPECT_EQ(report.x, 0);
    EXPECT_EQ(report.y, 0);
    EXPECT_EQ(report.h, 0);
    EXPECT_EQ(report.v, 0);
    EXPECT_EQ(report.buttons, input_report.buttons | (1 << POINTING_DEVICE_BUTTON2));
}
