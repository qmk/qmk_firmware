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

#include "keyboard_report_util.hpp"
#include <vector>
#include <algorithm>
using namespace testing;

namespace {
std::vector<uint8_t> get_keys(const report_keyboard_t& report) {
    std::vector<uint8_t> result;
#if defined(NKRO_ENABLE)
#    error NKRO support not implemented yet
#elif defined(RING_BUFFERED_6KRO_REPORT_ENABLE)
#    error 6KRO support not implemented yet
#else
    for (size_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (report.keys[i]) {
            result.emplace_back(report.keys[i]);
        }
    }
#endif
    std::sort(result.begin(), result.end());
    return result;
}
}  // namespace

bool operator==(const report_keyboard_t& lhs, const report_keyboard_t& rhs) {
    auto lhskeys = get_keys(lhs);
    auto rhskeys = get_keys(rhs);
    return lhs.mods == rhs.mods && lhskeys == rhskeys;
}

std::ostream& operator<<(std::ostream& stream, const report_keyboard_t& value) {
    stream << "Keyboard report:" << std::endl;
    stream << "Mods: " << (uint32_t)value.mods << std::endl;
    stream << "Keys: ";
    // TODO: This should probably print friendly names for the keys
    for (uint32_t k : get_keys(value)) {
        stream << k << " ";
    }
    stream << std::endl;
    return stream;
}

KeyboardReportMatcher::KeyboardReportMatcher(const std::vector<uint8_t>& keys) {
    memset(m_report.raw, 0, sizeof(m_report.raw));
    for (auto k : keys) {
        if (IS_MOD(k)) {
            m_report.mods |= MOD_BIT(k);
        } else {
            add_key_to_report(&m_report, k);
        }
    }
}

bool KeyboardReportMatcher::MatchAndExplain(report_keyboard_t& report, MatchResultListener* listener) const { return m_report == report; }

void KeyboardReportMatcher::DescribeTo(::std::ostream* os) const { *os << "is equal to " << m_report; }

void KeyboardReportMatcher::DescribeNegationTo(::std::ostream* os) const { *os << "is not equal to " << m_report; }
