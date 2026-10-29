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
#include "report.h"
#include <ostream>
#include <vector>
#include "gmock/gmock.h"

bool          operator==(const report_keyboard_t& lhs, const report_keyboard_t& rhs);
std::ostream& operator<<(std::ostream& stream, const report_keyboard_t& value);

class KeyboardReportMatcher : public testing::MatcherInterface<report_keyboard_t&> {
   public:
    KeyboardReportMatcher(const std::vector<uint8_t>& keys);
    virtual bool MatchAndExplain(report_keyboard_t& report, testing::MatchResultListener* listener) const override;
    virtual void DescribeTo(::std::ostream* os) const override;
    virtual void DescribeNegationTo(::std::ostream* os) const override;

   private:
    report_keyboard_t m_report;
};

inline testing::Matcher<report_keyboard_t&> KeyboardReport(const std::vector<uint8_t>& keys) {
    return testing::MakeMatcher(new KeyboardReportMatcher(keys));
}

template <typename... Ts>
inline testing::Matcher<report_keyboard_t&> KeyboardReport(Ts... keys) {
    return testing::MakeMatcher(new KeyboardReportMatcher({static_cast<uint8_t>(keys)...}));
}

#ifdef NKRO_BOOT_COMPAT_ENABLE
bool          operator==(const report_keyboard_nkro_t& lhs, const report_keyboard_nkro_t& rhs);
std::ostream& operator<<(std::ostream& stream, const report_keyboard_nkro_t& value);

/**
 * Matches a combined boot+NKRO report. `boot_keys` is the expected content of the
 * 6-key boot array, `nkro_keys` the expected content of the bitfield; modifiers may
 * appear in either list. Order does not matter in either list.
 */
class KeyboardNkroReportMatcher : public testing::MatcherInterface<report_keyboard_nkro_t&> {
   public:
    KeyboardNkroReportMatcher(const std::vector<uint8_t>& boot_keys, const std::vector<uint8_t>& nkro_keys);
    virtual bool MatchAndExplain(report_keyboard_nkro_t& report, testing::MatchResultListener* listener) const override;
    virtual void DescribeTo(::std::ostream* os) const override;
    virtual void DescribeNegationTo(::std::ostream* os) const override;

   private:
    report_keyboard_nkro_t m_report;
};

inline testing::Matcher<report_keyboard_nkro_t&> KeyboardNkroReportViews(const std::vector<uint8_t>& boot_keys, const std::vector<uint8_t>& nkro_keys) {
    return testing::MakeMatcher(new KeyboardNkroReportMatcher(boot_keys, nkro_keys));
}

inline testing::Matcher<report_keyboard_nkro_t&> KeyboardNkroReport(const std::vector<uint8_t>& keys) {
    std::vector<uint8_t> boot_keys;
    for (auto k : keys) {
        if (!IS_MODIFIER_KEYCODE(k) && boot_keys.size() < KEYBOARD_REPORT_KEYS) {
            boot_keys.push_back(k);
        }
    }
    return testing::MakeMatcher(new KeyboardNkroReportMatcher(boot_keys, keys));
}

template <typename... Ts>
inline testing::Matcher<report_keyboard_nkro_t&> KeyboardNkroReport(Ts... keys) {
    return KeyboardNkroReport(std::vector<uint8_t>{static_cast<uint8_t>(keys)...});
}
#endif
