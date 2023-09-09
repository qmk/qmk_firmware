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

#include "test_driver.hpp"

TestDriver* TestDriver::m_this = nullptr;

namespace {
// Given a hex digit between 0 and 15, returns the corresponding keycode.
uint8_t hex_digit_to_keycode(uint8_t digit) {
    // clang-format off
    static const uint8_t hex_keycodes[] = {
        KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
        KC_8, KC_9, KC_A, KC_B, KC_C, KC_D, KC_E, KC_F
    };
    // clang-format on
    return hex_keycodes[digit];
}
} // namespace

TestDriver::TestDriver() : m_driver{&TestDriver::keyboard_leds, &TestDriver::send_keyboard, &TestDriver::send_mouse, &TestDriver::send_extra} {
    host_set_driver(&m_driver);
    m_this = this;
}

TestDriver::~TestDriver() {
    m_this = nullptr;
}

uint8_t TestDriver::keyboard_leds(void) {
    return m_this->m_leds;
}

void TestDriver::send_keyboard(report_keyboard_t* report) {
    test_logger.trace() << *report;
    m_this->send_keyboard_mock(*report);
}

void TestDriver::send_mouse(report_mouse_t* report) {
    m_this->send_mouse_mock(*report);
}

void TestDriver::send_extra(report_extra_t* report) {
    m_this->send_extra_mock(*report);
}

namespace internal {
void expect_unicode_code_point(TestDriver& driver, uint32_t code_point) {
    testing::InSequence seq;
    EXPECT_REPORT(driver, (KC_LEFT_CTRL, KC_LEFT_SHIFT));
    EXPECT_REPORT(driver, (KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_U));
    EXPECT_REPORT(driver, (KC_LEFT_CTRL, KC_LEFT_SHIFT));
    EXPECT_EMPTY_REPORT(driver);

    bool print_zero = false;
    for (int i = 7; i >= 0; --i) {
        if (i <= 3) {
            print_zero = true;
        }

        const uint8_t digit = (code_point >> (i * 4)) & 0xf;
        if (digit || print_zero) {
            EXPECT_REPORT(driver, (hex_digit_to_keycode(digit)));
            EXPECT_EMPTY_REPORT(driver);
            print_zero = true;
        }
    }

    EXPECT_REPORT(driver, (KC_SPACE));
    EXPECT_EMPTY_REPORT(driver);
}
} // namespace internal
