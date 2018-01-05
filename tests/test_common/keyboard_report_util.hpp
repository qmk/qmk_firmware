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
#include "gmock/gmock.h"

bool operator==(const report_keyboard_t& lhs, const report_keyboard_t& rhs);
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


template<typename... Ts>
inline testing::Matcher<report_keyboard_t&> KeyboardReport(Ts... keys) {
    return testing::MakeMatcher(new KeyboardReportMatcher(std::vector<uint8_t>({keys...})));
}