// Copyright 2026 Roman Kuzmitskii (@damex)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "quantum/battery/battery.h"
#include "timer.h"

void advance_time(uint32_t ms);
}

using testing::_;
using testing::Return;

class BatteryChargerMock {
   public:
    virtual ~BatteryChargerMock() {}

    MOCK_METHOD0(battery_driver_init, void(void));
    MOCK_METHOD0(battery_driver_sample_percent, uint8_t(void));
    MOCK_METHOD0(battery_charger_init, void(void));
    MOCK_METHOD0(battery_charger_get_state, battery_charging_state_t(void));
    MOCK_METHOD1(battery_charging_state_changed_kb, void(battery_charging_state_t));
};

class BatteryChargerTest : public ::testing::Test {
   public:
    BatteryChargerTest() {
        _mock.reset(new ::testing::NiceMock<BatteryChargerMock>());
    }
    virtual ~BatteryChargerTest() {
        _mock.reset();
    }

    static std::unique_ptr<BatteryChargerMock> _mock;
};

std::unique_ptr<BatteryChargerMock> BatteryChargerTest::_mock;

extern "C" {

void battery_driver_init(void) {
    if (BatteryChargerTest::_mock) {
        BatteryChargerTest::_mock->battery_driver_init();
    }
}

uint8_t battery_driver_sample_percent(void) {
    if (BatteryChargerTest::_mock) {
        return BatteryChargerTest::_mock->battery_driver_sample_percent();
    }
    return 100;
}

void battery_charger_init(void) {
    if (BatteryChargerTest::_mock) {
        BatteryChargerTest::_mock->battery_charger_init();
    }
}

battery_charging_state_t battery_charger_get_state(void) {
    if (BatteryChargerTest::_mock) {
        return BatteryChargerTest::_mock->battery_charger_get_state();
    }
    return BATTERY_CHARGING_UNKNOWN;
}

void battery_charging_state_changed_kb(battery_charging_state_t state) {
    if (BatteryChargerTest::_mock) {
        BatteryChargerTest::_mock->battery_charging_state_changed_kb(state);
    }
}
}

TEST_F(BatteryChargerTest, TestInit) {
    EXPECT_CALL(*_mock, battery_charger_init()).Times(1);
    EXPECT_CALL(*_mock, battery_charger_get_state()).Times(1).WillOnce(Return(BATTERY_NOT_CHARGING));
    EXPECT_CALL(*_mock, battery_charging_state_changed_kb(_)).Times(0);

    battery_init();
}

TEST_F(BatteryChargerTest, TestPollingEveryTask) {
    EXPECT_CALL(*_mock, battery_charger_get_state()).WillRepeatedly(Return(BATTERY_NOT_CHARGING));

    battery_init();
    EXPECT_CALL(*_mock, battery_charger_get_state()).Times(3).WillRepeatedly(Return(BATTERY_NOT_CHARGING));

    battery_task();
    battery_task();
    battery_task();
}

TEST_F(BatteryChargerTest, TestStateChangeFiresCallback) {
    EXPECT_CALL(*_mock, battery_charger_get_state()).WillOnce(Return(BATTERY_NOT_CHARGING));
    battery_init();

    EXPECT_CALL(*_mock, battery_charger_get_state()).WillOnce(Return(BATTERY_CHARGING));
    EXPECT_CALL(*_mock, battery_charging_state_changed_kb(BATTERY_CHARGING)).Times(1);

    battery_task();
}

TEST_F(BatteryChargerTest, TestStateUnchangedSuppressesCallback) {
    EXPECT_CALL(*_mock, battery_charger_get_state()).WillOnce(Return(BATTERY_CHARGING));
    battery_init();

    EXPECT_CALL(*_mock, battery_charger_get_state()).Times(2).WillRepeatedly(Return(BATTERY_CHARGING));
    EXPECT_CALL(*_mock, battery_charging_state_changed_kb(_)).Times(0);

    battery_task();
    battery_task();
}

TEST_F(BatteryChargerTest, TestGetReturnsLastPolled) {
    EXPECT_CALL(*_mock, battery_charger_get_state()).WillOnce(Return(BATTERY_FULL));
    battery_init();

    EXPECT_EQ(battery_get_charging_state(), BATTERY_FULL);
}

TEST_F(BatteryChargerTest, TestGetReturnsUpdatedAfterTaskTransition) {
    EXPECT_CALL(*_mock, battery_charger_get_state()).WillOnce(Return(BATTERY_NOT_CHARGING));
    battery_init();
    EXPECT_EQ(battery_get_charging_state(), BATTERY_NOT_CHARGING);

    EXPECT_CALL(*_mock, battery_charger_get_state()).WillOnce(Return(BATTERY_FULL));
    battery_task();
    EXPECT_EQ(battery_get_charging_state(), BATTERY_FULL);
}
