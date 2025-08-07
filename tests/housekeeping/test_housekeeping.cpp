/* Copyright 2024 leep-frog
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
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_keymap_key.hpp"

using testing::_;

class HousekeepingMock {
   public:
    virtual ~HousekeepingMock() {}

    // mock methods
    MOCK_METHOD0(housekeeping_task_kb, void(void));
    MOCK_METHOD0(housekeeping_task_user, void(void));
};

class Housekeeping : public TestFixture {
   public:
    Housekeeping() {
        _housekeepingMock.reset(new ::testing::NiceMock<HousekeepingMock>());
    }
    virtual ~Housekeeping() {
        _housekeepingMock.reset();
    }

    static std::unique_ptr<HousekeepingMock> _housekeepingMock;
};

std::unique_ptr<HousekeepingMock> Housekeeping::_housekeepingMock;

extern "C" {
void housekeeping_task_kb(void) {
    if (Housekeeping::_housekeepingMock) {
        Housekeeping::_housekeepingMock->housekeeping_task_kb();
    }
}

void housekeeping_task_user(void) {
    if (Housekeeping::_housekeepingMock) {
        Housekeeping::_housekeepingMock->housekeeping_task_user();
    }
}
}

TEST_F(Housekeeping, Works) {
    TestDriver driver;

    EXPECT_CALL(*_housekeepingMock, housekeeping_task_kb()).Times(1);
    EXPECT_CALL(*_housekeepingMock, housekeeping_task_user()).Times(1);
    run_one_scan_loop();
}
