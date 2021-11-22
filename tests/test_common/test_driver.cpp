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

TestDriver::TestDriver() : m_driver{&TestDriver::keyboard_leds, &TestDriver::send_keyboard, &TestDriver::send_mouse, &TestDriver::send_system, &TestDriver::send_consumer} {
    host_set_driver(&m_driver);
    m_this = this;
}

TestDriver::~TestDriver() { m_this = nullptr; }

uint8_t TestDriver::keyboard_leds(void) { return m_this->m_leds; }

void TestDriver::send_keyboard(report_keyboard_t* report) { m_this->send_keyboard_mock(*report); }

void TestDriver::send_mouse(report_mouse_t* report) { m_this->send_mouse_mock(*report); }

void TestDriver::send_system(uint16_t data) { m_this->send_system_mock(data); }

void TestDriver::send_consumer(uint16_t data) { m_this->send_consumer(data); }
