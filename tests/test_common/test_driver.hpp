/* Copyright 2017 Fred Sundvik
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "gmock/gmock.h"
#include <stdint.h>
#include "host.h"
#include "keyboard_report_util.hpp"
#include "test_logger.hpp"

class TestDriver {
   public:
    TestDriver();
    ~TestDriver();
    void set_leds(uint8_t leds) {
        m_leds = leds;
    }

    MOCK_METHOD1(send_keyboard_mock, void(report_keyboard_t&));
    MOCK_METHOD1(send_mouse_mock, void(report_mouse_t&));
    MOCK_METHOD1(send_system_mock, void(uint16_t));
    MOCK_METHOD1(send_consumer_mock, void(uint16_t));

   private:
    static uint8_t     keyboard_leds(void);
    static void        send_keyboard(report_keyboard_t* report);
    static void        send_mouse(report_mouse_t* report);
    static void        send_system(uint16_t data);
    static void        send_consumer(uint16_t data);
    host_driver_t      m_driver;
    uint8_t            m_leds = 0;
    static TestDriver* m_this;
};

/**
 * @brief Sets gmock expectation that a keyboard report of `report` keys will be sent.
 * For this macro to parse correctly, the `report` arg must be surrounded by
 * parentheses ( ). For instance,
 *
 *   // Expect that a report of "KC_LSFT + KC_A" is sent to the host.
 *   EXPECT_REPORT(driver, (KC_LSFT, KC_A));
 *
 * is shorthand for
 *
 *   EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_LSFT, KC_A)));
 *
 * It is possible to use .Times() and other gmock APIS with EXPECT_REPORT, for instance,
 * allow only single report to be sent:
 *
 *   EXPECT_REPORT(driver, (KC_LSFT, KC_A)).Times(1);
 */
#define EXPECT_REPORT(driver, report) EXPECT_CALL((driver), send_keyboard_mock(KeyboardReport report))

/**
 * @brief Sets gmock expectation that Unicode `code_point` is sent with UC_LNX input
 * mode. For instance for U+2013,
 *
 *   EXPECT_UNICODE(driver, 0x2013);
 *
 * expects the sequence of keys:
 *
 *   "Ctrl+Shift+U, 2, 0, 1, 3, space".
 */
#define EXPECT_UNICODE(driver, code_point) internal::expect_unicode_code_point((driver), (code_point))

/**
 * @brief Sets gmock expectation that a empty keyboard report will be sent.
 * It is possible to use .Times() and other gmock APIS with EXPECT_EMPTY_REPORT, for instance,
 * allow any number of empty reports with:
 *
 *   EXPECT_EMPTY_REPORT(driver).Times(AnyNumber());
 */
#define EXPECT_EMPTY_REPORT(driver) EXPECT_REPORT(driver, ())

/**
 * @brief Sets gmock expectation that a keyboard report will be sent, without matching its content.
 * It is possible to use .Times() and other gmock APIS with EXPECT_ANY_REPORT, for instance,
 * allow a single arbitrary report with:
 *
 *   EXPECT_ANY_REPORT(driver).Times(1);
 */
#define EXPECT_ANY_REPORT(driver) EXPECT_CALL((driver), send_keyboard_mock(_))

/**
 * @brief Sets gmock expectation that no keyboard report will be sent at all.
 */
#define EXPECT_NO_REPORT(driver) EXPECT_ANY_REPORT(driver).Times(0)

namespace internal {
void expect_unicode_code_point(TestDriver& driver, uint32_t code_point);
} // namespace internal
