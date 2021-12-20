/* Copyright 2022
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

#include <stdint.h>
#include "quantum.h"
#include "digitizer.h"

#define IS_DIGITIZER(code) (DZ_CODE_MIN <= (code) && (code) <= DZ_CODE_MAX)
#define IS_DIGITIZER_BUTTON(code) (DZ_BUTTON_MIN <= (code) && (code) <= DZ_BUTTON_MAX)
#define IS_DIGITIZER_POINTER(code) (DZ_POINTER_MIN <= (code) && (code) <= DZ_POINTER_MAX)

bool process_digitizer(uint16_t keycode, keyrecord_t *record);
