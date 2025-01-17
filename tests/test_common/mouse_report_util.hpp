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

bool          operator==(const report_mouse_t& lhs, const report_mouse_t& rhs);
std::ostream& operator<<(std::ostream& stream, const report_mouse_t& value);

class MouseReportMatcher : public testing::MatcherInterface<report_mouse_t&> {
   public:
    MouseReportMatcher(int16_t x, int16_t y, int8_t h, int8_t v, uint8_t button_mask);
    virtual bool MatchAndExplain(report_mouse_t& report, testing::MatchResultListener* listener) const override;
    virtual void DescribeTo(::std::ostream* os) const override;
    virtual void DescribeNegationTo(::std::ostream* os) const override;

   private:
    report_mouse_t m_report;
};

inline testing::Matcher<report_mouse_t&> MouseReport(int16_t x, int16_t y, int8_t h, int8_t v, uint8_t button_mask) {
    return testing::MakeMatcher(new MouseReportMatcher(x, y, h, v, button_mask));
}
