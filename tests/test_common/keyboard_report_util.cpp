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
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace testing;

extern std::map<uint16_t, std::string> KEYCODE_ID_TABLE;

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

std::vector<uint8_t> get_mods(const report_keyboard_t& report) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < 8; i++) {
        if (report.mods & (1 << i)) {
            uint8_t code = KC_LEFT_CTRL + i;
            result.emplace_back(code);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

} // namespace

bool operator==(const report_keyboard_t& lhs, const report_keyboard_t& rhs) {
    auto lhskeys = get_keys(lhs);
    auto rhskeys = get_keys(rhs);
    return lhs.mods == rhs.mods && lhskeys == rhskeys;
}

std::ostream& operator<<(std::ostream& os, const report_keyboard_t& report) {
    auto keys = get_keys(report);
    auto mods = get_mods(report);

    os << std::setw(10) << std::left << "report: ";

    if (!keys.size() && !mods.size()) {
        return os << "empty" << std::endl;
    }

    os << "(";
    for (auto key = keys.cbegin(); key != keys.cend();) {
        os << KEYCODE_ID_TABLE.at(*key);
        key++;
        if (key != keys.cend()) {
            os << ", ";
        }
    }

    os << ") [";

    for (auto mod = mods.cbegin(); mod != mods.cend();) {
        os << KEYCODE_ID_TABLE.at(*mod);
        mod++;
        if (mod != mods.cend()) {
            os << ", ";
        }
    }

    return os << "]" << std::endl;
}

KeyboardReportMatcher::KeyboardReportMatcher(const std::vector<uint8_t>& keys) {
    memset(&m_report, 0, sizeof(report_keyboard_t));
    for (auto k : keys) {
        if (IS_MODIFIER_KEYCODE(k)) {
            m_report.mods |= MOD_BIT(k);
        } else {
            add_key_byte(&m_report, k);
        }
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
