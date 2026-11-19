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
#include <iomanip>

extern "C" {
#include "keycode_string.h"
}

using namespace testing;

extern std::map<uint16_t, std::string> KEYCODE_ID_TABLE;

namespace {

std::vector<uint8_t> get_keys(const report_keyboard_t& report) {
    std::vector<uint8_t> result;
#if defined(NKRO_ENABLE) && !defined(NKRO_BOOT_COMPAT_ENABLE)
#    error NKRO support not implemented yet
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

std::vector<uint8_t> mods_to_keycodes(uint8_t mods) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < 8; i++) {
        if (mods & (1 << i)) {
            uint8_t code = KC_LEFT_CTRL + i;
            result.emplace_back(code);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

std::vector<uint8_t> get_mods(const report_keyboard_t& report) {
    return mods_to_keycodes(report.mods);
}

#ifdef NKRO_BOOT_COMPAT_ENABLE
std::vector<uint8_t> get_boot_keys(const report_keyboard_nkro_t& report) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (report.keys[i]) {
            result.emplace_back(report.keys[i]);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

std::vector<uint8_t> get_nkro_keys(const report_keyboard_nkro_t& report) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < NKRO_REPORT_BITS; i++) {
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (report.bits[i] & (1 << bit)) {
                result.emplace_back(static_cast<uint8_t>(i * 8 + bit));
            }
        }
    }
    return result;
}

void print_keycodes(std::ostream& os, const std::vector<uint8_t>& keys) {
    for (auto key = keys.cbegin(); key != keys.cend();) {
        os << get_keycode_string(*key);
        key++;
        if (key != keys.cend()) {
            os << ", ";
        }
    }
}
#endif

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
        os << get_keycode_string(*key);
        key++;
        if (key != keys.cend()) {
            os << ", ";
        }
    }

    os << ") [";

    for (auto mod = mods.cbegin(); mod != mods.cend();) {
        os << get_keycode_string(*mod);
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

#ifdef NKRO_BOOT_COMPAT_ENABLE
bool operator==(const report_keyboard_nkro_t& lhs, const report_keyboard_nkro_t& rhs) {
    return lhs.mods == rhs.mods && get_boot_keys(lhs) == get_boot_keys(rhs) && get_nkro_keys(lhs) == get_nkro_keys(rhs);
}

std::ostream& operator<<(std::ostream& os, const report_keyboard_nkro_t& report) {
    auto boot_keys = get_boot_keys(report);
    auto nkro_keys = get_nkro_keys(report);
    auto mods      = mods_to_keycodes(report.mods);

    os << std::setw(10) << std::left << "report: ";

    if (!boot_keys.size() && !nkro_keys.size() && !mods.size()) {
        return os << "empty" << std::endl;
    }

    os << "boot (";
    print_keycodes(os, boot_keys);
    os << ") nkro (";
    print_keycodes(os, nkro_keys);
    os << ") [";
    print_keycodes(os, mods);
    return os << "]" << std::endl;
}

KeyboardNkroReportMatcher::KeyboardNkroReportMatcher(const std::vector<uint8_t>& boot_keys, const std::vector<uint8_t>& nkro_keys) {
    memset(&m_report, 0, sizeof(m_report));
    size_t slot = 0;
    for (auto k : boot_keys) {
        if (IS_MODIFIER_KEYCODE(k)) {
            m_report.mods |= MOD_BIT(k);
        } else if (slot < KEYBOARD_REPORT_KEYS) {
            m_report.keys[slot++] = k;
        }
    }
    for (auto k : nkro_keys) {
        if (IS_MODIFIER_KEYCODE(k)) {
            m_report.mods |= MOD_BIT(k);
        } else if ((k >> 3) < NKRO_REPORT_BITS) {
            m_report.bits[k >> 3] |= 1 << (k & 7);
        }
    }
}

bool KeyboardNkroReportMatcher::MatchAndExplain(report_keyboard_nkro_t& report, MatchResultListener* listener) const {
    return m_report == report;
}

void KeyboardNkroReportMatcher::DescribeTo(::std::ostream* os) const {
    *os << "is equal to " << m_report;
}

void KeyboardNkroReportMatcher::DescribeNegationTo(::std::ostream* os) const {
    *os << "is not equal to " << m_report;
}
#endif
