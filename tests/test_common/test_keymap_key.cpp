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
#include "test_logger.hpp"
#include "gtest/gtest-message.h"
#include "gtest/gtest.h"

void KeymapKey::press() {
    test_logger.trace() << "Key pressed:  (" << +this->position.col << "," << +this->position.row << ")" << std::endl;
    press_key(this->position.col, this->position.row);
}

void KeymapKey::release() {
    test_logger.trace() << "Key released: (" << +this->position.col << "," << +this->position.row << ")" << std::endl;
    release_key(this->position.col, this->position.row);
}