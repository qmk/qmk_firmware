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

 #include "keyboard_report_util.h"
 using namespace testing;

bool operator==(const report_keyboard_t& lhs, const report_keyboard_t& rhs) {
    return memcmp(lhs.raw, rhs.raw, sizeof(lhs.raw))==0;
}

std::ostream& operator<<(std::ostream& stream, const report_keyboard_t& value) {
    stream << "Keyboard report:" << std::endl;
    stream << (uint32_t)value.keys[0] << std::endl;
    return stream;
}

KeyboardReportMatcher::KeyboardReportMatcher(const std::vector<uint8_t>& keys) {
    memset(m_report.raw, 0, sizeof(m_report.raw));
    for (auto k: keys) {
        add_key_to_report(&m_report, k);
    }
}

bool KeyboardReportMatcher::MatchAndExplain(report_keyboard_t& report, MatchResultListener* listener) const {
    return m_report == report;
}

void KeyboardReportMatcher::DescribeTo(::std::ostream* os) const {
    *os << "is equal to " << m_report;
}

void KeyboardReportMatcher::DescribeNegationTo(::std::ostream* os) const {
    *os << "is not equal to " << m_report;
}