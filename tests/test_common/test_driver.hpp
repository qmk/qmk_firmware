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
#include "keycode_util.hpp"
#include "test_logger.hpp"

class TestDriver {
   public:
    TestDriver();
    ~TestDriver();
    void set_leds(uint8_t leds) {
        m_leds = leds;
    }

    MOCK_METHOD1(send_keyboard_mock, void(report_keyboard_t&));
    MOCK_METHOD1(send_nkro_mock, void(report_nkro_t&));
    MOCK_METHOD1(send_mouse_mock, void(report_mouse_t&));
    MOCK_METHOD1(send_extra_mock, void(report_extra_t&));

   private:
    static uint8_t     keyboard_leds(void);
    static void        send_keyboard(report_keyboard_t* report);
    static void        send_nkro(report_nkro_t* report);
    static void        send_mouse(report_mouse_t* report);
    static void        send_extra(report_extra_t* report);
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
 * @brief Sets gmock expectation that a mouse report of `report` will be sent.
 * For this macro to parse correctly, the `report` arg must be surrounded by
 * parentheses ( ). For instance,
 *
 *   // Expect that a report of "X:-10 Y:0 H:0 V:10 BTN:1 " is sent to the host.
 *   EXPECT_REPORT(driver, (-10, 0, 0, 0, 1));
 *
 * is shorthand for
 *
 *   EXPECT_CALL(driver, send_mouse_mock(MouseReport(-10, 0, 0, 0, 1)));
 *
 * It is possible to use .Times() and other gmock APIS with EXPECT_REPORT, for instance,
 * allow only single report to be sent:
 *
 *    EXPECT_REPORT(driver, (-10, 0, 0, 0, 1)).Times(1);
 */
#define EXPECT_MOUSE_REPORT(driver, report) EXPECT_CALL((driver), send_mouse_mock(MouseReport report))

/**
 * @brief Sets gmock expectation that Unicode `code_point` is sent with UNICODE_MODE_LINUX input
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
 * @brief Sets gmock expectation that a empty keyboard report will be sent.
 * It is possible to use .Times() and other gmock APIS with EXPECT_EMPTY_MOUSE_REPORT, for instance,
 * allow any number of empty reports with:
 *
 *   EXPECT_EMPTY_MOUSE_REPORT(driver).Times(AnyNumber());
 */
#define EXPECT_EMPTY_MOUSE_REPORT(driver) EXPECT_MOUSE_REPORT(driver, (0, 0, 0, 0, 0))

/**
 * @brief Sets gmock expectation that a keyboard report will be sent, without matching its content.
 * It is possible to use .Times() and other gmock APIS with EXPECT_ANY_REPORT, for instance,
 * allow a single arbitrary report with:
 *
 *   EXPECT_ANY_REPORT(driver).Times(1);
 */
#define EXPECT_ANY_REPORT(driver) EXPECT_CALL((driver), send_keyboard_mock(_))

/**
 * @brief Sets gmock expectation that a mouse report will be sent, without matching its content.
 * It is possible to use .Times() and other gmock APIS with EXPECT_ANY_MOUSE_REPORT, for instance,
 * allow a single arbitrary report with:
 *
 *   EXPECT_ANY_MOUSE_REPORT(driver).Times(1);
 */
#define EXPECT_ANY_MOUSE_REPORT(driver) EXPECT_CALL((driver), send_mouse_mock(_))

/**
 * @brief Sets gmock expectation that no keyboard report will be sent at all.
 */
#define EXPECT_NO_REPORT(driver) EXPECT_ANY_REPORT(driver).Times(0)

/**
 * @brief Sets gmock expectation that no keyboard report will be sent at all.
 */
#define EXPECT_NO_MOUSE_REPORT(driver) EXPECT_ANY_MOUSE_REPORT(driver).Times(0)

/** @brief Tests whether keycode `actual` is equal to `expected`. */
#define EXPECT_KEYCODE_EQ(actual, expected) EXPECT_THAT((actual), KeycodeEq((expected)))

MATCHER_P(KeycodeEq, expected_keycode, "is equal to " + testing::PrintToString(expected_keycode) + ", keycode " + get_keycode_identifier_or_default(expected_keycode)) {
    if (arg == expected_keycode) {
        return true;
    }
    *result_listener << "keycode " << get_keycode_identifier_or_default(arg);
    return false;
}

/**
 * @brief Verify and clear all gmock expectations that have been setup until
 * this point.
 */
#define VERIFY_AND_CLEAR(driver) testing::Mock::VerifyAndClearExpectations(&driver)

namespace internal {
void expect_unicode_code_point(TestDriver& driver, uint32_t code_point);
} // namespace internal
