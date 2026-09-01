// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::_;

class BatteryDriverMock {
   public:
    virtual ~BatteryDriverMock() {}

    // mock methods
    MOCK_METHOD0(battery_driver_init, void(void));
    MOCK_METHOD0(battery_driver_sample_percent, uint8_t(void));
    MOCK_METHOD1(battery_percent_changed_kb, void(uint8_t));
};

class BatteryTest : public ::testing::Test {
   public:
    BatteryTest() {
        _batteryDriverMock.reset(new ::testing::NiceMock<BatteryDriverMock>());
    }
    virtual ~BatteryTest() {
        _batteryDriverMock.reset();
    }

    static std::unique_ptr<BatteryDriverMock> _batteryDriverMock;
};

std::unique_ptr<BatteryDriverMock> BatteryTest::_batteryDriverMock;

extern "C" {
#include "quantum/battery/battery.h"
#include "timer.h"

void advance_time(uint32_t ms);

void battery_driver_init(void) {
    if (BatteryTest::_batteryDriverMock) {
        BatteryTest::_batteryDriverMock->battery_driver_init();
    }
}

uint8_t battery_driver_sample_percent(void) {
    if (BatteryTest::_batteryDriverMock) {
        return BatteryTest::_batteryDriverMock->battery_driver_sample_percent();
    }
    return 255;
}

void battery_percent_changed_kb(uint8_t level) {
    if (BatteryTest::_batteryDriverMock) {
        BatteryTest::_batteryDriverMock->battery_percent_changed_kb(level);
    }
}
}

TEST_F(BatteryTest, TestInit) {
    // init driver and initial sample
    EXPECT_CALL(*_batteryDriverMock, battery_driver_init()).Times(1);
    EXPECT_CALL(*_batteryDriverMock, battery_driver_sample_percent()).Times(1);

    battery_init();
}

TEST_F(BatteryTest, TestSampleCached) {
    // sample before timeout
    EXPECT_CALL(*_batteryDriverMock, battery_driver_sample_percent()).Times(0);

    advance_time(1);
    battery_task();
}

TEST_F(BatteryTest, TestSampleNotCached) {
    // sample after timeout
    EXPECT_CALL(*_batteryDriverMock, battery_driver_sample_percent()).Times(1);

    advance_time(60000);
    battery_task();
}

TEST_F(BatteryTest, TestGet) {
    // sample does not directly sample
    EXPECT_CALL(*_batteryDriverMock, battery_driver_sample_percent()).Times(0);

    battery_get_percent();
}

TEST_F(BatteryTest, TestChanged) {
    // callbacks on value changed
    EXPECT_CALL(*_batteryDriverMock, battery_percent_changed_kb(_)).Times(1);

    battery_task();
    advance_time(60000);
    battery_task();
}
