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
    void set_leds(uint8_t leds) { m_leds = leds; }

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
