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

#include "mouse_report_util.hpp"
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace testing;

bool operator==(const report_mouse_t& lhs, const report_mouse_t& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.h == rhs.h && lhs.v == rhs.v && lhs.buttons == rhs.buttons;
}

std::ostream& operator<<(std::ostream& os, const report_mouse_t& report) {
    os << std::setw(10) << std::left << "mouse report: ";

    if (report.x == 0 && report.y == 0 && report.h == 0 && report.v == 0 && report.buttons == 0) {
        return os << "empty" << std::endl;
    }

    os << "(X:" << (int)report.x << ", Y:" << (int)report.y << ", H:" << (int)report.h << ", V:" << (int)report.v << ", B:" << (int)report.buttons << ")";
    return os << std::endl;
}

MouseReportMatcher::MouseReportMatcher(int16_t x, int16_t y, int8_t h, int8_t v, uint8_t button_mask) {
    memset(&m_report, 0, sizeof(report_mouse_t));
    m_report.x       = x;
    m_report.y       = y;
    m_report.h       = h;
    m_report.v       = v;
    m_report.buttons = button_mask;
}

bool MouseReportMatcher::MatchAndExplain(report_mouse_t& report, MatchResultListener* listener) const {
    return m_report == report;
}

void MouseReportMatcher::DescribeTo(::std::ostream* os) const {
    *os << "is equal to " << m_report;
}

void MouseReportMatcher::DescribeNegationTo(::std::ostream* os) const {
    *os << "is not equal to " << m_report;
}
