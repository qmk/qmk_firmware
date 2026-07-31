/* Copyright 2022 Isaac Elenbaas
 * Copyright 2025 Google LLC
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

#define SPECULATIVE_HOLD
#define PERMISSIVE_HOLD

#define RETRO_SHIFT 2 * TAPPING_TERM
// releases between AUTO_SHIFT_TIMEOUT and TAPPING_TERM are not tested
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_MODIFIERS

#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F24
