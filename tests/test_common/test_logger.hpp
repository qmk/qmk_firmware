/* Copyright 2021 Stefan Kerkmann
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

#include <ostream>
#include <sstream>

class TestLogger : public std::ostream {
   public:
    TestLogger() : std::ostream(&m_log){};
    TestLogger& info();
    TestLogger& trace();
    TestLogger& error();
    void        print_log();
    void        print_header();
    void        reset();

   private:
    TestLogger&    timestamp();
    std::stringbuf m_log;
};

extern TestLogger test_logger;
