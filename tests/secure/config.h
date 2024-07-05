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

#pragma once

#include "test_common.h"

// clang-format off
#define SECURE_UNLOCK_SEQUENCE \
    {                          \
        {0, 1},                \
        {0, 2},                \
        {0, 3},                \
        {0, 4}                 \
    }
// clang-format on

#define SECURE_UNLOCK_TIMEOUT 20
#define SECURE_IDLE_TIMEOUT 50
