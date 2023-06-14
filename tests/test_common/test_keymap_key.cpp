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

#include "test_keymap_key.hpp"
#include <cstdint>
#include <ios>
#include "matrix.h"
#include "test_logger.hpp"
#include "gtest/gtest-message.h"
#include "gtest/gtest.h"
#include "timer.h"

void KeymapKey::press() {
    EXPECT_FALSE(matrix_is_on(position.row, position.col)) << "tried to press key " << this->name << " that was already pressed! Check the test code." << std::endl;

    press_key(this->position.col, this->position.row);
    this->timestamp_pressed = timer_read32();
    test_logger.trace() << std::setw(10) << std::left << "pressed: " << this->name << std::endl;
}

void KeymapKey::release() {
    EXPECT_TRUE(matrix_is_on(this->position.row, this->position.col)) << "tried to release key " << this->name << " that wasn't pressed before! Check the test code." << std::endl;

    release_key(this->position.col, this->position.row);
    uint32_t now = timer_read32();
    test_logger.trace() << std::setw(10) << std::left << "released: " << this->name << " was pressed for " << now - this->timestamp_pressed << "ms" << std::endl;
}
